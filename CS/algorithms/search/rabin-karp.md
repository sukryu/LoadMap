# 라빈-카프 (Rabin-Karp) 알고리즘

* 개념
    * **라빈-카프**는 해시 함수를 활용한 문자열 패턴 매칭 알고리즘입니다.
    * 특징:
        - 롤링 해시(Rolling Hash) 사용
        - 여러 패턴 동시 검색 가능
        - 평균 O(n + m) 시간 복잡도
        - 해시 충돌 처리 필요

* 핵심 구성 요소
    1. 롤링 해시
        - 윈도우가 이동할 때 해시값을 효율적으로 업데이트
        - 모듈러 연산을 통한 오버플로우 방지
        - 적절한 기수(base)와 모듈러(mod) 선택 중요

    2. 윈도우 슬라이딩
        - 텍스트를 고정 크기 윈도우로 순회
        - 해시값의 증분 계산

* 기본 구현
    ```python
    class RabinKarp:
        def __init__(self, pattern):
            self.pattern = pattern
            self.pattern_len = len(pattern)
            self.base = 256  # ASCII 문자 기준
            self.mod = 10**9 + 7  # 큰 소수
            self.pattern_hash = self._calculate_hash(pattern)
            
        def _calculate_hash(self, text):
            """문자열의 초기 해시값 계산"""
            hash_value = 0
            for i in range(len(text)):
                hash_value = (hash_value * self.base + ord(text[i])) % self.mod
            return hash_value
        
        def _recalculate_hash(self, old_hash, old_char, new_char, power):
            """롤링 해시 업데이트"""
            hash_value = old_hash
            hash_value = (hash_value - ord(old_char) * power) % self.mod
            hash_value = (hash_value * self.base + ord(new_char)) % self.mod
            return hash_value
        
        def search(self, text):
            """패턴 매칭 수행"""
            n = len(text)
            if n < self.pattern_len:
                return []
                
            # 첫 번째 윈도우의 해시값 계산
            text_hash = self._calculate_hash(text[:self.pattern_len])
            
            # 가장 큰 자릿수의 거듭제곱값 계산
            power = pow(self.base, self.pattern_len - 1, self.mod)
            
            matches = []
            # 첫 윈도우 검사
            if (text_hash == self.pattern_hash and 
                text[:self.pattern_len] == self.pattern):
                matches.append(0)
            
            # 나머지 윈도우 순회
            for i in range(n - self.pattern_len):
                # 해시값 업데이트
                text_hash = self._recalculate_hash(
                    text_hash,
                    text[i],
                    text[i + self.pattern_len],
                    power
                )
                
                current_pos = i + 1
                # 해시값이 같으면 실제 문자열 비교
                if (text_hash == self.pattern_hash and
                    text[current_pos:current_pos + self.pattern_len] == self.pattern):
                    matches.append(current_pos)
                    
            return matches
    ```

* 최적화된 구현 (다중 패턴 검색)
    ```python
    class MultiPatternRabinKarp:
        def __init__(self, patterns):
            self.patterns = set(patterns)
            self.pattern_len = len(next(iter(patterns)))  # 모든 패턴의 길이가 같다고 가정
            self.base = 256
            self.mod = 10**9 + 7
            self.pattern_hashes = {self._calculate_hash(p) for p in patterns}
            
        def search_multiple(self, text):
            """여러 패턴 동시 검색"""
            n = len(text)
            matches = []
            
            if n < self.pattern_len:
                return matches
                
            # 첫 윈도우 해시값
            window_hash = self._calculate_hash(text[:self.pattern_len])
            power = pow(self.base, self.pattern_len - 1, self.mod)
            
            # 첫 윈도우 검사
            if window_hash in self.pattern_hashes:
                substr = text[:self.pattern_len]
                if substr in self.patterns:
                    matches.append((0, substr))
            
            # 나머지 윈도우 검사
            for i in range(n - self.pattern_len):
                window_hash = self._recalculate_hash(
                    window_hash,
                    text[i],
                    text[i + self.pattern_len],
                    power
                )
                
                if window_hash in self.pattern_hashes:
                    substr = text[i + 1:i + 1 + self.pattern_len]
                    if substr in self.patterns:
                        matches.append((i + 1, substr))
                        
            return matches
    ```

* 충돌 처리 최적화
    ```python
    class CollisionResistantRK:
        def __init__(self, pattern):
            self.pattern = pattern
            self.pattern_len = len(pattern)
            # 두 개의 서로 다른 해시 함수 사용
            self.base1 = 256
            self.base2 = 257
            self.mod1 = 10**9 + 7
            self.mod2 = 10**9 + 9
            self.pattern_hash1 = self._calculate_hash(pattern, self.base1, self.mod1)
            self.pattern_hash2 = self._calculate_hash(pattern, self.base2, self.mod2)
            
        def _calculate_double_hash(self, text, start):
            """이중 해시 계산"""
            hash1 = self._calculate_hash(
                text[start:start + self.pattern_len],
                self.base1,
                self.mod1
            )
            hash2 = self._calculate_hash(
                text[start:start + self.pattern_len],
                self.base2,
                self.mod2
            )
            return hash1, hash2
    ```

* 시간 복잡도
    |연산|평균|최악|
    |---|-----|-----|
    |전처리|O(m)|O(m)|
    |검색|O(n + m)|O(nm)|
    |다중 패턴|O(n + mk)|O(nmk)|

    * n: 텍스트 길이
    * m: 패턴 길이
    * k: 패턴 개수

* 공간 복잡도
    - O(1): 단일 패턴 검색
    - O(k): k개의 패턴 검색

* 장단점
    1. 장점
        - 여러 패턴 동시 검색 가능
        - 구현이 비교적 단순
        - 평균적으로 효율적
        - 롤링 해시로 빠른 계산

    2. 단점
        - 해시 충돌 가능성
        - 추가 메모리 필요 (다중 패턴)
        - 최악의 경우 성능 저하
        - 전처리 오버헤드

* 활용 예시
    1. 표절 검사
        ```python
        def plagiarism_check(document, patterns):
            """문서에서 표절 패턴 검사"""
            rk = MultiPatternRabinKarp(patterns)
            matches = rk.search_multiple(document.lower())
            
            return [(pos, pattern, len(pattern)) 
                    for pos, pattern in matches]
        ```

    2. DNA 서열 분석
        ```python
        def find_dna_motifs(sequence, motifs):
            """DNA 서열에서 여러 모티프 검색"""
            rk = MultiPatternRabinKarp(motifs)
            matches = rk.search_multiple(sequence)
            
            # 모티프별 위치 그룹화
            motif_positions = {}
            for pos, motif in matches:
                if motif not in motif_positions:
                    motif_positions[motif] = []
                motif_positions[motif].append(pos)
                
            return motif_positions
        ```

* 최적화 전략
    1. 해시 함수 선택
        ```python
        def optimize_hash_parameters(text_sample):
            """텍스트 특성에 따른 최적 해시 파라미터 선택"""
            # 문자 분포 분석
            char_freq = {}
            for c in text_sample:
                char_freq[c] = char_freq.get(c, 0) + 1
                
            # 특성에 따른 base 값 조정
            unique_chars = len(char_freq)
            if unique_chars < 26:  # 알파벳보다 적은 경우
                return 31, 10**9 + 7  # 작은 base 값
            else:
                return 256, 10**9 + 7  # 큰 base 값
        ```

    2. 병렬 처리
        ```python
        from concurrent.futures import ThreadPoolExecutor

        def parallel_search(text, patterns, num_threads=4):
            """병렬 처리를 통한 검색 최적화"""
            chunk_size = len(text) // num_threads
            chunks = [
                text[i:i + chunk_size] 
                for i in range(0, len(text), chunk_size)
            ]
            
            with ThreadPoolExecutor(max_workers=num_threads) as executor:
                futures = []
                for chunk in chunks:
                    rk = MultiPatternRabinKarp(patterns)
                    futures.append(
                        executor.submit(rk.search_multiple, chunk)
                    )
                    
                results = []
                offset = 0
                for future in futures:
                    chunk_matches = future.result()
                    results.extend(
                        (pos + offset, pattern) 
                        for pos, pattern in chunk_matches
                    )
                    offset += chunk_size
                    
                return results
        ```

* 마무리
    - 라빈-카프는 해시를 활용한 효율적인 문자열 검색 알고리즘
    - 다중 패턴 검색에 특히 유용
    - 적절한 해시 함수 선택이 중요
    - DNA 분석, 표절 검사 등 실제 응용에 활용

```mermaid
graph TD
    subgraph "라빈-카프 과정"
        A[패턴 해시 계산] --> B[첫 윈도우 해시 계산]
        B --> C[해시값 비교]
        C --> D{해시 일치?}
        D -->|Yes| E[문자열 비교]
        D -->|No| F[윈도우 이동]
        F --> G[롤링 해시 계산]
        G --> C
        E -->|일치| H[매칭 위치 저장]
        E -->|불일치| F
    end
    
    subgraph "해시 계산"
        I[윈도우 내 문자]
        J[기수(base) 거듭제곱]
        K[모듈러 연산]
        
        I --> J
        J --> K
    end
    
    style A fill:#f9f,stroke:#333
    style B fill:#bfb,stroke:#333
    style C fill:#bbf,stroke:#333
    style H fill:#fbf,stroke:#333
```