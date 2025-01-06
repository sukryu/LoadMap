# SQL

## SQL 이란?

SQL(Structured Query Language)은 데이터베이스를 관리하고 조작하기 위한 표준 언어입니다.
1974년 IBM에서 처음 개발되었고, 현재는 거의 모든 데이터베이스 시스템에서 사용되고 있습니다.

쉽게 설명하자면, SQL은 데이터베이스와 "대화"하는 언어입니다. 마치 가게 점원에게 "빨간색 티셔츠 주세요"
라고 요청하는 것처럼, 데이터베이스에 "모든 고객의 이름을 보여주세요"같은 요청을 할 수 있습니다.

## 데이터베이스와 DBMS

- 데이터베이스: 체계적으로 저장된 데이터의 모음
    - 예: 학교의 학생 명부, 온라인 쇼핑몰의 상품 목록

- DBMS(Database Management System): 데이터베이스를 관리하는 소프트웨어
    - 예: MySQL, PostgreSQL, Oracle 등

생각해보면 엑셀도 일종의 데이터베이스입니다. 하지만 대량의 데이터를 더 효율적으로 관리하고,
여러 사람이 동시에 사용할 수 있도록 만든 것이 DBMS입니다.

## SQL 명령어 분류

- SQL 명령어는 용도에 따라 크게 4가지로 나눕니다.

    1. DDL(Data Definition Language): 데이터 정의어
        - 데이터베이스의 구조를 만들고 변경하는 명령어
        - 주요 명령어: `CREATE`, `ALTER`, `DROP`, `TRUNCATE`

        ```sql
        CREATE TABLE student (
        id INT,
        name VARCHAR(50),
        grade INT,
        );
        ```

    2. DML(Data Manipulation Language): 데이터 조작어
        - 데이터를 조회하고 변경하는 명령어
        - 주요 명령어: `SELECT`, `INSERT`, `UPDATE`, `DELETE`

        ```sql
        SELECT name FROM student;
        INSERT INTO student VALUES (1001, '김철수', 1);
        ```

    3. DCL(Data Control Language): 데이터 제어어
        - 데이터베이스 접근 권한을 관리하는 명령어
        - 주요 명령어: `GRANT`,` REVOKE`

        ```sql
        GRANT SELECT ON 학생 TO 사용자1;
        ```

    4. TCL(Transaction Control Language): 트랜잭션 제어어
        - 데이터베이스 변경사항을 관리하는 명령어
        - 주요 명령어: `COMMIT`, `ROLLBACK`

        ```sql
        BEGIN;
        UPDATE account SET money = money - 1000 WHERE account_number = '1234';
        COMMIT;
        ```

## 기본 명령어 상세 설명

1. SELECT 문 기본 구조
  ```sql
  SELECT 열이름 FROM 테이블이름 WHERE 조건;
  ```

  - 가장 기본적인 데이터 조회 명령어
  - 예시:
    ```sql
    -- 모든 학생의 모든 정보 조회
    SELECT * FROM 학생;

    -- 학생의 이름과 학년만 조회
    SELECT 이름, 학년 FROM 학생;
    ```

2. WHERE 절 사용하기
  - 특정 조건에 맞는 데이터만 사용
  ```sql
  -- 1학년 학생만 조회
  SELECT * FROM 학생 WHERE 학년 = 1;
  -- 김씨 성을 가진 학생만 조회
  SELECT * FROM 학생 WHERE 이름 LIKE '김%';
  ```

3. ORDER BY로 정렬하기
    - 결과를 특정 기준으로 정렬
    ```sql
    -- 학년 순으로 정렬
    SELECT * FROM 학생 ORDER BY 학년 ASC -- 오름순순
    SELECT * FROM 학생 ORDER BY 학년 DESC -- 내림차순
    ```

4. LIMIT과 OFFSET
    - 결과의 개수를 제한하거나 특정 위치부터 조회
    ```sql
    -- 상위 5명만 조회
    SELECT * FROM 학생 LIMIT 5;

    -- 6번째부터 10번째 학생 조회
    SELECT * FROM 학생 LIMIT 5 OFFSET 5;
    ```

5. DISTINCT로 중복 제거
    - 중복된 값을 제거하고 유니크한 값만 조회
    ```sql
    -- 학년 종류만 조회 (중복 제거)
    SELECT DISTINCT 학년 FROM 학생;
    ```

## 데이터 정의 언어(DDL)과 테이블 관리

1. 테이블 생성 (CREATE TABLE)
    - 기본 문법
    ```sql
    CREATE TABLE 테이블이름 (
        열이름1 데이터타입 [제약조건],
        열이름2 데이터타입 [제약조건],
        ...
    );
    ```

    - 실제 예시:
    ```sql
    CREATE TABLE 학생 (
        학번 INT PRIMARY KEY AUTO_INCREMENT,
        이름 VARCHAR(50) NOT NULL,
        생년월일 DATE,
        학과_코드 VARCHAR(10),
        입학일 DATE DEFAULT CURRENT_DATE,
        평균성적 DECIMAL(3, 2)
    );
    ```

2. 테이블 삭제와 비우기
    1. DROP TABLE: 테이블 자체를 삭제
        ```sql
        DROP TABLE 학생; -- 테이블 완전 삭제
        DROP TABLE IF EXISTS 학생; -- 있을 경우에만 삭제
        ``` 

    2. TRUNCATE TABLE: 테이블 구조는 남기고 데이터만 삭제
        ```sql
        TRUNCATE TABLE 학생;
        ```

3. 테이블 수정(ALTER TABLE)
    1. 열 추가
        ```sql
        ALTER TABLE 학생 ADD COLUMN 이메일 VARCHAR(100);
        ```

    2. 열 수정
        ```sql
        ALTER TABLE 학생 MODIFY COLUMN 이름 VARCHAR(100);
        ```

    3. 열 이름 변경
        ```sql
        ALtER TABLE 학생 RENAME COLUMN 이멜 TO 이메일주소;
        ```

    4. 열 삭제
        ```sql
        ALTER TABLE 학생 DROP COLUMN 이메일;
        ```

4. 주요 데이터 타입
    1. 숫자형
        - INT: 정수 (-2,147,483,648 ~ 2,147,483,647)
        - BIGINT: 큰 정수
        - DECIMAL: (전체자릿수, 소수자릿수): 정확한 소수
        - FLOAT/DOUBLE: 부동소수점

    2. 문자형
        - CHAR(n): 고정 길이 문자열
        - VARCHAR(n): 가변 길이 문자열
        - TEXT: 긴 텍스트

    3. 날짜/시간형
        - DATE: 날짜(YYYY-MM-DD)
        - TIME: 시간(HH:MM:SS)
        - DATETIME: 날짜와 시간
        - TIMESTAMP: 타입스탬프

    - 예시:
        ```sql
        CREATE TABLE 제품 (
        제품번호 INT,
        제품명 VARCHAR(100),
        가격 DECIMAL(10,2),  -- 총 10자리, 소수점 2자리
        등록일 DATETIME,
        설명 TEXT
        );
        ```
    
5. 제약조건
    1. NULL과 NOT NULL
        - NULL: 값이 없음을 허용
        - NOT NULL: 반드시 값이 있어야 함
        ```sql
        CREATE TABLE 회원 (
        회원번호 INT,
        이름 VARCHAR(50) NOT NULL, -- 이름은 필수
        별명 VARCHAR(50) NULL -- 별명은 선택
        );
        ```

    2. 자동 증가(AUTO_INCREMENT)
        - 새 행이 추가될 때마다 자동으로 1씩 증가
        ```sql
        CREATE TABLE 게시물 (
        글번호 INT AUTO_INCREMENT PRIMARY KEY,
        제목 VARCHAR(200)
        );
        ```

    3. 기본 키 (PRIMARY KEY)
        - 각 행을 고유하게 식별하는 열
        - 자동으로 NOT NULL과 UNIQUE 제약조건 포함

        ```sql
        CREATE TABLE 직원 (
        사원번호 INT PRIMARY KEY,  -- 단일 열 기본 키
        이름 VARCHAR(50)
        );

        -- 또는 복합 기본 키
        CREATE TABLE 수강신청 (
        학번 INT,
        과목코드 VARCHAR(10),
        신청일 DATE,
        PRIMARY KEY (학번, 과목코드)  -- 복합 기본 키
        );
        ```

    4. 외래 키 (FOREIGN KEY)
        - 다른 테이블의 기본 키를 참조하는 열

        ```sql
        CREATE TABLE 주문 (
        주문번호 INT PRIMARY KEY,
        회원번호 INT,
        주문일자 DATE,
        FOREIGN KET (회원번호) REFERENCES 회원(회원번호)
        );
        ```

    5. 고유 키(UNIQUE)
        - 중복값을 허용하지 않음

        ```sql
        CREATE TABLE 회원 (
        회원번호 INT PRIMARY KEY,
        이메일 VARCHAR(100) UNIQUE,  -- 이메일 중복 불가
        전화번호 VARCHAR(20) UNIQUE  -- 전화번호 중복 불가
        );
        ```

    6. 체크 제약(CHECK)
        - 입력할 수 있는 값의 범위 제한

        ```sql
        CREATE TABLE 직원 (
        사원번호 INT PRIMARY KEY,
        나이 INT CHECK (나이 >= 18),  -- 18세 이상만 가능
        급여 DECIMAL(10,2) CHECK (급여 >= 0)  -- 음수 급여 불가
        );
        ```

    7. 기본값(DEFAULT)
        - 값을 지정하지 않았을 때 사용할 값

        ```sql
        CREATE TABLE 게시물 (
        글번호 INT AUTO_INCREMENT PRIMARY KEY,
        제목 VARCHAR(200),
        작성일 DATETIME DEFAULT CURRENT_TIMESTAMP,
        조회수 INT DEFAULT 0,
        삭제여부 CHAR(1) DEFAULT 'N'
        );
        ```

    - 전체 예시:
    ```sql
    CREATE TABLE 상품 (
        상품번호 INT AUTO_INCREMENT PRIMARY KEY,
        상품명 VARCHAR(100) NOT NULL,
        가격 DECIMAL(10,2) CHECK (가격 >= 0),
        재고량 INT DEFAULT 0,
        등록일 DATETIME DEFAULT CURRENT_TIMESTAMP,
        카테고리_코드 VARCHAR(10),
        설명 TEXT NULL,
        UNIQUE (상품명),
        FOREIGN KEY (카테고리_코드) REFERENCES 카테고리(카테고리_코드)
    );
    ```

# SQL 제약 조건 요약

| 제약 조건      | 설명                                          | 중복 허용 여부 | NULL 허용 여부 |
|----------------|-----------------------------------------------|----------------|----------------|
| PRIMARY KEY    | 테이블에서 각 행을 고유하게 식별               | 불가           | 불가           |
| FOREIGN KEY    | 다른 테이블의 PRIMARY KEY를 참조              | 가능           | 가능           |
| UNIQUE         | 열의 모든 값이 유일해야 함                    | 불가           | 가능           |
| NOT NULL       | 해당 열에 반드시 값이 존재해야 함             | 가능           | 불가           |
| CHECK          | 조건을 만족하는 데이터만 입력 가능            | 가능           | 가능           |
| DEFAULT        | 값이 없을 때 기본값을 설정                    | 가능           | 가능           |
| AUTO_INCREMENT | 새로운 행 추가 시 자동으로 값 증가            | 불가           | 불가           |

## 데이터 조작 언어(DML)과 트랜젝션 제어

1. 데이터 추가 (INSERT INTO)
    1. 기본 문법
        ```sql
        -- 모든 열에 데이터 추가
        INSERT INTO 테이블이름 VALUES (값1, 값2, ...);

        -- 특정 열에만 데이터 추가
        INSERT INTO 테이블 이름 (열1, 열2, ...) VALUES (열1, 열2, ...);
        ```

    2. 실제 예시:
        ```sql
        -- 모든 열에 데이터 추가
        INSERT INTO 직원 VALUES (1001, '김철수', '개발팀', 3000000);

        -- 특정 열에만 데이터 추가 (나머지는 NULL 또는 DEFAULT 값우로 설정됨.)
        INSERT INTO 직원 (사원번호, 이름) VALUES (1002, '박영희');
        ```

    3. 다중 행 삽입
    ```sql
    INSERT INTO 직원 (사원번호, 이름, 부서, 급여) VALUES
        (1003, '이영수', '영업팀', 3500000),
        (1004, '최민지', '인사팀', 3200000),
        (1005, '정대현', '개발팀', 3800000);
    ```

2. 데이터 수정 (UPDATE)
    1. 기본 문법
        ```sql
        UPDATE 테이블이름
        SET 열1 = 값1, 열2 = 값2, ...
        WHERE 조건;
        ```

    2. 실제 예시:
        ```sql
        -- 특정 직원의 급여 수정
        UPDATE 직원 
        SET 급여 = 3500000 
        WHERE 사원번호 = 1001;

        -- 여러 열 동시 수정
        UPDATE 직원 
        SET 급여 = 급여 * 1.1, 
            부서 = '기획팀'
        WHERE 부서 = '개발팀';
        ```

    * ⚠️ 주의: WHERE 절을 생략하면 모든 행이 수정됩니다!

    3. 데이터 삭제 (DELETE)
    1. 기본 문법
        ```sql
        DELETE FROM 테이블이름 WHERE 조건;
        ```

    2. 실제 예시:
        ```sql
        -- 특정 직원 삭제
        DELETE FROM 직원 WHERE 사원번호 = 1001;
        -- 특정 부서의 모든 직원 삭제
        DELETE FROM 직원 WHERE 부서 = '영업팀';
        ```
  
  * ⚠️ 주의: WHERE 절을 생략하면 모든 데이터가 삭제됩니다!

4. 트랜잭션 제어 (TCL)
    1. 트랜잭션이란?
        - 데이터베이스의 상태를 변화시키는 하나의 논리적 작업 단위
        - 여러 개의 명령어의 집합이 정상적으로 처리되면 정상 종료하고, 하나라도 오류가 발생하면 전체가 취소되어야 함.

    2. 트랜잭션의 특성 (ACID):
        - 원자성 (Atomicity): 모두 실행되거나 모두 취소되거나
        - 일관성 (Consistency): 실행 전과 후의 데이터베이스가 일관된 상태 유지
        - 격리성 (Isolation): 동시에 실행되는 트랜잭션들이 서로 영향을 미치지 않음
        - 지속성 (Durability): 완료된 트랜잭션의 결과는 영구적으로 보존

    3. 주요 명령어

        1. COMMIT
        - 트랜잭션의 변경사항을 영구적으로 저장
        ```sql
        BEGIN; -- 트랜잭션 시작
            UPDATE 계좌 SET 잔액 = 잔액 - 1000 WHERE 계좌번호 = 'A001';
            UPDATE 계좌 SET 잔액 = 잔액 + 1000 WHERE 계좌번호 = 'B001';
        COMMIT; -- 트랜잭션 종료
        ```

        2. ROLLBACK
        - 트랜잭션의 변경사항을 취소하고 이전 상태로 되돌림
        ```sql
        BEGIN;
            UPDATE 계좌 SET 잔액 = 잔액 - 1000 WHERE 계좌번호 = 'A001';
            -- 오류 발생 시
            ROLLBACK; -- 변경사항 취소
        ```

        3. SAVEPOINT
        - 트랜잭션 내에 중간 저장점을 만듦
        ```sql
        BEGIN;
            UPDATE 테이블1 SET ...;
            SAVEPOINT save1; -- 저장점 생성

            UPDATE 테이블2 SET ...;
            -- 문제 발생
            ROLLBACK TO save1; -- save1 지점으로 롤백

            -- 다른 작업 수행
            COMMIT;
        ```

        4. 실제 예시 (계좌 이체):
        ```sql
        BEGIN;
            -- 출금 계좌에서 금액 차감
            UPDATE 계좌
            SET 잔액 = 잔액 - 50000
            WHERE 계좌번호 = 'A001';

            -- 잔액 확인
            SAVEPOINT 출금완료;

            -- 입금 계좌에 금액 추가
            UPDATE 계좌
            SET 잔액 = 잔액 + 50000
            WHERE 계좌번호 = 'B001';

            -- 모든 처리가 정상적이면 커밋
            COMMIT;

        -- 일부 RDBMS에서는 예외처리 문법을 지원하지 않을 수 있습니다.
        EXCEPTION
            WHEN OTHERS THEN
            -- 오류 발생 시 롤백
            ROLLBACK;
        ```

5. 데이터 조작 시 주의사항
    - `UPDATE`와 `DELETE`사용 시 항상 `WHERE`절 고려
    - 대량의 데이터 처리 시 트랜잭션 단위 고려
    - 실행 전 SELECT로 영향 받을 데이터 미리 확인

    1. 효율적인 데이터 처리
        ```sql
        -- 대량 데이터 삽입 시 한 번에 처리
        INSERT INTO 직원 VALUES
        (값들), (값들), (값들) ...;

        -- UPDATE 시 서브쿼리 활용
        UPDATE 직원
        SET 급여 = (SELECT AVG(급여) FROM 지원) * 1.1
        WHERE 부서 = '영업팀';
        ```

    2. 트랜잭션 활용 팁
        - 트랜잭션은 짧게 유지
        - 중요한 데이터 처리 시 반드시 트랜잭션 사용
        - SAVEPOINT를 적절히 활용하여 복잡한 처리 관리

## SQL의 기본 함수와 연산자

1. 산술 연산자 및 비교 연산자
    1. 산술 연산자
        ```sql
        -- 기본 산술 연산
        SELECT
        가격 + 500 as 할증가격, -- 덧셈
        가격 - 500 as 할인가격, -- 뺄셈
        가격 * 1.1 as 부가세포함, -- 곱셈
        가격 / 2 as 반값 -- 나눗셈
        FROM 제품;
        ```

    2. 비교 연산자
        ```sql
        -- 비교 연산자 사용
        SELECT * FROM 직원
        WHERE
        급여 >= 3000000 AND -- 크거나 같음
        급여 <= 5000000 AND -- 작거나 같음
        부서 = '개발팀' AND -- 같음
        입사일 != '2023-01-01'; -- 다름
        ```

2. 기본 내장 함수
    1. 수학 함수
        ```sql
        SELECT
        SUM(급여) as 총급여, -- 합계
        AVG(급여) as 평균급여, -- 평균
        MAX(급여) as 최대급여, -- 최대값
        MIN(급여) as 최소급여, -- 최소값
        COUNT(*) as 직원수, -- 행 수 계산
        ROUND(급여, -3) as 천원단위, -- 반올림
        CEIL(급여) as 올림, -- 올림
        FLOOR(급여) as 내림 -- 내림
        FROM 직원;
        ```

    2. 문자열 함수
        ```sql
        SELECT
        CONCAT(성, ' ', 이름) as 전체이름, -- 문자열 연결
        LENGTH(이름) as 이름길이, -- 문자열 길이
        UPPER(이메일) as 대문자이메일, -- 대문자 변환
        LOWER(이메일) as 소문자이메일, -- 소문자 변환
        SUBSTRING(전화번호, 1, 3) as 지역번호, -- 부분 문자열
        TRIM(주소) as 공백제거, -- 앞 뒤 공백 제거
        REPLACE(이메일, '@', '#') as 변경 -- 치환
        FROM 직원;
        ```

    3. 날짜 함수
        ```sql
        SELECT
        NOW() as 현재시간, -- 현재 날짜시간
        CURRENT_DATE() as 오늘날짜, -- 현재 날짜
        DATE_ADD(입사일, INTERVAL 1 YEAR) as 근속1년, -- 날짜 더하기
        DATEDIFF(NOW(), 입사일) as 근무일수, -- 날짜 차이
        YEAR(입사일) as 입사년도, -- 년도 추출
        MONTH(입사일) as 입사월, -- 월 추출
        DAY(입사일) as 입사일, -- 일 추출
        DATE_FORMAT(입사일, '%Y년 %m월 %d일') as 형식적용 -- 날짜 형식 변경
        FROM 직원;
        ```

3. 논리 연산자
    ```sql
    -- AND, OR, NOT 사용
    SELECT * FROM 직원
    WHERE
        (부서 = '개발팀' OR 부서 = '영업팀') -- OR 연산
        AND
        (급여 >= 3000000) -- AND 연산
        AND
        NOT (직급 = '인턴'); -- NOT 연산
    ```

4. CASE 문과 조건문
    1. 단순 CASE문
        ```sql
        SELECT
        이름,
        급여,
        CASE 부서
            WHEN '개발팀' THEN '개발'
            WHEN '영업팀' THEN '영업'
            WHEN '인사팀' THEN '인사'
            ELSE '기타'
        END as 부서구문
        FROM 직원;
        ```

    2. 검색 CASE문
        ```sql
        SELECT
        이름,
        급여
        CASE
            WHEN 급여 >= 5000000 THEN '상위급여'
            WHEN 급여 >= 3000000 THEN '중위급여'
            ELSE '하위급여'
        END as 급여등급,
        CASE
            WHEN DATEDIFF(NOW(), 입사일) >= 365 THEN '1년이상'
            WHEN DATEDIFF(NOW(), 입사일) >= 180 THEN '6개월이상'
            ELSE '신입'
        END as 근속기간
        FROM 직원;
        ```

5. 실제 활용 예시
    1. 급여 통계 분석
        ```sql
        SELECT
        부서,
        COUNT(*) as 직원수,
        ROUND(AVG(급여), 0) as 평균급여,
        MAX(급여) as 최대급여,
        MIN(급여) as 최소급여,
        CASE
            WHEN AVG(급여) >= 4000000 THEN '고급여부서'
            WHEN AVG(급여) >= 3000000 THEN '중급여부서'
            ELSE '저급여부서'
        END as 부서등급
        FROM 직원
        GROUP BY 부서;
        ```

    2. 직원 평가 리포트
        ```sql
        SELECT
        이름,
        CONCAT(
            SUBSTRING(주민번호, 1, 6),
            '-*******'
        ) as 주민번호,
        CASE
            WHEN 성과등급 = 'A' THEN 급여 * 1.2
            WHEN 성과등급 = 'B' THEN 급여 * 1.1
            ELSE 급여
        END as 조정급여,
        DATE_FORMAT(
            DATE_ADD(입사일, INTERVAL 1 YEAR),
            '%Y년 %m월 %d일'
        ) as 근속1년일
        FROM 직원;
        ```

    3. 복합 조건 검색
        ```sql
        SELECT
        제품명,
        가격,
        제고
        CASE
            WHEN 재고 = 0 THEN '품절'
            WHEN 재고 < 10 THEN '부족'
            WHEN 재고 < 50 THEN '적정'
            ELSE '충분'
        END as 재고상태,
        CASE
            WHEN 가격 >= 100000 AND 재고 > 0 THEN '고가품'
            WHEN 가격 >= 50000 AND 재고 > 0 THEN '중가품'
            WHEN 재고 > 0 THEN '저가품'
            ELSE '품절상품'
        END as 가격분류
        FROM 제품;
        ```

## 조인(Join)과 복잡한 쿼리 작성

1. 조인의 개념과 유형
    - 조인은 두 개 이상의 테이블을 연결하여 데이터를 조회하는 방법입니다.

    1. INNER JOIN (내부 조인)
        - 두 테이블에서 일치하는 데이터만 조회
        ```sql
        -- 직원과 부서 정보 조회
        SELECT E.이름, E.직급, D.부서명, D.위치
        FROM 직원 E
        INNER JOIN 부서 D ON E.부서코드 = D.부서코드;
        ```

    2. LEFT OUTER JOIN (좌측 외부 조인)
        - 왼쪽 테이블의 모든 데이터와 오른쪽 테이블의 일치하는 데이터 조회
        ```sql
        -- 모든 직원의 부서 정보 조회 (부서가 없는 직원도 포함)
        SELECT E.이름, D.부서명
        FROM 직원 E
        LEFT JOIN 부서 D ON E.부서코드 = D.부서코드;
        ```

    3. RIGHT OUTER JOIN (오른쪽 외부 조인)
        - 오른쪽 테이블의 모든 데이터와 왼쪽 테이블의 일치하는 데이터 조회
        ```sql
        -- 모든 부서와 소속 직원 조회 (직원이 없는 부서도 포함)
        SELECT D.부서명, E.이름
        FROM 직원 E
        RIGHT JOIN 부서 D ON E.부서코드 = D.부서코드;
        ```

    4. FULL OUTER JOIN (전체 외부 조인)
        - 양쪽 테이블의 모든 데이터 조회
        ```sql
        -- MySQL에서는 UNION을 사용하여 구현
        SELECT E.이름, D.부서명
        FROM 직원 E
        LEFT JOIN 부서 D ON E.부서코드 = D.부서코드
        UNION
        SELECT E.이름, D.부서명
        FROM 직원 E
        RIGHT JOIN 부서 D ON E.부서코드 = D.부서코드;
        ```

    5. SELF JOIN (자체 조인)
        - 같은 테이블을 자기 자신과 조인
        ```sql
        -- 직원과 관리자 정보 조회
        SELECT
        E1.이름 as 직원,
        E2.이름 as 관리자
        FROM 직원 E1
        LEFT JOIN 직원 E2 ON E1.관리자ID = E2.직원ID;
        ```

2. 서브쿼리
    1. 단일 행 서브쿼리
        ```sql
        -- 평균 급여보다 많이 받는 직원 조회
        SELECT 이름, 급여
        FROM 직원
        WHERE 급여 > (SELECT AVG(급여) FROM 직원);
        ```

    2. 다중 행 서브쿼리
        ```sql
        -- 각 부서의 최고 급여를 받는 직원 조회
        SELECT 이름, 부서코드, 급여
        FROM 직원
        WHERE (부서코드, 급여) IN (
        SELECT 부서코드, MAX(급여)
        FROM 직원
        GROUP BY 부서코드
        );
        ```

    3. 상관 서브쿼리
        ```sql
        -- 각 부서별 평균 급여보다 많이 받는 직원 조회
        SELECT E1.이름, E1.부서코드, E1.급여
        FROM 직원 E1
        WHERE E1.급여 > (
        SELECT AVG(E2.급여)
        FROM 직원 E2
        WHERE E2.부서코드 = E1.부서코드
        );
        ```

    4. EXISTS 활용
        ```sql
        -- 주문이 있는 고객만 조회
        SELECT *
        FROM 고객 C
        WHERE EXISTS (
        SELECT 1
        FROM 주문 O
        WHERE O.고객ID = C.고객ID
        );
        ```

3. 집계와 그룹화
    1. GROUP BY 기본 사용
        ```sql
        -- 부서별 직원 수와 평균 급여
        SELECT
        부서코드,
        COUNT(*) as 직원수,
        AVG(급여) as 평균급여,
        FROM 직원
        GROUP BY 부서코드;
        ```

    2. HAVING 절 사용
        ```sql
        -- 평균 급여가 3백만원 이상인 부서
        SELECT
        부서코드,
        COUNT(*) as 직원수,
        AVG(급여) as 평균급여
        FROM 직원
        GROUP BY 부서코드
        HAVING AVG(급여) >= 3000000;
        ```

4. 실제 활용 예시
    1. 복잡한 조인과 서브쿼리 조합
        ```sql
        -- 부서별 최고 급여자 정보와 부서 정보 조회
        SELECT
        D.부서명,
        E.이름,
        E.급여,
        (SELECT AVG(급여) FROM 직원
        WHERE 부서코드 = E.부서코드) as 부서평균급여
        FROM 직원 E
        INNER JOIN 부서 D ON E.부서코드 = D.부서코드
        WHERE (E.부서코드, E.급여) IN (
        SELECT 부서코드, MAX(급여)
        FROM 직원
        GROUP BY 부서코드
        );
        ```

    2. 다중 테이블 조인과 집게
        ```sql
        -- 부서별, 직급별 인원수와 급여 통계
        SELECT
        D.부서명,
        E.직급,
        COUNT(*) as 인원수,
        MIN(E.급여) as 최소급여,
        MAX(E.급여) as 최대급여,
        AVG(E.급여) as 평균급여
        FROM 직원 E
        INNER JOIN 부서 D ON E.부서코드 = D.부서코드
        GROUP BY D.부서명, E.직급
        HAVING COUNT(*) >= 2
        ORDER BY D.부서명, AVG(E.급여) DESC;
        ```

    3. 조인과 윈도우 함수 활용
        ```sql
        -- 부서별 급여 순위
        SELECT
        D.부서명,
        E.이름,
        E.급여,
        RANK() OVER (
            PARTITION BY E.부서코드
            ORDER BY E.급여 DESC
        ) as 부서내급여순위
        FROM 직원 E
        INNER JOIN 부서 D ON E.부서코드 = D.부서코드;
        ```

    4. 복잡한 조건의 그룹화
        ```sql
        -- 연도별, 분기별 매출 통계
        SELECT
        YEAR(주문일) as 연도,
        QUARTER(주문일) as 분기,
        COUNT(DISTINCT 고객ID) as 구매고객수,
        SUM(주문금액) as 총매출,
        AVG(주문금액) as 평균주문금액
        FROM 주문
        GROUP BY
        YEAR(주문일),
        QUARTER(주문일)
        HAVING
        COUNT(*) >= 10 AND
        SUM(주문금액) > 1000000
        ORDER BY 연도, 분기;
        ```

    5. 서브쿼리와 JOIN의 성능 비교
        1. 서브쿼리가 유리한 경우:
        - 한 테이블에서 다른 테이블의 존재 여부만 확인할 때 (EXISTS 사용)
        - 메인 쿼리의 결과가 서브쿼리의 결과에 의존적일 때 
        ```sql
        -- EXISTS를 사용한 효율적인 조회
        SELECT *
        FROM 고객 C
        WHERE EXISTS (
            SELECT 1
            FROM 주문 O
            WHERE O.고객ID = C.고객ID
            AND O.주문일 >= '2024-01-01'
        );
        ```

        2. JOIN이 유리한 경우:
        - 두 테이블의 데이터를 모두 가져와야 할 때
        - 여러 컬럼을 비교해야 할 때 
        ```sql
        -- JOIN을 사용한 효율적인 조회
        SELECT C.이름, O.주문번호, O.주문일
        FROM 고객 C
        INNER JOIN 주문 O ON C.고객ID = O.고객ID
        WHERE O.주문일 >= '2024-01-01';
        ```

    6. 복잡한 쿼리들을 작성할 때 주의할 점.
        1. 조인 조건을 정확히 설정하여 카테시안 곱 방지.
        2. 서브쿼리 사용 시 성능 고려 (JOIN으로 대체 가능한지 검토)
        3. GROUP BY 시 모든 집계되지 않은 컬럼을 포함
        4. 인덱스를 고려한 쿼리 작성
        5. 실행 계획(EXPLAIN) 확인으로 성능 최적화.

## 고급 SQL 기능들

1. 윈도우 함수 (Window Functions)
    1. 기본 개념과 문법
    - 윈도우 함수는 행과 행 간의 관계를 정의하여 계산을 수행하는 함수입니다.

    - 기본 문법:
        ```sql
        함수_이름() OVER (
        PARTITION BY 그룹화_열
        ORDER BY 정렬_열
        ROWS/RANGE BETWEEN 시작점 AND 끝점
        )
        ```

  2. 순위 함수
        ```sql
        SELECT
        이름,
        급여

        -- 단순 순변
        ROW_NUMBER() OVER (ORDER BY 급여 DESC) as 순번,

        -- 동일 값 동일 순위, 건너뛰기
        RANK() OVER (ORDER BY 급여 DESC) as 순위1,

        -- 동일 값 동일 순위, 순차적
        DENSE_RANK() OVER (ORDER BY 급여 DESC) as 순위2,

        -- 백분율 순위
        PERCENT_RANK() OVER(ORDER BY 급여 DESC) as 백분율순위
        FROM 직원;
        ```
        - 결과 예시:
        ```
        이름    급여     순번    순위1   순위2
        김철수  5000000  1       1       1
        이영희  5000000  2       1       1
        박민수  4000000  3       3       2
        정지원  3000000  4       4       3
        ```
        - 순번: 동일 급여여도 고유한 번호 부여
        - 순위1: 동일 급여는 같은 순위, 다음 순위는 건너뜀
        - 순위2: 동일 급여는 같은 순위, 다음 순위는 연속

  3. 파티션별 순위
        ```sql
        SELECT
        부서코드,
        이름,
        급여,

        -- 부서별 급여 순위
        RANK() OVER (
            PARTITION BY 부서코드
            ORDER BY 급여 DESC
        ) as 부서내순위,

        -- 부서별 급여 백분율
        ROUND(
            급여 / SUM(급여) OVER (PARTITION BY 부서코드) * 100,
            2
        ) as 부서내급여비율
        FROM 직원;
        ```

  4. 윈도우 프레임
        ```sql
        SELECT
        주문일,
        주문금액,

        -- 이동 평균 (전후 3일)
        AVG(주문금액) OVER (
            ORDER BY 주문일
            ROWS BETWEEN 3 PRECEDING AND 3 FOLLOWING
        ) as 이동평균,

        -- 누적 합계
        SUM(주문금액) OVER (
            ORDER BY 주문일
            ROWS UNBOUNDED PRECEDING
        ) as 누적합계
        FROM 주문;
        ```

2. CTE(Common Table Expression)
    1. 기본 CTE
        ```sql
        WITH 매출요약 AS (
        SELECT
            고객ID,
            COUNT(*) as 주문수,
            SUM(주문금액) as 총주문금액
        FROM 주문
        GROUP BY 고객ID
        )
        SELECT
        C.이름,
        M.주문수,
        M.총주문금액
        FROM 고객 C
        JOIN 매출요약 M ON C.고객ID = M.고객ID;
        ```

    2. 다중 CTE
        ```sql
        WITH
        월별매출 AS (
        SELECT
            EXTRACT(YEAR_MONTH FROM 주문일) as 년월,
            SUM(주문금액) as 매출액
        FROM 주문
        GROUP BY EXTRACT(YEAR_MONTH FROM 주문일)
        ),
        매출증감 AS (
        SELECT
            년월,
            매출액,
            LAG(매출액) OVER (ORDER BY 년월) as 전월매출,
            매출액 - LAG(매출액) OVER (ORDER BY 년월) as 증감액
        FROM 월별 매출
        )
        SELECT *
        FROM 매출증감
        WHERE 증감액 < 0;
        ```

    3. 재귀적 CTE
        ```sql
        -- 조직도 계층 구조 조회
        WITH RECURSIVE 조직구조 AS (
        -- 초기 멤버 (최상위 관리자)
        SELECT
            직원ID,
            이름,
            관리자ID,
            1 as 레벨
        FROM 직원
        WHERE 관리자ID IS NULL

        UNION ALL

        -- 재귀 멤버
        SELECT
            E.직원ID,
            E.이름,
            E.관리자ID,
            O.레벨 + 1
        FROM 직원 E
        JOIN 조직구조 O ON E.관리자ID = O.직원ID
        )
        SELECT
        REPEAT('    ', 레벨 - 1) || 이름 as 조직도
        FROM 조직구조
        ORDER BY 레벨, 직원ID;
        ```

        - 무한 루프 방지
        ```sql
        -- 최대 재귀 깊이 설정
        WITH RECURSIVE 조직구조 AS (
            -- 기본 구문
            SELECT 직원ID, 이름, 관리자ID, 1 as 레벨
            FROM 직원
            WHERE 관리자ID IS NULL
            
            UNION ALL
            
            -- 재귀 구문
            SELECT 
                E.직원ID,
                E.이름,
                E.관리자ID,
                O.레벨 + 1
            FROM 직원 E
            JOIN 조직구조 O ON E.관리자ID = O.직원ID
            WHERE O.레벨 < 10  -- 최대 깊이 제한
        )
        SELECT * FROM 조직구조
        OPTION (MAXRECURSION 10);  -- 최대 재귀 횟수 제한
        ```

        - 재귀적 CTE 활용 사례
        ```sql
        -- 카테고리 계층 구조
        WITH RECURSIVE 카테고리트리 AS (
            -- 최상위 카테고리
            SELECT 
                카테고리ID,
                이름,
                상위카테고리ID,
                CAST(이름 as VARCHAR(1000)) as 전체경로,
                1 as 레벨
            FROM 카테고리
            WHERE 상위카테고리ID IS NULL
            
            UNION ALL
            
            -- 하위 카테고리
            SELECT 
                C.카테고리ID,
                C.이름,
                C.상위카테고리ID,
                CAST(CT.전체경로 + ' > ' + C.이름 as VARCHAR(1000)),
                CT.레벨 + 1
            FROM 카테고리 C
            JOIN 카테고리트리 CT ON C.상위카테고리ID = CT.카테고리ID
        )
        SELECT 
            REPLICATE('    ', 레벨 - 1) + 이름 as 계층구조,
            전체경로
        FROM 카테고리트리
        ORDER BY 전체경로;
        ```

3. 트랜잭션 고급 제어

    1. ACID 속성
        - Atomicity(원자성): 트랜잭션은 모두 실행되거나 모두 취소됨.
        - Consistency(일관성): 트랜잭션 실행 전후의 데이터베이스는 일관된 상태를 유지.
        - Isolation(격리성): 동시 실행되는 트랜잭션들은 서로 영향을 미치지 않음.
        - Durability(지속성): 완료된 트랜잭션의 결과는 영구적으로 보존.

    2. 트랜잭션 격리 수준
        ```sql
        -- 격리 수준 설정
        SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

        -- 각 격리 수준별 예쪠
        BEGIN;
        -- READ UNCOMMITTED: 더티 리드 발생 가능
        SELECT * FROM 계좌;

        -- READ COMMITTED: 커밋된 데이터만 읽음
        UPDATE 계좌 SET 잔액 = 잔액 - 1000 WHERE 계좌번호 = 'A001';

        -- REPEATABLE READ: 트랜잭션 내에서 일관된 읽기 보장
        SELECT * FROM 계좌 WHERE 계좌번호 = 'A001';

        -- SERIALIZABLE: 완전한 격리, 동시성 낮음
        SELECT SUM(잔액) FROM 계좌;
        COMMIT;
        ```

        - ACID 속성과 격리 수준 비교표
        ```
        격리 수준         | Dirty Read | Non-Repeatable Read | Phantom Read | 특징                        | 적용 예시
        READ UNCOMMITTED   가능          가능                  가능           가장 낮은 격리 수준, 성능 최고 실시간 통계
        READ COMMITTED     불가능        가능                  가능           일반적으로 사용, 적절한 성능    일반 조회
        REPETABLE READ     불가능        불가능                가능            동일 데이터 보장, 성능 저하    재무 보고서
        SERIALIZABLE       불가능        불가능                불가능          완벽한 격리, 성능 최저         금융 거래
        ```

        - 격리 수준별 예제
        ```sql
        -- READ UNCOMMITTED
        SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
        BEGIN TRANSACTION;
            -- 커밋되지 않은 데이터도 읽을 수 있음
            SELECT * FROM 계좌;
        COMMIT;

        -- SERIALIZABLE
        SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
        BEGIN TRANSACTION;
            -- 완벽한 격리, 다른 트랜잭션 차단
            SELECT SUM(금액) FROM 거래내역
            WHERE 계좌번호 = 'A001';
            
            INSERT INTO 거래내역(계좌번호, 금액)
            VALUES ('A001', 1000);
        COMMIT;
        ```

    3. 동시성 제어와 데드락 방지
        ```sql
        -- 데드락 방지를 위한 순서화된 락 획득
        BEGIN;
        -- 낮은 ID부터 락 획득
        SELECT * FROM 계좌 WHERE 계좌번호 IN ('A001', 'B001')
        ORDER BY 계좌번호 FOR UPDATE;

        -- 업데이트 수행
        UPDATE 계좌 SET 잔액 = 잔약 - 1000 WHERE 계좌번호 = 'A001';
        UPDATE 계좌 SET 잔액 = 잔약 + 1000 WHERE 계좌번호 = 'B001';
        COMMIT;
        ```

        1. 데드락 방지 전략
        - 타임아웃 설정
            ```sql
            -- 트랜잭션 타임아웃 설정
            SET LOCK_TIMEOUT 10000;  -- 10초

            BEGIN TRANSACTION;
                -- 락 획득 시도
                UPDATE 계좌 WITH (ROWLOCK)
                SET 잔액 = 잔액 - 1000
                WHERE 계좌번호 = 'A001';
                
                -- 두 번째 락 획득 시도
                UPDATE 계좌 WITH (ROWLOCK)
                SET 잔액 = 잔액 + 1000
                WHERE 계좌번호 = 'B001';
            COMMIT;
            ```

        - 락 획득 순서 표준화
            ```sql
            -- 항상 낮은 계좌번호부터 락 획득
            CREATE PROCEDURE 계좌이체
                @출금계좌 VARCHAR(10),
                @입금계좌 VARCHAR(10),
                @금액 DECIMAL(10,2)
            AS
            BEGIN
                DECLARE @첫번째계좌 VARCHAR(10), @두번째계좌 VARCHAR(10);
                
                -- 계좌번호 순서 정렬
                SELECT 
                    @첫번째계좌 = MIN(계좌),
                    @두번째계좌 = MAX(계좌)
                FROM (VALUES (@출금계좌), (@입금계좌)) AS Accounts(계좌);
                
                BEGIN TRANSACTION;
                    -- 항상 작은 번호의 계좌부터 락
                    UPDATE 계좌 SET 잔액 = 잔액 + (
                        CASE 계좌번호
                            WHEN @출금계좌 THEN -@금액
                            ELSE @금액
                        END
                    )
                    WHERE 계좌번호 IN (@첫번째계좌, @두번째계좌)
                    ORDER BY 계좌번호;
                COMMIT;
            END;
            ```

    4. 고급 트랜잭션 예제
        ```sql
        -- 재고 확인 및 주문 처리 트랜잭션
        BEGIN;
        DECLARE @재고수량 INT;

        -- 재고 확인 (FOR UPDATE로 락 획득)
        SELECT @재고수량 = 재고수량
        FROM 상품
        WHERE 상품ID = 1
        FOR UPDATE;

        IF @재고수량 >= 10
        BEGIN
            -- 재고 감소
            UPDATE 상품
            SET 재고수량 = 재고수량 - 10
            WHERE 상품ID = 1;
            
            -- 주문 등록
            INSERT INTO 주문 (상품ID, 수량, 주문일)
            VALUES (1, 10, CURRENT_TIMESTAMP);
            
            COMMIT;
        END
        ELSE
        BEGIN
            ROLLBACK;
            THROW 50001, '재고 부족', 1;
        END
        ```

4. 성능 최적화 팁
    1. 트랜잭션 최적화:
        - 트랜잭션은 최대한 짧게 유지
        - 불필요한 락 최소화
        - 데드락 가능성 있는 작업은 재시도 로직 구현

    2. 락 최적화:
        ```sql
        -- 필요한 범위만 락
        SELECT *
        FROM 주문
        WHERE 주문ID = 1
        FOR UPDATE NOWAIT;  -- 락 획득 실패시 즉시 에러

        -- 특정 행만 락
        SELECT *
        FROM 재고
        WHERE 상품ID = 1
        FOR UPDATE SKIP LOCKED;  -- 이미 락된 행 스킵
        ```

    3. 배치 처리:
        ```sql
        -- 대량 데이터 처리시 배치 단위로 커밋
        DECLARE @BatchSize INT = 1000;
        DECLARE @Processed INT = 0;

        WHILE EXISTS (SELECT 1 FROM 처리대상)
        BEGIN
            BEGIN TRANSACTION;
            
            UPDATE TOP (@BatchSize) 처리대상
            SET 처리여부 = 'Y'
            WHERE 처리여부 = 'N';
            
            SET @Processed = @@ROWCOUNT;
            
            COMMIT;
            
            IF @Processed < @BatchSize BREAK;
        END
        ```

## 인덱스 이해와 활용

1. 인덱스 기본 개념
    - 인덱스는 데이터베이스 테이블의 검색 속도를 향상시키는 자료구조입니다.
        ```sql
        -- 기본 인덱스 생성
        CREATE INDEX IX_직원_이름 ON 직원(이름);

        -- 복합 인덱스 생성
        CREATE INDEX IX_직원_부서_입사일 ON 직원(부서코드, 입사일);

        -- 유니크 인덱스 생성
        CREATE UNIQUE INDEX UIX_직원_이메일 ON 직원(이메일);

        -- 부분 인덱스 생성
        CREATE INDEX IX_주문_상태 ON 주문(주문상태)
        WHERE 주문상태 IN ('처리중', '배송중');
        ```

2. 인덱스 설계 전략
    ```sql
    -- 좋은 인덱스 설계 예시
    CREATE INDEX IX_주문_복합 ON 주문(
        고객ID, -- 높은 선택도
        주문일, -- 범위 검색
        주문상태 -- 추가 필터
    );

    -- 인덱스 재구성
    ALTER TABLE ALL ON 주문 REBUILD;

    -- 인덱스 통계 업데이트
    UPDATE STATISTICS 주문;
    ```

    - 인덱스 설계 고려사항:
        1. 선택도 (Selectivity) 고려
        2. 쿼리 패턴 분석
        3. 갱신 빈도 확인
        4. 저장 공간 고려

## 쿼리 최적화 기법

1. 실행 계획 분석
    ```sql
    -- 실행 계획 확인
    EXPLAIN ANALYZE
    SELECT 
        D.부서명,
        COUNT(*) as 직원수,
        AVG(E.급여) as 평균급여
    FROM 직원 E
    INNER JOIN 부서 D ON E.부서코드 = D.부서코드
    WHERE 
        E.입사일 >= '2023-01-01'
        AND E.급여 >= 3000000
    GROUP BY D.부서명;
    ```

    - 실행 계획 포인트:
        1. 테이블 접근 방식
        - Table Scan
        - Index Scan
        - Index Seek

        2. 조인 방식
        - Nested Loop Join
        - Hash Join
        - Merge Join

        3. 비용 분석
        - CPU cost
        - I/O cost
        - 예상 행수

2. 쿼리 최적화 예시
    - 최적화 전:
        ```sql
        SELECT *
        FROM 주문
        WHERE YEAR(주문일) = 2024;
        ```

    - 최적화 후:
        ```sql
        SELECT *
        FROM 주문
        WHERE 주문일 >= '2024-01-01'
        AND 주문일 <= '2025-01-01';
        ```

3. 쿼리 리팩토링 전략
    1. 서브쿼리 최적화:
        ```sql
        -- 최적화 전
        SELECT *
        FROM 직원
        WHERE 부서코드 IN (
            SELECT 부서코드 
            FROM 부서 
            WHERE 지역 = '서울'
        );

        -- 최적화 후
        SELECT E.*
        FROM 직원 E
        INNER JOIN 부서 D ON E.부서코드 = D.부서코드
        WHERE D.지역 = '서울';
        ```

    2. 집계 함수 최적화:
        ```sql
        -- 최적화 전
        SELECT 
            부서코드,
            COUNT(*) as 직원수,
            SUM(CASE WHEN 급여 >= 5000000 THEN 1 ELSE 0 END) as 고액연봉자
        FROM 직원
        GROUP BY 부서코드;

        -- 최적화 후 (인덱스 활용)
        WITH 급여통계 AS (
            SELECT 
                부서코드,
                COUNT(*) as 직원수,
                SUM(IIF(급여 >= 5000000, 1, 0)) as 고액연봉자
            FROM 직원
            WHERE 부서코드 IS NOT NULL
            GROUP BY 부서코드
        )
        SELECT * FROM 급여통계;
        ```

## 캐싱과 일관성

1. 결과 캐싱
    ```sql
    -- 임시 테이블을 활용한 캐싱
    CREATE TEMPORARY TABLE 일일매출통계 AS
    SELECT 
        날짜,
        COUNT(*) as 주문수,
        SUM(금액) as 총매출
    FROM 주문
    WHERE 날짜 >= CURRENT_DATE - INTERVAL '7 days'
    GROUP BY 날짜;

    -- 캐시 테이블 활용
    SELECT * FROM 일일매출통계
    WHERE 날짜 = CURRENT_DATE;
    ```

2. 일관성 유지 전략
    ```sql
    -- 트리거를 이용한 캐시 갱신
    CREATE TRIGGER TR_주문_통계갱신
    AFTER INSERT, UPDATE, DELETE ON 주문
    FOR EACH ROW
    BEGIN
        -- 통계 테이블 갱신
        MERGE INTO 일일매출통계 T
        USING (
            SELECT 
                NEW.날짜,
                COUNT(*) as 주문수,
                SUM(금액) as 총매출
            FROM 주문
            WHERE 날짜 = NEW.날짜
        ) S
        ON (T.날짜 = S.날짜)
        WHEN MATCHED THEN
            UPDATE SET 
                주문수 = S.주문수,
                총매출 = S.총매출
        WHEN NOT MATCHED THEN
            INSERT (날짜, 주문수, 총매출)
            VALUES (S.날짜, S.주문수, S.총매출);
    END;
    ```

## 파티셔닝과 샤딩
1. 테이블 파티셔닝
    1. 범위 파티셔닝:
      ```sql
      -- 날짜 기준 파티셔닝
      CREATE TABLE 주문 (
          주문ID INT,
          주문일 DATE,
          금액 DECIMAL(10,2)
      )
      PARTITION BY RANGE (주문일) (
          PARTITION p_2023_q1 VALUES LESS THAN ('2023-04-01'),
          PARTITION p_2023_q2 VALUES LESS THAN ('2023-07-01'),
          PARTITION p_2023_q3 VALUES LESS THAN ('2023-10-01'),
          PARTITION p_2023_q4 VALUES LESS THAN ('2024-01-01')
      );
      ```

    2. 리스트 파티셔닝:
      ```sql
      -- 지역 기준 파티셔닝
      CREATE TABLE 직원 (
          직원ID INT,
          이름 VARCHAR(100),
          지역 VARCHAR(20)
      )
      PARTITION BY LIST (지역) (
          PARTITION p_서울 VALUES IN ('서울'),
          PARTITION p_경기 VALUES IN ('경기'),
          PARTITION p_기타 VALUES IN ('인천', '부산', '대구')
      );
      ```

    3. 해시 파티셔닝:
      ```sql
      -- 고객ID 기준 해시 파티셔닝
      CREATE TABLE 고객데이터 (
          고객ID INT,
          데이터 JSON
      )
      PARTITION BY HASH (고객ID)
      PARTITIONS 4;
      ```

2. 샤딩 구현
    1. 수평 샤딩:
        ```sql
        -- 샤드 키 기준 테이블 분할
        CREATE TABLE 주문_샤드1 (
            주문ID INT,
            고객ID INT,
            CHECK (고객ID % 4 = 0)
        );

        CREATE TABLE 주문_샤드2 (
            주문ID INT,
            고객ID INT,
            CHECK (고객ID % 4 = 1)
        );

        -- 샤드 라우팅 함수
        CREATE FUNCTION Get_Shard_Table(
            p_고객ID INT
        ) RETURNS VARCHAR(20) AS
        BEGIN
            RETURN '주문_샤드' || (p_고객ID % 4 + 1)::VARCHAR;
        END;
        ```

    2. 수직 샤딩:
        ```sql
        -- 자주 접근하는 컬럼과 그렇지 않은 컬럼 분리
        CREATE TABLE 고객_기본정보 (
            고객ID INT PRIMARY KEY,
            이름 VARCHAR(100),
            이메일 VARCHAR(200)
        );

        CREATE TABLE 고객_상세정보 (
            고객ID INT PRIMARY KEY,
            주소 TEXT,
            생년월일 DATE,
            기타정보 JSON,
            FOREIGN KEY (고객ID) REFERENCES 고객_기본정보(고객ID)
        );
        ```
  
3. 성능 모니터링
    ```sql
    -- 파티션 사용량 확인
    SELECT 
        TABLE_NAME,
        PARTITION_NAME,
        TABLE_ROWS,
        DATA_LENGTH,
        INDEX_LENGTH
    FROM information_schema.PARTITIONS
    WHERE TABLE_SCHEMA = 'your_database';

    -- 파티션 프루닝 확인
    EXPLAIN ANALYZE
    SELECT *
    FROM 주문
    WHERE 주문일 BETWEEN '2023-01-01' AND '2023-03-31';
    ```

## Stored Procedure(저장 프로시저)와 Function(함수)

1. Stored Procedure & Function의 개요
    1. Stored Procedure
        - 데이터베이스 내부에 저장되어 실행되는 프로그램 단위로, 여러 SQL 문을 하나의 로직으로 묶어 실행할 수 있다.
        - 호출 시점에 필요한 파라미터(IN/OUT/INOUT)를 전달하고, 여러 쿼리를 일괄 수행하거나 복잡한 로직(조건문/반복문/변수사용 등)을 처리.

        - 장점:
            - 네트워크 트래픽 감소 (여러 개의 SQL 요청을 프로시저 내부에서 처리)
            - 보안 강화(직접 테이블 접근 대신 프로시저 호출로 제한)
            - 재사용성, 유지보수성 개선

    2. Function
        - 하나의 값을 반환해야 하며, SELECT 문 등에서 호출 가능(스칼라 함수 형태).
        - Stored Procedure와 달리, 여러 OUT 파라미터 없이 단일 리턴값을 반환.
        - 예: `SELECT 함수이름(열이름) FROM 테이블;`

2. 기본 문법 & 예시
    1. Stored Procedure
        ```sql
        DELIMITER //
        CREATE PROCEDURE GetEmployeesByDepartment(IN deptName VARCHAR(50))
        BEGIN
            SELECT employee_name, salary
            FROM employees
            WHERE department = deptName;
        END //
        DELIMITER ;

        -- 실행
        CALL GetEmployeesByDepartment('IT');
        ```
        - IN 파라미터: 호출 시 값을 전달만 받고, 내부에서 그 값 변경 불가능
        - OUT 파라미터: 프로시저 내부에서 계산된 값을 호출자에게 돌려줄 수 있음
        - INOUT 파라미터: 호출 시 전달받고, 내부에서 변경 가능, 최종 변경된 값이 호출자에게 반환

    2. Stored Function
        ```sql
        CREATE FUNCTION CalculateBonus(salary DECIMAL(10,2))
        RETURNS DECIMAL(10,2)
        DETERMINISTIC
        BEGIN
            RETURN salary * 0.1;
        END;
        ```
        - 사용 예시(SELECT문 내부):
        ```sql
        SELECT employee_name, CalculateBonus(salary) AS bonus
        FROM employees;
        ```
        - 주의: 함수는 SELECT 문이나 다른 SQL 구문에서 인라인으로 호출될 수 있지만, 반드시 하나의 값을 반환해야 함.

3. 오류 처리(Error Handling)
    1. MySQL 예시
        ```sql
        DELIMITER //
        CREATE PROCEDURE TransferAmount(
            IN fromAcc INT,
            IN toAcc INT,
            IN amount DECIMAL(10,2)
        )
        BEGIN
            DECLARE EXIT HANDLER FOR SQLEXCEPTION
            BEGIN
                -- 오류 발생 시 처리
                ROLLBACK;
                SELECT 'Error occurred, transaction rolled back' AS msg;
            END;

            START TRANSACTION;
                UPDATE account
                SET balance = balance - amount
                WHERE account_id = fromAcc;

                UPDATE account
                SET balance = balance + amount
                WHERE account_id = toAcc;
            COMMIT;
        END //
        DELIMITER ;
        ```
        - EXIT HANDLER: 예외 상황이 발생하면 핸들러 블록으로 이동.
        - SQLEXCEPTION: 모든 SQL 오류에 대한 핸들러. 필요 시 `SQLWARNING`, `NOT FOUND` 등 구체적 핸들러 선언 가능.

    2. Oracle PL/SQL 예시
        ```sql
        CREATE OR REPLACE PROCEDURE TransferAmount(
            p_fromAcc IN NUMBER,
            p_toAcc IN NUMBER,
            p_amount IN NUMBER
        )
        IS
            e_insufficient_funds EXCEPTION;
        BEGIN
            UPDATE account
            SET balance = balance - p_amount
            WHERE account_id = p_fromAcc;

            IF SQL%ROWCOUNT = 0 THEN
                RAISE_APPLICATION_ERROR(-20001, 'No fromAcc found');
            END IF;

            UPDATE account
            SET balance = balance + p_amount
            WHERE account_id = p_toAcc;

            COMMIT;

        EXCEPTION
            WHEN e_insufficient_funds THEN
                ROLLBACK;
                DBMS_OUTPUT.PUT_LINE('Insufficient Funds');
            WHEN OTHERS THEN
                ROLLBACK;
                DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
        END;
        ```
        - EXCEPTION 블록: 커스텀 예외(`e_insufficient_funds`), `WHEN OTHERS` 등으로 구분.

4. 커서(Cursor) 사용
    1. 커서: SELECT 결과 집합을 순회하며 레코드를 한 행씩 처리
    2. 타 언어(파이썬, 자바)에서 ResultSet과 유사. DB내부에서 로직 수행 시 사용.

    - MySQL 예시
        ```sql
        DELIMITER //
        CREATE PROCEDURE ListEmployees()
        BEGIN
            DECLARE done INT DEFAULT 0;
            DECLARE empName VARCHAR(100);

            DECLARE empCursor CURSOR FOR
                SELECT employee_name FROM employees;

            DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

            OPEN empCursor;
            REPEAT
                FETCH empCursor INTO empName;
                IF NOT done THEN
                    SELECT CONCAT('Employee: ', empName) AS emp_output;
                END IF;
            UNTIL done END REPEAT;
            CLOSE empCursor;
        END //
        DELIMITER ;
        ```
        - DECLARE empCursor: 커서 정의
        - OPEN: 커서 열기
        - FETCH: 한 행씩 가져오기
        - CLOSE: 커서 닫기

5. 트랜잭션 처리 (프로시저 내부)
    - 이미 트랜잭션 제어(TCL)에서 설명했지만, 프로시저 내부에서 `START TRANSACTION / COMMIT / ROLLBACK`을 활용해 원자적 작업 구성 가능.
    - 주의: 어떤 DB에서는 프로시저 내부에서 자동 COMMIT이 일어날 수도 있으니 DB별 트랜잭션 동작 방식 확인 필요.

6. 동적 SQL 실행
    1. MySQL
        ```sql
        DELIMITER //
        CREATE PROCEDURE DynamicSelect(IN tblName VARCHAR(64))
        BEGIN
            SET @query = CONCAT('SELECT * FROM ', tblName, ' LIMIT 10');
            PREPARE stmt FROM @query;
            EXECUTE stmt;
            DEALLOCATE PREPARE stmt;
        END //
        DELIMITER ;
        ```
        - PREPARE/EXECUTE: 런타임에 문자열로 만든 쿼리를 실행.
        - 보안 상 SQL Injection 위험이 커서 매개변수 바인딩 등 주의 필요.

    2. Oracle (Native Dynamic SQL)
        ```sql
        CREATE OR REPLACE PROCEDURE DynamicSelect(p_tblName IN VARCHAR2)
        IS
            v_query VARCHAR2(1000);
        BEGIN
            v_query := 'SELECT * FROM ' || p_tblName || ' WHERE ROWNUM <= 10';
            EXECUTE IMMEDIATE v_query;
        END;
        ```

7. Stored Procedure & Function 활용 사례
    1. 업무 로직 캡슐화
        - 예: 신규 주문 처리 시 재고 차감, 로그 기록, 포인트 적립 등을 일괄 수행

    2. 정기 배치 & ETL
        - 야간 배치(매출 집계, 통계 테이블 업데이트)
        - DB 내에서 대량 연산 처리(네트워크 트래픽 감소)

    3. 보안/권한 분리
        - 개발자나 애플리케이션이 직접 테이블 접근 대신 프로시저만 호출하도록 제한
        - 접근 제어/검증 로직 포함 가능

    4. 데이터 검증/트리거와 연계
        - 입력값 체크, 제약조건을 프로시저 내에서 추가적으로 처리
        - 트리거에서 프로시저 호출로 복잡 로직 처리