# Database 디렉토리

이 디렉토리는 데이터베이스에 대한 기초부터 고급 주제까지 폭넓게 학습할 수 있도록 구성된 자료 모음입니다.
데이터베이스의 기본 개념, SQL 명령어, 고급 쿼리 최적화, NoSQL 및 ORM 사용법 등을 포함하여 실무와 학습에 필요한 모든 내용을 체계적으로 정리합니다.

## 디렉토리 구조

```plaintext
Database/
├── README.md                  # 데이터베이스 디렉토리 소개 및 학습 가이드
├── basic/                     # 기초 SQL 및 개념
│   ├── intro.md               # SQL 및 DBMS 소개
│   ├── commands.md            # SQL 명령어 분류 및 기본 문법
│   ├── constraints.md         # 제약 조건 (PK, FK, Unique 등)
│   ├── joins.md               # 조인의 종류와 기본 사용법
│   ├── transactions.md        # 트랜잭션과 ACID
│   └── indexing.md            # 인덱스의 기본 이해
├── advanced/                  # 고급 SQL 및 실무 기술
│   ├── optimization.md        # 쿼리 최적화 기법
│   ├── partitioning.md        # 파티셔닝과 샤딩
│   ├── replication.md         # 복제와 고가용성
│   ├── tuning.md              # 복잡 쿼리 튜닝 사례집
│   ├── materialized_views.md  # Materialized View 활용
│   └── high_availability.md   # 클러스터링과 HA 전략
├── rdbms/                     # RDBMS별 정리
│   ├── intro.md               # RDBMS 개요
│   ├── mysql.md               # MySQL: 특징과 활용 사례
│   ├── postgresql.md          # PostgreSQL: 특징과 활용 사례
│   ├── mariadb.md             # MariaDB: 특징과 활용 사례
│   └── sqlite.md              # SQLite: 특징과 활용 사례
├── orm/                       # ORM 및 언어별 실무 정리
│   ├── intro.md               # ORM의 개념과 장단점
│   ├── python-orm.md          # Python: SQLAlchemy, Django ORM
│   ├── node-orm.md            # Node.js: Sequelize, TypeORM
│   ├── go-orm.md              # Go: GORM, Ent
│   └── tips.md                # ORM 사용 시 주의점 및 성능 튜닝
├── nosql/                     # NoSQL 및 분산 DB
│   ├── intro.md               # NoSQL 개요 (MongoDB, Redis, Cassandra 등)
│   ├── mongodb.md             # MongoDB 사용법과 사례
│   ├── redis.md               # Redis: 캐싱과 데이터 저장
│   ├── cassandra.md           # Cassandra: 분산 데이터베이스
│   └── cap_theorem.md         # CAP 이론 및 Eventual Consistency
└── storage/                   # 스토리지 및 파일시스템
    ├── intro.md               # 스토리지 개요
    ├── s3.md                  # S3: 특징과 설정 방법
    ├── hdfs.md                # HDFS: 분산 파일시스템 구조
    └── ceph.md                # Ceph: 분산 오브젝트 스토리지
```

## 학습 가이드

1. **기본 디렉토리(basic/)**
    - 대상: **SQL**과 **데이터베이스**를 처음 배우는 입문자.
    - 내용:
        - SQL 및 DBMS의 기본 개념.
        - DDL, DML, DCL, TCL 명령어 분류와 기초 문법.
        - 제약 조건과 조인의 종류.
        - 트랜잭션의 ACID 특성과 인덱스의 기본 이해.

    - 추천 학습 경로:
        1. `intro.md`
        2. `commands.md`
        3. `constraints.md`
        4. `joins.md`
        5. `transactions.md`
        6. `indexing.md`

2. **고급 디렉토리(advanced/)**
    - 대상: 데이터베이스를 실무에서 활용하거나 고급 최적화 기법을 배우고자 하는 중급/고급 사용자.
    - 내용:
        - 쿼리 최적화와 인덱스 튜닝.
        - 파티셔닝과 샤딩.
        - 고가용성을 위한 복제와 클러스터링.
        - 복잡한 쿼리 튜닝 사례 및 Materialized View 활용.

    - 학습 추천 경로:
        1. `optimization.md`
        2. `partitioning.md`
        3. `replication.md`
        4. `tuning.md`
        5. `materialized_views.md`
        6. `high_availability.md`

3. **RDBMS 디렉토리(rdbms/)**
    - 대상: 주요 관계형 데이터베이스 관리 시스템(RDBMS)를 학습하고 활용하려는 사용자.
    - 내용:
        - MySQL, PostgreSQL, MariaDB, SQLite의 특징 및 사용 사례.
        - 각 RDBMS의 주요 기능 및 차별점

    - 학습 추천 경로:
        1. `intro.md`
        2. `mysql.md`
        3. `postgresql.md`
        4. `mariadb.md`
        5. `sqlite.md`

4. **ORM 디렉토리(orm/)**
    - 대상: ORM(Object-Relational Mapping)을 활용한 개발을 학습하려는 사용자.
    - 내용:
        - ORM의 개념과 실무 장단점.
        - Python(SQLAlchemy, Django ORM), Node.js(Sequelize, TypeORM), Go(GORM, Ent)의 사용법.
        - ORM 성능 최적화 및 문제 해결 팁.

5. **NoSQL 디렉토리(nosql/)**
    - 대상: NoSQL 데이터베이스의 특징과 사용법을 배우고자 하는 사용자.
    - 내용:
        - MongoDB, Redis, Cassandra의 사용 사례.
        - CAP 이론 및 Eventual Consistency 개념.

6. **스토리지 디렉토리(Storage/)**
    - 대상: 분산 스토리지와 파일 시스템의 기본 개념을 배우고자 하는 사용자.
    - 내용:
        - S3, HDFS, Ceph의 특징과 주요 활용 사례.

## 학습 및 활용 팁

1. 순차 학습: `basic/`디렉토리의 기초를 확실히 다진 후, `advanced/`로 넘어가 심화 학습.
2. 실습 추천:
    - 데이터베이스 명령어 및 쿼리를 직접 실행해보세요. (MySQL, PostgreSQL, SQLite 등 사용)
    - ORM 및 NoSQL 사례를 작은 프로젝트에 적용해 학습 효과를 높이세요.

| 제약 조건      | 설명                                          | 중복 허용 여부 | NULL 허용 여부 |
|----------------|-----------------------------------------------|----------------|----------------|
| PRIMARY KEY    | 테이블에서 각 행을 고유하게 식별               | 불가           | 불가           |
| FOREIGN KEY    | 다른 테이블의 PRIMARY KEY를 참조              | 가능           | 가능           |
| UNIQUE         | 열의 모든 값이 유일해야 함                    | 불가           | 가능           |
| NOT NULL       | 해당 열에 반드시 값이 존재해야 함             | 가능           | 불가           |
| CHECK          | 조건을 만족하는 데이터만 입력 가능            | 가능           | 가능           |
| DEFAULT        | 값이 없을 때 기본값을 설정                    | 가능           | 가능           |
| AUTO_INCREMENT | 새로운 행 추가 시 자동으로 값 증가            | 불가           | 불가           |