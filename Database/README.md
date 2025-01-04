# 보완/확장 계획

1. Stored Procedure, Function, Trigger의 고급 활용
    - 이미 트리거 예시는 있지만, DB별로 프로시저 작성, 에러처리(TRY/CATCH), 변수/커서 사용 등 좀 더 상세한 예시가 있으면 실무에서 써먹기 좋음.
    - Oracle의 PL/SQL, PostgreSQL의 PL/pgSQL, MSSQL의 T-SQL 등 구체적인 예시도 도움이 됨.

2. ORM과의 연계
    - JPA, Hibernate, Django ORM, SQLAlchemy, etc.
    - "SQL 짜는 관점 + ORM에서 자동 생성/최적화된 SQL 보는 관점"을 비교해보면, 실제 프로젝트 시야가 넓어짐.

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