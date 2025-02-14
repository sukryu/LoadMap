/**
 * karatsuba.c
 *
 * 고도화된 Karatsuba 곱셈 알고리즘 구현 예제
 * - 이 파일은 큰 정수를 문자열로 표현한 경우에, Karatsuba 알고리즘을 이용하여 두 수의 곱셈을 수행합니다.
 * - Karatsuba 알고리즘은 전통적인 O(n²) 곱셈보다 더 빠른 O(n^log₂3) ≈ O(n^1.585)의 시간 복잡도를 달성합니다.
 *
 * 주요 단계:
 *   1. 입력 수들을 동일한 길이로 맞추기 위해 앞에 0을 추가하여 패딩합니다.
 *   2. 기저 사례: 길이가 1이면, 단일 자리 곱셈을 수행합니다.
 *   3. 재귀 분할: 수를 절반으로 나누어 각각 X1, X0, Y1, Y0로 표현합니다.
 *   4. 세 개의 재귀 곱셈:
 *         Z2 = karatsubaMultiply(X1, Y1)
 *         Z0 = karatsubaMultiply(X0, Y0)
 *         Z1 = karatsubaMultiply(addStrings(X1, X0), addStrings(Y1, Y0))
 *      그리고 Z1 = Z1 - Z2 - Z0.
 *   5. 결과 조합:
 *         result = Z2 * 10^(n) + Z1 * 10^(n/2) + Z0.
 *
 * 참고: 이 구현은 문자열 연산(덧셈, 뺄셈, 10의 거듭제곱 곱셈)을 위한 보조 함수를 포함하며,
 *       실무에서 큰 정수 곱셈의 개념을 이해하고 응용하는 데 도움을 줍니다.
 *
 * 컴파일 예시: gcc -Wall -O2 karatsuba.c -o karatsuba
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper function: Remove leading zeros from a numeric string.
char* removeLeadingZeros(const char* num) {
    while (*num == '0' && *(num + 1) != '\0') {
        num++;
    }
    return strdup(num);
}

// Helper function: Pad the string with leading zeros to reach length n.
char* padLeft(const char* num, int n) {
    int len = strlen(num);
    if (len >= n) return strdup(num);
    int diff = n - len;
    char* result = (char*)malloc(n + 1);
    if (!result) {
        fprintf(stderr, "메모리 할당 실패 (padLeft)\n");
        exit(EXIT_FAILURE);
    }
    memset(result, '0', diff);
    strcpy(result + diff, num);
    result[n] = '\0';
    return result;
}

// Helper function: Add two numeric strings and return the result as a new string.
char* stringAdd(const char* num1, const char* num2) {
    char *n1 = removeLeadingZeros(num1);
    char *n2 = removeLeadingZeros(num2);
    int len1 = strlen(n1);
    int len2 = strlen(n2);
    int maxLen = (len1 > len2) ? len1 : len2;
    char *a = padLeft(n1, maxLen);
    char *b = padLeft(n2, maxLen);
    free(n1);
    free(n2);

    int carry = 0;
    int sum, i;
    char *result = (char*)malloc(maxLen + 2); // +1 for possible carry, +1 for '\0'
    result[maxLen+1] = '\0';
    for (i = maxLen - 1; i >= 0; i--) {
        int digit1 = a[i] - '0';
        int digit2 = b[i] - '0';
        sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result[i+1] = (sum % 10) + '0';
    }
    free(a);
    free(b);
    if (carry) {
        result[0] = '1';
        return result;
    } else {
        char* finalResult = strdup(result+1);
        free(result);
        return finalResult;
    }
}

// Helper function: Subtract numeric string num2 from num1 (num1 >= num2) and return the result as a new string.
char* stringSubtract(const char* num1, const char* num2) {
    char *n1 = removeLeadingZeros(num1);
    char *n2 = removeLeadingZeros(num2);
    int len1 = strlen(n1);
    int len2 = strlen(n2);
    int maxLen = (len1 > len2) ? len1 : len2;
    char *a = padLeft(n1, maxLen);
    char *b = padLeft(n2, maxLen);
    free(n1);
    free(n2);

    int borrow = 0, diff, i;
    char *result = (char*)malloc(maxLen + 1);
    result[maxLen] = '\0';
    for (i = maxLen - 1; i >= 0; i--) {
        int digit1 = a[i] - '0';
        int digit2 = b[i] - '0';
        diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = diff + '0';
    }
    free(a);
    free(b);
    char* finalResult = removeLeadingZeros(result);
    free(result);
    return finalResult;
}

// Helper function: Multiply a numeric string by 10^power (i.e., append power number of '0's).
char* stringMultiplyBy10Power(const char* num, int power) {
    char *n = removeLeadingZeros(num);
    int len = strlen(n);
    char* result = (char*)malloc(len + power + 1);
    if (!result) {
        fprintf(stderr, "메모리 할당 실패 (stringMultiplyBy10Power)\n");
        exit(EXIT_FAILURE);
    }
    strcpy(result, n);
    free(n);
    memset(result + len, '0', power);
    result[len + power] = '\0';
    return result;
}

// Helper function: Multiply a numeric string by a single-digit integer.
char* stringMultiplyByDigit(const char* num, int digit) {
    if (digit < 0 || digit > 9) {
        fprintf(stderr, "단일 자리 숫자가 아닙니다.\n");
        exit(EXIT_FAILURE);
    }
    char *n = removeLeadingZeros(num);
    int len = strlen(n);
    int carry = 0, prod, i;
    char *result = (char*)malloc(len + 2);
    result[len+1] = '\0';
    for (i = len - 1; i >= 0; i--) {
        prod = (n[i] - '0') * digit + carry;
        carry = prod / 10;
        result[i+1] = (prod % 10) + '0';
    }
    free(n);
    if (carry) {
        result[0] = carry + '0';
        return result;
    } else {
        char* finalResult = strdup(result+1);
        free(result);
        return finalResult;
    }
}

// Karatsuba multiplication: Multiply two numeric strings using recursive divide and conquer.
char* karatsubaMultiply(const char* X, const char* Y) {
    // Remove leading zeros and determine lengths
    char *x = removeLeadingZeros(X);
    char *y = removeLeadingZeros(Y);
    int lenX = strlen(x);
    int lenY = strlen(y);
    
    // Base case: if either number has length 1, perform direct multiplication.
    if (lenX == 1 && lenY == 1) {
        int prod = (x[0] - '0') * (y[0] - '0');
        char buffer[3];
        sprintf(buffer, "%d", prod);
        free(x);
        free(y);
        return strdup(buffer);
    }
    
    // Ensure both numbers have the same length by padding with zeros on the left.
    int n = (lenX > lenY) ? lenX : lenY;
    // If n is odd, increment n to make it even.
    if (n % 2 != 0) n++;
    char *Xp = padLeft(x, n);
    char *Yp = padLeft(y, n);
    free(x);
    free(y);
    
    int mid = n / 2;
    
    // Split Xp and Yp into two halves: high and low parts.
    char *X1 = strndup(Xp, mid);
    char *X0 = strdup(Xp + mid);
    char *Y1 = strndup(Yp, mid);
    char *Y0 = strdup(Yp + mid);
    free(Xp);
    free(Yp);
    
    // Recursive calls:
    char *Z2 = karatsubaMultiply(X1, Y1);
    char *Z0 = karatsubaMultiply(X0, Y0);
    
    char *sumX1X0 = stringAdd(X1, X0);
    char *sumY1Y0 = stringAdd(Y1, Y0);
    char *Z1_temp = karatsubaMultiply(sumX1X0, sumY1Y0);
    char *Z2plusZ0 = stringAdd(Z2, Z0);
    char *Z1 = stringSubtract(Z1_temp, Z2plusZ0);
    
    free(X1);
    free(X0);
    free(Y1);
    free(Y0);
    free(sumX1X0);
    free(sumY1Y0);
    free(Z1_temp);
    free(Z2plusZ0);
    
    // Combine results:
    // Z2 * 10^(n) + Z1 * 10^(n/2) + Z0
    char *part1 = stringMultiplyBy10Power(Z2, n);
    char *part2 = stringMultiplyBy10Power(Z1, mid);
    char *tempSum = stringAdd(part1, part2);
    char *result = stringAdd(tempSum, Z0);
    
    free(Z2);
    free(Z1);
    free(Z0);
    free(part1);
    free(part2);
    free(tempSum);
    
    // Remove any leading zeros from the final result.
    char *finalResult = removeLeadingZeros(result);
    free(result);
    return finalResult;
}

/*---------------- main 함수 (데모) ----------------*/
int main(void) {
    // 예제: 두 큰 수의 곱셈
    const char *num1 = "314159265358979323846264338327950288419716939937510";
    const char *num2 = "271828182845904523536028747135266249775724709369995";
    
    char *product = karatsubaMultiply(num1, num2);
    printf("Num1: %s\n", num1);
    printf("Num2: %s\n", num2);
    printf("Karatsuba 곱셈 결과:\n%s\n", product);
    
    free(product);
    return 0;
}