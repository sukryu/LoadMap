/**
 * minimax.c
 *
 * 고도화된 미니맥스 알고리즘 구현 예제 (Tic Tac Toe 예제)
 * - 이 파일은 2인 제로섬 게임인 틱택토(Tic Tac Toe)에서 미니맥스(Minimax) 알고리즘을 사용하여
 *   최적의 수(최선의 움직임)를 선택하는 예제를 구현합니다.
 * - 미니맥스 알고리즘은 게임 트리를 재귀적으로 탐색하여, 각 게임 상태에서 상대방의 최선의 행동을 고려한 후,
 *   현재 플레이어에게 최적의 결과를 도출합니다.
 * - 이 구현체는 게임 상태 평가, 가능한 수의 생성, 승리 조건 판단 등의 기능을 포함하며,
 *   실무에서도 사용할 수 있도록 견고하게 작성되었습니다.
 *
 * 컴파일 예시: gcc -Wall -O2 minimax.c -o minimax
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

// 정의: 게임의 플레이어 상수
#define PLAYER 'X'   // 미니맥스 알고리즘을 적용할 플레이어 (최대화 플레이어)
#define OPPONENT 'O' // 상대 플레이어 (최소화 플레이어)
#define EMPTY '_'    // 빈 칸

// 보드 크기 정의 (틱택토는 3x3)
#define BOARD_SIZE 9

// 함수 프로토타입
void printBoard(char board[]);
bool isMovesLeft(char board[]);
int evaluate(char board[]);
int minimax(char board[], int depth, bool isMaximizing);
int findBestMove(char board[]);

/**
 * printBoard - 현재 게임 보드를 출력합니다.
 * @board: 게임 보드를 나타내는 문자 배열 (크기 BOARD_SIZE)
 */
void printBoard(char board[]) {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf(" %c ", board[i]);
        if ((i + 1) % 3 == 0)
            printf("\n");
    }
    printf("\n");
}

/**
 * isMovesLeft - 게임 보드에 아직 움직임(빈 칸)이 남아있는지 검사합니다.
 * @board: 게임 보드 배열
 * 반환값: 움직임이 남아있으면 true, 없으면 false.
 */
bool isMovesLeft(char board[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == EMPTY)
            return true;
    }
    return false;
}

/**
 * evaluate - 현재 게임 보드의 상태를 평가하여 점수를 반환합니다.
 * @board: 게임 보드 배열
 *
 * 반환값:  
 *   +10 if the PLAYER ('X') wins, 
 *   -10 if the OPPONENT ('O') wins,
 *    0 if there is no winner.
 *
 * 이 함수는 행, 열, 대각선에서 승리 조건을 검사합니다.
 */
int evaluate(char board[]) {
    // 행 검사
    for (int row = 0; row < 3; row++) {
        int idx = row * 3;
        if (board[idx] == board[idx+1] && board[idx+1] == board[idx+2]) {
            if (board[idx] == PLAYER)
                return +10;
            else if (board[idx] == OPPONENT)
                return -10;
        }
    }
    
    // 열 검사
    for (int col = 0; col < 3; col++) {
        if (board[col] == board[col+3] && board[col+3] == board[col+6]) {
            if (board[col] == PLAYER)
                return +10;
            else if (board[col] == OPPONENT)
                return -10;
        }
    }
    
    // 대각선 검사
    if (board[0] == board[4] && board[4] == board[8]) {
        if (board[0] == PLAYER)
            return +10;
        else if (board[0] == OPPONENT)
            return -10;
    }
    if (board[2] == board[4] && board[4] == board[6]) {
        if (board[2] == PLAYER)
            return +10;
        else if (board[2] == OPPONENT)
            return -10;
    }
    
    return 0;
}

/**
 * minimax - 미니맥스 알고리즘을 재귀적으로 실행하여 현재 게임 상태의 평가 점수를 계산합니다.
 * @board: 현재 게임 보드 배열
 * @depth: 재귀 깊이 (후보 수를 줄이기 위한 인자; 깊이가 깊어질수록 점수 조정 가능)
 * @isMaximizing: true이면 최대화 플레이어(PLAYER, 'X')의 차례, false이면 최소화 플레이어(OPPONENT, 'O')의 차례
 *
 * 반환값: 현재 게임 상태에 대한 평가 점수.
 *
 * 동작 원리:
 *   - 만약 승자가 있거나 더 이상의 움직임이 없다면, evaluate()를 통해 보드 평가 점수를 반환합니다.
 *   - 최대화 플레이어일 때는 가능한 움직임 중 가장 높은 점수를 선택하고,
 *     최소화 플레이어일 때는 가능한 움직임 중 가장 낮은 점수를 선택합니다.
 */
int minimax(char board[], int depth, bool isMaximizing) {
    int score = evaluate(board);

    // 만약 플레이어나 상대방이 승리했다면, 재귀를 종료합니다.
    if (score == 10 || score == -10)
        return score;
    
    // 더 이상의 움직임이 없으면 무승부이므로 0 반환
    if (!isMovesLeft(board))
        return 0;
    
    if (isMaximizing) {
        int best = -INT_MAX;
        // 가능한 모든 움직임에 대해 최대화 플레이어의 최선의 점수를 찾습니다.
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER;
                int val = minimax(board, depth + 1, false);
                best = (val > best) ? val : best;
                board[i] = EMPTY; // 백트래킹
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        // 가능한 모든 움직임에 대해 최소화 플레이어의 최선의 점수를 찾습니다.
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == EMPTY) {
                board[i] = OPPONENT;
                int val = minimax(board, depth + 1, true);
                best = (val < best) ? val : best;
                board[i] = EMPTY; // 백트래킹
            }
        }
        return best;
    }
}

/**
 * findBestMove - 미니맥스 알고리즘을 사용하여 현재 보드 상태에서 최적의 움직임(최선의 인덱스)를 찾습니다.
 * @board: 현재 게임 보드 배열
 *
 * 반환값: 최적의 움직임을 위한 보드 인덱스 (0~8)
 *
 * 이 함수는 가능한 모든 움직임에 대해 미니맥스 알고리즘을 실행하고,
 * 최대화 플레이어(PLAYER, 'X')의 입장에서 최적의 결과를 도출하는 움직임을 선택합니다.
 */
int findBestMove(char board[]) {
    int bestVal = -INT_MAX;
    int bestMove = -1;
    
    // 가능한 모든 움직임을 고려합니다.
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == EMPTY) {
            // 임시로 현재 위치에 PLAYER를 둡니다.
            board[i] = PLAYER;
            // 미니맥스 함수 호출 (최소화 플레이어의 차례로 시작)
            int moveVal = minimax(board, 0, false);
            // 백트래킹: 움직임 취소
            board[i] = EMPTY;
            // 최적의 점수를 업데이트합니다.
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    
    return bestMove;
}

/**
 * main - 미니맥스 알고리즘 데모 (틱택토 게임 예제)
 *
 * 이 함수는 기본적인 틱택토 게임 환경을 구성하여, 
 * 미니맥스 알고리즘을 통해 PLAYER('X')의 최적의 움직임을 찾고, 결과를 출력합니다.
 */
int main(void) {
    // 초기 게임 보드: 3x3 틱택토 보드 (배열 크기 9)
    char board[BOARD_SIZE] = { EMPTY, EMPTY, EMPTY,
                               EMPTY, EMPTY, EMPTY,
                               EMPTY, EMPTY, EMPTY };
    
    // 예제: 미니맥스 알고리즘을 통해 PLAYER('X')의 최적 움직임 찾기
    int bestMove = findBestMove(board);
    
    printf("현재 보드 상태:\n");
    printBoard(board);
    
    printf("PLAYER ('%c')의 최적의 움직임 인덱스: %d\n", PLAYER, bestMove);
    
    // 시뮬레이션: 최적의 움직임을 적용하고 보드를 출력
    if (bestMove != -1) {
        board[bestMove] = PLAYER;
        printf("최적의 움직임 후 보드 상태:\n");
        printBoard(board);
    } else {
        printf("더 이상의 움직임이 없습니다.\n");
    }
    
    return 0;
}
