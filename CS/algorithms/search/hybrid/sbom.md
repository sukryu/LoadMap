# Set-Backward Oracle Matching (SBOM)

* 개념
    * **SBOM**은 Factor Oracle을 사용한 다중 패턴 매칭 알고리즘입니다.
    * 특징:
        - Factor Oracle 오토마타 사용
        - 뒤에서부터 검사 수행
        - 효율적인 건너뛰기 규칙
        - 최소한의 메모리 사용

* 핵심 구성 요소
    1. Factor Oracle
        - 패턴의 모든 factor를 인식
        - 최소한의 상태로 구성
        - 외부 전이(External Transition)

    2. 건너뛰기 함수
        - Boyer-Moore 스타일 이동
        - 최대 이동량 계산
        - 패턴 집합 고려

* 기본 구현
    ```python
    class SBOM:
        class State:
            def __init__(self):
                self.transitions = {}  # 전이 함수
                self.supply = None     # supply 함수
                self.output = set()    # 매칭된 패턴
                
        def __init__(self, patterns):
            self.patterns = patterns
            self.min_length = min(len(p) for p in patterns)
            self.oracle = self._build_oracle()
            self.shifts = self._build_shift_table()
            
        def _build_oracle(self):
            """Factor Oracle 구축"""
            states = [self.State() for _ in range(self.min_length + 1)]
            
            # 기본 전이 설정
            for i in range(self.min_length):
                for pattern in self.patterns:
                    if i < len(pattern):
                        char = pattern[i]
                        states[i].transitions[char] = states[i + 1]
                        
                        if i == len(pattern) - 1:
                            states[i + 1].output.add(pattern)
                            
            # Supply 함수 설정
            for i in range(1, self.min_length + 1):
                state = states[i]
                prev = states[i - 1]
                
                for char, next_state in prev.transitions.items():
                    if char not in state.transitions:
                        state.supply = next_state
                        break
                        
            return states
            
        def _build_shift_table(self):
            """건너뛰기 테이블 구축"""
            shifts = {}
            
            for pattern in self.patterns:
                for i, char in enumerate(pattern[:-1]):
                    shifts[char] = min(shifts.get(char, self.min_length),
                                     len(pattern) - i - 1)
                    
            return shifts
            
        def search(self, text):
            """패턴 검색 수행"""
            matches = []
            n = len(text)
            pos = self.min_length - 1
            
            while pos < n:
                current = self.oracle[0]
                i = 0
                
                # 패턴의 끝에서부터 검사
                while i < self.min_length and current:
                    char = text[pos - i]
                    
                    if char in current.transitions:
                        current = current.transitions[char]
                    else:
                        current = current.supply
                        
                    i += 1
                    
                # 매칭 확인
                if current and current.output:
                    for pattern in current.output:
                        if pos - len(pattern) + 1 >= 0:
                            matches.append(pos - len(pattern) + 1)
                            
                # 이동량 계산
                if i < self.min_length:
                    char = text[pos - i]
                    pos += self.shifts.get(char, self.min_length)
                else:
                    pos += 1
                    
            return sorted(matches)
    ```

* 최적화된 구현
    ```python
    class OptimizedSBOM:
        def __init__(self, patterns):
            self.patterns = patterns
            self.min_length = min(len(p) for p in patterns)
            # 비트마스크를 사용한 최적화
            self.pattern_masks = self._build_pattern_masks()
            self.oracle = self._build_optimized_oracle()
            
        def _build_pattern_masks(self):
            """패턴별 비트마스크 생성"""
            masks = {}
            for i, pattern in enumerate(self.patterns):
                mask = 1 << i
                for char in pattern:
                    if char not in masks:
                        masks[char] = 0
                    masks[char] |= mask
            return masks
            
        def _build_optimized_oracle(self):
            """최적화된 Factor Oracle 구축"""
            states = []
            for i in range(self.min_length + 1):
                state = {
                    'transitions': {},
                    'mask': 0,
                    'supply': None
                }
                states.append(state)
                
            # 전이와 마스크 설정
            for pattern_idx, pattern in enumerate(self.patterns):
                mask = 1 << pattern_idx
                for i in range(min(len(pattern), self.min_length)):
                    char = pattern[i]
                    states[i]['transitions'][char] = states[i + 1]
                    states[i + 1]['mask'] |= mask
                    
            return states
            
        def search(self, text):
            """최적화된 검색"""
            matches = []
            n = len(text)
            window = self.min_length
            
            while window <= n:
                current_state = self.oracle[0]
                current_mask = (1 << len(self.patterns)) - 1
                pos = window - 1
                
                # 윈도우 검사
                while current_mask != 0 and pos >= window - self.min_length:
                    char = text[pos]
                    if char in current_state['transitions']:
                        next_state = current_state['transitions'][char]
                        current_mask &= next_state['mask']
                        current_state = next_state
                    else:
                        break
                    pos -= 1
                    
                # 매칭 확인
                if current_mask != 0:
                    for i in range(len(self.patterns)):
                        if current_mask & (1 << i):
                            pattern = self.patterns[i]
                            if window >= len(pattern):
                                matches.append(window - len(pattern))
                                
                window += 1
                
            return sorted(matches)
    ```

* 시간 복잡도
    |연산|복잡도|설명|
    |---|------|-----|
    |Oracle 구축|O(m)|m은 모든 패턴 길이의 합|
    |검색|O(n)|n은 텍스트 길이|
    |최악|O(nm)|m은 가장 짧은 패턴의 길이|

* 공간 복잡도
    - O(m): Oracle과 테이블 저장

* 장단점
    1. 장점
        - 효율적인 메모리 사용
        - 빠른 검색 속도
        - Factor Oracle의 단순성
        - 실제 데이터에서 좋은 성능

    2. 단점
        - 구현이 복잡
        - 최소 길이 제한
        - 전처리 시간 필요
        - 건너뛰기 최적화 제한

* 활용 예시
    1. DNA 시퀀스 검색
        ```python
        class DNAMatcher:
            def __init__(self, patterns):
                self.matcher = OptimizedSBOM(patterns)
                
            def find_sequences(self, genome):
                """DNA 시퀀스에서 패턴 검색"""
                chunk_size = 1024 * 1024  # 1MB
                matches = []
                
                for i in range(0, len(genome), chunk_size):
                    chunk = genome[i:i + chunk_size]
                    chunk_matches = self.matcher.search(chunk)
                    matches.extend(m + i for m in chunk_matches)
                    
                return matches
        ```

    2. 로그 분석
        ```python
        class LogAnalyzer:
            def __init__(self, patterns):
                self.matcher = SBOM(patterns)
                self.patterns = patterns
                
            def analyze_log(self, log_file):
                """로그 파일에서 여러 패턴 검색"""
                results = {}
                
                with open(log_file, 'r') as f:
                    for line_num, line in enumerate(f, 1):
                        matches = self.matcher.search(line)
                        for pos in matches:
                            pattern = self._find_pattern(line, pos)
                            if pattern not in results:
                                results[pattern] = []
                            results[pattern].append(line_num)
                            
                return results
                
            def _find_pattern(self, text, pos):
                """매칭된 패턴 찾기"""
                for pattern in self.patterns:
                    if text[pos:pos + len(pattern)] == pattern:
                        return pattern
                return None
        ```

* 최적화 전략
    1. 병렬 처리
        ```python
        from concurrent.futures import ProcessPoolExecutor
        
        def parallel_search(text, patterns, num_processes=4):
            """병렬 처리를 통한 검색"""
            chunk_size = len(text) // num_processes
            chunks = [
                text[i:i + chunk_size]
                for i in range(0, len(text), chunk_size)
            ]
            
            matcher = SBOM(patterns)
            
            with ProcessPoolExecutor(max_workers=num_processes) as executor:
                futures = []
                for i, chunk in enumerate(chunks):
                    futures.append(
                        executor.submit(matcher.search, chunk)
                    )
                    
                matches = []
                offset = 0
                for future in futures:
                    chunk_matches = future.result()
                    matches.extend(m + offset for m in chunk_matches)
                    offset += chunk_size
                    
                return sorted(matches)
        ```

    2. SIMD 최적화
        ```python
        class SIMDOptimizedSBOM:
            def __init__(self, patterns):
                self.matcher = SBOM(patterns)
                self.min_length = min(len(p) for p in patterns)
                
            def compare_block(self, text, pos, pattern):
                """SIMD를 활용한 블록 비교"""
                # 실제로는 C/C++에서 SIMD 명령어 사용
                block_size = 16  # SSE 레지스터 크기
                
                for i in range(0, len(pattern), block_size):
                    end = min(i + block_size, len(pattern))
                    if text[pos + i:pos + end] != pattern[i:end]:
                        return False
                return True
        ```

* 마무리
    - SBOM은 효율적인 다중 패턴 매칭 알고리즘
    - Factor Oracle의 단순성과 Boyer-Moore의 효율성 결합
    - 메모리 효율적이면서도 빠른 검색 가능
    - 생물정보학, 로그 분석 등에 활용

```mermaid
graph TD
    subgraph "Factor Oracle 구축"
        A[패턴 집합] --> B[기본 전이 설정]
        B --> C[Supply 함수 설정]
        C --> D[건너뛰기 테이블]
    end
    
    subgraph "검색 과정"
        E[텍스트 입력]
        F[윈도우 위치]
        G[Oracle 순회]
        H[매칭 확인]
        I[윈도우 이동]
        
        E --> F
        F --> G
        G --> H
        H --> I
        I --> F
    end
    
    style A fill:#f9f,stroke:#333
    style B fill:#bfb,stroke:#333
    style C fill:#bbf,stroke:#333
    style D fill:#fbf,stroke:#333
```