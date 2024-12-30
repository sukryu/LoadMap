# Hybrid Search

## Two-Way String Matching
* Boyer-Moore와 KMP의 아이디어를 결합
* 양방향(Bidirectional) 검색 수행
* 더 효율적인 건너뛰기를 위해 두 알고리즘의 장점을 활용

**실제 텍스트 검색 엔진에서 효율적으로 사용될 수 있는 실용적인 알고리즘**
[Two-Way String Matching](twsm.md)

## Hybrid Pattern Matching
* 패턴 길이에 따라 다른 알고리즘 사용
* 예: 짧은 패턴은 브루트 포스, 긴 패턴은 Boyer-Moore
* 상황에 따라 최적의 알고리즘 선택

**실제 응용에서 다양한 패턴을 효율적으로 처리할 수 있는 실용적인 접근 방식**
[Hybrid Pattern Matching](hpm.md)

## Commentz-Walter 알고리즘
* Aho-Corasick과 Boyer-Moore의 결합
* 다중 패턴 매칭에서 효율적인 건너뛰기 제공
* 역방향 검색과 실패 함수 모두 활용

**실제 다중 패턴 매칭이 필요한 시스템에서 효율적으로 사용될 수 있는 알고리즘**
[Commentz-Walter](cw.md)

## Set-Backward Oracle Matching (SBOM)
* Boyer-Moore와 오토마타 기반 접근의 결합
* 효율적인 다중 패턴 매칭
* Factor oracle 구조 활용

**특히 메모리 효율성과 검색 속도의 균형을 잘 맞춘 알고리즘**
[Set-Backward Oracle Matching](sbom.md)

## Wu-Manber 알고리즘
* Boyer-Moore와 해시 기반 접근의 결합
* 다중 패턴 매칭에 최적화
* 블록 단위 처리로 성능 향상

**실제 시스템에서 널리 사용되는 효율적인 다중 패턴 매칭 알고리즘.**
[Wu-Manber](wm.md)