# 분산 키-값 저장소 프로젝트

## 프로젝트 개요
이 프로젝트는 Erlang/OTP의 동시성, 분산 처리 및 고가용성 기능을 활용하여 **분산 키-값 저장소**를 구현한 예제입니다.  
분산 키-값 저장소는 여러 노드에 걸쳐 데이터를 저장, 조회 및 갱신할 수 있으며, 데이터 복제와 장애 복구 기능을 통해 높은 안정성을 제공합니다.

## 주요 기능
- **분산 데이터 저장:**  
  여러 노드에 데이터를 분산 저장하여, 단일 장애 지점을 제거하고 확장성을 보장합니다.
- **실시간 조회 및 갱신:**  
  키를 통한 빠른 데이터 조회 및 갱신 기능을 제공하며, ETS와 같은 고속 메모리 테이블을 활용합니다.
- **데이터 복제:**  
  복제 메커니즘을 통해 노드 장애 발생 시에도 데이터 손실 없이 시스템을 복구합니다.
- **오류 복구 및 자동 재시작:**  
  Supervisor 트리를 활용하여 장애 발생 시 자동으로 프로세스를 재시작하고, 데이터 일관성을 유지합니다.
- **분산 환경 지원:**  
  Erlang의 분산 기능을 통해 여러 노드 간의 통신을 지원하며, 클러스터 환경에서 운영할 수 있습니다.

## 시스템 아키텍처
이 시스템은 OTP의 주요 구성 요소들을 활용하여 안정적이고 확장 가능한 분산 저장소를 구현합니다.

### 프로세스 구조
- **데이터 저장 서버:**  
  각 노드에서 ETS를 활용해 키-값 데이터를 관리하며, 저장, 조회, 갱신 작업을 처리합니다.
- **데이터 복제 관리자:**  
  데이터의 복제와 동기화를 담당하며, 장애 발생 시 데이터 복구를 지원합니다.
- **Supervisor 트리:**  
  데이터 저장 서버와 복제 관리자를 감시하고, 프로세스 실패 시 자동 복구 및 재시작을 수행합니다.
- **분산 노드 통신:**  
  Erlang의 노드 간 메시지 전달 기능을 활용하여, 여러 노드에 분산된 데이터를 일관성 있게 관리합니다.

### OTP 구성 요소 활용
- **gen_server:**  
  각 데이터 저장 서버의 요청 처리, 상태 관리 및 메시지 처리를 위한 서버 로직을 구현합니다.
- **supervisor:**  
  데이터 저장 서버와 복제 관리 프로세스의 생명주기를 관리하며, 장애 발생 시 자동 재시작합니다.
- **ETS:**  
  메모리 내 빠른 데이터 저장 및 조회를 위해 ETS 테이블을 사용합니다.
- **분산 처리:**  
  Erlang의 분산 기능을 통해 노드 간 데이터 동기화 및 통신을 구현합니다.

## 설치 및 실행 방법

### 요구 사항
- Erlang/OTP 24 이상
- Linux, macOS 또는 Windows 운영체제
- 터미널 또는 명령 프롬프트 환경

### 설치 방법

1. **Erlang/OTP 설치**
   - **Ubuntu/Debian:**
     ```bash
     sudo apt-get update
     sudo apt-get install erlang
     ```
   - **macOS:**
     ```bash
     brew install erlang
     ```
   - **Windows:**
     - Erlang 공식 웹사이트에서 인스톨러를 다운로드하거나, Chocolatey를 통해 설치:
       ```bash
       choco install erlang
       ```

2. **프로젝트 클론**
   ```bash
   git clone https://github.com/your-repo/distributed-key-value-store.git
   cd distributed-key-value-store
   ```

3. **컴파일**
   - `src` 디렉토리에 있는 Erlang 소스 파일들을 컴파일하여 `ebin` 디렉토리에 출력합니다.
     ```bash
     erlc -o ebin src/*.erl
     ```

### 실행 방법

1. **Erlang 쉘 시작**
   ```bash
   erl -pa ebin
   ```

2. **노드 시작 및 클러스터 구성**
   - 여러 노드를 실행할 경우, 각 노드를 서로 연결하여 클러스터를 구성합니다.
     ```erlang
     %% 예시: 노드 이름을 지정하여 시작
     erl -name node1@hostname -pa ebin
     erl -name node2@hostname -pa ebin
     %% 노드 간 연결은 net_adm:ping/1 함수로 확인할 수 있습니다.
     net_adm:ping('node2@hostname').
     ```

3. **데이터 저장 서버 시작**
   - Erlang 쉘에서 데이터 저장 서버를 시작합니다.
     ```erlang
     distributed_kv_store:start().
     ```
   - 서버는 ETS를 활용하여 키-값 데이터를 관리하며, 클러스터 내 다른 노드와 데이터 동기화를 수행합니다.

4. **데이터 조작**
   - 키를 통한 데이터 저장, 조회, 갱신 등의 작업은 다음과 같이 수행할 수 있습니다.
     ```erlang
     %% 데이터 저장: {ok, Value} 형식의 응답
     distributed_kv_store:put(my_key, "Hello, Distributed World!").

     %% 데이터 조회: 저장된 값 반환
     distributed_kv_store:get(my_key).

     %% 데이터 갱신: 키에 대한 값을 변경
     distributed_kv_store:update(my_key, fun(Old) -> Old ++ " Updated" end).
     ```

## 코드 구조

- **src/distributed_kv_store.erl:**  
  데이터 저장 서버의 핵심 로직을 구현한 모듈로, 키-값 저장, 조회, 갱신, 삭제 기능을 포함합니다.
  
- **src/replication_manager.erl:**  
  데이터 복제와 동기화를 관리하는 모듈로, 노드 간 데이터 일관성을 유지하는 역할을 합니다.
  
- **src/supervisor_kv.erl:**  
  Supervisor 트리를 구성하여, 데이터 저장 서버 및 복제 관리 프로세스의 생명주기를 관리합니다.
  
- **README.md:**  
  이 문서로, 프로젝트 개요, 실행 방법, 시스템 아키텍처 등을 상세히 설명합니다.

## 예제 사용 시나리오
1. **노드 클러스터 구성:**  
   여러 노드를 연결하여 분산 환경에서 시스템을 구성합니다.
2. **서버 시작:**  
   각 노드에서 데이터 저장 서버를 실행하고, 데이터 복제 관리자가 동작하는지 확인합니다.
3. **데이터 저장 및 조회:**  
   클라이언트가 데이터를 저장하면, 저장 서버는 이를 ETS에 기록하고, 다른 노드와 동기화합니다.
4. **데이터 갱신 및 삭제:**  
   데이터 변경 요청 시, 모든 노드에 변경 사항이 반영되도록 처리합니다.
5. **장애 복구:**  
   노드나 프로세스 장애 발생 시, Supervisor가 자동으로 프로세스를 재시작하여 데이터 일관성을 유지합니다.

## 개발 및 테스트
- **개발 환경:**  
  Erlang/OTP R24 이상, VSCode 또는 기타 Erlang 지원 IDE
- **테스트:**  
  단위 테스트와 통합 테스트를 통해 각 모듈의 기능과 클러스터 환경에서의 동작을 검증합니다.
- **모니터링:**  
  로그 및 상태 모니터링 기능을 통해 시스템의 성능 및 장애 발생 시 복구 상태를 확인합니다.

## 확장 계획
- **데이터 영속성 강화:**  
  현재 ETS 기반의 인메모리 저장소 외에, 디스크 기반 저장소와 연동하여 영속성을 보장하는 기능 추가.
- **데이터 복제 알고리즘 개선:**  
  보다 정교한 복제 및 일관성 유지 알고리즘 적용을 통한 데이터 신뢰성 강화.
- **웹 인터페이스:**  
  사용자 및 관리자용 웹 대시보드를 통해 데이터 상태를 모니터링하고 제어할 수 있는 기능 도입.
- **보안 강화:**  
  노드 간 통신 암호화 및 접근 제어 기능 추가.

## 참고 자료
- [Programming Erlang - Joe Armstrong](https://pragprog.com/titles/jjoe/programming-erlang/)
- [Learn You Some Erlang for Great Good! - Fred Hebert](http://learnyousomeerlang.com/)
- [Erlang 공식 문서](https://www.erlang.org/docs)

---

이 프로젝트는 분산 환경에서의 데이터 관리와 복제, 그리고 OTP 기반의 고가용성 시스템 구축을 실전에서 경험할 수 있는 좋은 예제입니다.  
의견이나 개선 사항은 [이슈 트래커](https://github.com/your-repo/distributed-key-value-store/issues)를 통해 공유해 주시기 바랍니다.

Happy coding!