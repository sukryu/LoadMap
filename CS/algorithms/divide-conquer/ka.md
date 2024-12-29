# 카라츠바 알고리즘 (Karatsuba Algorithm, 큰 정수 곱셈)

* 카라츠바 알고리즘의 개념
    * 큰 수의 곱셈을 효율적으로 수행하기 위한 분할 정복 알고리즘입니다.
    * 일반적인 곱셈의 O(n^2)의 복잡도를 O(n^1.585)로 개선합니다.
    * 두 큰 수를 더 작은 부분으로 분할하여 곱셈을 수행합니다.

* 알고리즘 원리
    * x와 y를 각각 두 부분으로 분할:
        - `x = x1 x 10^(n/2) + x0`
        - `y = y1 x 10^(n/2) + y0`

    * 다음 세 값을 계산:
        - `z2 = x1 x y1`
        - `zo = x0 x y0`
        - `z1 = (x1 + x0)(y1 + y0) - z2 - z0`

    * 최종 결과:
        - `X x Y = z2 x 10^n + z1 x 10^(n/2) + z0`

* 기본 구현
    ```python
    def karatsuba(x, y):
        # 기저 사례
        if x < 10 or y < 10:
            return x * y
        
        # 자릿수 계산
        n = max(len(str(x)), len(str(y)))
        m = n // 2
        
        # 숫자 분할
        power = 10**m
        x1, x0 = divmod(x, power)
        y1, y0 = divmod(y, power)
        
        # 세 번의 재귀 호출
        z2 = karatsuba(x1, y1)
        z0 = karatsuba(x0, y0)
        z1 = karatsuba(x1 + x0, y1 + y0) - z2 - z0
        
        return (z2 * 10**(2*m)) + (z1 * 10**m) + z0
    ```

* 최적화된 구현
    ```python
    class KaratsubaMultiplier:
        def __init__(self):
            self.threshold = 64  # 임계값 설정
            
        def multiply(self, x, y):
            if x < self.threshold or y < self.threshold:
                return x * y
                
            n = max(self._bit_length(x), self._bit_length(y))
            m = (n + 32) // 64 * 32
            
            x1, x0 = x >> m, x & ((1 << m) - 1)
            y1, y0 = y >> m, y & ((1 << m) - 1)
            
            z2 = self.multiply(x1, y1)
            z0 = self.multiply(x0, y0)
            z1 = self.multiply(x1 + x0, y1 + y0) - z2 - z0
            
            return (z2 << (2*m)) + (z1 << m) + z0
            
        def _bit_length(self, n):
            return len(bin(n)) - 2
    ```

* 문자열 기반 구현 (매우 큰 수 처리)
    ```python
    def string_karatsuba(x_str, y_str):
        # 문자열 길이를 동일하게 맞춤
        n = max(len(x_str), len(y_str))
        if n == 1:
            return str(int(x_str) * int(y_str))
            
        x_str = x_str.zfill(n)
        y_str = y_str.zfill(n)
        
        m = n // 2
        x1, x0 = x_str[:-m], x_str[-m:]
        y1, y0 = y_str[:-m], y_str[-m:]
        
        # 재귀 호출
        z2 = int(string_karatsuba(x1, y1))
        z0 = int(string_karatsuba(x0, y0))
        z1 = int(string_karatsuba(str(int(x1) + int(x0)), 
                                str(int(y1) + int(y0)))) - z2 - z0
        
        # 결과 조합
        return str(z2 * 10**(2*m) + z1 * 10**m + z0)
    ```

* 병렬 처리 버전
    ```python
    from concurrent.futures import ProcessPoolExecutor

    def parallel_karatsuba(x, y, num_processes=4):
        if x < 1000 or y < 1000:
            return x * y
            
        n = max(len(str(x)), len(str(y)))
        m = n // 2
        power = 10**m
        
        x1, x0 = divmod(x, power)
        y1, y0 = divmod(y, power)
        
        with ProcessPoolExecutor(max_workers=num_processes) as executor:
            # 병렬로 세 부분 계산
            futures = [
                executor.submit(karatsuba, x1, y1),
                executor.submit(karatsuba, x0, y0),
                executor.submit(karatsuba, x1 + x0, y1 + y0)
            ]
            
            z2 = futures[0].result()
            z0 = futures[1].result()
            z1 = futures[2].result() - z2 - z0
            
        return (z2 * 10**(2*m)) + (z1 * 10**m) + z0
    ```

- 카라츠바 알고리즘은 매우 큰 수의 곱셈을 효율적으로 처리할 수 있는 중요한 알고리즘입니다.
특히 암호화나 큰 수의 정밀 계산이 필요한 분야에서 유용하게 사용됩니다. 하지만 작은 수의 경우 일반적인 곱셈이 더 효율적일 수 있으므로,
입력 크기에 따라 적절한 알고리즘을 선택하는 것이 중요합니다.