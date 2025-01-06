3. 데이터베이스 설계 이론
    - 정규화/비정규화, 각 종 키(key) 정의, ERD 설계 패턴, 데이터 모델링 기법 등
    - 이미 DDL/제약조건 부분에서 어느 정도 언급했지만, 좀 더 "DB 스키마 설계" 이론에 초점을 맞춘 정리도 있으면 "DB 스키마 아키텍트" 관점에서 도움이 됨.

4. 복잡한 쿼리 튜닝 사례집
    - 쿼리 리라이팅, 조인 순서 변경, 인덱스 힌트 사용, 파티션 프루닝, Materialized View(물리화 뷰) 등
    - DB 엔진 별 성능 차이, 옵티마이저 힌트, 실행계획 캐싱(Plan Cache) 이슈 등도 고급 튜닝에서 자주 다루는 내용

5. 복제(Replication)와 고가용성(High Availability)
    - 마스터-슬레이브 복제, 클러스터링, 분산 트랜잭션, 2PC(Two Phase Commit) 등
    - 현업 시니어급으로 가면, DB 단일 노드가 아닌 "분산/고가용" 구조로 운영해야 하는 상황을 많이 만나기 때문

6. NoSQL과 비교
    - MongoDB, Redis, Cassandra 등 NoSQL에서 SQL과 어떻게 다른지, 언제 RDB vs NoSQL 쓰는지
    - MLOps나 빅데이터 엔지니어 진로라면, SQL-on-Hadoop(Spark SQL, Presto, HiveQL) 같은 빅데이터 관련 SQL 방언도 흥미로움.

7. 관계형 DB
    - SQL 최적화, 인덱스 구조(B-Tree, Hash 인덱스), 조인 전략, 트랜잭션 격리 수준 등
    - ORM(Hibernate/JPA, Sequelize, SQLAlchemy 등) 실무 사용 & 쿼리 튜닝
    - Replica, Sharding, High Availability(e.g. Galera, Aurora, Ratroni 등)

8. NoSQL / 분산 DB
    - Redis, MongoDB, Cassandra, Elasticsearch 등 사용 사례
    - CAP 이론(Consistency, Availability, Partition Tolerance), Eventual Consistency 이해
    - 데이터 모델링(문서형/키-값형/와이드 컬럼형 등)

9. 스토리지/파일 시스템
    - 객체 스토리지(S3, GCS) 특징, 업로드/다운로드 방법, 보안 설정
    - 분산 파일시스템(HDFS, Ceph, GlusterFS 등) 개념 (아주 심화까지는 아니어도 구조를 알면 좋음.)