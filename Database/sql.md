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
  )
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
    )
    ```

  2. 자동 증가(AUTO_INCREMENT)
    - 새 행이 추가될 때마다 자동으로 1씩 증가
    ```sql
    CREATE TABLE 게시물 (
      글번호 INT AUTO_INCREMENT PRIMARY KEY,
      제목 VARCHAR(200)
    )
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