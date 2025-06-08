# 🚀 백엔드/클라우드/실시간 시스템 통합 학습 로드맵 2025-2026

이 리포지토리는 백엔드 개발자 및 클라우드 엔지니어로 성장하기 위한 학습 로드맵입니다. 군 복무 중(2025년 6월 ~ 2026년 8월) 이론 학습을 체화하고, 전역 후(2026년 9월 ~) 실전 프로젝트로 포트폴리오를 구축하여 한국 IT 기업 취업(2027년 9월), 미국 이직(2029~2030년), 창업(2031년~)을 목표합니다. AI 대체 위험을 최소화하며, 실시간 시스템(채팅, 메타버스)과 클라우드 네이티브 기술에 초점 맞춥니다.

## 📋 목차
1. [학습 목표](#학습-목표)
2. [현재 기술 스택](#현재-기술-스택)
3. [군 복무 중 학습 계획 (2025년 6월 ~ 2026년 8월)](#군-복무-중-학습-계획)
4. [전역 후 학습 및 커리어 전략](#전역-후-학습-및-커리어-전략)
5. [기술 스택 로드맵](#기술-스택-로드맵)

## 📌 학습 목표
- **단기 (2025년 6월 ~ 2026년 8월)**: 군 복무 중 CS 기초(자료구조, 알고리즘, 네트워크, OS), 언어/프레임워크(Go, TypeScript, NestJS, Elixir), 클라우드/시스템 디자인/암호화 이론 체화.
- **중기 (2026년 9월 ~ 2027년 9월)**: 복학 후 실전 프로젝트(채팅 앱, 마이크로서비스 API)로 포트폴리오 구축, 한국 IT 기업 취업(네이버, 카카오 등, 연봉 3,800만~5,000만).
- **장기 (2029년 ~ 2031년)**: 미국 IT 기업 이직(연봉 1억 3,500만~2억 1,000만), 자본(1억 6,000만~2억 4,000만)과 인맥으로 AI 기반 SaaS/메타버스 창업.
- **AI 대응**: AI/ML 통합, 고급 설계(마이크로서비스, Kubernetes), 보안(TLS, HSM) 역량 강화로 대체 위험 최소화.

## 🛠 현재 기술 스택
- **주 언어**: Go (고루틴, 채널, Gin, Echo, GORM)
- **서브 언어**: TypeScript (NestJS, TypeORM), C/C++ (libuv), Elixir (OTP)
- **프레임워크**: NestJS, Express.js, Spring Boot
- **DB**: MySQL, PostgreSQL, MongoDB, Cassandra, Redis, Elasticsearch
- **컨테이너**: Docker, Docker-Compose
- **CI/CD**: Jenkins, GitHub Actions, ArgoCD (GitOps)
- **클라우드 네이티브**: Kubernetes, Prometheus, Grafana, Istio
- **메시지 큐**: Kafka, RabbitMQ
- **기타**: 네트워크 (OSI, TCP/IP), OS (프로세스, 동시성), 암호화 (AES, TLS), 시스템 디자인 (마이크로서비스, 확장성)
- **수준**: 기본 사용 경험, 일부 이론 이해, 실전 구현은 전역 후 강화 예정.

## 📚 군 복무 중 학습 계획 (2025년 6월 ~ 2026년 8월)
군 복무 환경(컴퓨터 사용 제한)을 고려해 이론 중심 학습을 진행, 교재/PDF, 노트 정리, Replit(휴가/주말) 활용. 주 10~12시간 학습, 3단계로 구성.

### 단계 1: CS 기초 심화 (2025년 6월 ~ 2025년 10월, 5개월)
**목표**: 자료구조, 알고리즘, 네트워크, OS 기초 체화, 면접 및 시스템 이해 기반 구축.
- **자료구조** (3주/주제):
  - 기본: 배열, 연결 리스트, 스택, 큐, 해시 테이블 (충돌 해결: 체이닝, 오픈 어드레싱).
  - 트리: 이진 트리, BST, AVL 트리 (순회, 삽입/삭제).
  - 그래프: DFS, BFS, 위상 정렬.
  - 심화: LSM Tree, B* Tree (Cassandra, MySQL 인덱스 이론).
- **알고리즘** (3주/주제):
  - 정렬: 퀵소트, 병합 정렬, 기수 정렬.
  - 탐색: 이진 탐색, KMP 문자열 검색.
  - 동적 계획법: 배낭, 최장 공통 부분 수열.
  - 심화: Bitmask DP, DP on Trees 개요.
- **네트워크** (2주):
  - OSI 7계층, TCP/IP, HTTP/REST, gRPC.
  - 부하 분산, API 게이트웨이 개념.
- **운영체제** (2주):
  - 프로세스 vs 스레드, 메모리 관리, 동시성(락, 세마포어).
  - 멀티스레딩, 스케줄링.
- **리소스**:
  - 교재:
    - “Introduction to Algorithms” (CLRS, 챕터 2, 3, 6, 10~12, 15).
    - “Computer Networking: A Top-Down Approach” (Kurose, 챕터 1~3).
    - “Operating Systems: Three Easy Pieces” (무료 PDF, 챕터 4~7, 13~15).
  - 노트: 다이어그램 (TCP 3-way handshake, AVL 트리 회전), 의사코드 (퀵소트, DFS).
  - Replit: 휴가 시 Go로 연결 리스트, TypeScript로 이진 탐색.
- **성과**: LeetCode Easy~Medium 30문제 의사코드, CS 개념 80% 이해.
- **예상 시간**: 주 10시간 × 20주 = 200시간 (자료구조 80시간, 알고리즘 80시간, 네트워크/OS 40시간).

### 단계 2: 언어 및 프레임워크 이론 (2025년 11월 ~ 2026년 3월, 5개월)
**목표**: Go, TypeScript, NestJS, Elixir, C의 내부 동작과 설계 철학 이해, 실전 대비.
- **Go** (8주):
  - 고루틴, 채널, CSP 모델.
  - Gin, Echo, GORM 아키텍처.
  - 동시성 프로그래밍 이론 (예: 마이크로서비스 API).
- **TypeScript/NestJS** (8주):
  - 타입 시스템, 제네릭, DI, 모듈 구조.
  - TypeORM, Prisma로 ORM 설계.
- **Elixir** (3주):
  - BEAM VM, OTP, Actor 모델.
  - 실시간 시스템(채팅, 메타버스) 이론.
- **C** (3주):
  - 메모리 관리, 포인터 (libuv는 전역 후).
- **리소스**:
  - 교재:
    - Go: “The Go Programming Language” (Donovan, 챕터 8~9).
    - TypeScript: “Programming TypeScript” (Cherny, 챕터 1~4).
    - NestJS: 공식 문서 PDF, “NestJS in Action”.
    - Elixir: “Programming Elixir” (Dave Thomas, 챕터 1~6).
    - C: “C Programming Language” (K&R, 챕터 5~6).
  - 노트: Go 채널 vs 락, NestJS 컨트롤러 플로우, OTP 다이어그램.
  - Replit: 휴가 시 Go로 HTTP 서버, TypeScript로 타입 함수, Elixir로 GenServer.
- **성과**: 언어/프레임워크 원리 80% 이해, API 설계 플로우 작성.
- **예상 시간**: 주 10~12시간 × 20주 = 220시간 (Go 90시간, TypeScript/NestJS 90시간, Elixir/C 40시간).

### 단계 3: 클라우드, 시스템 디자인, 암호화 (2026년 4월 ~ 2026년 8월, 4개월)
**목표**: Kubernetes, Kafka, 시스템 디자인, 암호화 이론 이해, 미국/창업 대비.
- **Kubernetes** (6주):
  - 노드/파드, 서비스, HPA, RBAC.
  - 서비스 메시(Istio) 개념.
- **Kafka/RabbitMQ** (4주):
  - 파티션, 브로커, 컨슈머 그룹.
  - Event Sourcing, CQRS 이론.
- **시스템 디자인** (3주):
  - 확장성, 가용성, 마이크로서비스, 캐싱.
  - API Gateway, DB 샤딩.
- **암호화** (3주):
  - AES, RSA, TLS/SSL, 키 관리.
  - HSM, DevSecOps 이론.
- **리소스**:
  - 교재:
    - Kubernetes: “Kubernetes in Action” (Luksa, 챕터 1~7).
    - Kafka: “Kafka: The Definitive Guide” (Confluent, 챕터 1~4).
    - 시스템 디자인: “Designing Data-Intensive Applications” (Kleppmann, 챕터 1~3).
    - 암호화: “Cryptography and Network Security” (Stallings, 챕터 2~5).
  - 노트: Kubernetes 클러스터 다이어그램, Kafka 파티션 흐름, TLS 핸드셰이크.
  - Replit: 휴가 시 Docker로 Go 앱 컨테이너, GitHub Actions YAML.
- **성과**: 시스템 아키텍처 설계(종이), 암호화 원리 80% 이해.
- **예상 시간**: 주 10~12시간 × 16주 = 180시간 (Kubernetes 70시간, Kafka 50시간, 시스템 디자인/암호화 60시간).

## 🚀 전역 후 학습 및 커리어 전략 (2026년 9월 ~)
### 복학 및 실전 학습 (2026년 9월 ~ 2027년 9월)
- **목표**: 포트폴리오 구축, 한국 IT 기업 취업(2027년 9월, 연봉 3,800만~5,000만).
- **프로젝트**:
  1. **실시간 채팅 앱**:
     - NestJS(TypeScript)로 WebSocket API, Kafka로 메시지 처리, Redis 캐싱.
     - Kubernetes로 배포, Prometheus/Grafana 모니터링, TLS 보안.
  2. **마이크로서비스 API**:
     - Go로 REST/gRPC API, PostgreSQL/Cassandra, Istio 서비스 메시.
     - ArgoCD로 GitOps 배포.
  3. **메타버스 프로토타입**:
     - Elixir로 실시간 아바타 인터랙션, Kafka로 이벤트 스트리밍.
     - Docker-Compose 로컬 테스트, AWS Free Tier 배포.
- **방법**:
  - **환경**: 개인 PC, Minikube, AWS Free Tier.
  - **리소스**: Udemy(”Kubernetes for Developers”, “NestJS Zero to Hero”), GitHub 오픈소스 기여.
  - **네트워킹**: KCD Korea, AWS Community Day 참가.
  - **시간**: 주 20~30시간, 프로젝트 2~3개 완성.
- **성과**: GitHub에 3개 프로젝트, LeetCode Medium~Hard 50문제, 기술 면접 준비.

### 미국 이직 (2029년 ~ 2030년)
- **목표**: FAANG(아마존, 구글) 또는 스타트업, 연봉 9만~14만 달러(1억 3,500만~2억 1,000만).
- **준비**:
  - 한국 2~3년 경력(마이크로서비스, Kubernetes, Kafka).
  - LeetCode Hard, 시스템 디자인(예: URL 단축기, 채팅 시스템).
  - H-1B 비자 스폰서십, 영어 기술 문서/블로그 작성.
- **성과**: 미국 근무로 자본(연 5,000만~9,000만 저축), 인맥 확보.

### 창업 (2031년~)
- **목표**: AI 기반 SaaS(데이터 분석) 또는 메타버스(실시간 채팅/아바타), 자본 1억 6,000만~2억 4,000만.
- **실행**:
  - Go/NestJS로 MVP 개발, Kubernetes로 배포.
  - 한국(TIPS 프로그램) 또는 미국 VC(Sequoia) 펀딩.
  - KubeCon, AWS re:Invent로 네트워킹.
- **성과**: 초기 제품 개발, 시장 진출.

## 🛠 기술 스택 로드맵
- **Languages and Frameworks**:
  - Go (Gin, Echo, GORM), TypeScript (NestJS, TypeORM), Elixir (OTP), C/C++ (libuv).
  - Java (Spring Boot, Hibernate, JPA).
- **Database**:
  - 관계형: MySQL, PostgreSQL (인덱스, 쿼리 튜닝).
  - NoSQL: MongoDB, Cassandra, Redis, Elasticsearch.
  - 심화: LSM Tree, B* Tree.
- **Message Queue**:
  - Kafka (파티션, CQRS), RabbitMQ (익스체인지).
- **Cloud & DevOps**:
  - **Container & Orchestration**: Docker, Kubernetes (HPA, RBAC, Istio).
  - **CI/CD**: Jenkins, GitHub Actions, ArgoCD.
  - **Monitoring & Logging**: Prometheus, Grafana.
  - **IaC**: Terraform (전역 후 학습).
  - **Secrets Management**: AWS KMS, HashiCorp Vault.
- **Network**: OSI, TCP/IP, gRPC, API Gateway.
- **OS**: 프로세스, 동시성, 스케줄링.
- **Security**: AES, RSA, TLS/SSL, HSM.
- **System Design**: 마이크로서비스, 확장성, 캐싱, 샤딩.

## 📅 Last Updated
2025년 6월 8일

## 📖 About
백엔드, 클라우드, 실시간 시스템 엔지니어로 성장하기 위한 학습 로드맵. 군 복무 중 이론 학습, 전역 후 실전 프로젝트로 한국 취업, 미국 이직, 창업 목표.

---
© 2025 GitHub, Inc.