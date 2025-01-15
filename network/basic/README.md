# 네트워크 기초(Basic) 디렉토리

이 디렉토리는 **네트워크를 처음 접하거나 기초 지식을 탄탄히 하고 싶은 분**들을 위해 준비되었습니다.  
**OSI 모델**부터 **TCP/IP**, **IP 주소 체계**, **TCP/UDP** 동작, 그리고 **HTTP/HTTPS**, **DNS** 등 **핵심 프로토콜**의 기본 원리를 이해하는 데 초점을 맞춥니다.

---

## 디렉토리 구성 (Files Overview)

현재 `basic/` 디렉토리에는 다음과 같은 문서들이 있습니다:

1. **`01_osi_and_tcpip.md`**  
   - **OSI 7계층**과 **TCP/IP 4계층**의 개념 비교  
   - 각 계층의 역할과 대표 프로토콜 예시  
   - 데이터가 어떻게 "**캡슐화(encapsulation)**" 과정을 통해 전송되는지 이해

2. **`02_ip_addressing.md`**  
   - **IP 주소(IPv4) 구조**, 서브넷 마스크, CIDR 표기법  
   - 게이트웨이, ARP, ICMP 등 IP 계층 핵심 개념  
   - LAN과 WAN에서 IP가 어떻게 라우팅되는지 기본 원리

3. **`03_tcp_udp_details.md`**  
   - **TCP**의 3-way handshake, 4-way 종료, 시퀀스/ACK 번호, 흐름 제어, 혼잡 제어  
   - **UDP** 헤더 구조, 비연결형 특성, 주요 활용 사례(DNS, 스트리밍 등)  
   - 각 프로토콜을 Wireshark/tcpdump로 간단히 살펴보는 예시

4. **`04_http_https.md`**  
   - **HTTP/1.1, HTTP/2, HTTP/3(QUIC)** 개념 비교  
   - 요청/응답 구조, 메서드(GET/POST 등), 상태 코드, 쿠키  
   - **TLS/SSL** 동작 방식, **HTTPS 보안**, 인증서 개념(서명·체인)

5. **`05_dns.md`**  
   - **DNS(Domain Name System)**의 기본 구조와 작동 원리  
   - 도메인 계층(Root, TLD, Authoritative), 재귀/반복 쿼리, TTL(캐싱)  
   - **DNS 레코드**(A, CNAME, MX, NS, TXT 등)와 **Zone 파일** 예시  
   - **DNS 서버**(Recursive/Authoritative) 구성, **BIND/PowerDNS/CoreDNS** 설정  
   - **DNS 보안(DNSSEC, 캐시 포이즈닝 방지, DoH/DoT)**  
   - 클라우드 DNS(Route53, GCP Cloud DNS) 활용 & 실무 도구(dig, nslookup)

---

## 학습 순서 (Recommended Reading Order)

1. **OSI & TCP/IP**  
   - 네트워크 계층화 개념을 먼저 이해 (물리 계층부터 애플리케이션 계층까지)

2. **IP 주소 & ARP/ICMP**  
   - 패킷이 실제로 어떤 경로(라우팅)를 통해 전달되는지 익히기  
   - 서브넷 마스크, 게이트웨이, IP 충돌 문제 등

3. **TCP/UDP**  
   - 연결 지향 vs 비연결형 프로토콜의 차이와 **내부 동작**(3-way handshake, 흐름/혼잡 제어) 파악  
   - 실무에서 **Wireshark**나 **tcpdump**로 패킷 분석 연습

4. **HTTP/HTTPS**  
   - 웹 통신의 기본 프로토콜 및 보안(암호화) 기초  
   - HTTP/1.1 vs HTTP/2 vs HTTP/3, TLS/SSL 인증서, HTTPS 설정

5. **DNS**  
   - 도메인 이름을 IP 주소로 변환하는 핵심 시스템  
   - 레코드 유형(A, CNAME, MX 등)과 **DNS 서버** 구성, 보안(DNSSEC, DoH/DoT)  
   - 클라우드 DNS(Route53, GCP Cloud DNS) 활용, `dig`/`nslookup` 실습

> **이 5단계를 마치면, 기본적인 네트워크 이해(전송 계층~애플리케이션 계층)와 실무 통신 프로토콜의 흐름을 대체로 익히게 됩니다.**

---

## 문서 특징 (Key Points)

- **기초 지식에 충실**: 용어 정의와 배경 지식을 충분히 제공  
- **그림/예시/실습 위주**:  
  - 다이어그램, Wireshark 캡처 샘플 등을 통해 시각화  
- **설계 철학 설명**:  
  - 단순 암기보다는 “왜 이런 구조로 동작하는가?” 배경을 알도록 서술  
- **초심자 친화적**:  
  - 복잡한 부분은 추가 자료나 `advanced/` 디렉토리로 연결

---

## 학습 팁 (Study Tips)

1. **차근차근 따라하기**  
   - 문서를 읽으며, 실제로 `ping`, `traceroute`, `tcpdump` 등의 명령어를 직접 실행해 보세요.  
   - IP 주소, 포트, 프로토콜 필드를 눈으로 확인하면 이해도가 훨씬 높아집니다.

2. **Wireshark 실습 권장**  
   - **TCP 3-way handshake**나 **HTTP 요청/응답**을 캡처해보면, 프로토콜 헤더 구조가 명확해집니다.  
   - 직접 패킷을 뜯어보면, “이게 시퀀스 번호!” “여기서 TLS 핸드셰이크!”라는 식으로 구체적으로 파악 가능.

3. **추가 질문**  
   - “왜 ARP가 필요한가?” “TCP 혼잡 제어는 어떻게 작동?” 등 의문이 생기면 **스스로 리서치** or **Issue/PR**로 질문  
   - 문서를 개선하고 토론하면서 학습 효과를 높일 수 있습니다.

---

## 앞으로의 확장 (Future Extensions)

여기서 **네트워크 기초**를 한 바퀴 돌아봤다면, 더 **심화된** 주제나 **확장 내용**으로 넘어갈 수 있습니다:

1. **Proxy & Load Balancing**  
   - **Reverse Proxy**: Nginx, HAProxy, Envoy 등  
   - **Forward Proxy**: 사내 방화벽, 캐싱/필터링  
   - **Load Balancing**(L4 vs L7, 알고리즘, 세션 스티커)  
   - 이미 `advanced/06_proxy.md`, `advanced/07_loadbalancing.md`에서 자세히 다룬 내용 참고

2. **클라우드 네트워크(VPC)**  
   - AWS/GCP/Azure에서 **서브넷, NAT, 게이트웨이, 보안 그룹**  
   - 하이브리드 클라우드(VPN/Direct Connect) 등 인프라 설계  
   - 쿠버네티스 네트워크(CNI, Ingress)와 연계

3. **애플리케이션 레벨 프로토콜**  
   - **gRPC**, **WebSocket**, **MQTT**, **AMQP**(Kafka, RabbitMQ)  
   - 실시간 통신, RPC, 메시지 큐, 이벤트 드리븐 아키텍처  
   - 프로젝트 필요에 따라 학습

4. **서비스 메시(Service Mesh)**  
   - Istio, Linkerd 등을 통해 mTLS, Observability, Traffic Control  
   - 마이크로서비스 아키텍처에서 Proxy/LoadBalancing 개념이 확장된 형태

5. **네트워크 보안 심화**  
   - 방화벽(iptables/nftables), IDS/IPS, WAF, VPN, DDoS 방어  
   - Zero Trust, SASE, TLS 1.3 등

6. **대규모 라우팅(BGP/OSPF)**  
   - ISP나 대형 엔터프라이즈 환경에서의 동적 라우팅  
   - IX(Internet Exchange), 피어링(피어 관계)

---

### 학습 흐름 예시

1. **Basic** 디렉토리 (현재)  
2. **Proxy & Load Balancing** → 이미 `advanced/06_proxy.md`, `07_loadbalancing.md` 작성됨  
3. **VPC/클라우드 네트워킹** → AWS VPC, GCP VPC, 하이브리드 클라우드  
4. **애플리케이션 레벨 프로토콜**(gRPC/WebSocket 등) or **서비스 메시**
5. **(필요 시) 네트워크 보안/대규모 라우팅**  
   
이런 방식으로 확장해가면, **백엔드/클라우드 인프라**에서 필요로 하는 대부분의 네트워크 지식을 종합적으로 습득할 수 있습니다.

---

즐거운 학습 되시길 바랍니다!  
**이 `basic/` 디렉토리**의 문서들을 탄탄히 학습한 뒤, **`advanced/06_proxy.md`, `advanced/07_loadbalancing.md`** 등으로 자연스럽게 넘어가시면, **프록시와 로드 밸런싱**까지 깊이 이해할 수 있습니다. 이후 **클라우드 VPC**, **애플리케이션 레벨 프로토콜**, **컨테이너 네트워킹** 등도 순차적으로 학습해보세요.
