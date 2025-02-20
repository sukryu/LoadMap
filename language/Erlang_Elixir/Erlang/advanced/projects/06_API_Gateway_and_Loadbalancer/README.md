# API Gateway 및 로드 밸런서 프로젝트

## 프로젝트 개요
이 프로젝트는 Erlang/OTP의 강력한 동시성, 분산 처리 및 내결함성 기능을 활용하여 **API Gateway 및 로드 밸런서**를 구현한 예제입니다.  
이 시스템은 다양한 백엔드 서비스로 전달되는 API 요청을 중앙에서 처리하며, 요청을 적절히 라우팅하고 부하를 분산시켜 전체 시스템의 안정성과 확장성을 보장합니다.

## 주요 기능
- **API 요청 라우팅:**  
  클라이언트로부터 들어오는 API 요청을 분석하여, 적절한 백엔드 서비스로 전달합니다.
- **로드 밸런싱:**  
  다수의 백엔드 인스턴스에 API 요청을 균등하게 분배하여, 부하를 효과적으로 조절합니다.
- **서비스 모니터링 및 헬스 체크:**  
  각 백엔드 서비스의 상태를 주기적으로 확인하고, 장애 발생 시 자동으로 요청을 다른 인스턴스로 전환합니다.
- **오류 복구 및 자동 재시작:**  
  Supervisor 트리를 활용하여 게이트웨이와 로드 밸런서 관련 프로세스의 장애를 감시하고, 자동 복구를 수행합니다.
- **분산 처리 지원:**  
  Erlang의 노드 간 통신 기능을 이용하여, 클러스터 환경에서도 API Gateway 및 로드 밸런싱 기능을 확장할 수 있습니다.

## 시스템 아키텍처
이 시스템은 OTP의 주요 구성 요소들을 활용하여 다음과 같이 구성됩니다.

### 프로세스 구조
- **API Gateway 서버:**  
  클라이언트의 API 요청을 수신하고, 요청 내용을 기반으로 적절한 백엔드 서비스로 라우팅합니다.
- **로드 밸런서 모듈:**  
  백엔드 서비스 인스턴스의 상태를 모니터링하고, 각 요청을 동적으로 분배하여 부하를 균형 있게 조절합니다.
- **헬스 체크 프로세스:**  
  주기적으로 백엔드 서비스의 상태를 점검하여, 장애가 발생한 인스턴스를 식별하고 로드 밸런싱 목록에서 제외합니다.
- **Supervisor 트리:**  
  전체 시스템의 프로세스들을 감시하며, 장애 발생 시 자동 재시작하여 서비스의 지속성을 보장합니다.

### OTP 구성 요소 활용
- **gen_server:**  
  API Gateway 서버와 로드 밸런서 모듈의 상태 관리 및 메시지 처리를 담당합니다.
- **gen_event 또는 별도 모듈:**  
  헬스 체크 이벤트와 로그를 처리하여, 모니터링 정보를 제공할 수 있습니다.
- **supervisor:**  
  각 프로세스의 생명주기를 관리하고, 오류 발생 시 자동 복구 기능을 제공합니다.
- **분산 처리:**  
  여러 노드 간의 통신을 통해, 클러스터 환경에서의 API 요청 라우팅 및 로드 밸런싱을 지원합니다.

## 설치 및 실행 방법

### 요구 사항
- Erlang/OTP 24 이상
- Linux, macOS 또는 Windows 운영체제
- 네트워크 연결 환경 및 클러스터 구성 (옵션)

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
   git clone https://github.com/your-repo/api-gateway-load-balancer.git
   cd api-gateway-load-balancer
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

2. **API Gateway 및 로드 밸런서 시작**
   - Erlang 쉘에서 다음 명령을 통해 시스템을 시작합니다.
     ```erlang
     api_gateway:start().
     ```
   - 시스템은 클라이언트 요청 수신 및 백엔드 서비스 인스턴스 모니터링을 시작합니다.

3. **백엔드 서비스 등록**
   - 백엔드 서비스 인스턴스를 등록하여, API Gateway가 요청을 라우팅할 수 있도록 합니다.
     ```erlang
     api_gateway:add_backend({backend1, "http://backend1.example.com"}).
     api_gateway:add_backend({backend2, "http://backend2.example.com"}).
     ```

4. **API 요청 전송 및 테스트**
   - 클라이언트 또는 테스트 스크립트를 통해 API 요청을 전송합니다.
     ```erlang
     Response = api_gateway:route_request({get, "/api/data", []}).
     io:format("API 응답: ~p~n", [Response]).
     ```

## 코드 구조

- **src/api_gateway.erl:**  
  API Gateway 서버의 핵심 로직을 구현한 모듈로, 클라이언트 요청 수신, 라우팅, 백엔드 등록 및 관리 기능을 포함합니다.
  
- **src/load_balancer.erl:**  
  로드 밸런싱 로직을 구현한 모듈로, 백엔드 서비스의 상태를 모니터링하고, 요청 분배 알고리즘을 적용합니다.
  
- **src/health_check.erl:**  
  백엔드 서비스의 헬스 체크 및 상태 감시 기능을 담당하는 모듈입니다.
  
- **src/supervisor_gateway.erl:**  
  Supervisor 트리를 구성하여, API Gateway, 로드 밸런서 및 헬스 체크 프로세스의 생명주기를 관리합니다.
  
- **README.md:**  
  이 문서로, 프로젝트 개요와 실행 방법, 시스템 아키텍처 등을 상세히 설명합니다.

## 예제 사용 시나리오
1. **시스템 시작:**  
   API Gateway 및 로드 밸런서 시스템을 실행하여, 클라이언트 요청을 수신할 준비를 합니다.
2. **백엔드 등록:**  
   여러 백엔드 서비스 인스턴스를 등록하고, 헬스 체크를 통해 정상 상태를 유지합니다.
3. **API 요청 라우팅:**  
   클라이언트에서 전송된 API 요청이, 로드 밸런서 알고리즘에 따라 적절한 백엔드로 라우팅됩니다.
4. **오류 및 장애 대응:**  
   백엔드 서비스 장애 발생 시, Supervisor가 자동으로 해당 프로세스를 재시작하고, 로드 밸런서는 정상 인스턴스로 요청을 전환합니다.

## 개발 및 테스트
- **개발 환경:**  
  Erlang/OTP R24 이상, VSCode 또는 기타 Erlang 지원 IDE
- **테스트:**  
  각 모듈에 대해 단위 테스트 및 통합 테스트를 수행하여, API 요청 라우팅, 로드 밸런싱 및 헬스 체크 기능을 검증합니다.
- **모니터링:**  
  로그 파일 및 실시간 모니터링 도구를 통해 시스템 성능과 장애 복구 상태를 지속적으로 확인합니다.

## 확장 계획
- **동적 백엔드 등록 및 제거:**  
  운영 중인 백엔드 서비스 인스턴스를 실시간으로 추가하거나 제거하는 기능 도입.
- **정교한 로드 밸런싱 알고리즘:**  
  응답 시간, 부하 상태, 에러율 등을 고려한 고급 분산 로드 밸런싱 알고리즘 적용.
- **보안 강화:**  
  API 요청 인증, SSL/TLS 암호화 및 접근 제어 기능 추가.
- **웹 기반 대시보드:**  
  API Gateway와 백엔드 서비스의 상태를 실시간으로 모니터링하고 제어할 수 있는 웹 인터페이스 개발.

## 참고 자료
- [Programming Erlang - Joe Armstrong](https://pragprog.com/titles/jjoe/programming-erlang/)
- [Learn You Some Erlang for Great Good! - Fred Hebert](http://learnyousomeerlang.com/)
- [Erlang 공식 문서](https://www.erlang.org/docs)
- [API Gateway 및 로드 밸런서 관련 사례](https://example.com/api-gateway-case-study)

---

이 프로젝트는 OTP를 활용한 API Gateway 및 로드 밸런서의 설계와 구현을 통해, 분산 환경에서의 고가용성과 확장성을 실전에서 경험할 수 있는 좋은 예제입니다.  
의견이나 개선 사항은 [이슈 트래커](https://github.com/your-repo/api-gateway-load-balancer/issues)를 통해 공유해 주시기 바랍니다.

Happy coding!