/**
 * direct.c
 *
 * 직접 재귀(Direct Recursion) 알고리즘 구현 예제
 *
 * 이 파일은 함수가 자기 자신을 직접 호출하여 문제를 해결하는 직접 재귀 방식의 여러 예제를 포함합니다.
 * 직접 재귀는 문제를 더 작은 부분 문제로 분할하고, 재귀 호출을 통해 해결한 후 결과를 결합하는 전통적인 재귀 기법입니다.
 *
 * 아래 예제들은 실무에서도 활용 가능한 직접 재귀 함수 예시입니다:
 *  - 팩토리얼 계산 (직접 재귀 방식)
 *  - 피보나치 수열 계산 (중복 계산이 발생하는 직접 재귀)
 *  - 배열의 합 계산 (순차적 직접 재귀)
 *  - 거듭제곱 계산 (직접 재귀)
 *  - 최대공약수 (GCD) 계산 (유클리드 알고리즘의 직접 재귀)
 *
 * 컴파일: gcc -Wall -O2 direct.c -o direct
 */

#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------
  직접 재귀를 이용한 팩토리얼 계산
---------------------------------------*/
/**
 * factorial_direct - 직접 재귀를 이용하여 n의 팩토리얼을 계산합니다.
 * @n: 0 이상의 정수
 *
 * 반환값: n! (n의 팩토리얼)
 *
 * 예: factorial_direct(5) = 120
 */
long long factorial_direct(int n) {
    if (n < 0) {
        fprintf(stderr, "음수에 대한 팩토리얼은 정의되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0)
        return 1;
    // 직접 재귀: 함수가 자기 자신을 호출하여 결과를 계산
    return n * factorial_direct(n - 1);
}

/*--------------------------------------
  직접 재귀를 이용한 피보나치 수열 계산
---------------------------------------*/
/**
 * fibonacci_direct - 직접 재귀를 이용하여 n번째 피보나치 수를 계산합니다.
 * @n: 피보나치 수열의 인덱스 (0 기반)
 *
 * 반환값: n번째 피보나치 수
 *
 * 주의: 이 직접 재귀 구현은 중복 계산으로 인해 n이 커질 경우 비효율적입니다.
 */
long long fibonacci_direct(int n) {
    if (n < 0) {
        fprintf(stderr, "음수 인덱스에 대한 피보나치 수는 정의되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    // 직접 재귀 호출: 두 개의 하위 문제를 풀어 합산
    return fibonacci_direct(n - 1) + fibonacci_direct(n - 2);
}

/*--------------------------------------
  직접 재귀를 이용한 배열의 합 계산
---------------------------------------*/
/**
 * sum_array_direct - 직접 재귀를 이용하여 정수 배열의 합을 계산합니다.
 * @arr: 정수 배열
 * @n: 배열의 길이
 *
 * 반환값: 배열의 모든 원소의 합
 *
 * 예: {1, 2, 3, 4, 5} => 15
 */
int sum_array_direct(const int *arr, int n) {
    if (n <= 0)
        return 0;
    // 직접 재귀: 현재 첫 원소와 나머지 배열의 합을 계산
    return arr[0] + sum_array_direct(arr + 1, n - 1);
}

/*--------------------------------------
  직접 재귀를 이용한 거듭제곱 계산 (base^exp)
---------------------------------------*/
/**
 * power_direct - 직접 재귀를 이용하여 base의 exp 제곱을 계산합니다.
 * @base: 밑
 * @exp: 0 이상의 정수 지수
 *
 * 반환값: base의 exp 제곱
 *
 * 예: power_direct(2, 10) = 1024
 */
long long power_direct(int base, int exp) {
    if (exp < 0) {
        fprintf(stderr, "음수 지수는 지원되지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    if (exp == 0)
        return 1;
    // 직접 재귀 호출: base와 exp - 1의 곱을 반환
    return base * power_direct(base, exp - 1);
}

/*--------------------------------------
  직접 재귀를 이용한 최대공약수 (GCD) 계산
---------------------------------------*/
/**
 * gcd_direct - 직접 재귀를 이용하여 두 정수의 최대공약수를 계산합니다.
 * @a: 첫 번째 정수
 * @b: 두 번째 정수
 *
 * 반환값: a와 b의 최대공약수
 *
 * 예: gcd_direct(48, 180) = 12
 */
int gcd_direct(int a, int b) {
    if (b == 0)
        return a;
    // 직접 재귀: a와 b의 나머지에 대해 gcd 호출
    return gcd_direct(b, a % b);
}

/*--------------------------------------
  직접 재귀를 이용한 문자열 역출력
---------------------------------------*/
/**
 * print_string_reverse - 직접 재귀를 이용하여 문자열을 역순으로 출력합니다.
 * @s: 출력할 문자열 (NULL 종료)
 *
 * 이 함수는 문자열의 마지막 문자부터 첫 문자까지 역순으로 출력합니다.
 */
void print_string_reverse(const char *s) {
    if (*s == '\0')
        return;
    // 먼저 재귀 호출하여 문자열의 뒷부분을 처리
    print_string_reverse(s + 1);
    // 재귀 호출이 반환된 후 현재 문자를 출력
    putchar(*s);
}

int main(void) {
    // 팩토리얼 직접 재귀 예제
    int num = 5;
    printf("직접 재귀 팩토리얼(%d) = %lld\n", num, factorial_direct(num));
    
    // 피보나치 직접 재귀 예제
    int fibIndex = 10;
    printf("직접 재귀 피보나치(%d) = %lld\n", fibIndex, fibonacci_direct(fibIndex));
    
    // 배열의 합 직접 재귀 예제
    int arr[] = {1, 2, 3, 4, 5};
    int arrLength = sizeof(arr) / sizeof(arr[0]);
    printf("직접 재귀 배열의 합 = %d\n", sum_array_direct(arr, arrLength));
    
    // 거듭제곱 직접 재귀 예제
    int base = 3, exp = 4;
    printf("직접 재귀: %d의 %d제곱 = %lld\n", base, exp, power_direct(base, exp));
    
    // 최대공약수 직접 재귀 예제
    int a = 48, b = 180;
    printf("직접 재귀 gcd(%d, %d) = %d\n", a, b, gcd_direct(a, b));
    
    // 문자열 역출력 직접 재귀 예제
    const char *text = "DirectRecursion";
    printf("직접 재귀 문자열 역순 출력: ");
    print_string_reverse(text);
    printf("\n");
    
    return 0;
}