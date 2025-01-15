# 고급 네트워크(Advanced) 디렉토리

이 디렉토리는 **실무에서 네트워크를 다루는 엔지니어**, 혹은 **기본 프로토콜 지식을 이미 습득한 분**들을 위해 마련되었습니다.  
VPC 설계, **프록시**, **로드밸런서**, 트러블슈팅, 클라우드 네트워킹, 애플리케이션 레벨 프로토콜, 보안/성능 최적화 등 폭넓은 고급 주제를 다룹니다.

---

## 디렉토리 구성 (Files Overview)

이 곳에는 현재 다음과 같은 문서들이 있습니다:

1. **`network-basics.md`**  
   - 이미 `basic/` 디렉토리에서 다룬 프로토콜 개념을 **실무 시나리오**에 맞춰 간단히 재정리
   - **TCP vs UDP, HTTP/HTTPS, DNS** 등 주요 포인트를 빠르게 훑어보고 싶을 때 참고

2. **`network-design.md`**  
   - **네트워크 인프라 설계 원칙**: VPC, 서브넷팅, NAT 게이트웨이, 방화벽(보안 그룹/NACL)  
   - **로드밸런싱(L4/L7) 기본**, DNS 설계, 이중화/고가용성(HA) 전략 등

3. **`troubleshooting.md`**  
   - **패킷 분석**(tcpdump, Wireshark), **네트워크 모니터링**(MTR, iperf3), **QoS/Traffic Shaping**  
   - 실제 장애 시나리오(연결 안 됨, 지연 증가, DNS 오작동 등)를 단계별로 해결

4. **`06_proxy.md`**  
   - **Forward/Reverse Proxy** 개념 및 구현  
   - **Squid, Nginx/HAProxy**를 활용한 프록시 설정  
   - 캐싱, 보안/필터링, SSL 오프로딩 등 다양한 활용 사례

5. **`07_loadbalancing.md`**  
   - **로드 밸런싱**(Load Balancing) 심화  
   - **L4 vs L7**, 알고리즘(라운드 로빈, Least Conn, IP Hash), 세션 스티커, 헬스체크  
   - **HAProxy, Nginx, AWS ELB** 등 실무 설정 예시  
   - 고급 주제: Blue-Green/Canary 배포, Geo LB, SSL 오프로딩

6. **`Cloud-networking/README.md`**  
   - **AWS/GCP/Azure**에서의 VPC, 네트워크 보안, 하이브리드 클라우드(VPN, Direct Connect)  
   - 컨테이너 환경(**Kubernetes CNI**, Service Mesh) 및 마이크로서비스 네트워킹

7. **`app-level-networking.md`**  
   - **RESTful API, gRPC, WebSocket, GraphQL** 등 애플리케이션 레벨 프로토콜/아키텍처  
   - MSA(마이크로서비스) 통신 구조, API Gateway, 메시 브로커, 서버리스 연계

8. **`security-performance.md`**  
   - **TLS/SSL**, 인증서 관리, DDoS 방어, WAF, CDN 활용  
   - 로드 테스트, 캐싱, 로드밸런서 최적화, 고트래픽 서비스 설계

9. **`appendix.md`**  
   - 용어 사전, FAQ, 추가 참고 링크, 권장 도구 목록  
   - 전체 문서에서 자주 언급되는 용어/설정 예시를 한곳에 정리

---

## 학습 및 활용 방법 (How to Use)

1. **특정 주제만 빠르게**  
   - 예: “VPC/Subnet 설계가 궁금” → `network-design.md` 참고  
   - “프록시 설정과 보안” → `06_proxy.md`를 찾아보세요.  
   - “로드밸런서 알고리즘/Blue-Green 배포” → `07_loadbalancing.md`에서 확인  
   - “TCP 캡처로 문제 디버깅?” → `troubleshooting.md`의 tcpdump·Wireshark 활용 파트를 참고

2. **순차적으로 심화 학습**  
   - “네트워크 아키텍처 전반을 알고 싶다”면 `network-design.md`로 시작해,  
   - 이어서 **프록시(`06_proxy.md`) → 로드밸런싱(`07_loadbalancing.md`) → 클라우드 네트워킹(`cloud-networking.md`)** → 애플리케이션 레벨(`app-level-networking.md`) → 보안/성능(`security-performance.md`) 순으로 보면 체계적

3. **실무 시나리오 기반**  
   - 각 문서에는 “실제 설정 예시(Nginx, HAProxy, AWS 등)”나 “트러블슈팅 시나리오”가 포함되어 있습니다.  
   - 바로 적용할 수 있는 **코드 스니펫** 및 명령어 예시가 많으니, 복붙해 테스트하거나 사내 문서에 참고해도 좋습니다.

---

## 대상 독자 (Who Is This For?)

- **인프라/시스템 엔지니어**: VPC 설계, 방화벽 정책, 로드밸런서, 모니터링 등  
- **클라우드/DevOps 엔지니어**: AWS/GCP/Azure 네트워킹, CI/CD, 쿠버네티스 CNI, 서비스 메시  
- **백엔드 개발자**: REST/gRPC/WebSocket/GraphQL, 고트래픽 서비스, API 게이트웨이, 보안과 성능 최적화  
- **네트워크 문제를 직접 해결해야 하는 분**: tcpdump, Wireshark 분석, QoS/Traffic Shaping, CDN/WAF 설정

---

## 추천 학습 경로 (Suggested Reading Path)

1. **`network-design.md`**  
   - VPC, 서브넷, 로드밸런싱(L4/L7) 기초, DNS, 방화벽 구조 이해

2. **`06_proxy.md`**  
   - Forward/Reverse Proxy, SSL 오프로딩, 캐싱/보안/필터링 활용  
   - Nginx/HAProxy/Envoy 등 설정 예시

3. **`07_loadbalancing.md`**  
   - L4 vs L7 로드밸런싱 심화, 알고리즘(Round Robin, Least Conn 등), 세션 스티커, 헬스체크  
   - HAProxy/Nginx/클라우드 LB(AWS, GCP) 실무 예시

4. **`troubleshooting.md`**  
   - 패킷 분석(tcpdump, Wireshark), 네트워크 모니터링(MTR, iperf3), 장애 해결 프로세스

5. **`Cloud-networking/README.md`**  
   - AWS/GCP/Azure VPC, 하이브리드 클라우드(VPN, Direct Connect), K8s CNI, Service Mesh

6. **`app-level-networking.md`**  
   - REST, gRPC, WebSocket, MQTT, GraphQL 등 마이크로서비스 통신 구조

7. **`security-performance.md`**  
   - TLS/SSL, DDoS, WAF, CDN, 성능 테스트(로드 테스트), 고트래픽 최적화

(원하는 주제부터 골라 읽어도 무방합니다. 그러나 **Proxy**와 **Load Balancing**을 기초로 한 후, **클라우드 네트워킹** → **애플리케이션 레벨** → **보안/성능** 순서로 가면 한층 더 체계적으로 파악할 수 있습니다.)

---

즐거운 학습 되시길 바랍니다!  
**네트워크 기초**를 이미 익히셨다면, **프록시/로드밸런싱** → **클라우드 네트워크(VPC)** → **애플리케이션 레벨** → **보안·성능 최적화** 식으로 확장해가며 실무 역량을 더욱 탄탄히 다져보세요.
