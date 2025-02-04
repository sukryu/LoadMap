# 복잡 쿼리 튜닝 사례집

대규모 시스템이나 복잡한 데이터 집합을 다루는 환경에서는 쿼리 성능이 전체 시스템의 응답 속도와 안정성에 큰 영향을 미칩니다.  
이 문서에서는 다양한 복잡 쿼리 튜닝 사례를 통해 쿼리 분석, 인덱스 최적화, 조인 전략 개선, 쿼리 리팩토링 등의 기법과 실제 구현 방법을 소개합니다.

---

## 1. 개념 개요

복잡한 쿼리 튜닝은 단순히 쿼리를 빠르게 만드는 것을 넘어, 전체 시스템의 리소스 사용을 최적화하고 확장성을 높이는 데 목적이 있습니다.  
주요 튜닝 요소는 다음과 같습니다.

- **인덱스 최적화:**  
  쿼리 대상 컬럼에 적절한 인덱스를 생성하여 데이터 스캔 범위를 최소화합니다.

- **조인 최적화:**  
  여러 테이블 간 조인의 순서와 방식(Nested Loop, Hash Join 등)을 조정하여 효율성을 높입니다.

- **쿼리 리팩토링:**  
  서브쿼리, 복잡한 조건문 등을 단순화하거나, CTE(Common Table Expression)를 활용해 가독성과 성능을 개선합니다.

- **실행 계획 분석:**  
  데이터베이스의 실행 계획(EXPLAIN, EXPLAIN ANALYZE 등)을 통해 병목 구간을 식별하고 개선합니다.

---

## 2. 문제 상황과 해결 방안

### 2.1. 문제 상황: 복잡 쿼리로 인한 성능 저하

- **지연된 응답 시간:**  
  다수의 테이블을 조인하거나, 대용량 데이터를 스캔하는 쿼리에서 응답 시간이 길어져 사용자 경험이 저하됩니다.
  
- **높은 리소스 사용량:**  
  불필요한 전체 테이블 스캔, 비효율적인 조인 순서 등으로 CPU 및 메모리 사용량이 급증합니다.
  
- **실행 계획 비효율:**  
  잘못된 인덱스 설정이나 부적절한 조인 전략으로 인해 데이터베이스 실행 계획이 최적화되지 않습니다.

### 2.2. 해결 방안

- **인덱스 추가 및 재구성:**  
  쿼리 조건에 맞는 복합 인덱스 생성 및 기존 인덱스 재검토
- **조인 순서 및 방식 최적화:**  
  조인 순서를 재조정하거나, 적절한 조인 방식을 선택하여 불필요한 중간 결과 생성을 줄임
- **쿼리 구조 개선:**  
  서브쿼리를 CTE로 변경하거나, 불필요한 조건 및 연산을 제거하여 쿼리 단순화
- **실행 계획 분석 도구 활용:**  
  EXPLAIN, EXPLAIN ANALYZE 등을 통해 병목 구간을 식별하고, 그에 따른 인덱스나 쿼리 리팩토링 적용

---

## 3. 구체적 구현 방법 및 베스트 프랙티스

### 3.1. 사례 1: 인덱스 최적화를 통한 성능 개선

**문제 상황:**  
회원 테이블(`users`)과 주문 테이블(`orders`)을 조인하는 쿼리에서, 인덱스 부재로 인해 전체 테이블 스캔이 발생하여 응답 시간이 길어짐.

**개선 전 쿼리:**
```sql
SELECT u.username, o.order_date, o.amount
FROM users u
JOIN orders o ON u.user_id = o.user_id
WHERE o.order_date >= '2024-01-01';
```

**개선 방안:**  
- `orders` 테이블의 `order_date`와 `user_id` 컬럼에 복합 인덱스를 생성합니다.
  
**인덱스 생성 예시:**
```sql
CREATE INDEX idx_order_user_date ON orders(user_id, order_date);
```

**개선 후 결과:**  
- 쿼리 실행 계획에서 인덱스를 활용하는 것을 확인  
- 전체 스캔 대신 인덱스 스캔으로 변경되어 응답 속도 및 리소스 사용량 개선

### 3.2. 사례 2: 조인 순서 및 방식 최적화

**문제 상황:**  
두 개 이상의 테이블 조인 시, 조인 순서가 비효율적으로 설정되어 불필요한 중간 결과가 생성됨.

**개선 전 쿼리:**
```sql
SELECT p.product_name, c.category_name, s.supplier_name
FROM products p
JOIN suppliers s ON p.supplier_id = s.supplier_id
JOIN categories c ON p.category_id = c.category_id
WHERE s.region = 'Asia';
```

**개선 방안:**  
- 먼저 지역 필터가 적용된 `suppliers` 테이블을 서브쿼리 또는 CTE로 처리하여 데이터량을 줄인 후 조인합니다.

**개선 후 쿼리 (CTE 사용 예시):**
```sql
WITH filtered_suppliers AS (
  SELECT supplier_id, supplier_name
  FROM suppliers
  WHERE region = 'Asia'
)
SELECT p.product_name, c.category_name, fs.supplier_name
FROM products p
JOIN filtered_suppliers fs ON p.supplier_id = fs.supplier_id
JOIN categories c ON p.category_id = c.category_id;
```

**개선 후 결과:**  
- 먼저 필터링된 공급업체만 조인 대상이 되어 불필요한 데이터 로드를 줄임  
- 전체 쿼리 실행 시간이 단축됨

### 3.3. 사례 3: 서브쿼리 리팩토링

**문제 상황:**  
중첩된 서브쿼리로 인해 복잡도가 높아지고, 실행 계획이 최적화되지 않아 성능 저하 발생.

**개선 전 쿼리:**
```sql
SELECT user_id, username
FROM users
WHERE user_id IN (
  SELECT user_id
  FROM orders
  WHERE amount > (
    SELECT AVG(amount)
    FROM orders
  )
);
```

**개선 방안:**  
- 서브쿼리를 CTE로 분리하여 가독성을 높이고, 데이터베이스가 더 효율적으로 실행 계획을 생성할 수 있도록 유도합니다.

**개선 후 쿼리 (CTE 사용 예시):**
```sql
WITH avg_order AS (
  SELECT AVG(amount) AS avg_amount
  FROM orders
),
high_value_orders AS (
  SELECT user_id
  FROM orders, avg_order
  WHERE amount > avg_order.avg_amount
)
SELECT u.user_id, u.username
FROM users u
JOIN high_value_orders hvo ON u.user_id = hvo.user_id;
```

**개선 후 결과:**  
- CTE를 통해 각 서브쿼리의 결과를 명확하게 분리  
- 실행 계획 분석 시, 각 단계별 최적화가 용이해짐

---

## 4. 추가 고려 사항

- **실행 계획 주기적 분석:**  
  주기적으로 `EXPLAIN` 또는 `EXPLAIN ANALYZE` 명령어를 사용해 실행 계획을 분석하고, 병목 구간을 확인합니다.
  
- **데이터 분포 및 통계 정보:**  
  쿼리 튜닝 시, 데이터 분포와 통계 정보를 활용해 인덱스 선택과 조인 순서를 결정합니다.
  
- **캐싱 전략 활용:**  
  자주 사용되는 쿼리 결과를 캐싱하여, 반복 실행 시 데이터베이스 부하를 줄이는 방안을 고려합니다.
  
- **쿼리 모니터링 및 로그 분석:**  
  데이터베이스 모니터링 도구를 통해 쿼리 실행 시간, 리소스 사용량 등을 실시간으로 모니터링하고, 로그를 분석하여 추가 최적화 포인트를 도출합니다.

- **테스트 환경에서의 검증:**  
  실제 운영 환경에 적용하기 전에 테스트 환경에서 튜닝 결과를 검증하고, 예상치 못한 부작용이 없는지 확인합니다.

---

## 5. 결론

복잡 쿼리 튜닝은 단순한 문법 수정 이상의 문제로, 데이터 구조, 인덱스 전략, 조인 순서, 서브쿼리 처리 등 다각적인 접근이 필요합니다.

- **인덱스 최적화, 조인 전략 개선, 쿼리 리팩토링** 등 다양한 기법을 상황에 맞게 조합하여 최적의 성능을 도출할 수 있습니다.
- **실행 계획 분석**과 **모니터링**을 통해 지속적으로 튜닝 포인트를 발굴하고, 시스템 변화에 맞춰 유연하게 대응하는 것이 중요합니다.

이 문서에서 소개한 사례들을 참고하여, 실제 시스템 환경에 맞는 최적의 쿼리 튜닝 전략을 수립하고 적용함으로써, 안정적이고 효율적인 데이터베이스 운영을 달성할 수 있기를 바랍니다.