# 분산 키-값 저장소 프로젝트

## 프로젝트 개요
이 프로젝트는 OTP와 Elixir의 강력한 분산 처리, 동시성, 내결함성 기능을 활용하여 **분산 키-값 저장소**를 구현한 예제입니다.  
본 시스템은 여러 노드에 걸쳐 데이터를 저장, 조회, 갱신할 수 있도록 설계되었으며, 데이터 복제와 동기화, 장애 복구 기능을 통해 높은 가용성과 안정성을 보장합니다.

---

## 주요 기능
- **분산 데이터 저장:**  
  데이터를 여러 노드에 분산하여 저장함으로써 단일 장애 지점을 제거하고, 데이터 손실 없이 시스템을 운영합니다.
  
- **실시간 데이터 조회 및 갱신:**  
  키를 기반으로 데이터를 신속하게 조회하고 갱신할 수 있는 기능을 제공하며, ETS를 활용하여 메모리 내에서 빠른 데이터 처리를 지원합니다.
  
- **데이터 복제 및 동기화:**  
  각 노드에 데이터 복제를 수행하여, 한 노드의 장애가 발생해도 다른 노드에서 데이터를 유지할 수 있도록 합니다.
  
- **오류 복구 및 자동 재시작:**  
  Supervisor가 데이터 저장 서버와 복제 관리 프로세스의 장애를 감시하고, 오류 발생 시 자동 재시작 전략을 통해 시스템의 내결함성을 확보합니다.
  
- **분산 노드 통신:**  
  Erlang의 분산 기능을 이용하여, 여러 노드 간에 데이터를 동기화하고 일관성 있게 관리할 수 있습니다.

---

## 시스템 아키텍처

### 프로세스 구조
- **데이터 저장 서버:**  
  - 각 노드에서 ETS 테이블을 사용하여 키-값 데이터를 관리합니다.
  - 데이터를 저장, 조회, 갱신하는 기본 기능을 제공합니다.
  
- **데이터 복제 관리자:**  
  - 데이터 변경 시, 변경 사항을 다른 노드에 복제하여 데이터 일관성을 유지합니다.
  
- **Supervisor 트리:**  
  - 데이터 저장 서버와 복제 관리 프로세스의 생명주기를 관리하며, 장애 발생 시 자동 재시작을 통해 시스템의 안정성을 보장합니다.

### OTP 구성 요소 활용
- **GenServer:**  
  데이터 저장 서버의 상태 관리와 클라이언트 요청 처리에 활용됩니다.
  
- **Supervisor:**  
  각 노드에서 실행되는 데이터 저장 서버와 복제 관리 프로세스를 감시하고, 실패 시 자동으로 재시작합니다.
  
- **ETS:**  
  메모리 내 데이터 저장 및 빠른 조회를 위해 사용되며, 실시간 데이터 처리를 지원합니다.
  
- **분산 통신:**  
  노드 간 메시지 전달 기능을 통해, 여러 서버 간에 데이터를 동기화하고 복제합니다.

---

## 설치 및 실행 방법

### 요구 사항
- Erlang/OTP 24 이상
- Elixir 1.12 이상
- Linux, macOS 또는 Windows 운영체제
- 네트워크 연결 및 클러스터 구성 환경

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
     - 설치 프로그램을 [Elixir 공식 웹사이트](https://elixir-lang.org/install.html)에서 다운로드하거나, Chocolatey를 이용하여 설치:
       ```bash
       choco install erlang
       choco install elixir
       ```

2. **프로젝트 클론**
   ```bash
   git clone https://github.com/your-repo/distributed-key-value-store.git
   cd distributed-key-value-store
   ```

3. **컴파일**
   - 프로젝트 루트 디렉토리에서 Mix를 사용하여 소스 파일들을 컴파일합니다.
     ```bash
     mix compile
     ```

### 실행 방법

1. **IEx 셸 시작**
   ```bash
   iex -S mix
   ```

2. **데이터 저장 서버 시작**
   - IEx 셸에서 데이터 저장 서버를 시작합니다.
     ```elixir
     DistributedKVStore.start()
     ```
   - 서버는 ETS 테이블을 초기화하고, 클라이언트의 데이터 요청을 처리할 준비를 합니다.

3. **데이터 조작**
   - 데이터를 저장, 조회, 갱신하는 함수들을 통해 키-값 데이터를 처리합니다.
     ```elixir
     # 데이터 저장
     DistributedKVStore.put(:user1, %{name: "Alice", age: 30})
     
     # 데이터 조회
     DistributedKVStore.get(:user1)
     
     # 데이터 갱신
     DistributedKVStore.update(:user1, fn data -> Map.put(data, :age, 31) end)
     ```

4. **분산 클러스터 구성 (선택 사항)**
   - 여러 노드를 연결하여 분산 클러스터를 구성하고, 노드 간 데이터 복제 및 동기화 기능을 테스트할 수 있습니다.
     ```elixir
     # 예시: 다른 노드에 접속
     Node.connect(:"node2@hostname")
     DistributedKVStore.sync()  # (데이터 동기화 함수; 구현 방식에 따라 다름)
     ```

---

## 코드 구조

- **src/distributed_kv_store.ex:**  
  데이터 저장 서버의 핵심 로직을 구현한 모듈로, ETS를 활용한 데이터 저장, 조회, 갱신 기능이 포함되어 있습니다.
  
- **src/replication_manager.ex:**  
  데이터 복제 및 동기화를 관리하는 모듈로, 노드 간 데이터 일관성을 유지하는 역할을 수행합니다.
  
- **src/supervisor_kv.ex:**  
  Supervisor 트리를 구성하여, 데이터 저장 서버와 복제 관리 프로세스의 생명주기를 관리합니다.
  
- **README.md:**  
  이 문서로, 프로젝트 개요, 설치 및 실행 방법, 시스템 아키텍처 등을 상세히 설명합니다.

---

## 예제 사용 시나리오

1. **서버 시작:**  
   데이터 저장 서버를 실행하여 클라이언트의 데이터 요청을 대기합니다.
   
2. **데이터 저장:**  
   클라이언트가 데이터를 저장하면, ETS 테이블에 기록되고 복제 관리자를 통해 다른 노드에 동기화됩니다.
   
3. **데이터 조회 및 갱신:**  
   저장된 데이터를 키를 통해 조회하거나, 갱신 요청을 통해 데이터를 업데이트합니다.
   
4. **데이터 복제 및 장애 복구:**  
   노드 간 데이터 동기화가 정상적으로 이루어지며, 장애 발생 시 Supervisor가 자동으로 재시작하여 시스템의 안정성을 유지합니다.

---

## 개발 및 확장 계획

- **데이터 영속성 강화:**  
  ETS 외에 디스크 기반 저장소와 연동하여 데이터 영속성을 보장하는 기능을 추가할 계획입니다.
  
- **복제 알고리즘 개선:**  
  데이터 복제 및 동기화 알고리즘을 최적화하여, 노드 간 일관성을 강화합니다.
  
- **웹 인터페이스 도입:**  
  관리자 및 사용자 인터페이스를 위한 웹 대시보드를 도입하여, 데이터 상태 모니터링과 제어 기능을 제공합니다.
  
- **보안 강화:**  
  데이터 암호화, 인증, 접근 제어 기능을 추가하여, 보안에 민감한 환경에서도 안전하게 운영할 수 있도록 합니다.

---

## 참고 자료

- [Programming Erlang - Joe Armstrong](https://pragprog.com/titles/jjoe/programming-erlang/)
- [Learn You Some Erlang for Great Good! - Fred Hebert](http://learnyousomeerlang.com/)
- [Elixir 공식 문서](https://hexdocs.pm/elixir/)
- [OTP Design Principles](https://erlang.org/doc/design_principles/)

---

이 프로젝트는 분산 환경에서의 데이터 관리, 복제, 그리고 고가용성 시스템 구축을 실전에서 경험할 수 있도록 설계되었습니다.  
분산 키-값 저장소를 통해 동시성, 내결함성, 분산 처리의 원리를 심도 있게 이해하고, 실제 운영 환경에 적용할 수 있는 기반을 마련하시기 바랍니다.

의견이나 개선 사항은 [이슈 트래커](https://github.com/your-repo/distributed-key-value-store/issues)를 통해 공유해 주시기 바랍니다.

Happy coding!