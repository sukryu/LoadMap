# Set-Backward Oracle Matching (SBOM)

## 개요
Set-Backward Oracle Matching (SBOM) 알고리즘은 Boyer-Moore의 불일치 휴리스틱과 오토마타 기반 접근의 장점을 결합한 문자열 검색 알고리즘입니다.  
특히, factor oracle 자료구조를 활용하여 다중 패턴 매칭 및 단일 패턴 매칭에서 효율적인 성능과 낮은 메모리 소비를 목표로 합니다.  
SBOM은 패턴 집합에 대한 정보를 통합하고, 각 패턴의 특성을 반영한 건너뛰기 전략을 적용함으로써, 다양한 검색 환경에서 우수한 성능을 발휘합니다.

## 동작 원리
- **Factor Oracle 기반 오토마타:**  
  - SBOM은 문자열의 factor oracle을 구축하여, 패턴 내 모든 가능한 부분 문자열(요인)의 정보를 효율적으로 저장합니다.  
  - 이 오토마타는 전통적인 오토마타보다 간결하며, 검색에 필요한 최소한의 정보를 제공하여 메모리 사용량을 절감합니다.

- **뒤로 검색 (Backward Matching):**  
  - Boyer-Moore 알고리즘과 유사하게, 패턴의 뒤쪽부터 텍스트와 비교를 시작합니다.  
  - 불일치가 발생하면, factor oracle과 오토마타 기반 정보를 활용하여 적절한 건너뛰기(shift) 값을 계산합니다.

- **집합 기반 매칭:**  
  - 다중 패턴 검색을 위해, 여러 패턴의 정보를 하나의 집합으로 통합합니다.  
  - 각 패턴에 대해 개별적으로 계산한 건너뛰기 값을 활용하여, 텍스트를 한 번만 스캔하면서 모든 패턴의 매칭 결과를 효율적으로 찾아냅니다.

## 알고리즘 특징
- **효율성:**  
  - 불필요한 문자 비교를 최소화하며, 특히 다중 패턴 검색 상황에서 뛰어난 성능을 보입니다.  
  - 최악의 경우에도 경쟁력 있는 시간 복잡도를 유지할 수 있습니다.
  
- **공간 효율성:**  
  - Factor oracle은 전통적인 오토마타에 비해 간결하게 구성되어, 메모리 사용량을 절감합니다.  
  - 많은 수의 패턴을 처리하는 경우에도 상대적으로 낮은 공간 복잡도를 유지합니다.
  
- **적응성:**  
  - 패턴의 길이와 문자 분포에 따라 동적으로 건너뛰기 값을 조정할 수 있어, 다양한 데이터 환경에 유연하게 적용됩니다.
  
- **단점:**  
  - 초기 전처리(오토마타 및 factor oracle 구축) 과정이 복잡하고 구현 난이도가 높을 수 있습니다.  
  - 특정 데이터 분포에서는 최신 다른 알고리즘과 비교하여 성능 차이가 미미할 수 있습니다.

## 활용 사례
- **다중 패턴 검색:**  
  - 검색 엔진, 콘텐츠 필터링, 보안 검사 등 다수의 패턴을 동시에 검색해야 하는 시스템에서 활용됩니다.
  
- **실시간 시스템:**  
  - 빠른 검색 응답이 요구되는 실시간 애플리케이션에서 효율적인 매칭 성능을 제공합니다.
  
- **메모리 제한 환경:**  
  - 모바일 기기나 임베디드 시스템과 같이 메모리 사용량을 최소화해야 하는 환경에서 유리합니다.

## 참고 자료
- [Wikipedia - Factor Oracle](https://en.wikipedia.org/wiki/Factor_oracle)
- 관련 연구 논문 및 알고리즘 서적:  
  - Allauzen, C., Crochemore, M., & Raffinot, M. (1999). "Factor Oracles: A New Structure for Pattern Matching".
- 최신 학술 논문 및 기술 보고서