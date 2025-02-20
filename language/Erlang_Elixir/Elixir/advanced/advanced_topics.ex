defmodule AdvancedTopics do
  @moduledoc """
  이 모듈은 OTP의 고급 기능들을 활용한 GenServer 예제를 제공합니다.

  이 예제에서는 단순 카운터 기능을 넘어서, 다음과 같은 고급 OTP 기능들을 보여줍니다:

  1. **상태 관리 및 동기/비동기 호출 처리:**
     - 카운터 값을 증가, 감소, 조회 및 리셋하는 기능을 제공합니다.

  2. **타임아웃 처리:**
     - 일정 시간 간격(5000ms)마다 `handle_info/2`를 통해 타임아웃 메시지를 처리하며,
       현재 상태를 로그로 출력하고 타이머를 재설정합니다.

  3. **핫 코드 업그레이드 지원:**
     - `code_change/3` 콜백을 구현하여, 실행 중인 시스템에서 코드 업그레이드를 부드럽게 처리할 수 있습니다.

  4. **종료 처리:**
     - 서버 종료 시 `terminate/2` 콜백을 통해 종료 사유와 최종 상태를 기록합니다.

  이 모듈은 Elixir에서 OTP 기반의 견고한 시스템을 구현하는 방법과 함께,
  실무에서 필요한 다양한 상황에 대응하는 고급 패턴들을 이해하는 데 도움을 줍니다.
  """

  use GenServer

  # -------------------------------
  # 클라이언트 API
  # -------------------------------
  @doc """
  GenServer를 시작하며, 초기 카운터 값을 설정합니다.

  ## 파라미터:
    - initial_value: 시작 시 설정할 카운터 값 (기본값: 0)

  ## 예제:
      iex> AdvancedTopics.start_link(100)
      {:ok, pid}
  """
  def start_link(initial_value \\ 0) do
    GenServer.start_link(__MODULE__, initial_value, name: __MODULE__)
  end

  @doc """
  카운터 값을 1 증가시킵니다.

  ## 예제:
      iex> AdvancedTopics.increment()
      101
  """
  def increment do
    GenServer.call(__MODULE__, :increment)
  end

  @doc """
  카운터 값을 1 감소시킵니다.

  ## 예제:
      iex> AdvancedTopics.decrement()
      99
  """
  def decrement do
    GenServer.call(__MODULE__, :decrement)
  end

  @doc """
  현재 카운터 값을 조회합니다.

  ## 예제:
      iex> AdvancedTopics.get_value()
      100
  """
  def get_value do
    GenServer.call(__MODULE__, :get_value)
  end

  @doc """
  카운터 값을 지정한 값으로 리셋합니다.

  ## 파라미터:
    - new_value: 리셋할 값

  ## 예제:
      iex> AdvancedTopics.reset(50)
      :ok
  """
  def reset(new_value) do
    GenServer.cast(__MODULE__, {:reset, new_value})
  end

  @doc """
  GenServer를 정상 종료합니다.

  ## 예제:
      iex> AdvancedTopics.stop()
      :ok
  """
  def stop do
    GenServer.call(__MODULE__, :stop)
  end

  # -------------------------------
  # GenServer 콜백 함수
  # -------------------------------
  @impl true
  @doc """
  초기화 콜백입니다.

  초기 상태로 전달받은 값으로 카운터를 설정하고,
  5000ms의 타임아웃을 설정하여 주기적인 타임아웃 처리(handle_info/2)를 유도합니다.

  ## 반환값:
    - {:ok, state, timeout}
  """
  def init(initial_value) do
    IO.puts("AdvancedTopics 초기화: 초기 값 #{initial_value}")
    {:ok, initial_value, 5000}
  end

  @impl true
  @doc """
  동기 호출을 처리하는 콜백입니다.

  지원되는 메시지:
    - :increment : 카운터를 1 증가시킵니다.
    - :decrement : 카운터를 1 감소시킵니다.
    - :get_value : 현재 카운터 값을 반환합니다.
    - :stop : 서버를 정상 종료합니다.
    - 그 외: 오류 메시지를 반환합니다.

  각 요청 후 5000ms의 타임아웃을 재설정합니다.
  """
  def handle_call(:increment, _from, state) do
    new_state = state + 1
    {:reply, new_state, new_state, 5000}
  end

  def handle_call(:decrement, _from, state) do
    new_state = state - 1
    {:reply, new_state, new_state, 5000}
  end

  def handle_call(:get_value, _from, state) do
    {:reply, state, state, 5000}
  end

  def handle_call(:stop, _from, state) do
    {:stop, :normal, :ok, state}
  end

  def handle_call(_unknown, _from, state) do
    {:reply, {:error, :unknown_message}, state, 5000}
  end

  @impl true
  @doc """
  비동기 cast 메시지를 처리하는 콜백입니다.

  지원되는 메시지:
    - {:reset, new_value} : 카운터 값을 new_value로 리셋합니다.

  타임아웃은 5000ms로 재설정됩니다.
  """
  def handle_cast({:reset, new_value}, _state) do
    IO.puts("카운터 리셋 요청: 새로운 값 #{new_value}")
    {:noreply, new_value, 5000}
  end

  def handle_cast(_msg, state) do
    {:noreply, state, 5000}
  end

  @impl true
  @doc """
  비동기 메시지 및 타임아웃 처리를 위한 콜백입니다.

  - :timeout 메시지가 도착하면, 현재 상태를 로그로 출력하고 타임아웃을 재설정합니다.
  - 그 외의 메시지는 무시하고 현재 상태를 유지합니다.

  ## 반환값:
    - {:noreply, state, timeout}
  """
  def handle_info(:timeout, state) do
    IO.puts("타임아웃 발생: 현재 카운터 값은 #{state}")
    {:noreply, state, 5000}
  end

  def handle_info(_msg, state) do
    {:noreply, state, 5000}
  end

  @impl true
  @doc """
  서버 종료 시 호출되는 콜백입니다.

  종료 사유와 최종 상태를 로그로 출력하며, 리소스 정리나 추가 처리가 필요할 경우 여기에 구현합니다.
  """
  def terminate(reason, state) do
    IO.puts("AdvancedTopics 종료됨. 종료 사유: #{inspect(reason)}, 최종 상태: #{state}")
    :ok
  end

  @impl true
  @doc """
  핫 코드 업그레이드를 처리하는 콜백입니다.

  새로운 코드로 업그레이드할 때 호출되며, 현재 상태를 유지하거나 변경할 수 있습니다.
  이 예제에서는 상태를 그대로 유지하며, 로그로 업그레이드 사실을 기록합니다.
  """
  def code_change(_old_vsn, state, _extra) do
    IO.puts("코드 업그레이드 실행: 현재 상태 #{state} 유지")
    {:ok, state}
  end
end

defmodule AdvancedTopicsExample do
  @moduledoc """
  이 모듈은 AdvancedTopics GenServer를 활용한 실전 예제를 실행합니다.

  주요 흐름:
    1. AdvancedTopics 서버를 시작하여 초기 값을 설정합니다.
    2. 동기 호출을 통해 상태를 변경하고 조회합니다.
    3. 비동기 cast를 이용해 상태를 리셋합니다.
    4. 타임아웃에 따른 로그 메시지를 확인합니다.
    5. 서버를 정상 종료하여 종료 처리와 코드 업그레이드 콜백을 검증합니다.

  이 예제는 OTP의 고급 기능들을 실무에 적용하는 방법을 자세하게 보여줍니다.
  """

  @doc """
  `run/0` 함수는 AdvancedTopics 예제를 실행하며, 각 단계별 결과를 콘솔에 출력하고 최종 결과를 맵 형태로 반환합니다.

  실행 순서:
    - 서버 시작 (초기 값 100)
    - :increment, :decrement, :get_value, 및 {:reset, new_value} 메시지 처리
    - 타임아웃 처리 확인을 위한 대기
    - 서버 정상 종료 및 종료 로그 확인
  """
  def run do
    IO.puts("=== AdvancedTopics 예제 시작 ===")

    # 서버를 초기 값 100으로 시작합니다.
    {:ok, _pid} = AdvancedTopics.start_link(100)

    # 현재 값 조회
    initial = AdvancedTopics.get_value()
    IO.puts("초기 값: #{initial}")

    # 1 증가 후 값
    inc = AdvancedTopics.increment()
    IO.puts("1 증가 후 값: #{inc}")

    # 1 감소 후 값
    dec = AdvancedTopics.decrement()
    IO.puts("1 감소 후 값: #{dec}")

    # 카운터를 50으로 리셋합니다.
    AdvancedTopics.reset(50)
    reset_val = AdvancedTopics.get_value()
    IO.puts("리셋 후 값: #{reset_val}")

    # 타임아웃이 발생하여 로그가 출력되도록 5500ms 대기합니다.
    :timer.sleep(5500)

    # 서버를 정상 종료합니다.
    stop_resp = AdvancedTopics.stop()
    IO.puts("서버 종료 응답: #{stop_resp}")

    IO.puts("=== AdvancedTopics 예제 종료 ===")

    # 각 단계의 결과를 맵으로 반환합니다.
    %{
      initial_value: initial,
      after_increment: inc,
      after_decrement: dec,
      after_reset: reset_val,
      stop_response: stop_resp
    }
  end
end

# 모듈 실행: 이 파일을 실행하면 AdvancedTopics 예제 결과가 콘솔에 출력됩니다.
AdvancedTopicsExample.run()
