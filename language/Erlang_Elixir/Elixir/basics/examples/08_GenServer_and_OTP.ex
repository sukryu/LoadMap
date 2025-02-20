defmodule Counter do
  @moduledoc """
  이 모듈은 GenServer를 활용하여 간단한 카운터(숫자 증가/감소)를 구현한 예제입니다.

  GenServer를 사용하여 상태를 유지하며, 클라이언트로부터의 요청(증가, 감소, 현재 값 조회)을 처리합니다.

  주요 기능:
  - 초기 값을 설정하고 시작 (start_link/1)
  - :increment 메시지를 받아 상태(카운터 값)를 1 증가시킴 (handle_call/3)
  - :decrement 메시지를 받아 상태(카운터 값)를 1 감소시킴 (handle_call/3)
  - :get_value 메시지를 통해 현재 카운터 값을 반환 (handle_call/3)
  - 종료 시 로그 출력 (terminate/2)
  """

  use GenServer

  # ---------------------------------------------------------------------------
  # 클라이언트 API 함수들
  # ---------------------------------------------------------------------------
  @doc """
  GenServer 프로세스를 시작합니다.

  초기 값(initial_value)을 인자로 받아, 해당 값으로 카운터를 초기화합니다.
  프로세스는 모듈 이름(__MODULE__)을 등록 이름으로 사용합니다.

  ## 예제
      iex> Counter.start_link(10)
      {:ok, pid}
  """
  def start_link(initial_value \\ 0) do
    GenServer.start_link(__MODULE__, initial_value, name: __MODULE__)
  end

  @doc """
  카운터 값을 1 증가시키고, 증가한 결과 값을 반환합니다.

  GenServer.call/2를 사용하여 동기 호출을 통해 요청을 처리합니다.
  """
  def increment do
    GenServer.call(__MODULE__, :increment)
  end

  @doc """
  카운터 값을 1 감소시키고, 감소한 결과 값을 반환합니다.

  GenServer.call/2를 사용하여 동기 호출로 요청을 처리합니다.
  """
  def decrement do
    GenServer.call(__MODULE__, :decrement)
  end

  @doc """
  현재 카운터의 상태(값)를 조회합니다.

  동기 호출을 통해 현재 상태를 반환받습니다.
  """
  def get_value do
    GenServer.call(__MODULE__, :get_value)
  end

  # ---------------------------------------------------------------------------
  # GenServer 콜백 함수들
  # ---------------------------------------------------------------------------

  @doc """
  초기화 콜백 함수입니다.

  - 초기 상태로 전달된 값을 그대로 상태(state)로 설정합니다.
  - 초기화 시 간단한 로그 메시지를 출력합니다.

  반환값: {:ok, state}
  """
  def init(initial_value) do
    IO.puts("Counter 초기화: 초기 값 #{initial_value}")
    {:ok, initial_value}
  end

  @doc """
  동기 호출 요청(:increment)을 처리하는 콜백입니다.

  - 현재 상태(state)에 1을 더한 새로운 상태를 계산합니다.
  - 새 상태를 응답과 함께 반환합니다.

  반환값: {:reply, new_state, new_state}
  """
  def handle_call(:increment, _from, state) do
    new_state = state + 1
    {:reply, new_state, new_state}
  end

  @doc """
  동기 호출 요청(:decrement)을 처리하는 콜백입니다.

  - 현재 상태(state)에서 1을 뺀 새로운 상태를 계산합니다.
  - 새 상태를 응답과 함께 반환합니다.

  반환값: {:reply, new_state, new_state}
  """
  def handle_call(:decrement, _from, state) do
    new_state = state - 1
    {:reply, new_state, new_state}
  end

  @doc """
  동기 호출 요청(:get_value)을 처리하는 콜백입니다.

  - 현재 상태(state)를 그대로 반환합니다.

  반환값: {:reply, state, state}
  """
  def handle_call(:get_value, _from, state) do
    {:reply, state, state}
  end

  @doc """
  처리하지 않은 메시지에 대한 기본 처리.

  잘못된 메시지를 수신한 경우, 에러 메시지를 반환합니다.
  """
  def handle_call(_unknown, _from, state) do
    {:reply, {:error, :unknown_message}, state}
  end

  @doc """
  서버 종료 시 호출되는 콜백 함수입니다.

  종료 사유와 최종 상태를 로그로 출력합니다.
  """
  def terminate(reason, state) do
    IO.puts("Counter 종료됨. 종료 사유: #{inspect(reason)}, 최종 상태: #{state}")
    :ok
  end
end

defmodule GenServerExample do
  @moduledoc """
  이 모듈은 GenServer를 활용한 간단한 카운터 서버 예제를 실행하는 모듈입니다.

  주요 흐름:
  1. Counter GenServer를 시작하여 초기 값을 설정합니다.
  2. :get_value, :increment, :decrement 요청을 통해 상태를 조회 및 변경합니다.
  3. 각 요청에 대한 결과를 콘솔에 출력합니다.

  이 예제를 통해 GenServer의 시작, 동기 호출 처리, 상태 관리, 종료 로직 등을 자세하게 이해할 수 있습니다.
  """

  @doc """
  `run/0` 함수는 카운터 서버 예제를 실행합니다.

  실행 순서:
  - Counter 서버를 10으로 초기화하며 시작합니다.
  - 현재 값 조회, 증가, 감소 후 최종 값을 확인합니다.

  각 단계에서 결과를 콘솔에 출력하고, 최종 결과를 맵 형태로 반환합니다.
  """
  def run do
    IO.puts("=== GenServer 예제 시작 ===")

    # GenServer를 시작하고 초기 값을 10으로 설정합니다.
    {:ok, _pid} = Counter.start_link(10)

    # 초기 값을 조회합니다.
    initial = Counter.get_value()
    IO.puts("초기 값: #{initial}")

    # 카운터 값을 1 증가시키고 결과를 출력합니다.
    inc1 = Counter.increment()
    IO.puts("1 증가 후 값: #{inc1}")

    # 다시 1 증가시켜 최종 값을 확인합니다.
    inc2 = Counter.increment()
    IO.puts("또 1 증가 후 값: #{inc2}")

    # 카운터 값을 1 감소시키고 결과를 출력합니다.
    dec = Counter.decrement()
    IO.puts("1 감소 후 값: #{dec}")

    # 최종 값을 조회합니다.
    final = Counter.get_value()
    IO.puts("최종 값: #{final}")

    IO.puts("=== GenServer 예제 종료 ===")

    # 최종 결과를 하나의 맵으로 반환합니다.
    %{
      initial_value: initial,
      after_first_increment: inc1,
      after_second_increment: inc2,
      after_decrement: dec,
      final_value: final
    }
  end
end

# 모듈 실행: 이 파일을 실행하면 콘솔에 GenServer 예제 결과가 출력됩니다.
GenServerExample.run()
