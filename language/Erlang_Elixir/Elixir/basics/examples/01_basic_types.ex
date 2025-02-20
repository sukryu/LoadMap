defmodule BasicTypesExample do
  @moduledoc """
  이 모듈은 Elixir의 기본 데이터 타입들을 상세하게 예시하는 예제입니다.
  초보자부터 실무자까지 모두가 Elixir의 데이터 타입에 대해 이해할 수 있도록,
  각 데이터 타입의 생성, 특징 및 사용법을 아주 자세한 주석과 함께 설명합니다.

  다루는 데이터 타입:
    - 정수 (Integer)
    - 부동소수점 (Float)
    - 과학적 표기법 (Scientific Notation)
    - 아톰 (Atom)
    - 문자열 (String)
    - 리스트 (List)
    - 튜플 (Tuple)
    - 맵 (Map)
    - 바이너리 (Binary)
  """

  @doc """
  `run/0` 함수는 다양한 기본 데이터 타입 예제를 실행하여,
  각 데이터 타입의 예제와 그 결과를 콘솔에 출력합니다.

  각 예제마다 생성 방법, 사용법 및 특징을 상세하게 주석으로 설명하고 있습니다.
  """
  def run do
    # -----------------------------------------------------------------
    # 정수 (Integer)
    # -----------------------------------------------------------------
    # 정수는 소수점이 없는 숫자입니다.
    # 예: 42, -10, 0 등
    int_example = 42
    IO.puts("정수 예제:")
    IO.inspect(int_example)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 부동소수점 (Float)
    # -----------------------------------------------------------------
    # 부동소수점 숫자는 소수점을 포함한 숫자입니다.
    # Elixir는 기본적으로 64비트 부동소수점을 사용합니다.
    float_example = 3.14159
    IO.puts("부동소수점 예제:")
    IO.inspect(float_example)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 과학적 표기법 (Scientific Notation)
    # -----------------------------------------------------------------
    # 매우 큰 수나 매우 작은 수를 간결하게 표현할 때 사용됩니다.
    # 예: 1.0e-3은 1.0 * 10^-3, 즉 0.001을 의미합니다.
    scientific_example = 1.0e-3
    IO.puts("과학적 표기법 예제:")
    IO.inspect(scientific_example)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 아톰 (Atom)
    # -----------------------------------------------------------------
    # 아톰은 이름 그 자체를 값으로 가지는 상수입니다.
    # 일반적으로 : 기호로 시작하며, 시스템의 상태를 표현하거나 구분자로 사용됩니다.
    atom_example1 = :hello
    # 공백이나 특수 문자가 포함된 아톰은 큰따옴표로 감싸서 표현합니다.
    atom_example2 = :"Hello World"
    IO.puts("아톰 예제:")
    IO.inspect(atom_example1)
    IO.inspect(atom_example2)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 문자열 (String)
    # -----------------------------------------------------------------
    # 문자열은 이중 인용부호(")로 감싸 표현하며, 내부적으로 UTF-8 인코딩된 바이너리입니다.
    # 문자열은 불변(immutable)이며, 조작 시 새로운 문자열이 생성됩니다.
    string_example = "Hello, Elixir!"
    IO.puts("문자열 예제:")
    IO.inspect(string_example)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 리스트 (List)
    # -----------------------------------------------------------------
    # 리스트는 0개 이상의 요소를 포함하는 시퀀스 자료구조로, 대괄호([])로 표현합니다.
    # 리스트는 서로 다른 타입의 요소들을 포함할 수 있고, 길이가 가변적입니다.
    list_example = [1, 2, 3, "four", :five]
    IO.puts("리스트 예제:")
    IO.inspect(list_example)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 튜플 (Tuple)
    # -----------------------------------------------------------------
    # 튜플은 고정된 개수의 요소를 가지며, 요소들이 중괄호({})로 묶여 있습니다.
    # 주로 여러 관련 값을 한 그룹으로 묶어 표현할 때 사용합니다.
    tuple_example = {:ok, "성공", 200}
    IO.puts("튜플 예제:")
    IO.inspect(tuple_example)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 맵 (Map)
    # -----------------------------------------------------------------
    # 맵은 키-값 쌍의 자료구조로, `%{}` 구문을 사용합니다.
    # 키는 보통 아톰이나 문자열을 사용하며, 빠른 검색 및 업데이트가 가능합니다.
    map_example = %{name: "Alice", age: 30, city: "Seoul"}
    IO.puts("맵 예제:")
    IO.inspect(map_example)
    IO.puts("----------------------------------------------------")

    # -----------------------------------------------------------------
    # 바이너리 (Binary)
    # -----------------------------------------------------------------
    # 바이너리는 이진 데이터를 효율적으로 저장하고 처리할 때 사용됩니다.
    # Elixir에서 문자열은 사실상 바이너리이며, <<>> 구문을 사용하여 생성합니다.
    binary_example = <<"Elixir">>
    IO.puts("바이너리 예제:")
    IO.inspect(binary_example)
    IO.puts("----------------------------------------------------")
  end
end

# 모듈 실행: 이 파일을 실행하면 콘솔에 각 데이터 타입의 예제 결과가 출력됩니다.
BasicTypesExample.run()
