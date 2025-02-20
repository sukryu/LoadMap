defmodule TestExamples do
  use ExUnit.Case, async: true
  import ExUnit.CaptureIO

  @moduledoc """
  이 모듈은 ExUnit을 활용한 단위 테스트 예제를 상세하게 보여줍니다.

  초보자부터 실무자까지 모두가 Elixir의 다양한 기능을 테스트하는 방법을 이해할 수 있도록,
  이 모듈에서는 기본 산술 연산, 리스트 조작, 패턴 매칭, 맵 추출, 예외 처리, 그리고 콘솔 출력 캡처 등
  다양한 테스트 케이스들을 아주 자세한 주석과 함께 제공합니다.

  테스트 케이스 예제:
    1. 정수 덧셈 테스트
    2. 리스트 연결 테스트
    3. 튜플 패턴 매칭 테스트
    4. 맵 패턴 매칭 테스트
    5. 예외 발생 테스트 (ArithmeticError)
    6. 콘솔 출력 캡처 테스트
  """

  @doc """
  정수 덧셈 테스트

  이 테스트는 간단한 산술 연산인 1 + 2의 결과가 3임을 검증합니다.
  """
  test "integer addition" do
    assert 1 + 2 == 3
  end

  @doc """
  리스트 연결 테스트

  이 테스트는 두 리스트를 ++ 연산자를 사용해 연결한 결과가 올바른지 확인합니다.
  예: [1, 2] ++ [3, 4] == [1, 2, 3, 4]
  """
  test "list concatenation" do
    list1 = [1, 2]
    list2 = [3, 4]
    expected = [1, 2, 3, 4]
    assert list1 ++ list2 == expected
  end

  @doc """
  튜플 패턴 매칭 테스트

  이 테스트는 튜플 패턴 매칭을 통해 값을 올바르게 추출하는지 검증합니다.
  예를 들어, {:ok, value} = {:ok, 10} 에서 value가 10인지 확인합니다.
  """
  test "tuple pattern matching" do
    tuple = {:ok, 10}
    {:ok, value} = tuple
    assert value == 10
  end

  @doc """
  맵 패턴 매칭 테스트

  이 테스트는 맵 패턴 매칭을 통해 특정 키의 값을 추출하는 방법을 검증합니다.
  예: %{name: "Alice", age: 30} 에서 name을 추출하여 "Alice"와 일치하는지 확인합니다.
  """
  test "map pattern matching" do
    map = %{name: "Alice", age: 30}
    %{name: extracted_name} = map
    assert extracted_name == "Alice"
  end

  @doc """
  예외 발생 테스트 (ArithmeticError)

  이 테스트는 1/0 연산을 수행할 때 발생하는 ArithmeticError를 검증합니다.
  assert_raise를 사용하여 올바른 예외가 발생하는지 확인합니다.
  """
  test "arithmetic error on division by zero" do
    assert_raise ArithmeticError, fn ->
      1 / 0
    end
  end

  @doc """
  콘솔 출력 캡처 테스트

  이 테스트는 ExUnit.CaptureIO 모듈을 사용하여, IO.puts와 같은 콘솔 출력이 올바르게 수행되는지 확인합니다.
  예: "Hello, World!"가 출력되는지 검증합니다.
  """
  test "capture IO output" do
    output = capture_io(fn -> IO.puts("Hello, World!") end)
    assert output == "Hello, World!\n"
  end
end

# ExUnit 시작 (테스트 파일로 실행 시 자동으로 시작됨)
ExUnit.start()
