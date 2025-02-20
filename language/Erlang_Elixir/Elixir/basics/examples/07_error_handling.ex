defmodule ErrorHandlingExample do
  @moduledoc """
  이 모듈은 Elixir의 오류 처리 예제를 상세하게 보여줍니다.

  Elixir에서는 try/rescue, try/catch, 그리고 try/after 구문을 통해 예외 상황을 포착하고 적절히 처리할 수 있습니다.
  본 예제에서는 다양한 오류 처리 기법을 다음과 같이 다룹니다:

  1. **try/rescue 구문 (ArithmeticError):**
     - 1/0 연산을 통해 발생하는 ArithmeticError를 포착하여, "0으로 나눌 수 없습니다"라는 메시지를 반환합니다.

  2. **try/rescue 구문 (MatchError):**
     - 패턴 매칭 실패로 인한 MatchError를 의도적으로 발생시키고, 이를 포착하여 오류 메시지를 반환합니다.

  3. **try/catch 구문 (throw 처리):**
     - throw를 사용하여 예외 상황을 발생시키고, catch 구문으로 해당 값을 포착하는 방법을 보여줍니다.

  4. **try/after 구문 (리소스 정리):**
     - try 블록의 성공 여부와 관계없이 항상 실행되는 after 절을 사용하여, 리소스 정리나 보장된 후처리를 수행하는 예제를 보여줍니다.
  """

  @doc """
  `run/0` 함수는 여러 오류 처리 예제를 실행하고, 각 예제의 결과를 콘솔에 출력합니다.

  반환되는 결과는 다음과 같은 정보를 포함합니다:
    - arithmetic_result: 0으로 나눌 때 발생한 오류 처리 결과
    - match_result: 패턴 매칭 실패 오류 처리 결과
    - throw_result: throw된 값을 포착한 결과
    - after_result: after 절을 통해 항상 실행되는 후처리 결과
  """
  def run do
    IO.puts("=== Elixir 오류 처리 예제 시작 ===")
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 1. try/rescue 구문 예제: ArithmeticError
    # -----------------------------------------------------------------
    # 아래 코드는 1/0 연산을 수행하여 ArithmeticError를 발생시킵니다.
    # try/rescue 구문을 통해 해당 오류를 포착하고, "0으로 나눌 수 없습니다." 메시지를 반환합니다.
    arithmetic_result =
      try do
        1 / 0
      rescue
        ArithmeticError ->
          "오류: 0으로 나눌 수 없습니다."
      end

    IO.puts("try/rescue (ArithmeticError) 예제 결과:")
    IO.puts(arithmetic_result)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 2. try/rescue 구문 예제: MatchError
    # -----------------------------------------------------------------
    # 아래 코드는 패턴 매칭 실패를 의도적으로 발생시켜 MatchError를 유도합니다.
    # 예를 들어, {ok, value} 패턴으로 매칭을 시도하지만 실제 값이 :error인 경우 발생합니다.
    match_result =
      try do
        {ok, value} = :error
        value
      rescue
        MatchError ->
          "오류: 패턴 매칭 실패가 발생했습니다."
      end

    IO.puts("try/rescue (MatchError) 예제 결과:")
    IO.puts(match_result)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 3. try/catch 구문 예제: throw 처리
    # -----------------------------------------------------------------
    # 아래 코드는 throw를 사용하여 예외 상황을 발생시키고,
    # try/catch 구문을 통해 throw된 값을 포착합니다.
    throw_result =
      try do
        throw(:unexpected_value)
      catch
        thrown_value ->
          "throw된 값 포착됨: #{inspect(thrown_value)}"
      end

    IO.puts("try/catch (throw) 예제 결과:")
    IO.puts(throw_result)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 4. try/after 구문 예제: 리소스 정리
    # -----------------------------------------------------------------
    # try/after 구문은 try 블록의 성공 여부와 관계없이 항상 실행되는 코드를 정의합니다.
    # 이 구문은 파일이나 네트워크 연결 같은 리소스 사용 후 반드시 정리해야 할 때 유용합니다.
    after_result =
      try do
        "리소스를 사용 중..."
      after
        IO.puts("항상 실행됨: 리소스 정리 작업 수행")
      end

    IO.puts("try/after 예제 결과:")
    IO.puts(after_result)
    IO.puts("----------------------------------------------------")

    IO.puts("=== Elixir 오류 처리 예제 종료 ===")

    # 최종 결과들을 하나의 맵으로 반환합니다.
    %{
      arithmetic_result: arithmetic_result,
      match_result: match_result,
      throw_result: throw_result,
      after_result: after_result
    }
  end
end

# 모듈 실행: 이 파일을 실행하면 콘솔에 오류 처리 예제 결과가 출력됩니다.
ErrorHandlingExample.run()
