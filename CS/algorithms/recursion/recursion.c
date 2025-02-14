/**
 * recursion.c
 *
 * 일반 재귀(Recursion) 알고리즘 구현 예제
 *
 * 이 파일은 재귀 알고리즘을 활용한 여러 가지 예제를 포함하고 있습니다.
 * 재귀를 사용하여 문제를 작은 단위로 분할하고 해결하는 방법을 보여줍니다.
 * 실무에서도 활용할 수 있는 다양한 재귀 함수 예시를 제공합니다.
 *
 * 예제:
 *  - 팩토리얼 계산
 *  - 피보나치 수열 계산
 *  - 배열의 합 계산
 *  - 거듭제곱 계산
 *  - 최대공약수 (GCD) 계산
 *  - 배열 원소를 역순으로 출력 (재귀적 출력)
 *
 * 컴파일: gcc -Wall -O2 recursion.c -o recursion
 */

#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------
  팩토리얼 계산 (n!)
---------------------------------------*/
/**
 * factorial - 재귀를 이용하여 팩토리얼을 계산합니다.
 * @n: 계산할 수 (음수 입력은 처리하지 않습니다)
 *
 * 반환값: n! (n의 팩토리얼)
 *
 * 사용 예:
 *   factorial(5) => 120
 */
long long factorial(int n) {
    if (n < 0) {
        fprintf(stderr, "음수에 대한 팩토리얼은 정의되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

/*--------------------------------------
  피보나치 수열 계산
---------------------------------------*/
/**
 * fibonacci - 재귀를 이용하여 n번째 피보나치 수를 계산합니다.
 * @n: 피보나치 수열의 인덱스 (0 기반)
 *
 * 반환값: n번째 피보나치 수
 *
 * 주의: 단순 재귀 방식은 중복 계산으로 비효율적일 수 있으므로, 
 *       n이 큰 경우에는 메모이제이션 등의 기법을 고려해야 합니다.
 */
long long fibonacci(int n) {
    if (n < 0) {
        fprintf(stderr, "음수에 대한 피보나치 수는 정의되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/*--------------------------------------
  배열의 합 계산
---------------------------------------*/
/**
 * sum_array - 재귀를 이용하여 정수 배열의 모든 원소의 합을 계산합니다.
 * @arr: 정수 배열
 * @n: 배열의 길이
 *
 * 반환값: 배열의 합
 *
 * 예: arr = {1, 2, 3, 4, 5} => sum_array(arr, 5) = 15
 */
int sum_array(const int *arr, int n) {
    if (n <= 0)
        return 0;
    return arr[0] + sum_array(arr + 1, n - 1);
}

/*--------------------------------------
  거듭제곱 계산 (base^exp)
---------------------------------------*/
/**
 * power - 재귀를 이용하여 base의 exp 제곱을 계산합니다.
 * @base: 밑
 * @exp: 지수 (0 이상의 정수)
 *
 * 반환값: base^exp
 *
 * 예: power(2, 10) = 1024
 */
long long power(int base, int exp) {
    if (exp < 0) {
        fprintf(stderr, "음수 지수는 지원되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    if (exp == 0)
        return 1;
    return base * power(base, exp - 1);
}

/*--------------------------------------
  최대공약수 (GCD) 계산 - 유클리드 알고리즘
---------------------------------------*/
/**
 * gcd - 재귀를 이용하여 두 정수의 최대공약수를 계산합니다.
 * @a: 첫 번째 정수
 * @b: 두 번째 정수
 *
 * 반환값: a와 b의 최대공약수
 *
 * 예: gcd(48, 180) = 12
 */
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

/*--------------------------------------
  배열 원소를 역순으로 출력
---------------------------------------*/
/**
 * print_reverse - 재귀를 이용하여 배열의 원소를 역순으로 출력합니다.
 * @arr: 정수 배열
 * @n: 배열의 길이
 *
 * 이 함수는 배열의 첫 원소부터 마지막 원소까지 출력하는 대신,
 * 재귀 호출 후에 출력함으로써 역순으로 출력합니다.
 */
void print_reverse(const int *arr, int n) {
    if (n <= 0)
        return;
    print_reverse(arr + 1, n - 1);
    printf("%d ", arr[0]);
}

int main(void) {
    // 팩토리얼 예제
    int num = 10;
    printf("팩토리얼(%d) = %lld\n", num, factorial(num));
    
    // 피보나치 예제
    int fibIndex = 10;
    printf("피보나치(%d) = %lld\n", fibIndex, fibonacci(fibIndex));
    
    // 배열의 합 예제
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrLength = sizeof(arr) / sizeof(arr[0]);
    printf("배열의 합 = %d\n", sum_array(arr, arrLength));
    
    // 거듭제곱 예제
    int base = 2, exp = 10;
    printf("%d의 %d제곱 = %lld\n", base, exp, power(base, exp));
    
    // 최대공약수 예제
    int a = 48, b = 180;
    printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
    
    // 배열 원소 역순 출력 예제
    printf("배열 원소를 역순으로 출력: ");
    print_reverse(arr, arrLength);
    printf("\n");
    
    return 0;
}