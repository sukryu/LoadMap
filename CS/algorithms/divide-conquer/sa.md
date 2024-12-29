# 스트라센 알고리즘 (Strassen Algorithm, 행렬 곱셈)

* 스트라센 알고리즘의 개념
    * 행렬 곱셈을 효율적으로 수행하기 위한 분할 정복 알고리즘입니다.
    * 일반적인 행렬 곱셈의 O(n^3) 복잡도를 O(n^2.807)로 개선합니다.
    * 7번의 곱셈과 18번의 덧셈/뺄셈으로 행렬 곱셈을 수행합니다.

* 기본 구현
    ```python
    import numpy as np

    def strassen(A, B):
        n = len(A)
        
        # 기저 사례: 1x1 행렬
        if n == 1:
            return np.array([[A[0][0] * B[0][0]]])
        
        # 행렬을 4등분
        mid = n // 2
        A11 = A[:mid, :mid]
        A12 = A[:mid, mid:]
        A21 = A[mid:, :mid]
        A22 = A[mid:, mid:]
        
        B11 = B[:mid, :mid]
        B12 = B[:mid, mid:]
        B21 = B[mid:, :mid]
        B22 = B[mid:, mid:]
        
        # 7개의 곱셈
        M1 = strassen(A11 + A22, B11 + B22)
        M2 = strassen(A21 + A22, B11)
        M3 = strassen(A11, B12 - B22)
        M4 = strassen(A22, B21 - B11)
        M5 = strassen(A11 + A12, B22)
        M6 = strassen(A21 - A11, B11 + B12)
        M7 = strassen(A12 - A22, B21 + B22)
        
        # 결과 행렬 계산
        C11 = M1 + M4 - M5 + M7
        C12 = M3 + M5
        C21 = M2 + M4
        C22 = M1 - M2 + M3 + M6
        
        # 결과 합치기
        C = np.vstack([np.hstack([C11, C12]),
                    np.hstack([C21, C22])])
        
        return C
    ```

* 최적화된 구현
    ```python
    class StrassenMultiplier:
        def __init__(self, threshold=64):
            self.threshold = threshold
            
        def multiply(self, A, B):
            n = len(A)
            # 임계값보다 작은 경우 일반 행렬 곱셈 사용
            if n <= self.threshold:
                return np.dot(A, B)
                
            # 2의 제곱수로 패딩
            next_power = 1 << (n-1).bit_length()
            if n != next_power:
                A_padded = np.pad(A, ((0, next_power - n), (0, next_power - n)))
                B_padded = np.pad(B, ((0, next_power - n), (0, next_power - n)))
                result = self._strassen(A_padded, B_padded)
                return result[:n, :n]
                
            return self._strassen(A, B)
            
        def _strassen(self, A, B):
            n = len(A)
            if n <= self.threshold:
                return np.dot(A, B)
                
            mid = n // 2
            A11, A12, A21, A22 = self._split_matrix(A)
            B11, B12, B21, B22 = self._split_matrix(B)
            
            # 7개의 곱셈 수행
            M1 = self._strassen(A11 + A22, B11 + B22)
            M2 = self._strassen(A21 + A22, B11)
            M3 = self._strassen(A11, B12 - B22)
            M4 = self._strassen(A22, B21 - B11)
            M5 = self._strassen(A11 + A12, B22)
            M6 = self._strassen(A21 - A11, B11 + B12)
            M7 = self._strassen(A12 - A22, B21 + B22)
            
            C11 = M1 + M4 - M5 + M7
            C12 = M3 + M5
            C21 = M2 + M4
            C22 = M1 - M2 + M3 + M6
            
            return self._combine_matrix(C11, C12, C21, C22)
            
        def _split_matrix(self, M):
            n = len(M)
            mid = n // 2
            return (M[:mid, :mid], M[:mid, mid:],
                M[mid:, :mid], M[mid:, mid:])
                
        def _combine_matrix(self, C11, C12, C21, C22):
            return np.vstack([np.hstack([C11, C12]),
                            np.hstack([C21, C22])])
    ```

* 병렬 처리 버전
    ```python
    from concurrent.futures import ProcessPoolExecutor

    class ParallelStrassen:
        def __init__(self, threshold=64, num_processes=4):
            self.threshold = threshold
            self.num_processes = num_processes
            
        def multiply(self, A, B):
            with ProcessPoolExecutor(max_workers=self.num_processes) as executor:
                return self._parallel_strassen(A, B, executor)
                
        def _parallel_strassen(self, A, B, executor):
            n = len(A)
            if n <= self.threshold:
                return np.dot(A, B)
                
            mid = n // 2
            A11, A12, A21, A22 = self._split_matrix(A)
            B11, B12, B21, B22 = self._split_matrix(B)
            
            # 병렬로 7개의 곱셈 수행
            futures = [
                executor.submit(self._parallel_strassen,
                            A11 + A22, B11 + B22, executor),
                executor.submit(self._parallel_strassen,
                            A21 + A22, B11, executor),
                executor.submit(self._parallel_strassen,
                            A11, B12 - B22, executor),
                executor.submit(self._parallel_strassen,
                            A22, B21 - B11, executor),
                executor.submit(self._parallel_strassen,
                            A11 + A12, B22, executor),
                executor.submit(self._parallel_strassen,
                            A21 - A11, B11 + B12, executor),
                executor.submit(self._parallel_strassen,
                            A12 - A22, B21 + B22, executor)
            ]
            
            M1, M2, M3, M4, M5, M6, M7 = [f.result() for f in futures]
            
            C11 = M1 + M4 - M5 + M7
            C12 = M3 + M5
            C21 = M2 + M4
            C22 = M1 - M2 + M3 + M6
            
            return self._combine_matrix(C11, C12, C21, C22)
    ```

- 스트라센 알고리즘은 이론적으로는 더 빠르지만, 실제로는 작은 크기의 행렬에서 일반적인 행렬 곱셈보다는 느릴 수 있습니다.
따라서 적절한 임계값을 설정하여 하이브리드 방식으로 구현하는 것이 좋습니다. 또한, 수치 안정성 문제가 있을 수 있으므로 과학 계산에서는 주의가
필요합니다.

- 실제 응용에서는 BLAS나 LAPACK과 같은 최적화된 라이브러리를 사용하는 것이 더 효율적일 수 있습니다. 스트라센 알고리즘은 주로 이론적인 중요성과
대규모 행렬 연산의 가능성을 보여주는 데 의의가 있습니다.