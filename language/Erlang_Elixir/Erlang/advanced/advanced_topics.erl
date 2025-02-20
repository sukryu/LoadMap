%%%-------------------------------------------------------------------
%%% @doc
%%% advanced_topics 모듈은 OTP의 고급 기능들을 실습하기 위해 작성된 예제입니다.
%%% 이 모듈은 gen_server Behavior를 이용하여 간단한 카운터 서버를 구현합니다.
%%%
%%% 기능:
%%% - 카운터 값을 증가(increment) 및 감소(decrement)시키며,
%%%   현재 값을 조회(get_value)하고, 초기화(reset)할 수 있습니다.
%%% - stop 요청을 통해 서버를 정상 종료합니다.
%%%
%%% 또한, 이 모듈은 OTP의 고급 콜백 함수들(init/1, handle_call/3, handle_cast/2,
%%% handle_info/2, terminate/2, code_change/3)을 상세하게 구현 및 주석 처리하여,
%%% 고급 OTP 기능(타임아웃, 핫 코드 업그레이드 등)의 이해를 돕습니다.
%%%
%%% 사용 예:
%%% 1. 서버 시작: advanced_topics:start_link().
%%% 2. 값 증가: advanced_topics:increment().
%%% 3. 값 감소: advanced_topics:decrement().
%%% 4. 현재 값 조회: advanced_topics:get_value().
%%% 5. 카운터 초기화: advanced_topics:reset().
%%% 6. 서버 종료: advanced_topics:stop().
%%%-------------------------------------------------------------------
-module(advanced_topics).

%% OTP gen_server Behavior 사용 선언
-behaviour(gen_server).

%% API 함수들 export
-export([start_link/0, increment/0, decrement/0, get_value/0, reset/0, stop/0]).

%% gen_server 콜백 함수들 export
-export([init/1, handle_call/3, handle_cast/2, handle_info/2, terminate/2, code_change/3]).

%%%===================================================================
%%% API 함수들
%%%===================================================================

%%--------------------------------------------------------------------
%% @doc
%% gen_server 프로세스를 시작하고, 로컬 등록합니다.
%% - {local, advanced_topics} 옵션을 사용하여, 이후에 이름으로 접근 가능하도록 합니다.
%%
%% @spec start_link() -> {ok, Pid} | {error, Reason}
%%--------------------------------------------------------------------
start_link() ->
    gen_server:start_link({local, ?MODULE}, ?MODULE, [], []).

%%--------------------------------------------------------------------
%% @doc
%% 카운터 값을 1 증가시키고, 증가한 값을 반환합니다.
%%
%% @spec increment() -> NewCount :: integer()
%%--------------------------------------------------------------------
increment() ->
    gen_server:call(?MODULE, increment).

%%--------------------------------------------------------------------
%% @doc
%% 카운터 값을 1 감소시키고, 감소한 값을 반환합니다.
%%
%% @spec decrement() -> NewCount :: integer()
%%--------------------------------------------------------------------
decrement() ->
    gen_server:call(?MODULE, decrement).

%%--------------------------------------------------------------------
%% @doc
%% 현재 카운터 값을 조회하여 반환합니다.
%%
%% @spec get_value() -> Count :: integer()
%%--------------------------------------------------------------------
get_value() ->
    gen_server:call(?MODULE, get_value).

%%--------------------------------------------------------------------
%% @doc
%% 카운터 값을 0으로 초기화합니다.
%%
%% @spec reset() -> ok
%%--------------------------------------------------------------------
reset() ->
    gen_server:cast(?MODULE, reset).

%%--------------------------------------------------------------------
%% @doc
%% 서버를 정상 종료합니다.
%%
%% @spec stop() -> ok
%%--------------------------------------------------------------------
stop() ->
    gen_server:call(?MODULE, stop).

%%%===================================================================
%%% gen_server 콜백 함수들
%%%===================================================================

%%--------------------------------------------------------------------
%% @doc
%% 초기화 함수.
%% - 초기 상태로 카운터 값을 0으로 설정합니다.
%% - 5000밀리초(5초)의 타임아웃을 설정하여, 주기적으로 handle_info/2에서 timeout 메시지를 처리합니다.
%%
%% @spec init(Args :: list()) -> {ok, State} | {stop, Reason}
%%--------------------------------------------------------------------
init([]) ->
    InitialState = 0,
    {ok, InitialState, 5000}.

%%--------------------------------------------------------------------
%% @doc
%% 동기 요청을 처리하는 함수.
%%
%% 처리하는 요청:
%% - increment: 카운터 값을 1 증가시킴.
%% - decrement: 카운터 값을 1 감소시킴.
%% - get_value: 현재 카운터 값을 반환.
%% - stop: 서버를 정상 종료함.
%%
%% 각 요청에 대해 새로운 상태와 응답값을 반환하며, 타임아웃을 5000ms로 재설정합니다.
%%
%% @spec handle_call(Request, From, State) -> {reply, Reply, NewState} | {stop, Reason, Reply, NewState}
%%--------------------------------------------------------------------
handle_call(increment, _From, State) ->
    NewState = State + 1,
    {reply, NewState, NewState, 5000};
handle_call(decrement, _From, State) ->
    NewState = State - 1,
    {reply, NewState, NewState, 5000};
handle_call(get_value, _From, State) ->
    {reply, State, State, 5000};
handle_call(stop, _From, State) ->
    {stop, normal, ok, State};
handle_call(_Request, _From, State) ->
    {reply, {error, unknown_request}, State, 5000}.

%%--------------------------------------------------------------------
%% @doc
%% 비동기 요청(캐스트)을 처리하는 함수.
%%
%% 처리하는 메시지:
%% - reset: 카운터 값을 0으로 초기화.
%%
%% @spec handle_cast(Msg, State) -> {noreply, NewState}
%%--------------------------------------------------------------------
handle_cast(reset, _State) ->
    NewState = 0,
    {noreply, NewState, 5000};
handle_cast(_Msg, State) ->
    {noreply, State, 5000}.

%%--------------------------------------------------------------------
%% @doc
%% 비동기 메시지나 타임아웃 메시지를 처리하는 함수.
%%
%% 처리하는 메시지:
%% - timeout: 설정된 타임아웃(5000ms)이 만료되면 발생.
%%   이 예제에서는 타임아웃 시 현재 카운터 값을 로그로 출력하고, 타임아웃을 재설정합니다.
%%
%% @spec handle_info(Info, State) -> {noreply, NewState}
%%--------------------------------------------------------------------
handle_info(timeout, State) ->
    io:format("Advanced Topics GenServer Timeout: Current count is ~p~n", [State]),
    {noreply, State, 5000};
handle_info(_Info, State) ->
    {noreply, State, 5000}.

%%--------------------------------------------------------------------
%% @doc
%% 서버 종료 시 호출되는 함수.
%% - 종료 이유와 최종 상태를 기록하며, 필요한 정리 작업을 수행합니다.
%%
%% @spec terminate(Reason, State) -> any()
%%--------------------------------------------------------------------
terminate(Reason, State) ->
    io:format("Advanced Topics GenServer terminating. Reason: ~p, Final state: ~p~n", [Reason, State]),
    ok.

%%--------------------------------------------------------------------
%% @doc
%% 핫 코드 업그레이드 시 호출되는 함수.
%% - 이전 버전의 상태를 새로운 버전으로 변환할 수 있도록 합니다.
%% - 이 예제에서는 단순히 현재 상태를 그대로 유지합니다.
%%
%% @spec code_change(OldVsn, State, Extra) -> {ok, NewState}
%%--------------------------------------------------------------------
code_change(_OldVsn, State, _Extra) ->
    {ok, State}.
