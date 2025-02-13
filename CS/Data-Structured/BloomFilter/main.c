/*
 * main.c
 *
 * 이 파일은 블룸 필터(Bloom Filter) 자료구조의 고도화된 구현 예제입니다.
 * 블룸 필터는 매우 메모리 효율적인 확률적 데이터 구조로,  
 * 특정 원소가 집합에 포함되어 있는지를 빠르게 검사할 수 있습니다.
 * (검사 결과 "없음"은 확실하지만, "있음"의 경우 거짓 양성(False Positive)이 발생할 수 있습니다.)
 *
 * 주요 기능:
 * - bloom_filter_create: 지정된 비트 배열 크기(m)와 해시 함수 수(k)를 기반으로 블룸 필터를 초기화합니다.
 * - bloom_filter_add: 입력된 문자열을 블룸 필터에 추가하여, 관련 비트들을 설정합니다.
 * - bloom_filter_query: 입력된 문자열이 블룸 필터에 존재하는지 검사합니다.
 * - bloom_filter_free: 할당된 블룸 필터 메모리를 해제합니다.
 *
 * 이 구현은 B+ Tree의 고도화된 구현 스타일을 참고하여,  
 * 다중 해시 함수(더블 해싱)를 사용해 k개의 해시 값을 생성하고,  
 * 이를 이용하여 비트 배열의 특정 인덱스를 업데이트 및 검사합니다.
 *
 * 참고: 실제 실무 환경에서는 입력 검증, 동적 크기 조정, 해시 함수 최적화 등이 추가적으로 필요할 수 있습니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// -----------------------------
// 블룸 필터 자료구조 정의
// -----------------------------
typedef struct BloomFilter {
    unsigned char *bit_array;  // 비트 배열 (각 비트가 0 또는 1을 저장)
    size_t size;               // 비트 배열의 크기 (비트 단위)
    int num_hashes;            // 사용될 해시 함수 수 (k)
} BloomFilter;

// -----------------------------
// 헬퍼 함수: 비트 조작
// -----------------------------
// bit_array는 1바이트 단위로 저장되므로, 특정 비트 설정 및 확인을 위한 함수들입니다.
void set_bit(BloomFilter *bf, size_t pos) {
    size_t byte_index = pos / 8;
    int bit_index = pos % 8;
    bf->bit_array[byte_index] |= (1 << bit_index);
}

bool get_bit(BloomFilter *bf, size_t pos) {
    size_t byte_index = pos / 8;
    int bit_index = pos % 8;
    return (bf->bit_array[byte_index] & (1 << bit_index)) != 0;
}

// -----------------------------
// 해시 함수: 두 가지 기본 해시 함수 (djb2, sdbm)
// -----------------------------
unsigned int hash_djb2(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    return hash;
}

unsigned int hash_sdbm(const char *str) {
    unsigned int hash = 0;
    int c;
    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash;
}

// -----------------------------
// 블룸 필터 생성 및 초기화
// -----------------------------
/*
 * bloom_filter_create 함수:
 * 비트 배열의 크기(m, 비트 단위)와 해시 함수의 개수(k)를 받아 블룸 필터를 초기화합니다.
 * 비트 배열은 1-indexed가 아닌, 0-indexed로 바이트 단위로 할당됩니다.
 */
BloomFilter* bloom_filter_create(size_t m, int k) {
    BloomFilter *bf = (BloomFilter*) malloc(sizeof(BloomFilter));
    if (bf == NULL) {
        fprintf(stderr, "bloom_filter_create: 메모리 할당 실패!\n");
        exit(EXIT_FAILURE);
    }
    bf->size = m;
    bf->num_hashes = k;
    // 바이트 단위로 할당: m 비트를 저장하려면 (m+7)/8 바이트 필요
    size_t byte_size = (m + 7) / 8;
    bf->bit_array = (unsigned char*) calloc(byte_size, sizeof(unsigned char));
    if (bf->bit_array == NULL) {
        fprintf(stderr, "bloom_filter_create: 비트 배열 메모리 할당 실패!\n");
        free(bf);
        exit(EXIT_FAILURE);
    }
    return bf;
}

// -----------------------------
// 블룸 필터에 원소 추가
// -----------------------------
/*
 * bloom_filter_add 함수:
 * 입력 문자열(item)을 블룸 필터에 추가합니다.
 * 두 개의 기본 해시 함수 (djb2와 sdbm)를 이용하여, 
 * 더블 해싱 기법으로 k개의 해시 값을 생성하고, 
 * 해당 비트들을 1로 설정합니다.
 */
void bloom_filter_add(BloomFilter *bf, const char *item) {
    unsigned int hash1 = hash_djb2(item);
    unsigned int hash2 = hash_sdbm(item);
    for (int i = 0; i < bf->num_hashes; i++) {
        // 더블 해싱: hash_i = (hash1 + i * hash2) mod m
        unsigned int combined_hash = (hash1 + i * hash2) % bf->size;
        set_bit(bf, combined_hash);
    }
}

// -----------------------------
// 블룸 필터에서 원소 존재 여부 검사
// -----------------------------
/*
 * bloom_filter_query 함수:
 * 입력 문자열(item)이 블룸 필터에 존재하는지 검사합니다.
 * k개의 해시 함수를 이용하여 계산한 모든 비트가 1이면, 
 * 원소가 존재할 가능성이 있다고 판단하며 (거짓 양성 가능성 있음),
 * 하나라도 0이면 원소가 없음을 확실하게 판별합니다.
 */
bool bloom_filter_query(BloomFilter *bf, const char *item) {
    unsigned int hash1 = hash_djb2(item);
    unsigned int hash2 = hash_sdbm(item);
    for (int i = 0; i < bf->num_hashes; i++) {
        unsigned int combined_hash = (hash1 + i * hash2) % bf->size;
        if (!get_bit(bf, combined_hash))
            return false;
    }
    return true;
}

// -----------------------------
// 블룸 필터 메모리 해제
// -----------------------------
void bloom_filter_free(BloomFilter *bf) {
    if (bf) {
        free(bf->bit_array);
        free(bf);
    }
}

// -----------------------------
// 블룸 필터 내부 상태 출력 (디버깅용)
// -----------------------------
void printBloomFilter(BloomFilter *bf) {
    size_t byte_size = (bf->size + 7) / 8;
    printf("Bloom Filter 상태 (비트 배열, 총 %zu 바이트):\n", byte_size);
    for (size_t i = 0; i < byte_size; i++) {
        printf("%02X ", bf->bit_array[i]);
    }
    printf("\n");
}

// -----------------------------
// main 함수: 블룸 필터 데모
// -----------------------------
int main(void) {
    // 난수 초기화 필요 없음. 블룸 필터는 확률적이지만, 해시 함수는 deterministic 합니다.
    // 블룸 필터 생성: 예를 들어, 1000 비트 크기의 배열과 4개의 해시 함수를 사용.
    size_t m = 1000;
    int k = 4;
    BloomFilter *bf = bloom_filter_create(m, k);
    
    printf("블룸 필터 생성: 비트 배열 크기 = %zu, 해시 함수 수 = %d\n", m, k);
    printBloomFilter(bf);
    printf("\n");
    
    // 테스트: 몇 가지 원소(문자열)를 추가합니다.
    const char *items_to_add[] = { "apple", "banana", "cherry", "date", "elderberry" };
    int num_items = sizeof(items_to_add) / sizeof(items_to_add[0]);
    for (int i = 0; i < num_items; i++) {
        bloom_filter_add(bf, items_to_add[i]);
        printf("Inserted: \"%s\"\n", items_to_add[i]);
    }
    printf("\n블룸 필터 상태 (업데이트 후):\n");
    printBloomFilter(bf);
    printf("\n");
    
    // 검색 테스트: 존재하는 원소와 존재하지 않는 원소를 검사합니다.
    const char *search_items[] = { "apple", "banana", "coconut", "date", "fig" };
    int num_search = sizeof(search_items) / sizeof(search_items[0]);
    for (int i = 0; i < num_search; i++) {
        bool found = bloom_filter_query(bf, search_items[i]);
        printf("Search: \"%s\" -> %s\n", search_items[i], found ? "Possibly Present" : "Definitely Not Present");
    }
    printf("\n");
    
    // 메모리 해제
    bloom_filter_free(bf);
    printf("블룸 필터 메모리 해제 완료.\n");
    
    return 0;
}