defmodule ControlStructuresExample do
  @moduledoc """
  이 모듈은 Elixir의 제어 구조들을 상세하게 예시하는 예제입니다.

  초보자부터 실무자까지 모두가 Elixir의 제어 구조를 이해하고 활용할 수 있도록,
  각 제어 구조의 사용법과 특징을 상세한 주석과 함께 설명합니다.

  다루는 제어 구조:
    1. if 문
    2. cond 문
    3. case 문
    4. unless 문
    5. with 문 (연속적인 패턴 매칭과 오류 처리)
  """

  @doc """
  `run/0` 함수는 여러 제어 구조 예제를 실행하고, 그 결과를 콘솔에 출력합니다.

  예제 항목:
  1. **if 문:**
     - 단일 조건을 평가하여, 조건이 참일 때와 거짓일 때의 결과를 반환합니다.
  2. **cond 문:**
     - 여러 조건을 순차적으로 평가하여, 첫 번째로 참인 조건의 결과를 반환합니다.
  3. **case 문:**
     - 주어진 값에 대해 패턴 매칭을 수행하고, 일치하는 패턴에 따라 분기 처리를 합니다.
  4. **unless 문:**
     - if 문의 반대 개념으로, 조건이 거짓일 때 실행되는 구문입니다.
  5. **with 문:**
     - 연속적인 패턴 매칭을 통해 여러 단계를 처리하며, 실패 시 별도의 처리를 할 수 있습니다.

  각 예제는 IO.puts/1, IO.inspect/1 등을 사용하여 결과를 출력합니다.
  """
  def run do
    IO.puts("=== Elixir 제어 구조 예제 시작 ===")
    IO.puts("------------------------------------")

    # -----------------------------------------------------------------
    # 1. if 문 예제
    # -----------------------------------------------------------------
    # if 문은 단일 조건을 평가하여, 조건이 참일 때와 거짓일 때 다른 값을 반환합니다.
    # Elixir의 if 문은 표현식(expression)이므로 항상 값이 반환됩니다.
    if_result =
      if 1 + 1 == 2 do
        "조건이 참입니다: 1 + 1은 2와 같습니다."
      else
        "조건이 거짓입니다."
      end

    IO.puts("1. if 문 결과:")
    IO.puts(if_result)
    IO.puts("------------------------------------")

    # -----------------------------------------------------------------
    # 2. cond 문 예제
    # -----------------------------------------------------------------
    # cond 문은 여러 조건을 순차적으로 평가하여, 첫 번째로 참인 조건의 결과를 반환합니다.
    # 이는 if-else if-else 체인의 대안으로 사용됩니다.
    cond_result =
      cond do
        5 < 3 ->
          "이 조건은 실행되지 않습니다: 5는 3보다 작지 않습니다."
        5 == 5 ->
          "조건이 참입니다: 5는 5와 같습니다."
        5 > 10 ->
          "이 조건도 실행되지 않습니다: 5는 10보다 크지 않습니다."
        true ->
          "모든 조건이 실패할 경우 실행되는 기본값입니다."
      end

    IO.puts("2. cond 문 결과:")
    IO.puts(cond_result)
    IO.puts("------------------------------------")

    # -----------------------------------------------------------------
    # 3. case 문 예제
    # -----------------------------------------------------------------
    # case 문은 주어진 값에 대해 패턴 매칭을 수행합니다.
    # 값이 어떤 패턴과 일치하는지에 따라 해당 분기문의 코드를 실행합니다.
    value = :b
    case_result =
      case value do
        :a ->
          "값이 :a와 일치합니다."
        :b ->
          "값이 :b와 일치합니다."
        _ ->
          "어떤 패턴과도 일치하지 않습니다."
      end

    IO.puts("3. case 문 결과:")
    IO.puts(case_result)
    IO.puts("------------------------------------")

    # -----------------------------------------------------------------
    # 4. unless 문 예제
    # -----------------------------------------------------------------
    # unless 문은 if 문의 반대 역할을 합니다.
    # 주어진 조건이 거짓일 때 해당 블록의 코드를 실행합니다.
    unless_result =
      unless 2 + 2 == 5 do
        "조건이 거짓입니다: 2 + 2는 5와 같지 않습니다."
      else
        "조건이 참일 때 실행될 코드입니다."
      end

    IO.puts("4. unless 문 결과:")
    IO.puts(unless_result)
    IO.puts("------------------------------------")

    # -----------------------------------------------------------------
    # 5. with 문 예제
    # -----------------------------------------------------------------
    # with 문은 연속적인 패턴 매칭을 통해 여러 단계를 처리할 수 있도록 합니다.
    # 각 단계에서 패턴 매칭에 실패하면, else 절에서 처리할 수 있습니다.
    with {:ok, a} <- {:ok, 10},
         {:ok, b} <- {:ok, 20} do
      sum = a + b
      IO.puts("5. with 문 결과:")
      IO.puts("a와 b의 합: #{sum}")
    else
      error ->
        IO.puts("with 문에서 오류 발생: #{inspect(error)}")
    end

    IO.puts("=== 제어 구조 예제 종료 ===")

    # 최종적으로 각 제어 구조의 결과들을 하나의 맵으로 반환하여 추가 처리에 활용할 수 있습니다.
    %{
      if_result: if_result,
      cond_result: cond_result,
      case_result: case_result,
      unless_result: unless_result
    }
  end
end

# 모듈 실행: 이 파일을 실행하면 콘솔에 각 제어 구조 예제 결과가 출력됩니다.
ControlStructuresExample.run()
