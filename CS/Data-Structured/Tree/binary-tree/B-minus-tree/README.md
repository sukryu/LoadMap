# B-Tree 자료구조 📚🗃️

B-Tree는 다진 균형 검색 트리(multiway balanced search tree)로,  
하나의 노드에 다수의 키와 자식 포인터를 저장하여 디스크 기반 저장 장치에서 효율적인 데이터 접근을 가능하게 합니다.  
주로 데이터베이스, 파일 시스템, 대용량 저장소에서 사용되며,  
최소한의 높이로 많은 키를 저장할 수 있도록 설계되어 디스크 I/O를 최소화합니다.

---

## 목차 📝
1. [개요](#개요-🧐)
2. [B-Tree의 정의와 특징](#b-tree의-정의와-특징-🔍)
3. [메모리 구조 및 다이어그램](#메모리-구조-및-다이어그램-🖼️)
4. [주요 연산](#주요-연산-🛠️)
5. [장단점](#장단점-⚖️)
6. [실무 활용 예시](#실무-활용-예시-💼)
7. [참고 자료](#참고-자료-🔗)

---

## 개요 🧐
B-Tree는 노드 하나가 다수의 키와 자식 포인터를 가질 수 있는 균형 잡힌 트리 자료구조입니다.  
이 구조는 데이터베이스나 파일 시스템과 같이 디스크 접근 비용이 높은 환경에서  
한 번의 디스크 읽기로 많은 데이터를 처리할 수 있게 해줍니다.  
B-Tree는 모든 리프 노드가 동일한 깊이에 위치하여, 최악의 경우에도 일정한 탐색 성능을 보장합니다.

---

## B-Tree의 정의와 특징 🔍
- **정의**:  
  B-Tree는 각 노드가 최대 *m*개의 자식을 가질 수 있는 다진 트리이며,  
  내부 노드와 리프 노드 모두에 실제 데이터(키)를 저장할 수 있습니다.
  
- **특징**:
  - **다중 자식**: 각 노드는 여러 개의 키와 자식 포인터를 보유하여, 트리의 높이를 낮게 유지합니다.
  - **균형 유지**: 모든 리프 노드는 동일한 깊이에 위치하여, 최악의 경우에도 O(log n) 탐색 성능을 보장합니다.
  - **동적 분할과 병합**: 삽입과 삭제 시 노드 분할(splitting)과 병합(merging)을 통해 트리의 균형을 유지합니다.
  - **디스크 I/O 최적화**: 노드에 다수의 키를 저장함으로써, 한 번의 디스크 접근으로 많은 정보를 읽어올 수 있습니다.

---

## 메모리 구조 및 다이어그램 🖼️
B-Tree의 각 노드는 여러 키와 자식 포인터를 저장합니다.  
내부 노드는 자식 노드에 대한 포인터와 키를 보유하며,  
리프 노드 또한 데이터를 저장하지만, B+ Tree와 달리 내부 노드에도 실제 데이터가 저장됩니다.

```mermaid
flowchart TD
    A[내부 노드<br>키1, 키2, ..., 키(m-1)]
    B[자식 노드]
    C[자식 노드]
    D[자식 노드]
    
    A --> B
    A --> C
    A --> D
```

이 다이어그램은 한 내부 노드가 여러 자식을 가질 수 있음을 보여주며, 각 자식은 다시 B-Tree 구조를 재귀적으로 구성합니다.

---

## 주요 연산 🛠️
B-Tree에서는 다음과 같은 연산이 수행됩니다:

- **검색 (Search)**:  
  루트에서 시작하여 내부 노드의 키들을 순차적으로 비교한 후, 해당 키가 존재하는 리프 노드를 찾아 데이터를 반환합니다.

- **삽입 (Insertion)**:  
  새로운 키를 저장할 리프 노드를 찾아 삽입합니다.  
  만약 노드가 가득 차면, 분할(splitting) 연산을 수행하여 부모 노드로 승격된 키를 삽입하고, 트리의 균형을 유지합니다.

- **삭제 (Deletion)**:  
  특정 키를 삭제한 후, 노드의 최소 키 수 미달이 발생하면 형제 노드와의 재분배(redistribution) 또는 병합(merging) 연산을 통해 트리의 균형을 회복합니다.

---

## 장단점 ⚖️

### 장점 👍
- **높은 디스크 I/O 효율**: 한 번의 디스크 접근으로 많은 키를 읽어올 수 있어, 대용량 데이터 처리에 유리합니다.
- **균형 유지**: 모든 리프 노드가 같은 깊이에 위치하여, 검색 및 업데이트 성능이 예측 가능합니다.
- **유연한 저장**: 노드 분할과 병합을 통해 동적으로 데이터를 관리할 수 있습니다.

### 단점 👎
- **구현 복잡성**: 노드 분할, 병합, 재분배 등 복잡한 연산을 포함하여 구현이 까다롭습니다.
- **메모리 오버헤드**: 각 노드에 다수의 키와 포인터를 저장하므로, 내부 노드의 공간 사용률이 떨어질 수 있습니다.
- **추가 관리 비용**: 데이터 삽입 및 삭제 시 노드 간 재배치 작업으로 인해 오버헤드가 발생할 수 있습니다.

---

## 실무 활용 예시 💼
- **데이터베이스 인덱스**: MySQL, Oracle 등에서 대용량 데이터를 빠르게 검색하기 위해 사용됩니다.
- **파일 시스템**: 디렉토리 구조와 파일 메타데이터를 효율적으로 관리합니다.
- **키-값 저장소**: 대용량 데이터의 범위 검색 및 정렬된 접근을 위해 활용됩니다.

---

## 참고 자료 🔗
- [B-Tree - Wikipedia](https://en.wikipedia.org/wiki/B-tree)
- [GeeksforGeeks - B-Tree Data Structure](https://www.geeksforgeeks.org/b-tree-set-1-introduction-2/)
- [Baekjoon Online Judge](https://www.acmicpc.net/)

---

B-Tree의 구조와 동작 원리를 이해하면,  
대용량 데이터베이스와 파일 시스템에서 효율적인 데이터 저장 및 검색 시스템을 구축할 수 있습니다. 