/**
 * fft.c
 *
 * 고도화된 Fast Fourier Transform (FFT) 알고리즘 구현 예제
 * - 이 파일은 Cooley-Tukey 분할 정복 방식을 사용하여, 
 *   2의 거듭제곱 크기의 입력 복소수 배열에 대한 FFT를 수행합니다.
 * - FFT는 시간 영역의 신호를 주파수 영역으로 변환하는 알고리즘으로,
 *   전통적인 이산 푸리에 변환(DFT)에 비해 O(n log n)의 시간 복잡도를 달성합니다.
 * - 이 구현은 C99 표준의 <complex.h> 라이브러리를 사용하며, 
 *   실무 환경에서 바로 활용할 수 있도록 동적 메모리 관리, 에러 처리 및 자세한 주석을 포함하고 있습니다.
 *
 * 컴파일 예시: gcc -std=c99 -Wall -O2 fft.c -o fft -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

/**
 * fft - Cooley-Tukey FFT 알고리즘을 재귀적으로 수행합니다.
 * @x: 입력 복소수 배열 (길이 n, n은 2의 거듭제곱)
 * @n: 배열의 크기 (2의 거듭제곱)
 * @invert: 0이면 정방향 FFT, 1이면 역 FFT(IFFT)
 *
 * 이 함수는 입력 배열 x에 대해 FFT를 수행하며, 결과는 x 배열에 in-place로 저장됩니다.
 * 역 FFT의 경우, 각 결과를 n으로 나눠 정규화합니다.
 */
void fft(complex double *x, int n, int invert) {
    if (n <= 1)
        return;

    // Allocate memory for even and odd indexed elements
    int half = n / 2;
    complex double *even = (complex double *)malloc(half * sizeof(complex double));
    complex double *odd  = (complex double *)malloc(half * sizeof(complex double));
    if (!even || !odd) {
        fprintf(stderr, "메모리 할당 실패 (fft)\n");
        exit(EXIT_FAILURE);
    }

    // 분할: 짝수 인덱스와 홀수 인덱스 요소 분리
    for (int i = 0; i < half; i++) {
        even[i] = x[2*i];
        odd[i]  = x[2*i + 1];
    }

    // 재귀 호출을 통해 FFT 계산
    fft(even, half, invert);
    fft(odd, half, invert);

    // 결합 단계: twiddle factor를 사용하여 결과 결합
    for (int k = 0; k < half; k++) {
        // 계산: exp(-2*pi*i*k/n) for 정방향, exp(2*pi*i*k/n) for 역 FFT
        double angle = 2 * M_PI * k / n;
        if (invert)
            angle = -angle;
        complex double t = cexp(-I * angle) * odd[k];
        x[k] = even[k] + t;
        x[k + half] = even[k] - t;
    }

    // 역 FFT인 경우, 결과 정규화: 각 원소를 n으로 나눕니다.
    if (invert) {
        for (int i = 0; i < n; i++)
            x[i] /= 2;
    }
    free(even);
    free(odd);
}

/**
 * printComplexArray - 복소수 배열을 출력하는 유틸리티 함수
 * @x: 복소수 배열
 * @n: 배열의 길이
 */
void printComplexArray(complex double *x, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f%+.2fi ", creal(x[i]), cimag(x[i]));
    }
    printf("\n");
}

/**
 * main - FFT 알고리즘 데모
 *
 * 이 함수는 예제 복소수 배열을 생성하여 정방향 FFT와 역 FFT(IFFT)를 수행한 결과를 출력합니다.
 */
int main(void) {
    // 예제: 8개의 복소수로 구성된 배열 (길이 8, 2의 거듭제곱)
    int n = 8;
    complex double *x = (complex double *)malloc(n * sizeof(complex double));
    if (!x) {
        fprintf(stderr, "메모리 할당 실패 (main: x)\n");
        exit(EXIT_FAILURE);
    }

    // 예제 입력: 실수부는 0~7, 허수부는 0으로 초기화
    for (int i = 0; i < n; i++) {
        x[i] = i + 0.0;
    }
    
    printf("원본 배열:\n");
    printComplexArray(x, n);
    
    // 정방향 FFT 수행
    fft(x, n, 0);
    printf("\n정방향 FFT 결과 (주파수 영역):\n");
    printComplexArray(x, n);
    
    // 역 FFT(IFFT) 수행: invert = 1
    fft(x, n, 1);
    printf("\n역 FFT(IFFT) 결과 (시간 영역, 복원):\n");
    printComplexArray(x, n);
    
    free(x);
    return 0;
}