# 📂 **05_scalability (확장성)**
> **목표:**  
> - **시스템의 성능을 유지하면서 확장하는 방법**을 학습한다.  
> - **수평/수직 확장, 로드 밸런싱, 멀티 리전, 서버리스 아키텍처** 등의 확장성 패턴을 익힌다.  
> - 실무에서 **대규모 트래픽을 처리하는 아키텍처**를 설계하는 방법을 배운다.

---

## 📌 **디렉토리 구조 및 학습 내용**
```
scalability/
├── horizontal/                # 수평적 확장
├── vertical/                  # 수직적 확장
├── patterns/                  # 확장성 패턴
├── load_balancing/            # 로드 밸런싱
├── multi_region/              # 멀티 리전 아키텍처
├── edge_computing/            # 엣지 컴퓨팅
├── serverless_architecture/   # 서버리스 아키텍처
└── real_world_examples/       # 실전 사례 분석
```

---

## 📖 **1. 수평적 확장 (horizontal/)**
> 여러 개의 서버를 추가하여 확장하는 방식 학습  

### 📚 학습 내용
- **Horizontal Scaling (수평적 확장)**
  - 트래픽 증가 시 서버를 추가하여 처리 성능 향상
  - 실무 적용: **웹 서버 클러스터링 (NGINX, HAProxy)**

- **Stateless vs Stateful Services**
  - 무상태(stateless) 서비스가 확장성에 유리한 이유
  - 실무 적용: **JWT 기반 인증, 세션 공유 아키텍처**

- **Auto-Scaling (자동 확장)**
  - 필요할 때만 인스턴스를 추가하는 방식
  - 실무 적용: **AWS Auto Scaling, Kubernetes HPA**

---

## 📖 **2. 수직적 확장 (vertical/)**
> 더 강력한 서버로 교체하여 성능을 높이는 방식 학습  

### 📚 학습 내용
- **Vertical Scaling (수직적 확장)**
  - CPU, RAM, 디스크 업그레이드를 통해 성능 향상
  - 실무 적용: **데이터베이스 서버에서의 활용 (MySQL, PostgreSQL)**

- **Scaling Up vs Scaling Out**
  - 언제 수직 확장을 하고 언제 수평 확장을 해야 하는가?
  - 실무 적용: **Monolithic 서비스의 단점 보완 방법**

- **Bottleneck Identification (병목 지점 분석)**
  - 성능 저하 원인을 찾고 해결하는 방법
  - 실무 적용: **프로파일링 도구 활용 (New Relic, Datadog)**

---

## 📖 **3. 확장성 패턴 (patterns/)**
> 대규모 시스템에서 활용되는 확장성 패턴 학습  

### 📚 학습 내용
- **Database Sharding (DB 샤딩)**
  - 데이터를 여러 개의 DB로 나누어 저장
  - 실무 적용: **SNS, 쇼핑몰 등의 대용량 데이터 처리**

- **Read-Write Splitting (읽기-쓰기 분리)**
  - 읽기 요청과 쓰기 요청을 다른 DB로 처리
  - 실무 적용: **Master-Slave Replication 활용**

- **Microservices & Event-Driven Scaling**
  - 독립적인 마이크로서비스를 사용해 시스템 확장
  - 실무 적용: **Kafka를 활용한 이벤트 기반 확장**

---

## 📖 **4. 로드 밸런싱 (load_balancing/)**
> 서버 간 부하를 분산하여 안정적인 서비스 제공  

### 📚 학습 내용
- **Layer 4 vs Layer 7 Load Balancing**
  - 네트워크 계층별 로드 밸런싱 차이점
  - 실무 적용: **NGINX, AWS ALB, Google Load Balancer**

- **Round Robin vs Least Connections**
  - 트래픽을 분산하는 다양한 로드 밸런싱 알고리즘
  - 실무 적용: **클라우드 로드 밸런서 설정 방법**

- **Global Load Balancing (글로벌 로드 밸런싱)**
  - 여러 지역에 분산된 서버로 트래픽 자동 라우팅
  - 실무 적용: **Cloudflare, AWS Route 53 활용**

---

## 📖 **5. 멀티 리전 아키텍처 (multi_region/)**
> 여러 데이터 센터를 활용하여 장애 대비 및 성능 최적화  

### 📚 학습 내용
- **Multi-Region Deployment (멀티 리전 배포)**
  - 서비스 장애에 대비한 리전 간 복제 전략
  - 실무 적용: **Netflix의 멀티 리전 아키텍처**

- **Data Replication Across Regions**
  - 데이터 동기화 및 복제 방식 비교
  - 실무 적용: **AWS Aurora Multi-Region DB**

- **Traffic Routing & GeoDNS**
  - 사용자의 위치에 따라 최적의 서버로 라우팅
  - 실무 적용: **Cloudflare Anycast, AWS Global Accelerator**

---

## 📖 **6. 엣지 컴퓨팅 (edge_computing/)**
> 데이터 처리를 사용자 가까운 곳에서 수행하여 성능 향상  

### 📚 학습 내용
- **What is Edge Computing? (엣지 컴퓨팅이란?)**
  - 중앙 서버가 아닌 분산된 노드에서 데이터 처리
  - 실무 적용: **5G 네트워크 기반 IoT 아키텍처**

- **CDN (Content Delivery Network)**
  - 정적 콘텐츠를 사용자 근처의 서버에서 제공
  - 실무 적용: **AWS CloudFront, Cloudflare CDN**

- **Edge AI & IoT Integration**
  - 엣지 디바이스에서 AI 모델 실행
  - 실무 적용: **스마트 홈, 자율주행 시스템**

---

## 📖 **7. 서버리스 아키텍처 (serverless_architecture/)**
> 서버 관리 없이 자동 확장되는 아키텍처 학습  

### 📚 학습 내용
- **What is Serverless? (서버리스란?)**
  - 서버 운영 없이 코드 실행
  - 실무 적용: **AWS Lambda, Google Cloud Functions**

- **Event-Driven Computing**
  - 요청이 있을 때만 실행되는 함수 기반 아키텍처
  - 실무 적용: **S3 파일 업로드 후 자동 처리**

- **Serverless vs Containers**
  - 서버리스와 컨테이너 기반 아키텍처 비교
  - 실무 적용: **Kubernetes + Knative 활용**

---

## 📖 **8. 실전 사례 분석 (real_world_examples/)**
> 실제 기업들이 확장성을 어떻게 해결했는지 학습  

### 📚 학습 내용
- **Netflix의 대규모 트래픽 처리 방식**
- **Amazon의 글로벌 로드 밸런싱 전략**
- **Google Spanner의 멀티 리전 데이터베이스 설계**
- **Uber의 수평 확장 및 자동 스케일링 적용**
- **Cloudflare의 엣지 네트워크 아키텍처**