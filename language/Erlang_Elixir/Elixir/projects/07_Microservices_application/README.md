# 마이크로서비스 기반 애플리케이션 프로젝트

## 프로젝트 개요
이 프로젝트는 OTP와 Elixir의 견고한 동시성, 내결함성 및 분산 처리 기능을 활용하여 **마이크로서비스 기반 애플리케이션**을 구현한 예제입니다.  
각 마이크로서비스는 독립적인 프로세스로 실행되며, 개별적으로 배포, 확장, 업데이트할 수 있습니다.  
이 프로젝트는 서비스 간 통신, 상태 격리, 동적 서비스 등록 및 장애 복구를 통해 높은 확장성과 유연성을 보장합니다.

---

## 주요 기능
- **서비스 분리 및 독립성:**  
  각 마이크로서비스는 단일 책임 원칙에 따라 독립적으로 구현되며, 다른 서비스와의 결합도를 낮춰 유지보수와 확장을 용이하게 합니다.
  
- **동적 서비스 등록 및 디스커버리:**  
  각 서비스는 클러스터 내에서 자신의 존재를 등록하고, 필요한 경우 다른 서비스를 동적으로 찾아 통신합니다.
  
- **내결함성 및 자동 복구:**  
  OTP Supervisor 트리를 통해 각 서비스의 생명주기를 관리하고, 장애 발생 시 자동 재시작 및 복구 기능을 제공합니다.
  
- **API 게이트웨이 통합:**  
  중앙 API 게이트웨이를 통해 외부 요청을 각 서비스로 라우팅하며, 인증, 로깅, 부하 분산 등의 기능을 수행합니다.
  
- **분산 메시지 브로커 연동:**  
  서비스 간 비동기 메시지 전달을 위해 분산 메시지 브로커와 연동하여, 데이터 교환 및 이벤트 기반 처리를 지원합니다.

---

## 시스템 아키텍처

### 프로세스 구조
- **각 마이크로서비스:**  
  - 독립적인 GenServer 또는 OTP 애플리케이션으로 구현됩니다.
  - 각 서비스는 자신의 데이터베이스, 캐시, 혹은 기타 리소스를 관리하며, 필요에 따라 외부 API와 통신합니다.
  
- **서비스 레지스트리 및 디스커버리:**  
  - 서비스들이 클러스터 내에 자신을 등록하고, 다른 서비스의 위치를 동적으로 확인할 수 있도록 합니다.
  
- **API Gateway:**  
  - 모든 외부 클라이언트 요청은 API Gateway를 통해 집계되어, 적절한 마이크로서비스로 라우팅됩니다.
  
- **Supervisor 트리:**  
  - 각 마이크로서비스는 Supervisor에 의해 감시되며, 서비스 장애 시 자동으로 재시작됩니다.
  
- **메시지 브로커:**  
  - 서비스 간 비동기 통신을 위해 분산 메시지 브로커를 도입하여, 이벤트 기반 데이터 흐름과 실시간 처리를 지원합니다.

### OTP 구성 요소 활용
- **GenServer 및 Application:**  
  - 각 마이크로서비스의 핵심 비즈니스 로직 및 상태 관리를 담당합니다.
  
- **Supervisor:**  
  - 서비스 장애 시 자동 복구 및 재시작을 통해 시스템의 내결함성을 보장합니다.
  
- **분산 노드 통신:**  
  - Erlang의 분산 기능을 활용하여, 여러 노드에 걸친 서비스 간 통신과 데이터 동기화를 지원합니다.
  
- **Dynamic Supervisor:**  
  - 동적 서비스 등록 및 관리가 필요한 경우, Dynamic Supervisor를 통해 런타임에 서비스 인스턴스를 추가하거나 제거할 수 있습니다.

---

## 설치 및 실행 방법

### 요구 사항
- Erlang/OTP 24 이상
- Elixir 1.12 이상
- Linux, macOS 또는 Windows 운영체제
- 네트워크 연결 및 클러스터 구성 환경 (분산 기능 사용 시)

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
     - [Elixir 공식 웹사이트](https://elixir-lang.org/install.html)에서 설치 프로그램 다운로드 또는 Chocolatey 이용:
       ```bash
       choco install erlang
       choco install elixir
       ```

2. **프로젝트 클론**
   ```bash
   git clone https://github.com/your-repo/microservices-app.git
   cd microservices-app
   ```

3. **컴파일**
   - 프로젝트 루트 디렉토리에서 Mix를 이용해 소스 파일들을 컴파일합니다.
     ```bash
     mix compile
     ```

### 실행 방법

1. **IEx 셸 시작**
   ```bash
   iex -S mix
   ```

2. **마이크로서비스 시작**
   - IEx 셸에서 각 마이크로서비스를 개별적으로 또는 Supervisor 트리를 통해 시작합니다.
     ```elixir
     MicroservicesApp.start_services()
     ```
   - 각 서비스는 자신의 프로세스로 실행되며, 동적 서비스 등록 및 상태 관리를 시작합니다.

3. **API Gateway 시작**
   - 외부 요청을 라우팅할 API Gateway를 실행합니다.
     ```elixir
     ApiGateway.start()
     ```

4. **서비스 간 통신 및 테스트**
   - API Gateway를 통해 클라이언트 요청을 전송하고, 각 마이크로서비스의 응답 및 상호 통신을 테스트합니다.
     ```elixir
     response = ApiGateway.route_request({:get, "/users", []})
     IO.puts("API 응답: #{inspect(response)}")
     ```

5. **분산 클러스터 구성 (선택 사항)**
   - 여러 노드를 연결하여 클러스터 환경을 구성하고, 노드 간 서비스 디스커버리 및 데이터 동기화를 테스트할 수 있습니다.
     ```elixir
     Node.connect(:"node2@hostname")
     MicroservicesApp.sync_services()
     ```

---

## 코드 구조

- **apps/service_a.ex:**  
  마이크로서비스 A의 핵심 비즈니스 로직과 상태 관리를 구현한 모듈입니다.
  
- **apps/service_b.ex:**  
  마이크로서비스 B의 기능 및 외부 API 연동 로직을 포함하는 모듈입니다.
  
- **apps/api_gateway.ex:**  
  외부 클라이언트의 요청을 받아, 적절한 마이크로서비스로 라우팅하는 API Gateway 모듈입니다.
  
- **lib/microservices_app.ex:**  
  전체 애플리케이션의 시작 및 서비스 등록, 동적 디스커버리 로직을 포함한 메인 모듈입니다.
  
- **lib/supervisor_app.ex:**  
  Supervisor 트리를 구성하여, 모든 마이크로서비스 및 API Gateway의 생명주기를 관리합니다.
  
- **README.md:**  
  이 문서는 프로젝트의 개요, 설치 및 실행 방법, 시스템 아키텍처, 코드 구조, 예제 사용 시나리오, 개발 및 확장 계획 등을 상세히 설명합니다.

---

## 예제 사용 시나리오

1. **서비스 시작:**  
   모든 마이크로서비스와 API Gateway가 Supervisor 트리를 통해 시작됩니다.
   
2. **서비스 등록 및 디스커버리:**  
   각 서비스는 클러스터에 동적으로 등록되어, 필요 시 서로를 디스커버리 할 수 있습니다.
   
3. **API 요청 라우팅:**  
   외부 클라이언트가 API Gateway를 통해 요청을 전송하면, 요청은 적절한 마이크로서비스로 라우팅되어 처리됩니다.
   
4. **서비스 간 통신:**  
   마이크로서비스 간 비동기 메시지 전달을 통해, 데이터 교환 및 협업이 이루어집니다.
   
5. **장애 발생 및 복구:**  
   한 서비스에서 장애가 발생하면, Supervisor가 자동으로 재시작하여 서비스 연속성을 보장합니다.

---

## 개발 및 확장 계획

- **서비스 확장:**  
  새로운 마이크로서비스를 추가하여 기능을 확장하고, 동적 서비스 등록 기능을 강화합니다.
  
- **API Gateway 개선:**  
  부하 분산, 인증, 로깅 및 모니터링 기능을 강화하여, 외부 요청 처리 효율을 높입니다.
  
- **분산 클러스터 최적화:**  
  여러 노드에 걸친 서비스 디스커버리 및 데이터 동기화 메커니즘을 최적화하여, 대규모 트래픽 환경에서도 안정성을 확보합니다.
  
- **보안 강화:**  
  서비스 간 통신 암호화, 인증, 접근 제어 등의 보안 기능을 추가하여, 민감한 데이터를 안전하게 보호합니다.
  
- **모니터링 및 로깅:**  
  실시간 모니터링 대시보드 및 로그 분석 도구를 도입하여, 운영 중인 서비스의 상태와 성능을 지속적으로 개선합니다.

---

## 참고 자료

- [Programming Erlang - Joe Armstrong](https://pragprog.com/titles/jjoe/programming-erlang/)
- [Learn You Some Erlang for Great Good! - Fred Hebert](http://learnyousomeerlang.com/)
- [Elixir 공식 문서](https://hexdocs.pm/elixir/)
- [OTP Design Principles](https://erlang.org/doc/design_principles/)

---

이 프로젝트는 OTP와 Elixir를 활용한 마이크로서비스 아키텍처의 핵심 개념을 실전에서 체험할 수 있도록 설계되었습니다.  
서비스 간의 독립성, 내결함성, 동적 디스커버리 및 분산 통신을 통해, 대규모 시스템에서도 유연하고 안정적인 애플리케이션을 구축할 수 있습니다.

의견이나 개선 사항은 [이슈 트래커](https://github.com/your-repo/microservices-app/issues)를 통해 공유해 주시기 바랍니다.

Happy coding!