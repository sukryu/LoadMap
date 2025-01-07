# 복잡한 쿼리 튜닝 가이드

1. 서론: 왜 복잡한 쿼리 튜닝이 중요한가?
    - 현대의 데이터베이스 시스템은 끊임없이 증가하는 데이터량과 더 빠른 응답 시간에 대한 요구를 마주하고 있습니다. 이러한 환경에서 복잡한 쿼리의 성능 튜닝은 시스템의 전반적인 성능과 사용자 경험에 결정적인 영향을 미치는 핵심 요소가 되었습니다.

    1. 고성능 요구의 증가
        1. 대규모 트래픽 처리
            - 수백만 사용자의 동시 접속 처리
            - 초당 수천 건의 트랜잭션 처리
            - 피크 시간대의 급격한 부하 증가 대응

        2. 빅데이터 분석
            - 페타바이트 규모의 데이터 처리
            - 실시간 데이터 분석과 리포팅
            - 복잡한 집계 및 통계 처리

        3. 실시간 응답 요구
            - 밀리초 단위의 응답 시간 보장
            - 지연 시간에 민감한 금융 거래
            - 실시간 추천 시스템

    2. 복잡 쿼리의 특징
        1. 다중 테이블 연산
            - 여러 테이블 간의 복잡한 조인
            - 중첩된 서브쿼리
            - 윈도우 함수와 고급 분석 기능

        2. 비즈니스 로직의 DB 내재화
            - 복잡한 비즈니스 규칙이 SQL에 포함
            - 데이터 무결성과 일관성 보장
            - 트랜잭션 처리와 동시성 제어

        3. 성능 영향 요소
            - 테이블 크기와 데이터 분포
            - 인덱스 구조와 활용
            - 시스템 리소스 제약

    3. 튜닝 전 접근 방법
        1. 특정 단계
            - 성능 지표 수집과 모니터링
            - 병목 지점 식별
            - 베이스라인 성능 측정

        2. 분석 단계
            - 실행계획 검토
            - 리소스 사용량 프로파일링
            - 문제 패턴 식별

        3. 수정 단계
            - 쿼리 리라이팅
            - 인덱스 최적화
            - 실행계획 제어

        4. 검증 단계
            - 성능 개선 측정
            - 부작용 검토
            - 스트레스 테스트

    4. 튜닝의 중요성
        - 복잡한 쿼리의 성능은 전체 시스템의 응답성과 확장성에 직접적인 영향을 미칩니다. 단일 쿼리의 비효율성이 데이터베이스 전체의 병목이 되어 시스템 전반의 성능을 저하시킬 수 있습니다. 따라서 체계적이고 효과적인 쿼리 튜닝은 현대 데이터베이스 시스템에서 필수적인 요소입니다.

        1. 비즈니스 영향
            - 사용자 경험 향상
            - 운영 비용 절감
            - 시스템 확장성 확보

        2. 기술적 영향
            - 리소스 효율성 증대
            - 시스템 안정성 향상
            - 유지보수성 개선

2. 튜닝 전 준비: 모니터링과 실행계획 분석
    - 효과적인 쿼리 튜닝을 위해서는 현재 시스템의 상태를 정확히 파악하고, 문제가 되는 쿼리를 식별하며, 그 쿼리의 실행 특성을 이해하는 것이 중요합니다. 이를 위한 체계적인 접근 방법을 살펴보겠습니다.

    1. 쿼리 로깅과 프로파일링
        1. DB 엔진별 쿼리 로그 설정
            1. MySQL
                ```sql
                -- 슬로우 쿼리 로그 활성화
                SET GLOBAL slow_query_log = 'ON';
                SET GLOBAL long_query_time = 1;  -- 1초 이상 걸리는 쿼리 기록
                SET GLOBAL slow_query_log_file = '/var/log/mysql/slow-query.log';

                -- 일반 쿼리 로그 (개발환경에서만 권장)
                SET GLOBAL general_log = 'ON';
                ```

            2. PostgreSQL
                ```sql
                -- 슬로우 쿼리 로깅 설정
                ALTER SYSTEM SET log_min_duration_statement = '1000';  -- 1초(1000ms)
                ALTER SYSTEM SET log_line_prefix = '%t [%p]: [%l-1] user=%u,db=%d ';
                ```

            3. Oracle
                ```sql
                -- 트레이스 파일 생성
                ALTER SESSION SET TIMED_STATISTICS = TRUE;
                ALTER SESSION SET MAX_DUMP_FILE_SIZE = UNLIMITED;
                ALTER SESSION SET EVENTS '10046 TRACE NAME CONTEXT FOREVER, LEVEL 12';
                ```

        2. 애플리케이션 레벨 SQL 로깅
            1. Java/Hibernate
                ```properties
                # application.properties
                logging.level.org.hibernate.SQL=DEBUG
                logging.level.org.hibernate.type.descriptor.sql.BasicBinder=TRACE
                ```

            2. Python/SQLAlchemy
                ```python
                import logging
                logging.basicConfig()
                logging.getLogger('sqlalchemy.engine').setLevel(logging.INFO)
                ```

    2. 실행계획(EXPLAIN) 분석
        1. 기본 실행계획 확인
            1. MySQL
                ```sql
                EXPLAIN SELECT * FROM orders o
                JOIN customers c ON o.customer_id = c.id
                WHERE o.status = 'PENDING'
                AND c.country = 'USA';
                ```

            2. PostgreSQL
                ```sql
                EXPLAIN ANALYZE SELECT * FROM orders o
                JOIN customers c ON o.customer_id = c.id
                WHERE o.status = 'PENDING'
                AND c.country = 'USA';
                ```

        2. 주요 성능 지표 해석
            * 접근 방식
                - Table Scan: 전체 테이블 스캔
                - Index Scan: 인덱스를 사용한 스캔
                - Index Seek: 인덱스를 통한 직접 접근

            * 조인 방식
                - Nested Loop Join: 작은 데이터셋에 효과적
                - Hash Join: 대량 데이터 조인에 유리
                - Merge Join: 정렬된 데이터셋 조인에 적합

            * 비용 추정
                - cost: 쿼리 실행의 상대적 비용
                - rows: 처리될 것으로 예상되는 행 수
                - actual time: 실제 실행 시간 (EXPLAIN ANALYZE)

        3. DB 모니터링 도구 활용
            1. MySQL 모니터링
                - MySQL Workbench
                - Performance Schema
                - Percona Monitoring and Management (PMM)

                ```sql
                -- Performance Schema 활성화
                UPDATE performance_schema.setup_instruments 
                SET ENABLED = 'YES', TIMED = 'YES';

                -- 테이블 별 I/O 통계
                SELECT * FROM performance_schema.table_io_waits_summary_by_table
                WHERE COUNT_STAR > 0;
                ```

            2. PostgreSQL 모니터링
                - pgAdmin
                - pg_stat_statements
                - pganalyze

                ```sql
                -- pg_stat_statements 설치 및 활성화
                CREATE EXTENSION pg_stat_statements;

                -- 가장 많은 시간을 소비하는 쿼리 확인
                SELECT query, calls, total_time, rows
                FROM pg_stat_statements
                ORDER BY total_time DESC
                LIMIT 10;
                ```

        4. 핵심 성능 지표 모니터링
            1. 시스템 레벨 지표
                - CPU 사용률
                - 디스크 I/O
                - 메모리 사용량
                - 네트워크 대역폭

            2. 데이터베이스 지표
                - 초당 쿼리 수 (QPS)
                - 초당 트랜잭션 수 (TPS)
                - 캐시 히트율
                - 락 경합 상태
                - 활성 세션 수

            3. 쿼리 별 지표
                - 실행 시간
                - 리소스 사용량
                - 대기 이벤트
                - 버퍼 풀 활용도

        5. 성능 데이터 수집과 분석
            1. 데이터 수집 주기
                - 실시간 모니터링 (1 ~ 5초 간격)
                - 단기 트렌드 (분 단위)
                - 장기 트렌드 (시간/일 단위)

            2. 문제 쿼리 식별
                - 실행 시간이 긴 쿼리
                - 자주 실행되는 쿼리
                - 리소스 사용량이 많은 쿼리
                - 락을 오래 보유하는 쿼리

            3. 분석 보고서 작성
                - 현재 성능 상태
                - 주요 문제점
                - 개선 필요 사항
                - 우선 순위 설정

3. 쿼리 리라이팅(Query Rewriting) 기법
    - 쿼리 리라이팅은 SQL 쿼리의 논리적 동등성을 유지하면서 성능을 개선하는 기법입니다. 이 장에서는 다양한 쿼리 리라이팅 패턴과 각각의 적용 시점을 살펴보겠습니다.

    1. 불필요한 요소 제거
        1. SELECT 절 최적화
            ```sql
            -- 비효율적인 쿼리
            SELECT * 
            FROM orders o
            JOIN customers c ON o.customer_id = c.id;

            -- 최적화된 쿼리
            SELECT o.order_id, o.order_date, c.name
            FROM orders o
            JOIN customers c ON o.customer_id = c.id;
            ```

        2. 불필요한 조인 제거
            ```sql
            -- 비효율적인 쿼리
            SELECT o.order_id, o.order_date
            FROM orders o
            JOIN customers c ON o.customer_id = c.id
            JOIN addresses a ON c.id = a.customer_id;

            -- 최적화된 쿼리 (addresses 테이블 불필요)
            SELECT o.order_id, o.order_date
            FROM orders o
            JOIN customers c ON o.customer_id = c.id;
            ```
        
    2. OR 조건의 UNION 변환
        1. 기존 변환 패턴
            ```sql
            -- OR 사용 쿼리
            SELECT * 
            FROM orders 
            WHERE status = 'PENDING' OR status = 'PROCESSING';

            -- UNION ALL 사용 쿼리
            SELECT * FROM orders WHERE status = 'PENDING'
            UNION ALL
            SELECT * FROM orders WHERE status = 'PROCESSING';
            ```

        2. 복합 조건에서의 변환
            ```sql
            -- 복잡한 OR 조건
            SELECT * 
            FROM orders 
            WHERE (status = 'PENDING' AND amount > 1000)
            OR (status = 'PROCESSING' AND amount > 500);

            -- UNION ALL로 분리
            SELECT * FROM orders 
            WHERE status = 'PENDING' AND amount > 1000
            UNION ALL
            SELECT * FROM orders 
            WHERE status = 'PROCESSING' AND amount > 500;
            ```

    3. 서브쿼리 최적화
        1. 상관 서브쿼리를 조인으로 변환
            ```sql
            -- 상관 서브쿼리
            SELECT *
            FROM orders o
            WHERE amount > (
                SELECT AVG(amount)
                FROM orders
                WHERE customer_id = o.customer_id
            );

            -- 조인으로 변환
            SELECT o.*
            FROM orders o
            JOIN (
                SELECT customer_id, AVG(amount) as avg_amount
                FROM orders
                GROUP BY customer_id
            ) avg_orders ON o.customer_id = avg_orders.customer_id
            WHERE o.amount > avg_orders.avg_amount;
            ```

        2. IN절을 JOIN으로 변환
            ```sql
            -- IN 사용
            SELECT * 
            FROM orders 
            WHERE customer_id IN (
                SELECT id 
                FROM customers 
                WHERE country = 'USA'
            );

            -- JOIN 사용
            SELECT DISTINCT o.*
            FROM orders o
            JOIN customers c ON o.customer_id = c.id
            WHERE c.country = 'USA';
            ```

    4. GROUP BY와 DISTINCT 최적화
        1. DISTINCT 대체
            ```sql
            -- DISTINCT 사용
            SELECT DISTINCT customer_id
            FROM orders;

            -- GROUP BY로 대체
            SELECT customer_id
            FROM orders
            GROUP BY customer_id;
            ```

        2. 집계 함수 최적화
            ```sql
            -- 비효율적인 집계
            SELECT COUNT(DISTINCT customer_id)
            FROM orders;

            -- 최적화된 집계
            SELECT COUNT(*)
            FROM (
                SELECT customer_id
                FROM orders
                GROUP BY customer_id
            ) t;
            ```

    5. 조건절 최적화
        1. 인덱스 활용을 위한 조건절 재작성
            ```sql
            -- 인덱스를 활용하지 못하는 조건
            SELECT * FROM orders
            WHERE YEAR(order_date) = 2023;

            -- 인덱스를 활용하는 조건
            SELECT * FROM orders
            WHERE order_date >= '2023-01-01'
            AND order_date < '2024-01-01';
            ```

        2. 범위 조건 최적화
            ```sql
            -- 비효율적인 범위 조건
            SELECT * FROM products
            WHERE price BETWEEN 100 AND 200
            OR price BETWEEN 300 AND 400;

            -- 최적화된 범위 조건
            SELECT * FROM products WHERE price BETWEEN 100 AND 200
            UNION ALL
            SELECT * FROM products WHERE price BETWEEN 300 AND 400;
            ```

    6. 애플리케이션 레벨 처리 활용
        1. 페이징 처리 최적화
            ```sql
            -- 비효율적인 페이징
            SELECT * FROM orders
            ORDER BY order_date DESC
            LIMIT 10 OFFSET 1000000;

            -- 최적화된 페이징 (키셋 페이지네이션)
            SELECT * FROM orders
            WHERE order_date < :last_seen_date
            ORDER BY order_date DESC
            LIMIT 10;
            ```

        2. 데이터 가공 위치 선택
            ```sql
            -- DB에서 문자열 처리
            SELECT CONCAT(first_name, ' ', last_name) as full_name
            FROM customers;

            -- 애플리케이션에서 처리
            SELECT first_name, last_name FROM customers;
            -- Application: fullName = firstName + " " + lastName;
            ```

    7. 리라이팅 시 고려사항
        1. 성능 영향 요소
            - 데이터 분포도
            - 인덱스 활용 가능성
            - 실행 계획의 변화
            - 캐시 효율성

        2. 주의사항
            - 논리적 동등성 유지
            - 트랜잭션 일관성 보장
            - 가독성과 유지보수성 고려
            - 데이터베이스 특성 고려

4. 조인 순서 변경과 인덱스 힌트 사용
    - 데이터베이스의 쿼리 옵티마이저가 항상 최적의 실행 계획을 선택하는 것은 아닙니다. 일언 경우 조인 순서를 명시적으로 지정하거나 인덱스 힌트를 사용하여 성능을 개선할 수 있습니다.

    1. 조인 순서의 중요성
        1. 기본 원칙
            - 작은 결과 집합을 먼저 처리
            - 필터링이 많이 되는 테이블을 우선 접근
            - 조인 조건이 있는 테이블 순서로 접근

        2. 잘못된 조인 순서의 영향
            ```sql
            -- 비효율적인 조인 순서 (큰 테이블 먼저 접근)
            SELECT o.*, c.name
            FROM orders o          -- 1,000,000 rows
            JOIN customers c       -- 10,000 rows
            ON o.customer_id = c.id
            WHERE c.country = 'USA';  -- 1,000 rows

            -- 실행 과정:
            -- 1. orders 테이블 전체 스캔 (1,000,000 rows)
            -- 2. 각 주문에 대해 customers 테이블 조인
            -- 3. country 필터링
            ```

    2. 조인 순서 제어
        1. MySQL의 STRAIGHT_JOIN
            ```sql
            -- 명시적 조인 순서 지정
            SELECT STRAIGHT_JOIN c.name, o.*
            FROM customers c      -- 먼저 처리됨
            JOIN orders o
            ON c.id = o.customer_id
            WHERE c.country = 'USA';
            ```

        2. Oracle의 LEADING 힌트
            ```sql
            -- Oracle에서 조인 순서 지정
            SELECT /*+ LEADING(c o) */ c.name, o.*
            FROM customers c
            JOIN orders o ON c.id = o.customer_id
            WHERE c.country = 'USA';
            ```

        3. PosgreSQL의 JOIN_ORDER 제어
            ```sql
            -- PostgreSQL에서 조인 순서 제어
            SET enable_nestloop = off;
            SELECT c.name, o.*
            FROM customers c
            JOIN orders o ON c.id = o.customer_id
            WHERE c.country = 'USA';
            ```

    3. 조인 방식 제어
        1. Nested Loop Join
            ```sql
            -- MySQL에서 Nested Loop Join 강제
            SELECT /*+ NL_JOIN(c o) */ c.name, o.*
            FROM customers c
            JOIN orders o ON c.id = o.customer_id
            WHERE c.country = 'USA';

            -- Oracle에서 Nested Loop Join 강제
            SELECT /*+ USE_NL(c o) */ c.name, o.*
            FROM customers c
            JOIN orders o ON c.id = o.customer_id
            WHERE c.country = 'USA';
            ```

        2. Hash Join
            ```sql
            -- MySQL에서 Hash Join 강제
            SELECT /*+ HASH_JOIN(c o) */ c.name, o.*
            FROM customers c
            JOIN orders o ON c.id = o.customer_id;

            -- Oracle에서 Hash Join 강제
            SELECT /*+ USE_HASH(c o) */ c.name, o.*
            FROM customers c
            JOIN orders o ON c.id = o.customer_id;
            ```

        3. Merge Join
            ```sql
            -- Oracle에서 Merge Join 강제
            SELECT /*+ USE_MERGE(c o) */ c.name, o.*
            FROM customers c
            JOIN orders o ON c.id = o.customer_id;
            ```

    4. 인덱스 힌트 활용
        1. 인덱스 강제 사용
            ```sql
            -- MySQL에서 특정 인덱스 사용 강제
            SELECT /*+ INDEX(c idx_customer_country) */ *
            FROM customers c
            WHERE country = 'USA';

            -- Oracle에서 특정 인덱스 사용 강제
            SELECT /*+ INDEX(c idx_customer_country) */ *
            FROM customers c
            WHERE country = 'USA';
            ```

        2. 인덱스 사용 제외
            ```sql
            -- MySQL에서 인덱스 사용 방지
            SELECT /*+ IGNORE_INDEX(c idx_customer_country) */ *
            FROM customers c
            WHERE country = 'USA';

            -- Oracle에서 인덱스 사용 방지
            SELECT /*+ NO_INDEX(c idx_customer_country) */ *
            FROM customers c
            WHERE country = 'USA';
            ```

    5. 병렬 처리 힌트
        1. Oracle 병렬 처리
            ```sql
            -- 테이블 병렬 읽기
            SELECT /*+ PARALLEL(c 4) */ *
            FROM customers c;

            -- 전체 쿼리 병렬 처리
            SELECT /*+ PARALLEL(4) */ c.name, o.*
            FROM customers c
            JOIN orders o ON c.id = o.customer_id;
            ```

        2. PostgreSQL 병렬 처리
            ```sql
            -- 병렬 처리 워커 수 설정
            SET max_parallel_workers_per_gather = 4;
            SET parallel_tuple_cost = 100;
            SET min_parallel_table_scan_size = '8MB';
            ```

    6. 힌트 사용 시 주의사항
        1. 일반적인 고려사항
            - 힌트는 최후의 수단으로 사용
            - 데이터 분포도 변화에 취약
            - 버전 업그레이드 시 영향 가능성
            - 유지보수성 저하 가능성

        2. 모니터링과 검증
            - 실행 계획 변경 확인
            - 성능 지표 측정
            - 부작용 모니터링
            - 장기적인 재검토

5. 파티션 프루닝(Partition Pruning)
    - 파티션 프루닝은 대용량 테이블에서 필요한 파티션만을 선택적으로 접근하여 성능을 향상시키는 기법입니다. 이 장에서는 효과적인 파티셔닝 전략과 프루닝 최적화 방법을 살펴보겠습니다.

    1. 파티셔닝 기본 개념
        1. 파티셔닝의 목적
            - 대용량 테이블의 관리 용이성 향상
            - 쿼리 성능 개선
            - 데이터 가용성 증가
            - 백업/복구 효율성 향상

        2. 파티션 유형
            ```sql
            -- 범위 파티셔닝 (Range Partitioning)
            CREATE TABLE orders (
                order_id INT,
                order_date DATE,
                amount DECIMAL(10,2)
            ) PARTITION BY RANGE (YEAR(order_date)) (
                PARTITION p2021 VALUES LESS THAN (2022),
                PARTITION p2022 VALUES LESS THAN (2023),
                PARTITION p2023 VALUES LESS THAN (2024),
                PARTITION p_future VALUES LESS THAN MAXVALUE
            );

            -- 리스트 파티셔닝 (List Partitioning)
            CREATE TABLE customers (
                customer_id INT,
                country VARCHAR(2),
                name VARCHAR(100)
            ) PARTITION BY LIST (country) (
                PARTITION p_asia VALUES IN ('KR', 'JP', 'CN'),
                PARTITION p_europe VALUES IN ('FR', 'DE', 'UK'),
                PARTITION p_america VALUES IN ('US', 'CA', 'BR')
            );

            -- 해시 파티셔닝 (Hash Partitioning)
            CREATE TABLE transactions (
                tx_id INT,
                customer_id INT,
                amount DECIMAL(10,2)
            ) PARTITION BY HASH (customer_id)
            PARTITIONS 4;
            ```

    2. 효과적인 프루닝 전략
        1. 파티션 키 선택
            ```sql
            -- 좋은 예: 파티션 키를 직접 비교
            SELECT * FROM orders
            WHERE order_date >= '2023-01-01'
            AND order_date < '2024-01-01';

            -- 나쁜 예: 파티션 키에 함수 사용
            SELECT * FROM orders
            WHERE YEAR(order_date) = 2023;  -- 프루닝 불가능
            ```

        2. 복합 키 파티셔닝
            ```sql
            -- 범위-리스트 복합 파티셔닝
            CREATE TABLE sales (
                sale_id INT,
                sale_date DATE,
                region VARCHAR(2),
                amount DECIMAL(10,2)
            ) PARTITION BY RANGE (YEAR(sale_date))
            SUBPARTITION BY LIST (region) (
                PARTITION p2023 VALUES LESS THAN (2024) (
                    SUBPARTITION p2023_asia VALUES IN ('KR', 'JP', 'CN'),
                    SUBPARTITION p2023_europe VALUES IN ('FR', 'DE', 'UK')
                ),
                PARTITION p2024 VALUES LESS THAN (2025) (
                    SUBPARTITION p2024_asia VALUES IN ('KR', 'JP', 'CN'),
                    SUBPARTITION p2024_europe VALUES IN ('FR', 'DE', 'UK')
                )
            );
            ```

    3. 프루닝 확인과 모니터링
        1. 실행 계획 분석
            ```sql
            -- MySQL에서 파티션 프루닝 확인
            EXPLAIN PARTITIONS
            SELECT * FROM orders
            WHERE order_date BETWEEN '2023-01-01' AND '2023-12-31';

            -- Oracle에서 파티션 프루닝 확인
            SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY_CURSOR(FORMAT=>'BASIC +PARTITION'));

            -- PostgreSQL에서 파티션 프루닝 확인
            EXPLAIN (ANALYZE, VERBOSE)
            SELECT * FROM orders
            WHERE order_date BETWEEN '2023-01-01' AND '2023-12-31';
            ```

        2. 프루닝 효율성 모니터링
            ```sql
            -- MySQL에서 파티션 사용량 확인
            SELECT PARTITION_NAME, TABLE_ROWS, AVG_ROW_LENGTH
            FROM information_schema.PARTITIONS
            WHERE TABLE_NAME = 'orders';

            -- Oracle에서 파티션 통계 확인
            SELECT PARTITION_NAME, NUM_ROWS, BLOCKS
            FROM USER_TAB_PARTITIONS
            WHERE TABLE_NAME = 'ORDERS';
            ```

    4. 동적 파티션 관리
        1. 파티션 추가 및 삭제
            ```sql
            -- MySQL에서 새 파티션 추가
            ALTER TABLE orders
            ADD PARTITION (
                PARTITION p2025 VALUES LESS THAN (2026)
            );

            -- 오래된 파티션 삭제
            ALTER TABLE orders
            DROP PARTITION p2021;
            ```

        2. 파티션 분할 및 병합
            ```sql
            -- Oracle에서 파티션 분할
            ALTER TABLE orders SPLIT PARTITION p2023 AT ('2023-07-01')
            INTO (PARTITION p2023_h1, PARTITION p2023_h2);

            -- 파티션 병합
            ALTER TABLE orders
            MERGE PARTITIONS p2021, p2022
            INTO PARTITION p_archive;
            ```

    5. 프루닝 최적화 사례
        1. 날짜 기반 프루닝
            ```sql
            -- 효과적인 프루닝 예시
            CREATE TABLE logs (
                log_id INT,
                log_date TIMESTAMP,
                message TEXT
            ) PARTITION BY RANGE (UNIX_TIMESTAMP(log_date)) (
                PARTITION p_last_month VALUES LESS THAN (UNIX_TIMESTAMP('2024-01-01')),
                PARTITION p_current VALUES LESS THAN (UNIX_TIMESTAMP('2024-02-01')),
                PARTITION p_future VALUES LESS THAN MAXVALUE
            );

            -- 특정 기간 로그 조회
            SELECT * FROM logs
            WHERE log_date BETWEEN '2024-01-01' AND '2024-01-31';
            ```

        2. 지역 기반 프루닝
            ```sql
            -- 지역별 데이터 분리
            CREATE TABLE sales (
                sale_id INT,
                region_code CHAR(2),
                amount DECIMAL(10,2)
            ) PARTITION BY LIST (region_code) (
                PARTITION p_domestic VALUES IN ('KR'),
                PARTITION p_overseas VALUES IN ('US', 'JP', 'CN'),
                PARTITION p_others VALUES DEFAULT
            );

            -- 국내 판매 데이터만 조회
            SELECT * FROM sales
            WHERE region_code = 'KR';
            ```

    6. 주의사항과 제약사항
        1. 파티셔닝 제약사항
            - 파티션 키 선택의 제한
            - 외래 키 제약 조건의 제약
            - 파티션 개수의 제한
            - UNIQUE 제약조건의 제한

        2. 성능 고려사항
            - 파티션 수가 많을 때의 관리 비용
            - 파티션 간 데이터 이동의 부하
            - 전체 파티션 스캔이 필요한 쿼리의 성능
            - 파티션 테이블의 인덱스 전략