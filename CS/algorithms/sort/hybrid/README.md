# 하이브리드 정렬
* 대부분 실제 프로그래밍 언어나 라이브러리에서 사용됨.
* 이론적 성능과 실제 성능의 균형을 고려.
* 메모리 사용량, 캐시 효율성, 안정성 등 다양한 요소를 최적화.
* 데이터의 특성에 따라 적절한 알고리즘으로 전환하는 적응형 방식 사용.

**이 중에서도 Time Sort와 Intro Sort가 가장 널리 사용되는 하이브리드 정렬 알고리즘.**

## Time Sort
* Python과 Java의 기본 정렬 알고리즘
* Merge Sort와 Insertion Sort의 조합
* 실제 데이터가 부분적으로 정렬된 경우 매우 효율적
* 안정적 정렬이 필요할 때
* 다양한 크기의 데이터 셋 처리리
[Time Sort](timesort.md)

## Intro Sort (Introspective Sort)
* C++ STL의 std::sort 구현에 사용
* Quick Sort, Heap Sort, Insertion Sort의 조합
* Quick Sort를 기본으로 사용하다가 재귀 깊이가 너무 깊어지면 Heap Sort로 전환
* 작은 크기의 배열에는 Insertion Sort 사용
* 최악의 경우 성능 보장 필요
* 메모리 사용량 제한이 있을 때
* 범용 정렬 알고리즘 필요요
[Intro Sort](introsort.md)

## Block Sort
* Merge Sort를 기반으로 하되, 메모리 지역성을 개선
* In-place merge sort의 최적화 버전
* 블록 단위로 데이터를 처리하여 캐시 효율성 향상
* 캐시 효율성이 중요한 환경
* 제한된 메모리에서 대용량 데이터 처리
* In-place 정렬이 필요할 때
[Block Sort](blocksort.md)

## PSort(Parallel Sort)
* 병렬 처리를 활용한 하이브리드 정렬
* 데이터를 여러 청크로 나누어 병렬 처리
* 각 청크는 다른 정렬 알고리즘(예: Quick Sort)으로 정렬 후 병합
* 멀티코어 환경
* 대용량 데이터 처리
* 병렬 처리 가능한 시스템템
[PSort](psort.md)

## Wiki Sort
* Block Merge Sort의 변형
* In-place Merge Sort의 최적화 버전
* 메모리 사용량과 실행 시간의 균형을 맞춤
* 메모리 사용량 최적화 필요
* In-place 정렬 요구
* 안정적 성능 필요요
[Wiki Sort](wikisort.md)

## Quick Merge Sort
* Quick Sort와 Merge Sort의 조합
* Quick Sort의 파티션을 사용하고 Merge Sort의 병합 과정을 최적화
* Quick Sort의 성능과 병합 정렬의 안정성 모두 필요
* 평균적으로 좋은 성능 요구
* 추가 메모리 사용 가능한 환경
[Quick Merege Sort](quickmergesort.md)