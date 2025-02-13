/*
 * main.c
 *
 * Array 자료구조를 활용하는 다양한 예제들을 포함한 파일입니다.
 * 이 코드는 C 언어에서 배열을 정적 및 동적으로 활용하는 방법과,
 * 정렬, 탐색, 2차원 배열의 사용 예제를 보여줍니다.
 *
 * 초보자부터 실무자까지 이해할 수 있도록 상세한 주석과 함께 작성되었습니다.
 */

#include <stdio.h>
#include <stdlib.h>

// 함수 원형 선언
void printArray(int arr[], int size);
void bubbleSort(int arr[], int size);
int binarySearch(int arr[], int size, int target);

int main(void) {
    // 1. 정적 배열(static array) 예제
    int staticArray[] = {5, 2, 8, 1, 9, 3};
    int staticSize = sizeof(staticArray) / sizeof(staticArray[0]);

    printf("=== 정적 배열 예제 ===\n");
    printf("초기 배열: ");
    printArray(staticArray, staticSize);

    // 버블 정렬을 사용하여 배열 정렬
    bubbleSort(staticArray, staticSize);
    printf("정렬된 배열: ");
    printArray(staticArray, staticSize);

    // 이진 탐색을 사용하여 값 검색 (정렬된 배열 필요)
    int target = 8;
    int index = binarySearch(staticArray, staticSize, target);
    if (index != -1) {
        printf("값 %d(은)는 인덱스 %d에서 발견되었습니다.\n\n", target, index);
    } else {
        printf("값 %d을(를) 배열에서 찾을 수 없습니다.\n\n", target);
    }

    // 2. 동적 배열(dynamic array) 예제
    int dynamicSize = 5;
    int* dynamicArray = (int*)malloc(dynamicSize * sizeof(int));
    if (dynamicArray == NULL) {
        fprintf(stderr, "동적 메모리 할당 실패!\n");
        return 1;
    }

    // 동적 배열 초기화: 10, 20, 30, 40, 50
    for (int i = 0; i < dynamicSize; i++) {
        dynamicArray[i] = (i + 1) * 10;
    }

    printf("=== 동적 배열 예제 ===\n");
    printf("동적 배열: ");
    printArray(dynamicArray, dynamicSize);

    // 동적 배열 메모리 해제
    free(dynamicArray);
    printf("\n");

    // 3. 2차원 배열 (Matrix) 예제
    printf("=== 2차원 배열 예제 ===\n");
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    printf("2차원 배열 (3x3 행렬):\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/*
 * printArray 함수:
 * 주어진 배열의 모든 요소를 출력합니다.
 */
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 * bubbleSort 함수:
 * 버블 정렬 알고리즘을 사용하여 배열을 오름차순으로 정렬합니다.
 */
void bubbleSort(int arr[], int size) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // 두 요소 교환
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/*
 * binarySearch 함수:
 * 정렬된 배열에서 이진 탐색 알고리즘을 사용하여 target 값을 찾습니다.
 * 성공하면 해당 인덱스를 반환하고, 실패하면 -1을 반환합니다.
 */
int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}