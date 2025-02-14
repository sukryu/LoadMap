/**
 * indirect.c
 *
 * 간접 재귀(Indirect Recursion) 알고리즘 구현 예제
 *
 * 이 파일은 여러 함수들이 서로를 순환적으로 호출하는 간접 재귀의 개념을 실무에서도 활용할 수 있도록
 * 다양한 예제를 포함하고 있습니다.
 *
 * 예제:
 *  - 짝수/홀수 판별: isEven와 isOdd 함수가 서로를 호출하여 정수가 짝수인지 홀수인지 판별합니다.
 *  - 상태 전환 예제: functionA와 functionB가 서로를 호출하며 상태 전환을 시뮬레이션합니다.
 *
 * 컴파일: gcc -Wall -O2 indirect.c -o indirect
 */

#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------
  짝수/홀수 판별 (Indirect Recursion)
---------------------------------------*/

/**
 * isOdd - 간접 재귀를 이용하여 정수가 홀수인지 판단합니다.
 * @n: 판단할 정수 (0 이상의 정수)
 *
 * 반환값: n이 홀수이면 1, 아니면 0.
 *
 * 이 함수는 isEven 함수를 호출하여 n이 홀수인지 판별합니다.
 */
int isOdd(int n);

/**
 * isEven - 간접 재귀를 이용하여 정수가 짝수인지 판단합니다.
 * @n: 판단할 정수 (0 이상의 정수)
 *
 * 반환값: n이 짝수이면 1, 아니면 0.
 *
 * 기본 종료 조건: n == 0인 경우 1을 반환합니다.
 */
int isEven(int n) {
    if(n == 0)
        return 1;  // 0은 짝수
    else
        return isOdd(n - 1);
}

/**
 * isOdd - 간접 재귀를 이용하여 정수가 홀수인지 판단합니다.
 * @n: 판단할 정수 (0 이상의 정수)
 *
 * 반환값: n이 홀수이면 1, 아니면 0.
 *
 * 이 함수는 isEven 함수를 호출하여 n이 홀수인지 판별합니다.
 */
int isOdd(int n) {
    if(n == 0)
        return 0;  // 0은 짝수이므로 홀수가 아님
    else
        return isEven(n - 1);
}

/*--------------------------------------
  간접 재귀 상태 전환 예제
---------------------------------------*/

/**
 * functionA - 간접 재귀를 이용한 상태 전환 함수 A
 * @n: 재귀 깊이 (0 이상의 정수)
 *
 * 이 함수는 n이 0이 될 때까지 functionB를 호출하여 상태 전환을 수행합니다.
 */
void functionB(int n);  // 전방 선언

void functionA(int n) {
    if(n <= 0) {
        printf("functionA: 종료\n");
        return;
    }
    printf("functionA: n = %d\n", n);
    functionB(n - 1);
}

/**
 * functionB - 간접 재귀를 이용한 상태 전환 함수 B
 * @n: 재귀 깊이 (0 이상의 정수)
 *
 * 이 함수는 n이 0이 될 때까지 functionA를 호출하여 상태 전환을 수행합니다.
 */
void functionB(int n) {
    if(n <= 0) {
        printf("functionB: 종료\n");
        return;
    }
    printf("functionB: n = %d\n", n);
    functionA(n - 1);
}

/*--------------------------------------
  main 함수 (데모)
---------------------------------------*/

int main(void) {
    // 짝수/홀수 판별 테스트
    int num = 7;
    if(isEven(num))
        printf("%d는 짝수입니다.\n", num);
    else
        printf("%d는 홀수입니다.\n", num);
    
    num = 8;
    if(isEven(num))
        printf("%d는 짝수입니다.\n", num);
    else
        printf("%d는 홀수입니다.\n", num);
    
    // 간접 재귀 상태 전환 예제 테스트
    printf("\n간접 재귀 상태 전환 예제:\n");
    functionA(5);
    
    return 0;
}