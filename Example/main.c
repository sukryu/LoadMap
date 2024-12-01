#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 연습 문제 1: 문자열 다루기
 * 목표: 사용자 입력 문자열을 다루는 기본 연습
 * 문제:
 *  1. 두 개의 문자열을 입력받아 동일한 문자열인지 비교하고, 같다면 "Equal"을 출력하세요. 다르다면 두 문자열을 이어붙여 출력하세요.
 *  2. 입력받은 문자열에서 특정 문자를 찾아 다른 문자로 바꾸는 프로그램을 작성하세요.
 *      - 예: hello -> helli ( 문자 'o' -> 'i' )
 */

// void my_gets(char *str, int size) {
//     char ch;
//     int i = 0;
//     while (i < size - 1 && (ch = getchar()) != '\n' && ch != EOF) {
//         str[i++] = ch;
//     }
//     str[i] = '\0';
// }

// int main() {
//     char f_str[100], s_str[100];

//     printf("첫 번째 문자열을 입력하세요. >> ");
//     my_gets(f_str, sizeof(f_str));

//     printf("두 번째 문자열을 입력하세요. >> ");
//     my_gets(s_str, sizeof(s_str));

//     if (strcmp(f_str, s_str) == 0) {
//         printf("Equal\n");
//     } else {
//         printf("%s%s\n", f_str, s_str);
//     }

//     return 0;
// }

// int main() {
//     char str[100];
//     char a, b;

//     // 문자열 입력
//     printf("문자열을 입력하시오 (최대 100자): ");
//     my_gets(str, sizeof(str));

//     // 변경할 문자와 새로운 문자 입력
//     printf("변경하고 싶은 문자와 새로운 문자를 입력하시오 (예: o i): ");
//     scanf(" %c %c", &a, &b);  // 앞의 공백은 개행 문자를 무시

//     // 문자열에서 문자 변경
//     for (int i = 0; str[i] != '\0'; i++) {
//         if (str[i] == a) {
//             str[i] = b;  // 문자를 대체
//         }
//     }

//     // 결과 출력
//     printf("변경된 문자열: %s\n", str);

//     return 0;
// }

/**
 * 연습 문제 2: 배열 다루기
 * 목표: 정수 배열의 기본 연산
 * 문제:
 *      1. 크기 5인 정수 배열을 입력받아 최댓값, 최솟값, 평균값을 구하세요.
 *      2. 배열의 짝수 인덱스와 홀수 인덱스에 있는 값들을 각각 다른 배열에 복사하고 출력하세요.
 */

// int main() {
//     int arr[5];
    
//     printf("정수 5개를 입력하세요: ");
//     for (int i = 0; i < 5; i++) {
//         scanf("%d", &arr[i]);
//     }

//     // 최댓값, 최솟값, 평균 계산
//     int max = arr[0];
//     int min = arr[0];
//     int sum = 0;
//     for (int i = 0; i < 5; i++) {
//         if (arr[i] > max) max = arr[i];
//         if (arr[i] < min) min = arr[i];
//         sum += arr[i];
//     }
//     double avg = (double)sum / 5;  // 형 변환 추가

//     printf("최대값: %d\n", max);
//     printf("최솟값: %d\n", min);
//     printf("평균: %.2lf\n", avg);  // 소수점 2자리 출력

//     // 짝수/홀수 인덱스 배열 분리
//     int a1[5], a2[5];  // 충분히 큰 크기 할당
//     int a1_len = 0, a2_len = 0;  // 각각의 길이 관리

//     for (int i = 0; i < 5; i++) {
//         if (i % 2 == 0) {
//             a1[a1_len++] = arr[i];
//         } else {
//             a2[a2_len++] = arr[i];
//         }
//     }

//     // 짝수 인덱스 출력
//     printf("짝수 인덱스: ");
//     for (int i = 0; i < a1_len; i++) {
//         printf("%d ", a1[i]);
//     }
//     printf("\n");

//     // 홀수 인덱스 출력
//     printf("홀수 인덱스: ");
//     for (int i = 0; i < a2_len; i++) {
//         printf("%d ", a2[i]);
//     }
//     printf("\n");

//     return 0;
// }

/**
 * 연습 문제 3: 포인터를 사용한 연산
 * 목표: 포인터의 기본 개념 연습
 * 문제:
 *      1. 두 개의 정수 변수를 입력받아 값을 포인터를 사용하여 서로 교환하는 프로그램을 작성하세요.
 *      2. 포인터를 사용하여 크기 5의 배열의 모든 값을 2배로 만드는 프로그램을 작성하세요.
 */

// void swap(int *p_a, int *p_b) {
//     int temp = *p_a;
//     *p_a = *p_b;
//     *p_b = temp;
// }

// int main() {
//     int a, b;

//     printf("두 정수를 입력하세요: ");
//     scanf("%d %d", &a, &b);

//     printf("교환 전: a = %d, b = %d\n", a, b);

//     swap(&a, &b);  // 포인터로 전달

//     printf("교환 후: a = %d, b = %d\n", a, b);

//     return 0;
// }

// // 배열의 모든 값을 2배로 만드는 함수
// void double_values(int *arr, int size) {
//     for (int i = 0; i < size; i++) {
//         arr[i] *= 2;
//     }
// }

// int main() {
//     int arr[5];

//     printf("배열의 값을 입력하세요 (5개): ");
//     for (int i = 0; i < 5; i++) {
//         scanf("%d", &arr[i]);
//     }

//     printf("원래 배열: ");
//     for (int i = 0; i < 5; i++) {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");

//     double_values(arr, 5);  // 배열의 주소 전달

//     printf("2배로 만든 배열: ");
//     for (int i = 0; i < 5; i++) {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");

//     return 0;
// }


/**
 * 연습 문제 4: 파일 입출력
 * 목표: 파일 읽기 및 쓰기
 * 문제:
 *      1. "input.txt"라는 파일에 사용자가 입력한 정수 5개를 저장하는 프로그램을 작성하세요.
 *      2. 저장된 "input.txt"를 읽어와 모든 값을 더한 후, "output.txt"에 결과를 저장하세요.
 */
// int main() {
//     int arr[5];

//     // 사용자로부터 정수 입력
//     printf("정수 5개를 입력하세요: ");
//     for (int i = 0; i < 5; i++) {
//         scanf("%d", &arr[i]);
//     }

//     // "input.txt"에 정수 저장
//     FILE *fp = fopen("input.txt", "w");
//     if (fp == NULL) {
//         printf("파일 열기 실패\n");
//         return 1;
//     }
//     for (int i = 0; i < 5; i++) {
//         fprintf(fp, "%d\n", arr[i]);  // 정수 저장 (줄바꿈 포함)
//     }
//     fclose(fp);

//     // "input.txt"에서 정수 읽기 및 합계 계산
//     int sum = 0, num;
//     FILE *fp_1 = fopen("input.txt", "r");
//     if (fp_1 == NULL) {
//         printf("파일 열기 실패\n");
//         return 1;
//     }
//     while (fscanf(fp_1, "%d", &num) != EOF) {
//         sum += num;
//     }
//     fclose(fp_1);

//     // 합계를 "output.txt"에 저장
//     FILE *fp_2 = fopen("output.txt", "w");
//     if (fp_2 == NULL) {
//         printf("파일 열기 실패\n");
//         return 1;
//     }
//     fprintf(fp_2, "합계: %d\n", sum);  // 합계를 파일에 저장
//     fclose(fp_2);

//     printf("입력된 정수의 합계가 'output.txt'에 저장되었습니다.\n");

//     return 0;
// }