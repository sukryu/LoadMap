# 강하게 연결된 성분 (Strongly Connected Components, SCC) 알고리즘

## 개요
강하게 연결된 성분(SCC)은 방향 그래프에서, 임의의 두 정점 u와 v에 대해 u에서 v로, v에서 u로 모두 도달할 수 있는 최대 정점 집합을 의미합니다.  
즉, 한 SCC 내의 모든 정점들은 서로 강하게 연결되어 있으며, SCC 간에는 단방향 연결만 존재합니다.

## 알고리즘의 핵심 아이디어
SCC를 찾기 위한 대표적인 알고리즘으로는 **Kosaraju의 알고리즘**과 **Tarjan의 알고리즘**이 있습니다.

- **Kosaraju의 알고리즘:**
  1. 원래 그래프에서 DFS를 수행하여 정점의 종료 순서를 기록합니다.
  2. 그래프의 모든 간선 방향을 반대로 한 전치 그래프(transpose graph)를 생성합니다.
  3. 전치 그래프에서, 첫 번째 DFS에서 기록한 정점의 역순으로 DFS를 수행하여 SCC를 추출합니다.

- **Tarjan의 알고리즘:**
  - 한 번의 DFS로 각 정점에 대해 방문 순서와 최소 도달 번호(low-link value)를 계산합니다.
  - DFS 스택을 이용해 현재 탐색 경로에 있는 정점들을 관리하고, low-link 값이 자신과 동일한 정점을 만나면 해당 경로 전체가 하나의 SCC임을 확인합니다.

## 시간 및 공간 복잡도
- **시간 복잡도:**  
  - Kosaraju: O(V + E)  
  - Tarjan: O(V + E)
- **공간 복잡도:**  
  O(V + E) (DFS 스택, 방문 기록, 전치 그래프 또는 low-link 배열 등)

## 장점 및 단점
- **장점:**  
  - 강하게 연결된 정점 집합을 효율적으로 찾을 수 있어, 네트워크 분석, 웹 페이지 링크 분석, 프로그램 의존성 분석 등 다양한 분야에 응용 가능합니다.
  - 선형 시간 알고리즘으로 대규모 그래프에서도 효율적입니다.
- **단점:**  
  - DFS 기반 탐색과 재귀 호출을 사용하므로, 구현이 다소 복잡할 수 있습니다.
  - 방향 그래프에 한정된 개념이며, 무방향 그래프에서는 연결 요소(Connected Components) 알고리즘을 사용합니다.

## 활용 사례
- **소셜 네트워크 분석:**  
  사용자 간 강한 상호 연결 관계를 분석하여 커뮤니티를 식별합니다.
- **웹 링크 분석:**  
  웹 그래프에서 상호 연결된 페이지 그룹을 찾아 검색 엔진 최적화(SEO) 및 웹 크롤링에 활용됩니다.
- **모듈 의존성 분석:**  
  소프트웨어 시스템에서 모듈 간의 강한 의존성을 분석하여 구조적 문제를 식별합니다.

## 참고 자료
- [Wikipedia - Strongly connected component](https://en.wikipedia.org/wiki/Strongly_connected_component)
- [Kosaraju의 알고리즘](https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm)
- [Tarjan의 알고리즘](https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm)