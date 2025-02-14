/**
 * alpha_beta.c
 *
 * 고도화된 알파-베타 가지치기 (Alpha-Beta Pruning) 구현 예제 (틱택토 게임 예제)
 * - 이 파일은 2인 제로섬 게임인 틱택토(Tic Tac Toe)에서 미니맥스 알고리즘에 알파-베타 가지치기를 적용하여
 *   최적의 움직임을 선택하는 예제를 구현합니다.
 * - 알파-베타 가지치기는 미니맥스 탐색 중 불필요한 하위 트리 탐색을 제거하여, 
 *   계산량을 크게 줄이는 최적화 기법입니다.
 *
 * 주요 단계:
 *   1. 미니맥스 알고리즘에 두 개의 파라미터, alpha와 beta를 추가합니다.
 *   2. 최대화 플레이어는 현재까지의 최대 보장 값(alpha)을, 최소화 플레이어는 최소 보장 값(beta)을 갱신합니다.
 *   3. 만약 beta <= alpha가 되면, 해당 분기를 가지치기(더 이상 탐색하지 않음) 합니다.
 *
 * 컴파일 예시: gcc -Wall -O2 alpha_beta.c -o alpha_beta
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define PLAYER 'X'   // 최대화 플레이어
#define OPPONENT 'O' // 최소화 플레이어
#define EMPTY '_'    // 빈 칸
#define BOARD_SIZE 9 // 틱택토 보드 크기

// 함수 프로토타입
void printBoard(char board[]);
bool isMovesLeft(char board[]);
int evaluate(char board[]);
int alphaBeta(char board[], int depth, int alpha, int beta, bool isMaximizing);
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
 *   +10 if PLAYER ('X') wins,
 *   -10 if OPPONENT ('O') wins,
 *    0 if 무승부 혹은 승리자가 없는 경우.
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
 * alphaBeta - 알파-베타 가지치기를 적용한 미니맥스 알고리즘 함수
 * @board: 현재 게임 보드 배열
 * @depth: 현재 재귀 깊이 (후보 수 제한 및 점수 조정을 위해 사용)
 * @alpha: 최대화 플레이어가 보장하는 최소 점수 (최대화)
 * @beta: 최소화 플레이어가 보장하는 최대 점수 (최소화)
 * @isMaximizing: true이면 최대화 플레이어(PLAYER, 'X'), false이면 최소화 플레이어(OPPONENT, 'O')
 *
 * 반환값: 현재 보드 상태의 평가 점수 (알파-베타 가지치기를 적용한 결과)
 *
 * 동작 원리:
 *   - 만약 승리 조건이 충족되거나 더 이상 움직임이 없으면, evaluate() 함수를 호출하여 현재 보드의 점수를 반환합니다.
 *   - 최대화 플레이어는 가능한 움직임 중 가장 높은 점수를 선택하고, 최소화 플레이어는 가장 낮은 점수를 선택합니다.
 *   - 알파(최대 보장 값)와 베타(최소 보장 값)를 업데이트하며, beta ≤ alpha가 되는 분기는 가지치기하여 탐색을 중단합니다.
 */
int alphaBeta(char board[], int depth, int alpha, int beta, bool isMaximizing) {
    int score = evaluate(board);
    
    // 기저 사례: 승리 상태 혹은 무승부
    if (score == 10 || score == -10)
        return score;
    if (!isMovesLeft(board))
        return 0;
    
    if (isMaximizing) {
        int best = -INT_MAX;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER;
                int val = alphaBeta(board, depth + 1, alpha, beta, false);
                best = (val > best) ? val : best;
                alpha = (alpha > best) ? alpha : best;
                board[i] = EMPTY;  // 백트래킹
                if (beta <= alpha)
                    break;  // 가지치기
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == EMPTY) {
                board[i] = OPPONENT;
                int val = alphaBeta(board, depth + 1, alpha, beta, true);
                best = (val < best) ? val : best;
                beta = (beta < best) ? beta : best;
                board[i] = EMPTY;  // 백트래킹
                if (beta <= alpha)
                    break;  // 가지치기
            }
        }
        return best;
    }
}

/**
 * findBestMove - 현재 보드 상태에서 알파-베타 가지치기를 적용하여
 *                PLAYER('X')에게 최적의 움직임을 찾습니다.
 * @board: 현재 게임 보드 배열
 *
 * 반환값: 최적의 움직임 인덱스 (0~8), 만약 움직임이 없으면 -1.
 *
 * 이 함수는 가능한 모든 움직임에 대해 alphaBeta 함수를 호출하고,
 * 최대화 플레이어 입장에서 가장 유리한 움직임을 선택합니다.
 */
int findBestMove(char board[]) {
    int bestVal = -INT_MAX;
    int bestMove = -1;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == EMPTY) {
            board[i] = PLAYER;
            int moveVal = alphaBeta(board, 0, -INT_MAX, INT_MAX, false);
            board[i] = EMPTY;  // 백트래킹
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

/**
 * main - 알파-베타 가지치기 미니맥스 알고리즘 데모 (틱택토 예제)
 *
 * 이 함수는 기본적인 틱택토 게임 보드를 구성하고, PLAYER('X')의 최적의 움직임을 계산 및 출력합니다.
 */
int main(void) {
    // 초기 게임 보드: 3x3 틱택토 보드 (배열 크기 9)
    char board[BOARD_SIZE] = { EMPTY, EMPTY, EMPTY,
                               EMPTY, EMPTY, EMPTY,
                               EMPTY, EMPTY, EMPTY };
    
    printf("현재 게임 보드:\n");
    printBoard(board);
    
    int bestMove = findBestMove(board);
    if (bestMove != -1) {
        printf("PLAYER ('%c')의 최적의 움직임 인덱스: %d\n", PLAYER, bestMove);
        board[bestMove] = PLAYER;
        printf("최적의 움직임 적용 후 보드:\n");
        printBoard(board);
    } else {
        printf("더 이상의 움직임이 없습니다.\n");
    }
    
    return 0;
}
