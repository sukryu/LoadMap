defmodule SyntaxExamples do
  @moduledoc """
  이 모듈은 Elixir의 기본 문법과 다양한 언어 기능들을 상세하게 예시하는 코드입니다.
  각 함수는 Elixir의 데이터 타입, 패턴 매칭, 제어 구조, 리스트 연산, 고급 함수형 기법, 동시성, 그리고 오류 처리 방법을 보여줍니다.

  초보자부터 실무자까지 모두가 Elixir의 문법을 이해하고, 이를 기반으로 실전 애플리케이션을 개발할 수 있도록 상세한 주석을 포함하였습니다.
  """

  # -------------------------------------------------------------------
  # 1. Basic Data Types Examples
  # -------------------------------------------------------------------
  @doc """
  `basic_types/0` 함수는 Elixir의 기본 데이터 타입들을 예시합니다.

  - 정수, 부동소수점, 과학적 표기법
  - 아톰
  - 문자열
  - 리스트
  - 튜플
  - 맵
  - 바이너리

  각 데이터 타입의 생성과 사용법을 확인할 수 있습니다.
  """
  def basic_types do
    # 정수: 간단한 숫자 표현
    integer_example = 42

    # 부동소수점: 소수점을 포함하는 숫자
    float_example = 3.14159

    # 과학적 표기법: 매우 크거나 작은 숫자 표현
    scientific_example = 1.0e-3

    # 아톰: 식별자 역할을 하며 불변인 상수 (보통 :기호를 앞에 붙임)
    atom_example1 = :hello
    atom_example2 = :"Hello World"  # 공백이 포함될 경우 따옴표 사용

    # 문자열: UTF-8 인코딩된 바이너리
    string_example = "Hello, Elixir!"

    # 리스트: 다양한 타입의 요소를 포함할 수 있는 시퀀스 자료구조
    list_example = [1, 2, 3, "four", :five]

    # 튜플: 고정된 크기의 자료구조, 요소들의 집합
    tuple_example = {:ok, "success", 200}

    # 맵: 키-값 쌍의 자료구조 (키는 보통 아톰)
    map_example = %{name: "Alice", age: 30}

    # 바이너리: <<>> 구문을 사용하여 생성, 효율적인 데이터 저장에 사용
    binary_example = <<"Elixir">>

    # 결과를 하나의 맵으로 반환하여 각 데이터 타입의 예제를 확인할 수 있습니다.
    %{
      integer: integer_example,
      float: float_example,
      scientific: scientific_example,
      atoms: [atom_example1, atom_example2],
      string: string_example,
      list: list_example,
      tuple: tuple_example,
      map: map_example,
      binary: binary_example
    }
  end

  # -------------------------------------------------------------------
  # 2. Pattern Matching Examples
  # -------------------------------------------------------------------
  @doc """
  `pattern_matching/0` 함수는 Elixir의 패턴 매칭 기능을 예시합니다.

  이 함수에서는:
  - 튜플 패턴 매칭을 통한 값 추출
  - 리스트 패턴 매칭 ([head | tail] 구문)으로 리스트 분해
  - 맵 패턴 매칭으로 키-값 추출

  패턴 매칭은 변수에 값을 바인딩하는 동시에 조건을 만족하는지 확인하는 강력한 기능입니다.
  """
  def pattern_matching do
    # 튜플 패턴 매칭: {:ok, result} 패턴을 사용하여 값 추출
    tuple_data = {:ok, 42}
    {:ok, result} = tuple_data

    # 리스트 패턴 매칭: 리스트의 첫 요소와 나머지 요소들을 분리
    list_data = [1, 2, 3, 4, 5]
    [head | tail] = list_data

    # 맵 패턴 매칭: 맵의 키에 해당하는 값 추출
    map_data = %{name: "Bob", age: 25}
    %{name: extracted_name, age: extracted_age} = map_data

    %{
      tuple_result: result,
      list_head: head,
      list_tail: tail,
      map_name: extracted_name,
      map_age: extracted_age
    }
  end

  # -------------------------------------------------------------------
  # 3. Control Structures Examples
  # -------------------------------------------------------------------
  @doc """
  `control_structures/0` 함수는 Elixir의 조건문과 제어 구조를 예시합니다.

  이 함수에서는:
  - `if` 문: 단순 조건 검사
  - `cond` 문: 여러 조건을 순차적으로 평가
  - `case` 문: 값에 대한 패턴 매칭을 통한 분기 처리

  각각의 구조는 다양한 상황에 따라 선택적으로 사용할 수 있습니다.
  """
  def control_structures do
    # if 문: 조건이 참이면 해당 블록 실행
    if_result =
      if 1 + 1 == 2 do
        "Math works!"
      else
        "Something is wrong."
      end

    # cond 문: 여러 조건을 순서대로 평가하여, 첫 번째로 참인 조건의 결과를 반환
    cond_result =
      cond do
        5 < 3 -> "5는 3보다 작습니다."
        5 == 5 -> "5는 5와 같습니다."
        true -> "어떤 조건에도 해당하지 않습니다."
      end

    # case 문: 값에 대해 패턴 매칭을 수행하여 분기 처리
    value = :b
    case_result =
      case value do
        :a -> "Value is :a"
        :b -> "Value is :b"
        _ -> "Unknown value"
      end

    %{
      if_result: if_result,
      cond_result: cond_result,
      case_result: case_result
    }
  end

  # -------------------------------------------------------------------
  # 4. List Operations Examples
  # -------------------------------------------------------------------
  @doc """
  `list_operations/0` 함수는 리스트를 조작하는 다양한 방법을 예시합니다.

  - 리스트 연결: `++` 연산자 사용
  - 리스트 컴프리헨션: 조건에 따라 요소 선택 및 변환
  - Enum 모듈을 사용한 매핑, 필터링, 합산 등

  이 함수는 리스트의 기본 연산을 이해하는 데 도움이 됩니다.
  """
  def list_operations do
    list1 = [1, 2, 3, 4, 5]
    list2 = [6, 7, 8]

    # 리스트 연결: 두 리스트를 하나로 합칩니다.
    concatenated = list1 ++ list2

    # 리스트 컴프리헨션: 짝수만 선택하고, 제곱하여 새로운 리스트 생성
    squared_evens = for x <- concatenated, rem(x, 2) == 0, do: x * x

    # Enum.map: 각 요소를 2배로 변환
    doubled = Enum.map(list1, fn x -> x * 2 end)

    # Enum.filter: 특정 조건을 만족하는 요소만 선택 (여기서는 3보다 큰 값)
    filtered = Enum.filter(concatenated, fn x -> x > 3 end)

    # Enum.reduce: 리스트의 모든 요소를 누적하여 합계 계산
    sum = Enum.reduce(concatenated, 0, fn x, acc -> x + acc end)

    %{
      list1: list1,
      list2: list2,
      concatenated: concatenated,
      squared_evens: squared_evens,
      doubled: doubled,
      filtered: filtered,
      sum: sum
    }
  end

  # -------------------------------------------------------------------
  # 5. Advanced Data Structures and Functions
  # -------------------------------------------------------------------
  @doc """
  `advanced_examples/0` 함수는 Elixir의 고급 데이터 구조와 함수형 프로그래밍 기법을 예시합니다.

  - 재귀 함수를 사용한 팩토리얼 계산
  - 구조체(Struct)를 사용한 데이터 정의와 사용 예제

  이 예제는 실무에서 자주 활용되는 패턴을 이해하는 데 도움을 줍니다.
  """
  def advanced_examples do
    # 재귀를 이용한 팩토리얼 계산 함수 (익명 함수로 정의)
    factorial = fn fact, n ->
      if n <= 1 do
        1
      else
        n * fact.(fact, n - 1)
      end
    end

    fact_5 = factorial.(factorial, 5)  # 5! = 120

    # 구조체 사용 예제: Person 구조체 정의 및 인스턴스 생성
    defmodule Person do
      @moduledoc """
      Person 구조체는 이름(name)과 나이(age)를 포함하는 간단한 데이터 구조입니다.
      """
      defstruct name: "", age: 0
    end

    person_example = %Person{name: "Charlie", age: 40}

    %{
      factorial_of_5: fact_5,
      person: person_example
    }
  end

  # -------------------------------------------------------------------
  # 6. Concurrency Example
  # -------------------------------------------------------------------
  @doc """
  `concurrency_example/0` 함수는 Elixir의 동시성 모델을 보여주는 간단한 예제입니다.

  - `spawn/1`을 이용해 새로운 프로세스를 생성합니다.
  - 메시지를 주고받아 에코 기능을 수행합니다.
  """
  def concurrency_example do
    # 에코 프로세스 함수: 수신된 메시지를 보낸 프로세스로 다시 전송합니다.
    echo = fn ->
      receive do
        {sender, message} ->
          send(sender, {self(), message})
      end
    end

    # 새로운 에코 프로세스를 생성합니다.
    pid = spawn(echo)

    # 현재 프로세스의 PID를 가져옵니다.
    self_pid = self()

    # 에코 프로세스에 메시지를 전송합니다.
    send(pid, {self_pid, "Hello, Concurrency!"})

    # 메시지 수신: 2000ms 대기 후 타임아웃 처리
    response =
      receive do
        {from, reply} ->
          {from, reply}
      after
        2000 ->
          :timeout
      end

    %{
      echo_pid: pid,
      response: response
    }
  end

  # -------------------------------------------------------------------
  # 7. Error Handling Example
  # -------------------------------------------------------------------
  @doc """
  `error_handling_example/0` 함수는 Elixir의 오류 처리 방법을 예시합니다.

  - `try/rescue` 구문을 사용하여 오류를 포착하고, 적절한 메시지를 반환합니다.
  """
  def error_handling_example do
    try do
      # 의도적으로 1/0 연산을 수행하여 ArithmeticError를 발생시킵니다.
      1 / 0
    rescue
      ArithmeticError -> "Cannot divide by zero"
    end
  end
end
