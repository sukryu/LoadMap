# 분산 작업 큐 시스템 프로젝트

## 프로젝트 개요
이 프로젝트는 OTP와 Elixir의 강력한 동시성, 분산 처리, 내결함성 기능을 활용하여 **분산 작업 큐 시스템**을 구현한 예제입니다.  
본 시스템은 다양한 작업을 중앙에서 수집한 후, 이를 여러 작업자(Worker) 프로세스에 효율적으로 분배하여 병렬로 처리합니다.  
또한, 작업 실패 시 자동 복구 및 재시작 기능을 통해 안정적인 작업 처리를 보장하며, 분산 환경에서도 확장성과 고가용성을 유지합니다.

---

## 주요 기능
- **작업 분배 및 병렬 처리:**  
  클라이언트로부터 제출된 작업을 중앙 큐에 저장한 후, 여러 Worker 프로세스에 분산하여 동시에 처리합니다.
  
- **동적 작업자 관리:**  
  작업자의 수를 동적으로 확장하거나 축소할 수 있으며, 각 Worker는 개별적으로 작업을 수행합니다.
  
- **오류 복구 및 자동 재시작:**  
  Supervisor가 각 Worker 프로세스를 감시하여, 실패 시 자동으로 재시작하여 작업 중단 없이 시스템을 복구합니다.
  
- **분산 처리 지원:**  
  여러 노드에 걸쳐 작업 큐 시스템을 배포할 수 있어, 대규모 작업 처리와 부하 분산에 유리합니다.

---

## 시스템 아키텍처

### 프로세스 구조
- **작업 큐 서버 (Task Queue Server):**  
  - 클라이언트로부터 작업 요청을 수신하여 큐에 저장합니다.
  - 작업 분배 로직을 통해 대기 중인 작업을 적절한 Worker에게 할당합니다.
  
- **작업자 (Worker) 프로세스:**  
  - 분배된 작업을 수행하며, 완료된 결과를 기록하거나 상위 시스템에 보고합니다.
  - 각 Worker는 독립적인 프로세스로 실행되어, 하나의 작업자가 실패해도 전체 시스템에 영향을 주지 않습니다.
  
- **Supervisor 트리:**  
  - 작업 큐 서버와 Worker 프로세스의 생명주기를 관리합니다.
  - 오류 발생 시 자동 재시작 전략(예: one_for_one 또는 rest_for_one)을 통해 안정성을 확보합니다.

### OTP 구성 요소 활용
- **GenServer:**  
  작업 큐 서버와 Worker의 상태 관리 및 메시지 처리를 위한 핵심 인터페이스로 활용됩니다.
  
- **Supervisor:**  
  각 프로세스의 오류를 감시하고, 실패 시 자동으로 재시작하여 전체 시스템의 내결함성을 보장합니다.
  
- **분산 노드 통신:**  
  Erlang의 분산 기능을 활용하여, 여러 서버 노드를 클러스터로 구성하고, 분산 작업 처리를 지원합니다.

---

## 설치 및 실행 방법

### 요구 사항
- Erlang/OTP 24 이상
- Elixir 1.12 이상
- Linux, macOS 또는 Windows 운영체제
- 터미널 또는 명령 프롬프트 환경

### 설치 방법

1. **Erlang/OTP 및 Elixir 설치**
   - **Ubuntu/Debian:**
     ```bash
     sudo apt-get update
     sudo apt-get install erlang elixir
     ```
   - **macOS (Homebrew):**
     ```bash
     brew install erlang elixir
     ```
   - **Windows:**
     - [Elixir 공식 웹사이트](https://elixir-lang.org/install.html)에서 설치 프로그램을 다운로드하거나, Chocolatey를 이용하여 설치:
       ```bash
       choco install erlang
       choco install elixir
       ```

2. **프로젝트 클론**
   ```bash
   git clone https://github.com/your-repo/distributed-task-queue.git
   cd distributed-task-queue
   ```

3. **컴파일**
   - 프로젝트 루트 디렉토리에서 Mix를 이용하여 소스 파일들을 컴파일합니다.
     ```bash
     mix compile
     ```

### 실행 방법

1. **IEx 셸 시작**
   ```bash
   iex -S mix
   ```

2. **작업 큐 서버 시작**
   - IEx 셸에서 작업 큐 서버를 시작합니다.
     ```elixir
     DistributedTaskQueue.start()
     ```
   - 서버는 클라이언트로부터 작업 요청을 대기하며, Worker들에게 작업을 분배할 준비를 합니다.

3. **작업 제출**
   - 클라이언트나 별도의 모듈에서 작업 요청을 큐에 추가합니다.
     ```elixir
     DistributedTaskQueue.submit_task(%{job: "데이터 처리", params: [1, 2, 3]})
     ```
   - 작업 데이터는 맵 형태로 전달되며, 각 Worker는 이를 받아 처리합니다.

4. **작업 처리 및 결과 확인**
   - Worker 프로세스는 분배된 작업을 수행한 후, 결과를 로그로 출력하거나 상위 시스템에 보고합니다.
   - 작업 완료 및 오류 발생 여부는 콘솔 로그를 통해 확인할 수 있습니다.

---

## 코드 구조

- **src/distributed_task_queue.ex:**  
  작업 큐 서버의 핵심 로직을 구현한 모듈로, 작업 요청 수신, 큐 관리 및 작업 분배 기능이 포함되어 있습니다.
  
- **src/task_worker.ex:**  
  개별 Worker 프로세스의 동작을 정의하는 모듈로, 분배된 작업을 수행하고 결과를 보고하는 로직을 구현합니다.
  
- **src/supervisor_task.ex:**  
  Supervisor 트리를 구성하여, 작업 큐 서버와 Worker 프로세스의 생명주기를 관리합니다.
  
- **README.md:**  
  이 문서는 프로젝트의 개요, 설치 및 실행 방법, 시스템 아키텍처 등을 상세히 설명합니다.

---

## 예제 사용 시나리오

1. **서버 시작:**  
   작업 큐 서버를 실행하여 클라이언트의 작업 요청을 대기합니다.
   
2. **작업 제출:**  
   클라이언트가 작업 요청을 제출하면, 서버는 이를 큐에 추가합니다.
   
3. **작업 분배:**  
   서버는 대기 중인 작업을 적절한 Worker 프로세스에 분배하여 병렬로 처리합니다.
   
4. **작업 처리 및 결과 보고:**  
   각 Worker 프로세스는 분배된 작업을 수행하고, 완료 결과를 상위 시스템에 보고하거나 로그로 출력합니다.
   
5. **오류 복구:**  
   Worker 또는 서버 프로세스가 실패하면, Supervisor가 자동으로 재시작하여 작업 처리의 연속성을 보장합니다.

---

## 개발 및 확장 계획

- **분산 처리 확장:**  
  여러 노드를 연결하여 클러스터 환경에서 작업 큐 시스템의 부하 분산과 확장성을 강화합니다.
  
- **결과 저장소 통합:**  
  처리된 작업 결과를 데이터베이스나 파일 시스템에 저장하는 기능을 추가하여, 작업 이력을 관리합니다.
  
- **웹 인터페이스 도입:**  
  작업 큐 및 Worker 상태 모니터링, 작업 제출 및 결과 확인을 위한 웹 기반 대시보드를 개발합니다.
  
- **보안 강화:**  
  작업 요청 인증 및 데이터 암호화 기능을 추가하여, 보안에 민감한 환경에서도 안전하게 운영될 수 있도록 합니다.

---

## 참고 자료

- [Programming Erlang - Joe Armstrong](https://pragprog.com/titles/jjoe/programming-erlang/)  
- [Learn You Some Erlang for Great Good! - Fred Hebert](http://learnyousomeerlang.com/)  
- [Elixir 공식 문서](https://hexdocs.pm/elixir/)  
- [OTP Design Principles](https://erlang.org/doc/design_principles/)

---

이 프로젝트는 OTP와 Elixir의 핵심 개념을 실전에서 체험할 수 있도록 설계되었습니다.  
분산 작업 큐 시스템을 통해 동시성, 내결함성, 그리고 분산 처리의 원리를 깊이 이해하고, 실제 환경에 적용할 수 있는 기반을 마련하시기 바랍니다.

의견이나 개선 사항은 [이슈 트래커](https://github.com/your-repo/distributed-task-queue/issues)를 통해 공유해 주시기 바랍니다.

Happy coding!