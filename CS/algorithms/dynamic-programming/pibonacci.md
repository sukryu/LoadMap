# 피보나치 수열 (Top-Down 및 Bottom-Up 방식)

* 피보나치 수열의 정의
    * 첫 두 항이 0과 1이며, 그 뒤의 모든 항은 앞의 두 항의 합으로 이루어진 수열
    * `F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1`

* Top-Down 방식 (메모이제이션)
    ```python
    def fib_top_down(n, memo=None):
        if memo is None:
            memo = {}
            
        # 기저 사례
        if n <= 1:
            return n
            
        # 이미 계산된 값인 경우
        if n in memo:
            return memo[n]
            
        # 값을 계산하고 메모에 저장
        memo[n] = fib_top_down(n-1, memo) + fib_top_down(n-2, memo)
        return memo[n]
    ```

* Bottom-Up 방식 (타뷸레이션)
    ```python
    def fib_bottom_up(n):
        if n <= 1:
            return n
            
        # dp 테이블 초기화
        dp = [0] * (n + 1)
        dp[1] = 1
        
        # 작은 문제부터 순차적으로 해결
        for i in range(2, n + 1):
            dp[i] = dp[i-1] + dp[i-2]
            
        return dp[n]
    ```

* 공간 최적화된 Bottom-Up
    ```python
    def fib_optimized(n):
        if n <= 1:
            return n
            
        prev2, prev1 = 0, 1
        
        for _ in range(2, n + 1):
            curr = prev1 + prev2
            prev2, prev1 = prev1, curr
            
        return prev1
    ```

* 행렬 거듭제곱을 이용한 방법
    ```python
    def fib_matrix(n):
        def multiply_matrix(a, b):
            return [
                [a[0][0]*b[0][0] + a[0][1]*b[1][0], a[0][0]*b[0][1] + a[0][1]*b[1][1]],
                [a[1][0]*b[0][0] + a[1][1]*b[1][0], a[1][0]*b[0][1] + a[1][1]*b[1][1]]
            ]
            
        def matrix_power(matrix, power):
            if power == 0:
                return [[1, 0], [0, 1]]
            if power == 1:
                return matrix
                
            # 분할 정복으로 거듭제곱 계산
            half = matrix_power(matrix, power // 2)
            if power % 2 == 0:
                return multiply_matrix(half, half)
            return multiply_matrix(multiply_matrix(half, half), matrix)
            
        if n <= 1:
            return n
            
        base_matrix = [[1, 1], [1, 0]]
        result_matrix = matrix_power(base_matrix, n-1)
        return result_matrix[0][0]
    ```

* 대용량 피보나치 수 계산
    ```python
    def large_fibonacci(n, modulo=1000000007):
        """
        매우 큰 피보나치 수를 특정 모듈로로 나눈 나머지 계산
        """
        if n <= 1:
            return n
            
        prev2, prev1 = 0, 1
        
        for _ in range(2, n + 1):
            curr = (prev1 + prev2) % modulo
            prev2, prev1 = prev1, curr
            
        return prev1
    ```

* 방식별 특징 비교
    * Top-Down
        - 장점: 필요한 값만 계산, 코드가 직관적
        - 단점: 재귀 호출 오버헤드, 스택 메모리 사용

    * Bottom-Up
        - 장점: 반복문으로 구현되어 효율적, 메모리 사용 예측 가능
        - 단점: 불필요한 값도 계산할 수 있음.

    * 최적화 버전
        - 장점: 최소한의 메모리 사용, 빠른 실행 시간
        - 단점: 중간 값들을 저장하지 않음.

- 두 방식 모두 다이나믹 프로그래밍의 핵심인 "중복 계산 방지"를 통해 효율성을 크게 향상시킵니다.
일반적으로 Bottom-Up 방식이 더 효율적이지만, 문제의 특성에 따라 적절한 방식을 선택해야 합니다.

- 실제 응용에서는 대부분 Bottom-Up 방식이나 최적화된 방식을 사용하며, 특히 대용량 계산이 필요한 경우
모듈러 연산을 함께 사용하는 것이 일반적입니다.