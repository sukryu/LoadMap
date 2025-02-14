/**
 * tail_recursion.c
 *
 * 꼬리 재귀(Tail Recursion) 알고리즘 구현 예제
 *
 * 이 파일은 꼬리 재귀를 활용한 여러 예제를 포함합니다.
 * 꼬리 재귀는 재귀 호출이 함수의 마지막 작업으로 이루어져,
 * 컴파일러 최적화를 통해 반복문처럼 변환되어 스택 사용을 최소화할 수 있습니다.
 *
 * 아래 예제들은 실무에서도 활용 가능한 꼬리 재귀 함수들을 보여줍니다:
 *  - 꼬리 재귀를 이용한 팩토리얼 계산
 *  - 꼬리 재귀를 이용한 피보나치 수열 계산
 *  - 꼬리 재귀를 이용한 배열의 합 계산
 *  - 꼬리 재귀를 이용한 거듭제곱 계산
 *  - 꼬리 재귀를 이용한 최대공약수(GCD) 계산
 *  - 꼬리 재귀를 이용한 배열 원소 순차 출력
 *
 * 컴파일: gcc -Wall -O2 tail_recursion.c -o tail_recursion
 */

#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------
  꼬리 재귀를 이용한 팩토리얼 계산
---------------------------------------*/
/**
 * tail_factorial_helper - 꼬리 재귀를 이용하여 팩토리얼을 계산하는 헬퍼 함수
 * @n: 계산할 수 (0 이상의 정수)
 * @acc: 누적 곱 (초기 호출 시 1)
 *
 * 반환값: n! (n의 팩토리얼)
 *
 * 이 함수는 꼬리 재귀 형태로 팩토리얼을 계산하며,
 * 재귀 호출 후 추가 작업이 없으므로, 컴파일러 최적화를 통해 반복문처럼 효율적으로 동작할 수 있습니다.
 */
static long long tail_factorial_helper(int n, long long acc) {
    if (n <= 1)
        return acc;
    return tail_factorial_helper(n - 1, acc * n);
}

/**
 * factorial_tail - 꼬리 재귀를 이용한 팩토리얼 계산 함수
 * @n: 계산할 수
 *
 * 반환값: n! (n의 팩토리얼)
 */
long long factorial_tail(int n) {
    if (n < 0) {
        fprintf(stderr, "음수에 대한 팩토리얼은 정의되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    return tail_factorial_helper(n, 1);
}

/*--------------------------------------
  꼬리 재귀를 이용한 피보나치 수열 계산
---------------------------------------*/
/**
 * tail_fibonacci_helper - 꼬리 재귀를 이용한 피보나치 수열 계산 헬퍼 함수
 * @n: 계산할 항의 인덱스 (0 기반)
 * @a: 현재 항의 값 (초기 호출 시 0)
 * @b: 다음 항의 값 (초기 호출 시 1)
 *
 * 반환값: n번째 피보나치 수
 *
 * 이 함수는 꼬리 재귀를 통해 피보나치 수열의 n번째 항을 효율적으로 계산합니다.
 */
static long long tail_fibonacci_helper(int n, long long a, long long b) {
    if (n == 0)
        return a;
    return tail_fibonacci_helper(n - 1, b, a + b);
}

/**
 * fibonacci_tail - 꼬리 재귀를 이용한 피보나치 수열 계산 함수
 * @n: 계산할 항의 인덱스 (0 기반)
 *
 * 반환값: n번째 피보나치 수
 */
long long fibonacci_tail(int n) {
    if (n < 0) {
        fprintf(stderr, "음수 인덱스에 대한 피보나치 수열은 정의되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    return tail_fibonacci_helper(n, 0, 1);
}

/*--------------------------------------
  꼬리 재귀를 이용한 배열의 합 계산
---------------------------------------*/
/**
 * tail_sum_array_helper - 꼬리 재귀를 이용하여 배열의 합을 계산하는 헬퍼 함수
 * @arr: 정수 배열
 * @n: 배열의 길이
 * @acc: 누적 합 (초기 호출 시 0)
 *
 * 반환값: 배열의 모든 원소의 합
 */
static int tail_sum_array_helper(const int *arr, int n, int acc) {
    if (n <= 0)
        return acc;
    return tail_sum_array_helper(arr + 1, n - 1, acc + arr[0]);
}

/**
 * sum_array_tail - 꼬리 재귀를 이용하여 배열의 합을 계산하는 함수
 * @arr: 정수 배열
 * @n: 배열의 길이
 *
 * 반환값: 배열의 모든 원소의 합
 */
int sum_array_tail(const int *arr, int n) {
    return tail_sum_array_helper(arr, n, 0);
}

/*--------------------------------------
  꼬리 재귀를 이용한 거듭제곱 계산 (base^exp)
---------------------------------------*/
/**
 * tail_power_helper - 꼬리 재귀를 이용한 거듭제곱 계산 헬퍼 함수
 * @base: 밑
 * @exp: 지수 (0 이상의 정수)
 * @acc: 누적 결과 (초기 호출 시 1)
 *
 * 반환값: base의 exp 제곱
 */
static long long tail_power_helper(int base, int exp, long long acc) {
    if (exp < 0) {
        fprintf(stderr, "음수 지수는 지원되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    if (exp == 0)
        return acc;
    return tail_power_helper(base, exp - 1, acc * base);
}

/**
 * power_tail - 꼬리 재귀를 이용한 거듭제곱 계산 함수
 * @base: 밑
 * @exp: 지수 (0 이상의 정수)
 *
 * 반환값: base의 exp 제곱
 */
long long power_tail(int base, int exp) {
    return tail_power_helper(base, exp, 1);
}

/*--------------------------------------
  꼬리 재귀를 이용한 최대공약수 (GCD) 계산
---------------------------------------*/
/**
 * gcd_tail - 꼬리 재귀를 이용하여 두 정수의 최대공약수를 계산하는 함수
 * @a: 첫 번째 정수
 * @b: 두 번째 정수
 *
 * 반환값: a와 b의 최대공약수
 *
 * 유클리드 알고리즘은 자연스럽게 꼬리 재귀 형태를 띄며, 
 * 이 함수는 마지막에 재귀 호출 없이 바로 결과를 반환합니다.
 */
int gcd_tail(int a, int b) {
    if (b == 0)
        return a;
    return gcd_tail(b, a % b);
}

/*--------------------------------------
  꼬리 재귀를 이용한 배열 원소 순차 출력
---------------------------------------*/
/**
 * tail_print_forward - 꼬리 재귀를 이용하여 배열의 원소를 순차적으로 출력하는 함수
 * @arr: 정수 배열
 * @n: 배열의 길이
 * @index: 현재 인덱스 (초기 호출 시 0)
 *
 * 이 함수는 현재 인덱스에서 배열 끝까지 원소를 출력한 후, 재귀 호출 없이 종료됩니다.
 */
void tail_print_forward(const int *arr, int n, int index) {
    if (index >= n)
        return;
    printf("%d ", arr[index]);
    tail_print_forward(arr, n, index + 1);
}

int main(void) {
    // 꼬리 재귀 팩토리얼 예제
    int num = 10;
    printf("꼬리 재귀 팩토리얼(%d) = %lld\n", num, factorial_tail(num));
    
    // 꼬리 재귀 피보나치 예제
    int fibIndex = 10;
    printf("꼬리 재귀 피보나치(%d) = %lld\n", fibIndex, fibonacci_tail(fibIndex));
    
    // 꼬리 재귀 배열의 합 예제
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrLength = sizeof(arr) / sizeof(arr[0]);
    printf("꼬리 재귀 배열의 합 = %d\n", sum_array_tail(arr, arrLength));
    
    // 꼬리 재귀 거듭제곱 예제
    int base = 2, exp = 10;
    printf("꼬리 재귀: %d의 %d제곱 = %lld\n", base, exp, power_tail(base, exp));
    
    // 꼬리 재귀 최대공약수 예제
    int a = 48, b = 180;
    printf("꼬리 재귀 gcd(%d, %d) = %d\n", a, b, gcd_tail(a, b));
    
    // 꼬리 재귀 배열 원소 순차 출력 예제
    printf("꼬리 재귀 배열 원소 순차 출력: ");
    tail_print_forward(arr, arrLength, 0);
    printf("\n");
    
    return 0;
}