# 시스템 설계 마스터 플랜

## 📂 **학습 디렉토리 구조**
```
system-design/
├── 01_fundamentals/                # 시스템 설계 기초
│   ├── principles/                 # 설계 원칙
│   ├── patterns/                   # 디자인 패턴
│   └── architecture/               # 아키텍처 스타일
│
├── 02_distributed_systems/         # 분산 시스템
│   ├── basics/                     # 분산 시스템 기초
│   ├── consensus/                  # 합의 알고리즘
│   ├── consistency/                # 일관성 모델
│   ├── event_driven_architecture/  # 이벤트 기반 아키텍처
│   └── global_distributed_systems/ # 글로벌 분산 시스템
│
├── 03_microservices/               # 마이크로서비스
│   ├── patterns/                   # MSA 패턴
│   ├── communication/              # 서비스 간 통신
│   ├── deployment/                 # 배포 전략
│   ├── security/                   # 마이크로서비스 보안
│   ├── observability/              # 모니터링 및 트레이싱
│   ├── resilience/                 # 장애 대응 및 복원력
│   ├── event_driven_architecture/  # 이벤트 기반 아키텍처
│   ├── ddd/                        # 도메인 주도 설계 (DDD)
│   └── advanced_patterns/          # 고급 마이크로서비스 패턴
│
├── 04_data_management/             # 데이터 관리
│   ├── storage/                    # 저장소 설계
│   ├── caching/                    # 캐싱 전략
│   ├── streaming/                  # 스트리밍 처리
│   ├── replication/                # 데이터 복제 및 샤딩
│   ├── consistency_models/         # 데이터 일관성 모델
│   └── event_sourcing_cqrs/        # 이벤트 소싱 및 CQRS
│
├── 05_scalability/                 # 확장성
│   ├── horizontal/                 # 수평적 확장
│   ├── vertical/                   # 수직적 확장
│   ├── patterns/                   # 확장 패턴
│   ├── load_balancing/             # 로드 밸런싱
│   ├── multi_region/               # 멀티 리전 아키텍처
│   ├── edge_computing/             # 엣지 컴퓨팅
│   └── serverless_architecture/    # 서버리스 아키텍처
│
├── 06_sre_observability/           # SRE & 모니터링
│   ├── sre_principles/             # SRE 원칙 및 운영 기법
│   ├── monitoring_logging/         # 모니터링 및 로깅
│   ├── tracing/                    # 분산 트레이싱
│   ├── alerting/                   # 알람 시스템
│   ├── chaos_engineering/          # 장애 실험(Chaos Engineering)
│   ├── error_budgeting/            # 에러 예산 및 SLA 관리
│   ├── reliability_patterns/       # 신뢰성 설계 패턴
│   └── performance_optimization/   # 성능 최적화
│
├── 07_security/                    # 보안
│   ├── authentication/             # 인증 및 인가
│   ├── api_security/               # API 보안
│   ├── data_encryption/            # 데이터 암호화
│   ├── devsecops/                  # DevSecOps & 보안 자동화
│   ├── zero_trust/                 # Zero Trust 아키텍처
│   ├── infrastructure_security/    # 인프라 보안
│   ├── identity_management/        # IAM & 권한 관리
│   └── compliance_gdpr/            # 데이터 규제 및 GDPR 대응
│
└── 08_real_world/                  # 실전 설계
    ├── case_studies/               # 사례 연구
    ├── best_practices/             # 모범 사례
    ├── trade_offs/                 # 설계 결정
    ├── large_scale_architecture/   # 대규모 시스템 설계
    ├── cloud_native_design/        # 클라우드 네이티브 설계
    ├── serverless_edge_computing/  # 서버리스 & 엣지 컴퓨팅
    ├── sre_real_world/             # 실전 SRE 사례
    └── multi_tenant_architecture/  # 멀티 테넌트 아키텍처
```

---

## 📚 **추가된 학습 주제**
- **도메인 주도 설계 (DDD)** 적용
- **고급 마이크로서비스 패턴** (Circuit Breaker, Bulkhead, Retry 등)
- **이벤트 소싱 및 CQRS** (비동기 데이터 모델링)
- **서버리스 및 엣지 컴퓨팅** (Cloudflare Workers, AWS Lambda 등)
- **Chaos Engineering & Reliability** (실전 장애 대응)
- **멀티 리전 & 글로벌 분산 시스템 설계**
- **DevSecOps 및 보안 자동화**
- **데이터 규제 및 GDPR 준수 전략**

---

## 📚 단계별 학습 내용

### 1️⃣ 시스템 설계 기초 (01_fundamentals)

#### 설계 원칙 (principles)
- SOLID 원칙의 시스템 설계 적용
  - 단일 책임 원칙 (SRP)의 시스템 레벨 적용
  - 개방-폐쇄 원칙 (OCP)을 통한 확장성 확보
  - 인터페이스 분리 원칙 (ISP)의 API 설계 적용

- 기타 핵심 원칙
  - DRY (Don't Repeat Yourself)
  - KISS (Keep It Simple, Stupid)
  - YAGNI (You Aren't Gonna Need It)

#### 디자인 패턴 (patterns)
- 생성 패턴
  - Factory Method와 마이크로서비스 생성
  - Builder 패턴과 복잡한 객체 구성
  - Singleton과 공유 리소스 관리

- 구조 패턴
  - Adapter와 레거시 시스템 통합
  - Proxy와 서비스 게이트웨이
  - Decorator와 동적 기능 확장

- 행위 패턴
  - Observer와 이벤트 기반 아키텍처
  - Strategy와 알고리즘 전략
  - Command와 작업 큐 시스템

#### 아키텍처 스타일 (architecture)
- 계층화 아키텍처
  - 프레젠테이션 계층
  - 비즈니스 계층
  - 데이터 계층
  - 각 계층 간 통신 및 의존성 관리

- 이벤트 기반 아키텍처
  - 이벤트 생산자/소비자 모델
  - 이벤트 버스 설계
  - 이벤트 소싱 패턴

### 2️⃣ 분산 시스템 (02_distributed_systems)

#### 분산 시스템 기초 (basics)
- CAP 이론 이해와 적용
  - Consistency (일관성)
  - Availability (가용성)
  - Partition Tolerance (분할 허용성)
  - 실제 시스템에서의 트레이드오프

- 분산 시스템 특성
  - 확장성 (Scalability)
  - 신뢰성 (Reliability)
  - 가용성 (Availability)
  - 성능 (Performance)
  - 관리성 (Manageability)

#### 합의 알고리즘 (consensus)
- Paxos 알고리즘
- Raft 알고리즘
- 분산 트랜잭션
  - 2PC (Two-Phase Commit)
  - 3PC (Three-Phase Commit)
  - SAGA 패턴

#### 일관성 모델 (consistency)
- 강한 일관성
- 최종 일관성
- 인과적 일관성
- 세션 일관성

### 3️⃣ 마이크로서비스 (03_microservices)

#### 마이크로서비스 패턴 (patterns)
- 서비스 분해 패턴
  - 도메인 주도 설계 (DDD) 적용
  - 서비스 경계 정의
  - 데이터 소유권 관리

- 통신 패턴
  - 동기식 통신 (REST, gRPC)
  - 비동기식 통신 (메시지 큐)
  - 이벤트 기반 통신

- 데이터 패턴
  - Database per Service
  - Shared Database
  - Event Sourcing
  - CQRS

### 4️⃣ 데이터 관리 (04_data_management)

#### 저장소 설계 (storage)
- 관계형 데이터베이스 설계
  - 샤딩 전략
  - 파티셔닝 방식
  - 복제 전략

- NoSQL 데이터베이스 활용
  - Key-Value 저장소
  - 문서형 데이터베이스
  - 칼럼형 데이터베이스
  - 그래프 데이터베이스

#### 캐싱 전략 (caching)
- 캐시 계층
  - 클라이언트 사이드 캐싱
  - CDN 캐싱
  - 애플리케이션 캐싱
  - 데이터베이스 캐싱

- 캐시 패턴
  - Cache-Aside
  - Write-Through
  - Write-Behind
  - Refresh-Ahead

### 5️⃣ 확장성 (05_scalability)

#### 수평적 확장 (horizontal)
- 로드 밸런싱
  - L4/L7 로드 밸런서
  - DNS 로드 밸런싱
  - 애플리케이션 레벨 로드 밸런싱

- 파티셔닝
  - 데이터 파티셔닝
  - 서비스 파티셔닝
  - 샤딩 전략

#### 수직적 확장 (vertical)
- 리소스 최적화
  - CPU 최적화
  - 메모리 최적화
  - I/O 최적화

- 성능 튜닝
  - 애플리케이션 프로파일링
  - 병목 지점 식별
  - 리소스 모니터링

### 6️⃣ 실전 설계 (06_real_world)

#### 사례 연구 (case_studies)
- 대규모 시스템 분석
  - Netflix 아키텍처
  - Uber 시스템 설계
  - Instagram 확장성

- 실제 문제 해결
  - URL 단축기 설계
  - 알림 시스템 설계
  - 실시간 채팅 시스템

#### 모범 사례 (best_practices)
- API 설계
  - RESTful API 설계
  - gRPC API 설계
  - GraphQL API 설계

- 보안 설계
  - 인증/인가
  - API 보안
  - 데이터 보안

## 📝 학습 진행 방식

1. 각 주제별 이론 학습
2. 작은 규모의 예제 구현
3. 실제 사례 분석 및 적용
4. 프로젝트 기반 실습
5. 설계 결정에 대한 문서화

## 🔍 평가 및 검증

- 각 단계별 미니 프로젝트 구현
- 시스템 설계 면접 문제 연습
- 실제 서비스에 대한 설계 문서 작성
- 동료 리뷰 및 피드백 수렴

## 📚 추천 학습 리소스

### 도서
- "Designing Data-Intensive Applications" by Martin Kleppmann
- "Building Microservices" by Sam Newman
- "Clean Architecture" by Robert C. Martin
- "System Design Interview" by Alex Xu

### 온라인 리소스
- System Design Primer (GitHub)
- AWS Architecture Center
- Microsoft Azure Architecture Center
- Google Cloud Architecture Center

### 실습 플랫폼
- GitHub 프로젝트
- Docker 및 Kubernetes 환경
- 클라우드 플랫폼 (AWS/GCP/Azure)