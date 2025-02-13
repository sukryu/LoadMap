/*
 * main.c
 *
 * 이 파일은 접미사 배열(Suffix Array) 자료구조의 고도화된 구현 예제입니다.
 * 접미사 배열은 주어진 문자열의 모든 접미사를 사전 순으로 정렬한 후,
 * 각 접미사의 시작 인덱스를 배열로 저장하는 자료구조로,
 * 패턴 매칭, 중복 서브스트링 검색, 텍스트 분석 등 다양한 응용 분야에서 활용됩니다.
 *
 * 이 구현은 B+ Tree의 고도화된 구현 스타일을 참고하여 작성되었으며,
 * 에러 처리, 메모리 관리 및 다양한 케이스를 모두 고려한 Naive 알고리즘을 사용합니다.
 * (실제 대규모 텍스트 처리에서는 O(n log n) 또는 O(n) 알고리즘(예: SA-IS)을 사용해야 하지만,
 *  본 예제에서는 교육용 Naive 방법을 채택하였습니다.)
 *
 * 주요 기능:
 * - buildSuffixArray: 입력 문자열에 대한 접미사 배열을 구축합니다.
 * - printSuffixArray: 접미사 배열과 정렬된 접미사를 출력하여 구조를 확인합니다.
 * - freeSuffixArray: 접미사 배열 생성에 사용된 동적 메모리를 해제합니다.
 *
 * 참고: 실제 실무 환경에서는 보다 효율적인 알고리즘, 추가적인 에러 처리 및 최적화가 필요합니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// 구조체: 각 접미사를 저장하는 구조체.
// index: 원본 문자열에서 해당 접미사의 시작 인덱스
// suffix: 원본 문자열에서 index 위치의 포인터 (접미사 문자열)
typedef struct {
    int index;
    const char *suffix;
} Suffix;

// Comparator 함수: 두 접미사를 사전 순으로 비교합니다.
int compareSuffixes(const void *a, const void *b) {
    Suffix *sufA = (Suffix *)a;
    Suffix *sufB = (Suffix *)b;
    return strcmp(sufA->suffix, sufB->suffix);
}

/*
 * buildSuffixArray 함수:
 * 입력 문자열 text와 그 길이 n을 받아, 접미사 배열을 구성하여
 * 정렬된 접미사의 시작 인덱스를 담은 int 배열을 반환합니다.
 * 반환된 배열의 크기는 n이며, 메모리 할당에 실패하면 프로그램을 종료합니다.
 */
int* buildSuffixArray(const char *text, int n) {
    // n개의 접미사를 저장할 임시 배열 할당
    Suffix *suffixes = (Suffix *) malloc(n * sizeof(Suffix));
    if (!suffixes) {
        fprintf(stderr, "buildSuffixArray: 접미사 배열 메모리 할당 실패.\n");
        exit(EXIT_FAILURE);
    }
    
    // 각 인덱스에서 시작하는 접미사를 초기화
    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].suffix = text + i;
    }
    
    // qsort를 사용하여 접미사들을 사전 순으로 정렬
    qsort(suffixes, n, sizeof(Suffix), compareSuffixes);
    
    // 정렬된 접미사의 시작 인덱스를 저장할 배열 할당
    int *suffixArray = (int *) malloc(n * sizeof(int));
    if (!suffixArray) {
        fprintf(stderr, "buildSuffixArray: suffixArray 메모리 할당 실패.\n");
        free(suffixes);
        exit(EXIT_FAILURE);
    }
    
    // 정렬된 순서에 따라 인덱스 저장
    for (int i = 0; i < n; i++) {
        suffixArray[i] = suffixes[i].index;
    }
    
    // 임시 배열 해제
    free(suffixes);
    return suffixArray;
}

/*
 * printSuffixArray 함수:
 * 입력 문자열 text와 접미사 배열 suffixArray, 그리고 배열 길이 n을 받아,
 * 정렬된 접미사 배열의 각 인덱스와 해당 접미사를 출력합니다.
 */
void printSuffixArray(const char *text, int *suffixArray, int n) {
    printf("Suffix Array (인덱스 순서):\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", suffixArray[i]);
    }
    printf("\n\n정렬된 접미사들:\n");
    for (int i = 0; i < n; i++) {
        printf("[%d]: %s\n", suffixArray[i], text + suffixArray[i]);
    }
}

/*
 * freeSuffixArray 함수:
 * buildSuffixArray 함수로 생성된 접미사 배열 메모리를 해제합니다.
 */
void freeSuffixArray(int *suffixArray) {
    free(suffixArray);
}

/*
 * main 함수:
 * 예제 문자열에 대해 접미사 배열을 구축, 출력 및 메모리 해제를 시연합니다.
 */
int main(void) {
    // 예제 문자열
    const char *text = "banana";
    int n = strlen(text);
    
    printf("원본 문자열: %s\n\n", text);
    
    // 접미사 배열 생성
    int *suffixArray = buildSuffixArray(text, n);
    
    // 접미사 배열 및 정렬된 접미사 출력
    printSuffixArray(text, suffixArray, n);
    
    // 메모리 해제
    freeSuffixArray(suffixArray);
    printf("\n접미사 배열 메모리 해제 완료.\n");
    
    return 0;
}
