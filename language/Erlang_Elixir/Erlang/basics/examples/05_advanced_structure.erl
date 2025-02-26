%%%-------------------------------------------------------------------
%%% @doc
%%% 이 모듈은 Erlang의 고급 데이터 구조를 상세하게 예시하는 코드입니다.
%%%
%%% 본 예제에서는 다음 주제들을 다룹니다:
%%% 1. 레코드(Record) 사용 예제:
%%%    - person 레코드를 정의하고, 해당 레코드를 생성하여 데이터를 저장하는 방법을 설명합니다.
%%%
%%% 2. 맵(Maps):
%%%    - 키-값 자료구조인 맵을 생성하고, 갱신하는 방법 및 데이터를 확인하는 방법을 보여줍니다.
%%%
%%% 3. ETS (Erlang Term Storage):
%%%    - ETS 테이블을 생성, 데이터 삽입, 조회, 삭제하는 과정을 통해,
%%%      메모리 내에서 빠르게 데이터를 다루는 방법을 설명합니다.
%%%
%%% 각 예제는 io:format/2 함수를 이용해 결과를 출력하며,
%%% 최종적으로 모든 예제 결과들을 하나의 튜플로 반환합니다.
%%%
%%%-------------------------------------------------------------------
-module(advanced_data_structures_examples).

%% 외부에서 호출할 수 있도록 고급 데이터 구조 예제 함수를 export 합니다.
-export([advanced_data_structures_demo/0]).

%%--------------------------------------------------------------------
%% 레코드 정의:
%% - 레코드는 고정된 구조의 데이터를 다루기 위해 사용됩니다.
%% - 아래에서 person 레코드를 정의하며, name, age, address 필드를 포함합니다.
%%--------------------------------------------------------------------
-record(person, {name, age, address}).

%%%-------------------------------------------------------------------
%%% @doc
%%% advanced_data_structures_demo/0 함수는 다음을 수행합니다:
%%% 1. 맵(Maps)을 생성하고, 갱신하는 예제를 통해 기본 사용법을 설명합니다.
%%% 2. person 레코드를 생성하여 데이터를 저장하는 방법을 보여줍니다.
%%% 3. ETS 테이블을 생성한 후, 데이터를 삽입, 조회, 삭제하는 과정을 예시합니다.
%%%
%%% 각 단계의 결과를 io:format/2를 통해 콘솔에 출력하고,
%%% 최종 결과들을 하나의 튜플로 반환합니다.
%%%-------------------------------------------------------------------
advanced_data_structures_demo() ->
    %% ================================================================
    %% 1. 맵(Maps) 예제
    %% ================================================================
    %% 설명:
    %% - 맵은 키-값 쌍으로 데이터를 저장하는 자료구조입니다.
    %% - 먼저 Map1을 생성하여 기본 정보를 저장합니다.
    Map1 = #{name => "John", age => 30},
    
    %% 맵 갱신:
    %% - 기존의 Map1에 address 필드를 추가하여 새로운 맵 Map2를 생성합니다.
    %% - 이 때, 기존 데이터는 그대로 유지되며, 새로운 키-값 쌍이 추가됩니다.
    Map2 = Map1#{address => "Seoul"},
    
    %% ================================================================
    %% 2. 레코드(Record) 예제
    %% ================================================================
    %% 설명:
    %% - 레코드는 정해진 구조에 따라 데이터를 저장하는 데 사용됩니다.
    %% - 아래에서는 person 레코드를 생성하여, 이름, 나이, 주소 정보를 저장합니다.
    Person = #person{
        name = "Jane",
        age = 25,
        address = "New York"
    },
    
    %% ================================================================
    %% 3. ETS (Erlang Term Storage) 예제
    %% ================================================================
    %% 설명:
    %% - ETS는 Erlang이 제공하는 메모리 내 테이블로, 빠른 데이터 조회 및 삽입을 지원합니다.
    %% - 아래 과정에서는 ETS 테이블을 생성하고, 데이터를 삽입한 후,
    %%   특정 키에 해당하는 데이터를 조회하고, 마지막에 테이블을 삭제합니다.
    
    %% ETS 테이블 생성:
    %% - 'example_table'이라는 이름으로 set 타입의 ETS 테이블을 생성합니다.
    TableId = ets:new(example_table, [set, public]),
    
    %% 데이터 삽입:
    %% - 각 데이터는 {Key, Value} 형식으로 삽입합니다.
    ets:insert(TableId, {1, "First Entry"}),
    ets:insert(TableId, {2, "Second Entry"}),
    
    %% 데이터 조회:
    %% - 키가 1인 데이터를 조회하여 ETSLookupResult에 저장합니다.
    ETSLookupResult = ets:lookup(TableId, 1),
    
    %% ETS 테이블 삭제:
    %% - 테이블 사용이 끝난 후, 메모리 관리를 위해 ETS 테이블을 삭제합니다.
    ets:delete(TableId),
    
    %% ================================================================
    %% 결과 출력 (Printing the Results)
    %% ================================================================
    %% io:format/2 함수를 사용하여 각 단계의 결과를 콘솔에 출력합니다.
    io:format("~n--- Erlang 고급 데이터 구조 예제 ---~n", []),
    io:format("1. 초기 맵 (Map1): ~p~n", [Map1]),
    io:format("2. 갱신된 맵 (Map2): ~p~n", [Map2]),
    io:format("3. 레코드 예제 (Person): ~p~n", [Person]),
    io:format("4. ETS 조회 결과 (키 1): ~p~n", [ETSLookupResult]),
    
    %% 최종 결과들을 하나의 튜플로 반환합니다.
    {advanced_data_structures_demo, Map1, Map2, Person, ETSLookupResult}.
