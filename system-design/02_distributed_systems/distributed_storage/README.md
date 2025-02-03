# 📂 분산 저장소 - distributed_storage

> **목표:**  
> - 분산 저장소(Distributed Storage)의 개념과 핵심 원리를 학습한다.  
> - NoSQL, 분산 파일 시스템, 오브젝트 스토리지 등의 다양한 저장소 기술을 이해한다.  
> - 확장성과 고가용성을 고려한 분산 저장소 시스템을 실무에 적용하는 방법을 연구한다.

---

## 📌 **디렉토리 구조**
```
distributed_storage/            # 분산 저장소 학습
├── introduction.md             # 분산 저장소 개요
├── nosql_databases.md          # NoSQL 데이터베이스 (Cassandra, DynamoDB 등)
├── distributed_file_system.md  # 분산 파일 시스템 (HDFS, Ceph 등)
├── object_storage.md           # 오브젝트 스토리지 (S3, MinIO 등)
├── storage_consistency.md      # 저장소 일관성 모델
├── distributed_storage_in_practice.md  # 실무에서의 분산 저장소 적용
└── README.md
```

---

## 📖 **1. 개념 개요**
> **분산 저장소는 여러 노드에서 데이터를 저장하고 관리하여 확장성과 가용성을 극대화하는 시스템이다.**

- ✅ **왜 중요한가?**  
  - 대량의 데이터를 효과적으로 저장하고 관리할 수 있다.
  - 장애 발생 시 데이터 유실을 방지하고 복구할 수 있다.
  - 글로벌 서비스 운영을 위한 데이터 복제 및 샤딩이 가능하다.

- ✅ **어떤 문제를 해결하는가?**  
  - 단일 노드의 저장 용량 한계를 극복
  - 데이터 정합성 유지와 고가용성 확보
  - 분산 환경에서의 성능 최적화 및 확장성 문제 해결

- ✅ **실무에서 어떻게 적용하는가?**  
  - **NoSQL 데이터베이스**를 활용한 글로벌 확장형 애플리케이션 설계
  - **분산 파일 시스템**을 이용한 대용량 데이터 처리 및 분석
  - **오브젝트 스토리지**를 사용하여 클라우드 네이티브 애플리케이션 구축

---

## 🏗 **2. 학습 내용**
### 📚 주요 학습 주제
- **분산 저장소 개요 (introduction.md)**
  - 분산 데이터 저장 개념 및 아키텍처
  - 데이터 복제 및 샤딩 전략

- **NoSQL 데이터베이스 (nosql_databases.md)**
  - Apache Cassandra, Amazon DynamoDB 등의 분산형 NoSQL DB
  - 튜너블 일관성(Tunable Consistency) 및 고가용성 전략

- **분산 파일 시스템 (distributed_file_system.md)**
  - HDFS(Hadoop Distributed File System), Ceph, GlusterFS
  - 데이터 노드 및 네임 노드 구조
  - 대용량 파일 저장 및 분석 활용 사례

- **오브젝트 스토리지 (object_storage.md)**
  - Amazon S3, Google Cloud Storage, MinIO
  - 오브젝트 스토리지의 장점과 사용 사례
  - 버전 관리 및 데이터 라이프사이클 정책

- **저장소 일관성 모델 (storage_consistency.md)**
  - 강한 일관성 vs 최종적 일관성
  - Eventual Consistency 모델 적용 방법
  - CAP/PACELC 이론과 분산 저장소

- **실무에서의 분산 저장소 적용 (distributed_storage_in_practice.md)**
  - 기업에서의 분산 저장소 사용 사례
  - 클라우드 환경(AWS, Google Cloud, Azure)에서의 데이터 저장 전략
  - 데이터 백업 및 복구 계획 수립

---

## 🚀 **3. 실전 사례 분석**
> **대규모 서비스에서 분산 저장소가 어떻게 활용되는가?**

- **Facebook** - Apache Cassandra를 이용한 대규모 데이터 저장
- **Netflix** - Amazon S3를 활용한 글로벌 콘텐츠 관리
- **Google** - Colossus 파일 시스템을 통한 분산 스토리지 운영

---

## 🎯 **4. 학습 방법**
1️⃣ 개념 이론 학습  
2️⃣ NoSQL, 분산 파일 시스템, 오브젝트 스토리지 비교 분석  
3️⃣ 실제 사례 분석  
4️⃣ 분산 저장소 시스템 설계 실습  

---

## 📚 **5. 추천 리소스**
- 📖 _Designing Data-Intensive Applications_ - Martin Kleppmann  
- 📖 _Hadoop: The Definitive Guide_ - Tom White  
- 📖 _NoSQL Distilled_ - Pramod J. Sadalage & Martin Fowler  
- 📌 [Apache Cassandra Documentation](https://cassandra.apache.org/doc/latest/)  
- 📌 [Ceph Storage Documentation](https://docs.ceph.com/en/latest/)  

---

## ✅ **마무리**
이 문서는 **분산 저장소 시스템의 핵심 개념과 실무 적용 방법을 학습하는 단계**입니다. 
이론 → 저장소 모델 학습 → 실전 사례 → 코드 실습의 흐름을 따라 학습하며, 
확장성과 가용성을 고려한 최적의 분산 저장소 시스템을 설계할 수 있도록 합니다. 🚀