#include <stdio.h>
#define MAX_N 20
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int N;
int satisfaction[MAX_N][MAX_N];  // 만족도 배열
int dp[1 << MAX_N];             // DP 배열
int visited[1 << MAX_N];        // 방문 체크 배열

// mask 상태에서의 최대 만족도를 계산하는 함수
int solve(int mask) {
    // 모든 사람에게 작업이 할당된 경우
    if (mask == (1 << N) - 1) return 0;
    
    // 이미 계산된 상태인 경우
    if (visited[mask]) return dp[mask];
    
    visited[mask] = 1;
    int person = __builtin_popcount(mask);  // 현재까지 할당된 사람의 수
    int maxSatisfaction = 0;
    
    // 아직 할당되지 않은 모든 작업에 대해 시도
    for (int job = 0; job < N; job++) {
        if (!(mask & (1 << job))) {  // job이 아직 할당되지 않은 경우
            int nextMask = mask | (1 << job);
            int result = satisfaction[person][job] + solve(nextMask);
            maxSatisfaction = MAX(maxSatisfaction, result);
        }
    }
    
    return dp[mask] = maxSatisfaction;
}

int main() {
    // 입력 받기
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &satisfaction[i][j]);
        }
    }
    
    // 결과 출력
    printf("%d\n", solve(0));
    
    return 0;
}