/**
 * heuristic.c
 *
 * 고도화된 상태 평가 함수(휴리스틱 함수) 구현 예제 - Tic Tac Toe 평가
 * - 이 파일은 간단한 3x3 틱택토 게임 보드의 상태를 평가하는 함수 예제를 제공합니다.
 * - 평가 함수는 각 행, 열, 대각선에서 승리 조건 또는 잠재적 승리 가능성을 분석하여
 *   현재 보드 상태의 점수를 산출합니다.
 * - 예를 들어, 한 행에 두 개의 'X'와 한 개의 빈 칸이 있으면, PLAYER('X')에게 유리한 상태로 평가합니다.
 *
 * 이 구현은 실무 환경에서 게임 AI나 상태 평가 함수의 기본 개념을 이해하고 응용할 수 있도록 설계되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 heuristic.c -o heuristic
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define BOARD_SIZE 9
#define ROWS 3
#define COLS 3

// 게임 기호 정의
#define PLAYER 'X'
#define OPPONENT 'O'
#define EMPTY '_' 

/**
 * evaluateLine - 한 행, 열 또는 대각선의 상태를 평가하는 함수
 * @a, @b, @c: 평가할 세 개의 셀 값
 *
 * 반환값: 해당 라인의 평가 점수
 *   - 만약 한 라인에서 PLAYER의 승리 가능성이 높으면 양수, OPPONENT의 승리 가능성이 높으면 음수 점수를 반환합니다.
 *   - 예를 들어, 두 개의 'X'와 한 개의 빈 칸이 있는 경우 +10, 반대의 경우 -10.
 */
int evaluateLine(char a, char b, char c) {
    int score = 0;
    
    // 첫 번째 셀 평가
    if (a == PLAYER)
        score = 1;
    else if (a == OPPONENT)
        score = -1;
    
    // 두 번째 셀 평가
    if (b == PLAYER) {
        if (score == 1)
            score = 10;    // 연속된 두 개의 'X'
        else if (score == -1)
            return 0;      // 혼합된 라인: 더 이상 승리 가능성이 없음
        else
            score = 1;
    } else if (b == OPPONENT) {
        if (score == -1)
            score = -10;   // 연속된 두 개의 'O'
        else if (score == 1)
            return 0;      // 혼합된 라인
        else
            score = -1;
    }
    
    // 세 번째 셀 평가
    if (c == PLAYER) {
        if (score > 0) {
            // 만약 이미 두 개의 'X'가 있다면, 승리 상황
            if (score == 10)
                score = 100;
            else
                score = 1;
        } else if (score < 0) {
            // 혼합된 경우는 이미 0을 반환했으므로 이 상황은 드뭅니다.
            return 0;
        } else {
            score = 1;
        }
    } else if (c == OPPONENT) {
        if (score < 0) {
            if (score == -10)
                score = -100;
            else
                score = -1;
        } else if (score > 0) {
            return 0;
        } else {
            score = -1;
        }
    }
    
    return score;
}

/**
 * evaluateBoard - 3x3 틱택토 보드의 상태를 평가하여 휴리스틱 점수를 반환합니다.
 * @board: 게임 보드를 나타내는 문자 배열 (크기 BOARD_SIZE)
 *
 * 반환값: 보드의 평가 점수 (양수이면 PLAYER('X')에게 유리, 음수이면 OPPONENT('O')에게 유리)
 *
 * 평가 방식:
 *   - 각 행, 열, 대각선에 대해 evaluateLine() 함수를 호출하여 점수를 산출합니다.
 *   - 전체 보드의 점수는 각 라인의 점수의 합으로 결정됩니다.
 */
int evaluateBoard(char board[]) {
    int totalScore = 0;
    
    // 행 평가
    for (int i = 0; i < ROWS; i++) {
        int idx = i * COLS;
        totalScore += evaluateLine(board[idx], board[idx + 1], board[idx + 2]);
    }
    
    // 열 평가
    for (int j = 0; j < COLS; j++) {
        totalScore += evaluateLine(board[j], board[j + COLS], board[j + 2 * COLS]);
    }
    
    // 대각선 평가
    totalScore += evaluateLine(board[0], board[4], board[8]);
    totalScore += evaluateLine(board[2], board[4], board[6]);
    
    return totalScore;
}

/**
 * main - 상태 평가 함수 데모
 *
 * 이 함수는 예제 틱택토 보드의 상태를 평가하고, 휴리스틱 점수를 출력합니다.
 */
int main(void) {
    // 예제 보드 (틱택토 3x3)
    // 보드 구성:
    // X O _
    // X _ _
    // _ O _
    char board[BOARD_SIZE] = {
        PLAYER, OPPONENT, EMPTY,
        PLAYER, EMPTY, EMPTY,
        EMPTY, OPPONENT, EMPTY
    };
    
    printf("현재 게임 보드:\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf(" %c ", board[i]);
        if ((i + 1) % COLS == 0)
            printf("\n");
    }
    
    int score = evaluateBoard(board);
    printf("\n상태 평가 점수: %d\n", score);
    
    return 0;
}
