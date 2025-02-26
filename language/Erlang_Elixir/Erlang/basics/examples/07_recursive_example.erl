%%%-------------------------------------------------------------------
%%% @doc
%%% 이 모듈은 Erlang의 오류 처리(error handling) 예제를 상세하게 보여줍니다.
%%%
%%% 본 예제에서는 아래와 같은 오류 처리 기법을 다룹니다:
%%% 1. try-catch 구문:
%%%    - 의도적으로 1 = 2와 같은 오류를 발생시키고, try-catch를 통해 에러를 포착하는 방법을 설명합니다.
%%%
%%% 2. catch 식:
%%%    - 간단한 catch 식을 사용하여 오류를 포착하는 예제를 보여줍니다.
%%%
%%% 3. 안전한 나눗셈 함수(safe_division/2):
%%%    - 0으로 나누기와 같은 오류 상황을 try-catch로 처리하는 안전한 함수를 예시합니다.
%%%
%%% 각 예제의 결과는 io:format/2를 통해 콘솔에 출력되며,
%%% 최종적으로 모든 결과들을 하나의 튜플로 반환합니다.
%%%-------------------------------------------------------------------
-module(error_handling_examples).

%% 외부에서 호출할 수 있도록 오류 처리 예제 함수를 export 합니다.
-export([error_handling_demo/0]).

%%%-------------------------------------------------------------------
%%% @doc
%%% error_handling_demo/0 함수는 여러 오류 처리 기법들을 실행한 후,
%%% 그 결과를 출력하고, 최종 결과를 하나의 튜플로 반환합니다.
%%% 
%%% - TryResult: try-catch 구문을 통해 포착한 오류의 결과.
%%% - CatchResult: catch 식을 사용하여 포착한 오류의 결과.
%%% - SafeDivisionResult: safe_division/2 함수를 이용한 안전한 나눗셈 실행 결과.
%%%-------------------------------------------------------------------
error_handling_demo() ->
    %% ================================================================
    %% 1. try-catch 구문을 이용한 오류 처리 예제
    %% ================================================================
    %% 설명:
    %% - 1 = 2는 명백히 실패하는 패턴 매칭으로, 이를 통해 오류를 의도적으로 발생시킵니다.
    %% - try 구문 내에서 오류가 발생하면 catch 절이 실행되어, 
    %%   error, throw, exit 등 다양한 오류 유형을 구분하여 처리할 수 있습니다.
    TryResult = try
        %% 여기서는 의도적으로 패턴 매칭 오류(1 = 2)를 발생시킵니다.
        1 = 2
    catch
        %% error:Pattern 절은 패턴 매칭 오류를 포착합니다.
        error:Pattern ->
            {caught_error, Pattern};
        %% throw:Value 절은 throw에 의한 예외를 포착합니다.
        throw:Value ->
            {caught_throw, Value};
        %% exit:Reason 절은 exit 신호에 의한 예외를 포착합니다.
        exit:Reason ->
            {caught_exit, Reason}
    end,
    
    %% ================================================================
    %% 2. catch 식을 이용한 오류 처리 예제
    %% ================================================================
    %% 설명:
    %% - catch 식은 try-catch 구문보다 간단하게 오류를 포착할 때 사용할 수 있습니다.
    %% - 아래 예제에서는 동일한 1 = 2 오류를 catch 식을 통해 포착합니다.
    CatchResult = catch 1 = 2,
    
    %% ================================================================
    %% 3. 안전한 나눗셈 함수(safe_division/2)를 통한 오류 처리 예제
    %% ================================================================
    %% 설명:
    %% - safe_division/2 함수는 두 숫자를 나누되, 분모가 0인 경우를 try-catch를 사용하여 안전하게 처리합니다.
    %% - 정상적인 경우 {ok, Result}를 반환하고, 0으로 나누려는 시도일 경우 {error, division_by_zero}를 반환합니다.
    SafeDivisionResult = safe_division(10, 2),
    
    %% ================================================================
    %% 결과 출력 (Printing the Results)
    %% ================================================================
    %% io:format/2 함수를 사용하여 각 오류 처리 기법의 결과를 콘솔에 출력합니다.
    io:format("~n--- Erlang 오류 처리 예제 ---~n", []),
    io:format("1. try-catch 구문 결과: ~p~n", [TryResult]),
    io:format("2. catch 식 결과: ~p~n", [CatchResult]),
    io:format("3. safe_division/2 함수 결과: ~p~n", [SafeDivisionResult]),
    
    %% 최종 결과들을 하나의 튜플로 반환합니다.
    {error_handling_demo, TryResult, CatchResult, SafeDivisionResult}.

%%%-------------------------------------------------------------------
%%% @doc
%%% safe_division/2 함수는 두 숫자를 나누는 안전한 나눗셈 함수입니다.
%%%
%%% - 입력:
%%%    A: 분자 (나눠지는 수)
%%%    B: 분모 (나누는 수)
%%%
%%% - 출력:
%%%    정상적인 경우 {ok, Result}를 반환합니다.
%%%    B가 0인 경우, 에러를 포착하여 {error, division_by_zero}를 반환합니다.
%%%-------------------------------------------------------------------
safe_division(A, B) ->
    try
        %% 정상적인 나눗셈을 수행하여 결과를 {ok, Result} 형태로 반환합니다.
        {ok, A / B}
    catch
        %% 분모가 0인 경우 발생하는 badarith 오류를 포착하여, 에러 메시지를 반환합니다.
        error:badarith ->
            {error, division_by_zero}
    end.
