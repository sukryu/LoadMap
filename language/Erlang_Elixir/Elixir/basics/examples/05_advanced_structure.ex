defmodule AdvancedExamples do
  @moduledoc """
  이 모듈은 Elixir의 고급 데이터 구조와 함수형 프로그래밍 기법을 상세하게 예시하는 예제입니다.

  이 예제에서는 다음과 같은 주제를 다룹니다:

  1. **재귀를 이용한 팩토리얼 계산:**
     - 단순 재귀를 통해 팩토리얼을 계산하는 방법을 보여줍니다.

  2. **꼬리 재귀를 이용한 팩토리얼 계산:**
     - 꼬리 재귀 최적화를 활용하여 스택 오버플로우 없이 팩토리얼을 계산하는 방법을 설명합니다.

  3. **구조체(Struct) 사용 예제:**
     - 사용자 정의 데이터 구조체를 생성하고, 그 인스턴스를 생성 및 활용하는 방법을 자세히 다룹니다.

  초보자도 이해할 수 있도록 각 단계마다 자세한 주석과 설명을 포함하여, 실무에서 자주 사용하는 고급 패턴들을 학습할 수 있도록 구성하였습니다.
  """

  @doc """
  `run/0` 함수는 고급 데이터 구조와 함수형 프로그래밍 기법 예제를 실행하고,
  각 예제의 결과를 콘솔에 출력합니다.

  반환되는 결과는 다음과 같은 정보를 포함합니다:
    - 재귀를 이용한 팩토리얼 계산 결과
    - 꼬리 재귀를 이용한 팩토리얼 계산 결과
    - 생성된 구조체(Person)의 정보
  """
  def run do
    IO.puts("=== 고급 데이터 구조 및 함수 예제 시작 ===")
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 1. 재귀를 이용한 팩토리얼 계산 예제
    # -----------------------------------------------------------------
    # 팩토리얼(n!)은 1부터 n까지의 정수의 곱입니다.
    # 재귀 함수는 문제를 더 작은 문제로 분할하여 자기 자신을 호출하는 기법입니다.
    #
    # 아래 모듈은 재귀적 방식으로 팩토리얼을 계산하는 예제를 제공합니다.
    defmodule RecursionExample do
      @moduledoc """
      이 모듈은 일반 재귀를 이용한 팩토리얼 계산 예제를 제공합니다.
      """

      @doc """
      `factorial/1` 함수는 주어진 정수 n의 팩토리얼(n!)을 계산합니다.

      재귀 종료 조건: n이 0 또는 1이면 1을 반환합니다.
      재귀 호출: n이 2 이상이면, n * factorial(n-1)을 호출하여 결과를 누적합니다.

      ## 예제

          iex> RecursionExample.factorial(5)
          120
      """
      def factorial(0), do: 1
      def factorial(1), do: 1
      def factorial(n) when n > 1 do
        n * factorial(n - 1)
      end
    end

    fact_recursive = RecursionExample.factorial(5)
    IO.puts("재귀를 이용한 팩토리얼 계산 (5!): #{fact_recursive}")
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 2. 꼬리 재귀를 이용한 팩토리얼 계산 예제
    # -----------------------------------------------------------------
    # 꼬리 재귀는 함수 호출이 마지막에 자기 자신을 호출하는 형태로,
    # 컴파일러가 최적화를 통해 스택 사용을 최소화할 수 있도록 합니다.
    #
    # 아래 모듈은 내부 헬퍼 함수를 사용하여 꼬리 재귀 방식으로 팩토리얼을 계산합니다.
    defmodule TailRecursionExample do
      @moduledoc """
      이 모듈은 꼬리 재귀를 이용한 팩토리얼 계산 예제를 제공합니다.
      """

      @doc """
      `factorial/1` 함수는 꼬리 재귀를 사용하여 정수 n의 팩토리얼을 계산합니다.

      내부 헬퍼 함수 `do_factorial/2`를 통해 누적값을 유지하며 계산합니다.

      ## 예제

          iex> TailRecursionExample.factorial(5)
          120
      """
      def factorial(n) when n >= 0 do
        do_factorial(n, 1)
      end

      # 내부 헬퍼 함수: do_factorial/2
      # - n: 남은 계산해야 할 숫자
      # - acc: 누적된 결과
      defp do_factorial(0, acc), do: acc
      defp do_factorial(n, acc) when n > 0 do
        do_factorial(n - 1, n * acc)
      end
    end

    fact_tail_recursive = TailRecursionExample.factorial(5)
    IO.puts("꼬리 재귀를 이용한 팩토리얼 계산 (5!): #{fact_tail_recursive}")
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 3. 구조체(Struct) 사용 예제
    # -----------------------------------------------------------------
    # 구조체는 맵과 유사하지만, 미리 정의된 필드와 기본값을 갖는 사용자 정의 데이터 구조입니다.
    # 주로 관련 데이터를 한 그룹으로 묶어 표현할 때 사용됩니다.
    defmodule Person do
      @moduledoc """
      Person 구조체는 이름(name)과 나이(age)를 포함하는 간단한 데이터 구조체입니다.
      """

      # defstruct를 사용하여 기본 필드와 초기값을 정의합니다.
      defstruct name: "Unknown", age: 0
    end

    # Person 구조체의 인스턴스를 생성하고, 필드에 접근합니다.
    person_example = %Person{name: "Charlie", age: 40}
    IO.puts("구조체 사용 예제 (Person):")
    IO.puts("이름: #{person_example.name}")
    IO.puts("나이: #{person_example.age}")
    IO.puts("----------------------------------------------------")

    IO.puts("=== 고급 데이터 구조 및 함수 예제 종료 ===")

    # 최종 결과들을 하나의 맵으로 반환합니다.
    %{
      factorial_recursive: fact_recursive,
      factorial_tail_recursive: fact_tail_recursive,
      person: person_example
    }
  end
end

# 모듈 실행: 이 파일을 실행하면 콘솔에 고급 데이터 구조 및 함수 예제 결과가 출력됩니다.
AdvancedExamples.run()
