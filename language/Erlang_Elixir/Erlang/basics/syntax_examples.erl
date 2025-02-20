%%%-------------------------------------------------------------------
%%% @doc Erlang 기본 문법 예제
%%% @author Claude
%%% @copyright 2025
%%%-------------------------------------------------------------------

-module(syntax_examples).

%% 외부에서 호출 가능한 함수들을 명시적으로 export
-export([
    basic_types/0,
    pattern_matching/0,
    control_structures/0,
    list_operations/0,
    advanced_data_structures/0,
    process_examples/0,
    error_handling/0
]).

%%%===================================================================
%%% 기본 데이터 타입 예제
%%%===================================================================

basic_types() ->
    % 숫자 (Numbers)
    Integer = 42,           % 정수
    Float = 3.14,          % 부동소수점
    Scientific = 1.0e-10,  % 과학적 표기법
    
    % 아톰 (Atoms)
    % 아톰은 상수이며, 그 자체가 값입니다.
    % 소문자로 시작하거나 작은따옴표로 감싸서 정의합니다.
    Atom1 = hello,
    Atom2 = 'Hello World',
    
    % 문자열 (Strings)
    String1 = "Hello World",          % 문자열은 실제로는 문자 리스트입니다
    String2 = [$H, $e, $l, $l, $o],  % 이것도 "Hello"와 동일합니다
    
    % 바이너리 (Binaries)
    Binary1 = <<"Hello">>,            % 바이너리 문자열
    Binary2 = <<1, 2, 3>>,           % 바이트 시퀀스
    
    % 결과를 튜플로 반환
    {numbers, Integer, Float, Scientific,
     atoms, Atom1, Atom2,
     strings, String1, String2,
     binaries, Binary1, Binary2}.

%%%===================================================================
%%% 패턴 매칭 예제
%%%===================================================================

pattern_matching() ->
    % 기본 패턴 매칭
    Point = {point, 10, 20},
    {point, X, Y} = Point,           % X = 10, Y = 20로 바인딩됩니다
    
    % 리스트 패턴 매칭
    List = [1, 2, 3, 4, 5],
    [Head | Tail] = List,            % Head = 1, Tail = [2,3,4,5]로 바인딩됩니다
    
    % 복잡한 패턴 매칭
    Data = {user, {name, "John"}, {age, 30}},
    {user, {name, Name}, {age, Age}} = Data,  % 중첩된 패턴 매칭
    
    % 가드를 사용한 함수 패턴 매칭의 예
    Result = case Point of
        {point, X1, Y1} when X1 > 0, Y1 > 0 ->
            "제1사분면";
        {point, X1, Y1} when X1 < 0, Y1 > 0 ->
            "제2사분면";
        {point, X1, Y1} when X1 < 0, Y1 < 0 ->
            "제3사분면";
        {point, X1, Y1} when X1 > 0, Y1 < 0 ->
            "제4사분면";
        {point, 0, 0} ->
            "원점"
    end,
    
    {patterns, {X, Y}, {Head, Tail}, {Name, Age}, Result}.

%%%===================================================================
%%% 제어 구조 예제
%%%===================================================================

control_structures() ->
    % if 문
    % if는 가드처럼 동작하며, true인 첫 번째 절이 실행됩니다
    IfResult = if
        1 + 1 =:= 2 ->
            "수학은 여전히 작동합니다";
        true ->  % else 역할을 하는 절
            "이것은 실행되지 않습니다"
    end,
    
    % case 문
    % 패턴 매칭을 기반으로 동작합니다
    Number = 15,
    CaseResult = case Number of
        N when N < 0 ->
            negative;
        N when N > 0, N < 10 ->
            small_positive;
        N when N >= 10 ->
            large_positive
    end,
    
    % receive 문
    % 프로세스 간 메시지 처리에 사용됩니다
    ReceiverPid = spawn(fun() ->
        receive
            {From, Message} ->
                From ! {self(), "받은 메시지: " ++ Message}
        after 1000 ->
            timeout
        end
    end),
    
    {control_structures, IfResult, CaseResult, ReceiverPid}.

%%%===================================================================
%%% 리스트 연산 예제
%%%===================================================================

list_operations() ->
    % 리스트 생성과 기본 연산
    List1 = [1, 2, 3],
    List2 = [4, 5, 6],
    
    % 리스트 연결 (++)
    Concatenated = List1 ++ List2,    % [1,2,3,4,5,6]
    
    % 리스트 컴프리헨션
    % 짝수만 선택하여 제곱
    Squares = [X * X || X <- Concatenated, X rem 2 =:= 0],
    
    % 폴딩 (접기) 연산
    Sum = lists:foldl(fun(X, Acc) -> X + Acc end, 0, Concatenated),
    
    % 매핑
    Doubled = lists:map(fun(X) -> X * 2 end, List1),
    
    % 필터링
    GreaterThanTwo = lists:filter(fun(X) -> X > 2 end, Concatenated),
    
    {lists, {original, List1, List2},
            {concatenated, Concatenated},
            {squares, Squares},
            {sum, Sum},
            {doubled, Doubled},
            {filtered, GreaterThanTwo}}.

%%%===================================================================
%%% 고급 데이터 구조 예제
%%%===================================================================

advanced_data_structures() ->
    % 레코드 정의 (모듈 상단에 정의되어야 함)
    -record(person, {name, age, address}).
    
    % 맵 (Maps)
    Map1 = #{name => "John", age => 30},
    Map2 = Map1#{address => "Seoul"},  % 맵 갱신
    
    % 레코드 사용
    Person = #person{name = "Jane",
                    age = 25,
                    address = "New York"},
    
    % ETS (Erlang Term Storage) 테이블 생성
    TableId = ets:new(example_table, [set, public]),
    ets:insert(TableId, {1, "First Entry"}),
    ets:insert(TableId, {2, "Second Entry"}),
    
    Result = ets:lookup(TableId, 1),
    ets:delete(TableId),
    
    {advanced_structures, {maps, Map1, Map2},
                         {record, Person},
                         {ets_result, Result}}.

%%%===================================================================
%%% 프로세스 예제
%%%===================================================================

process_examples() ->
    % 단순한 에코 서버 프로세스
    EchoPid = spawn(fun() ->
        echo_loop()
    end),
    
    % 메시지 전송
    EchoPid ! {self(), "Hello"},
    
    % 결과 수신
    receive
        {_Pid, Response} ->
            {echo_response, Response}
    after 1000 ->
        timeout
    end.

% 에코 서버의 루프 함수
echo_loop() ->
    receive
        {From, Message} ->
            From ! {self(), Message},
            echo_loop();
        stop ->
            ok
    end.

%%%===================================================================
%%% 오류 처리 예제
%%%===================================================================

error_handling() ->
    % try-catch 구문
    TryResult = try
        % 의도적인 오류 발생
        1 = 2
    catch
        error:Pattern ->
            {caught_error, Pattern};
        throw:Value ->
            {caught_throw, Value};
        exit:Reason ->
            {caught_exit, Reason}
    end,
    
    % catch 식
    CatchResult = catch(1 = 2),
    
    % maybe 모나드 스타일의 오류 처리
    MaybeResult = case safe_division(10, 2) of
        {ok, Result} ->
            {success, Result};
        {error, Reason} ->
            {failure, Reason}
    end,
    
    {error_handling, TryResult, CatchResult, MaybeResult}.

% 안전한 나눗셈 함수
safe_division(A, B) ->
    try
        {ok, A / B}
    catch
        error:badarith ->
            {error, division_by_zero}
    end.

%%%===================================================================
%%% 유틸리티 함수들
%%%===================================================================

% 프라이빗 헬퍼 함수들은 여기에 추가될 수 있습니다