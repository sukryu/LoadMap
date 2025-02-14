/**
 * pure.c
 *
 * 순수 재귀(Pure Recursion) 알고리즘 구현 예제
 *
 * 순수 재귀는 부수 효과(side effect) 없이 오직 입력값과 재귀 호출 결과만을 이용해 문제를 해결하는 방식입니다.
 * 이 파일에서는 순수 재귀의 개념을 보여주기 위해 여러 예제를 구현하였습니다.
 * 각 함수는 외부 상태에 의존하지 않고, 오직 전달된 인자에 기반하여 결과를 반환합니다.
 *
 * 포함된 예제:
 *  - 팩토리얼 계산 (factorial_pure)
 *  - 피보나치 수열 계산 (fibonacci_pure)
 *  - 배열의 합 계산 (sum_array_pure)
 *  - 최대공약수 (gcd_pure)
 *  - 문자열 길이 계산 (string_length)
 *
 * 컴파일: gcc -Wall -O2 pure.c -o pure
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--------------------------------------
  순수 재귀를 이용한 팩토리얼 계산
---------------------------------------*/
/**
 * factorial_pure - 순수 재귀를 이용하여 n의 팩토리얼을 계산합니다.
 * @n: 0 이상의 정수
 *
 * 반환값: n! (n의 팩토리얼)
 *
 * 이 함수는 부수 효과 없이 오직 재귀 호출만을 사용하여 결과를 반환합니다.
 * 예: factorial_pure(5) = 120
 */
long long factorial_pure(int n) {
    if (n < 0) {
        fprintf(stderr, "음수에 대한 팩토리얼은 정의되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0 || n == 1)
        return 1;
    return n * factorial_pure(n - 1);
}

/*--------------------------------------
  순수 재귀를 이용한 피보나치 수열 계산
---------------------------------------*/
/**
 * fibonacci_pure - 순수 재귀를 이용하여 n번째 피보나치 수를 계산합니다.
 * @n: 피보나치 수열의 인덱스 (0 기반)
 *
 * 반환값: n번째 피보나치 수
 *
 * 이 함수는 오직 재귀 호출만으로 결과를 반환하며, 외부 상태에 의존하지 않습니다.
 * 주의: 단순 재귀 구현으로 중복 계산이 발생하므로, n이 크면 비효율적입니다.
 */
long long fibonacci_pure(int n) {
    if (n < 0) {
        fprintf(stderr, "음수 인덱스에 대한 피보나치 수는 정의되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci_pure(n - 1) + fibonacci_pure(n - 2);
}

/*--------------------------------------
  순수 재귀를 이용한 배열의 합 계산
---------------------------------------*/
/**
 * sum_array_pure - 순수 재귀를 이용하여 정수 배열의 합을 계산합니다.
 * @arr: 정수 배열
 * @n: 배열의 길이
 *
 * 반환값: 배열의 모든 원소의 합
 *
 * 이 함수는 배열의 첫 요소와 나머지 배열의 합을 재귀적으로 계산하여 결과를 반환합니다.
 * 예: {1, 2, 3, 4, 5} => sum_array_pure(arr, 5) = 15
 */
int sum_array_pure(const int *arr, int n) {
    if (n <= 0)
        return 0;
    return arr[0] + sum_array_pure(arr + 1, n - 1);
}

/*--------------------------------------
  순수 재귀를 이용한 최대공약수 (GCD) 계산
---------------------------------------*/
/**
 * gcd_pure - 순수 재귀를 이용하여 두 정수의 최대공약수를 계산합니다.
 * @a: 첫 번째 정수
 * @b: 두 번째 정수
 *
 * 반환값: a와 b의 최대공약수
 *
 * 이 함수는 유클리드 알고리즘을 순수 재귀로 구현하여, 부수 효과 없이 결과를 반환합니다.
 * 예: gcd_pure(48, 180) = 12
 */
int gcd_pure(int a, int b) {
    if (b == 0)
        return a;
    return gcd_pure(b, a % b);
}

/*--------------------------------------
  순수 재귀를 이용한 문자열 길이 계산
---------------------------------------*/
/**
 * string_length - 순수 재귀를 이용하여 문자열의 길이를 계산합니다.
 * @s: 입력 문자열 (NULL 종료)
 *
 * 반환값: 문자열의 길이
 *
 * 이 함수는 NULL 종료 문자에 도달할 때까지 재귀적으로 호출되어 문자열 길이를 계산합니다.
 */
int string_length(const char *s) {
    if (*s == '\0')
        return 0;
    return 1 + string_length(s + 1);
}

/*--------------------------------------
  main 함수: 순수 재귀 예제 데모
---------------------------------------*/
int main(void) {
    // 팩토리얼 예제
    int num = 5;
    printf("순수 재귀 팩토리얼(%d) = %lld\n", num, factorial_pure(num));
    
    // 피보나치 예제
    int fibIndex = 10;
    printf("순수 재귀 피보나치(%d) = %lld\n", fibIndex, fibonacci_pure(fibIndex));
    
    // 배열의 합 예제
    int arr[] = {1, 2, 3, 4, 5};
    int arrLength = sizeof(arr) / sizeof(arr[0]);
    printf("순수 재귀 배열의 합 = %d\n", sum_array_pure(arr, arrLength));
    
    // 최대공약수 예제
    int a = 48, b = 180;
    printf("순수 재귀 gcd(%d, %d) = %d\n", a, b, gcd_pure(a, b));
    
    // 문자열 길이 계산 예제
    const char *text = "PureRecursion";
    printf("순수 재귀 문자열 길이(\"%s\") = %d\n", text, string_length(text));
    
    return 0;
}