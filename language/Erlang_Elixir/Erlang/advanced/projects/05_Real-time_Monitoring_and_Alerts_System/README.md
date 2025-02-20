# 실시간 모니터링 및 경보 시스템 프로젝트

## 프로젝트 개요
이 프로젝트는 Erlang/OTP의 강력한 동시성, 분산 처리 및 fault-tolerance 기능을 활용하여 **실시간 모니터링 및 경보 시스템**을 구현한 예제입니다.  
시스템의 상태, 로그, 및 주요 지표를 실시간으로 모니터링하고, 이상 징후나 임계치를 초과하는 상황 발생 시 경보를 발송하여 관리자에게 즉각적으로 알리는 것을 목표로 합니다.  
OTP의 gen_server, gen_event, 그리고 supervisor를 활용하여 안정적이고 확장 가능한 모니터링 인프라를 구성합니다.

## 주요 기능
- **실시간 모니터링:**  
  서버 및 애플리케이션의 상태, 성능 지표, 로그 등 다양한 데이터를 실시간으로 수집합니다.
- **경보 및 알림:**  
  미리 설정된 임계치를 초과하거나 비정상적인 상황이 감지되면, 이메일, SMS, 또는 기타 알림 채널을 통해 경보를 발송합니다.
- **이벤트 로깅 및 분석:**  
  모니터링 데이터를 이벤트로 기록하고, 후속 분석 및 문제 해결을 위한 로그 데이터를 축적합니다.
- **자동 복구 및 장애 대응:**  
  Supervisor 트리를 통해 모니터링 및 경보 관련 프로세스의 오류를 자동으로 복구하여, 시스템 안정성을 보장합니다.
- **확장성:**  
  분산 환경에서 여러 노드에 걸쳐 모니터링 에이전트를 배포하고, 중앙 Alert Manager를 통해 통합 관리할 수 있습니다.

## 시스템 아키텍처
프로젝트는 OTP의 핵심 구성 요소들을 활용하여 다음과 같이 구성됩니다.

### 프로세스 구조
- **모니터 에이전트 (Monitor Agent):**  
  각 노드 또는 서버의 상태와 주요 지표(메모리, CPU 사용량, 네트워크 트래픽 등)를 주기적으로 수집하는 프로세스입니다.
- **Alert Manager:**  
  수집된 모니터링 데이터를 분석하여, 임계치 초과나 이상 징후가 발견될 경우 경보를 발송하는 중앙 관리 프로세스입니다.
- **이벤트 로거 (Event Logger):**  
  gen_event 기반의 이벤트 로깅 시스템을 통해 모든 모니터링 이벤트와 경보 발생 기록을 저장합니다.
- **Supervisor 트리:**  
  모니터 에이전트, Alert Manager, 이벤트 로거 등의 생명주기를 관리하며, 장애 발생 시 자동 재시작을 수행합니다.

### OTP 구성 요소 활용
- **gen_server:**  
  모니터 에이전트와 Alert Manager의 상태 관리 및 메시지 처리를 담당합니다.
- **gen_event:**  
  이벤트 로깅 및 알림 발생 시 이벤트를 처리하여, 후속 분석 및 기록에 활용합니다.
- **supervisor:**  
  전체 시스템의 프로세스 장애 감시 및 자동 복구를 담당하여, 높은 안정성을 보장합니다.

## 설치 및 실행 방법

### 요구 사항
- Erlang/OTP 24 이상
- Linux, macOS 또는 Windows 운영체제
- 네트워크 연결 환경 (분산 모니터링 시 여러 노드 연결 필요)

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
   git clone https://github.com/your-repo/real-time-monitoring-alert-system.git
   cd real-time-monitoring-alert-system
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

2. **Supervisor 트리 시작**
   - Erlang 쉘에서 모니터링 시스템을 시작합니다.
     ```erlang
     monitoring_system:start().
     ```
   - 이 명령은 모니터 에이전트, Alert Manager, 이벤트 로거 등을 포함한 전체 Supervisor 트리를 초기화하고 실행합니다.

3. **모니터링 데이터 확인 및 경보 테스트**
   - 시스템이 정상적으로 작동 중이면, 각 모듈은 주기적으로 데이터를 수집하고 로그를 남깁니다.
   - 임계치 초과 등의 시뮬레이션 데이터를 전송하여 경보가 정상적으로 발생하는지 테스트할 수 있습니다.
   - 예를 들어:
     ```erlang
     monitoring_system:simulate_alert(threshold_exceeded).
     ```

## 코드 구조

- **src/monitoring_system.erl:**  
  전체 시스템의 시작 및 초기화 로직을 포함하며, Supervisor 트리를 구성합니다.
  
- **src/monitor_agent.erl:**  
  개별 서버나 노드의 상태 및 성능 지표를 주기적으로 수집하는 모듈입니다.
  
- **src/alert_manager.erl:**  
  모니터 에이전트로부터 받은 데이터를 분석하여 경보를 발송하는 중앙 관리 모듈입니다.
  
- **src/event_logger.erl:**  
  발생하는 이벤트 및 경보 기록을 처리하는 gen_event 기반 모듈입니다.
  
- **README.md:**  
  이 문서로, 프로젝트 개요, 실행 방법, 시스템 아키텍처 등을 상세히 설명합니다.

## 예제 사용 시나리오
1. **시스템 시작:**  
   Supervisor 트리를 통해 모니터 에이전트, Alert Manager, 이벤트 로거가 초기화되고 실행됩니다.
2. **데이터 수집:**  
   각 모니터 에이전트는 주기적으로 시스템의 상태와 성능 데이터를 수집하여 Alert Manager에 전송합니다.
3. **경보 발생:**  
   Alert Manager가 수신한 데이터에서 임계치 초과나 이상 징후를 감지하면, 즉시 경보를 발송하고 이벤트 로거에 기록합니다.
4. **경보 확인 및 대응:**  
   관리자는 경보를 확인하고, 필요 시 즉각적인 대응 조치를 취할 수 있습니다.
5. **장애 복구:**  
   개별 프로세스 장애 발생 시, Supervisor가 자동으로 재시작하여 시스템의 안정성을 유지합니다.

## 개발 및 테스트
- **개발 환경:**  
  Erlang/OTP R24 이상, VSCode 또는 기타 Erlang 지원 IDE
- **테스트:**  
  단위 테스트와 통합 테스트를 통해 모니터링 데이터 수집, 경보 발생 및 이벤트 로깅 기능을 검증합니다.
- **모니터링:**  
  시스템 로그와 실시간 모니터링 도구를 통해 각 프로세스의 상태와 장애 복구 상태를 지속적으로 확인합니다.

## 확장 계획
- **외부 알림 연동:**  
  이메일, SMS, 슬랙 등 외부 알림 서비스와의 연동 기능 추가.
- **웹 대시보드:**  
  실시간 모니터링 데이터를 시각화할 수 있는 웹 기반 대시보드 개발.
- **데이터 분석:**  
  축적된 이벤트 데이터를 기반으로 한 예측 분석 및 트렌드 분석 기능 도입.
- **보안 강화:**  
  모니터링 데이터 전송 시 암호화 및 접근 제어 기능 강화.

## 참고 자료
- [Programming Erlang - Joe Armstrong](https://pragprog.com/titles/jjoe/programming-erlang/)
- [Learn You Some Erlang for Great Good! - Fred Hebert](http://learnyousomeerlang.com/)
- [Erlang 공식 문서](https://www.erlang.org/docs)
- [실시간 모니터링 시스템 사례 및 모범 사례](https://example.com/monitoring-best-practices)

---

이 프로젝트는 실시간 시스템 모니터링 및 경보 시스템 구축을 통해, OTP의 고급 기능과 분산 처리, 오류 복구 메커니즘을 실전에서 경험할 수 있는 좋은 예제입니다.  
의견이나 개선 사항은 [이슈 트래커](https://github.com/your-repo/real-time-monitoring-alert-system/issues)를 통해 공유해 주시기 바랍니다.

Happy coding!