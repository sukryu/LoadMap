# 이진 검색 (Binary Search)의 심화

* 이진 검색의 변형
    1. 하한 검색 (Lower Bound)
        ```python
        def lower_bound(arr, target):
            """target 값이 처음 나타나는 위치를 찾음"""
            left, right = 0, len(arr)
            
            while left < right:
                mid = (left + right) // 2
                if arr[mid] < target:
                    left = mid + 1
                else:
                    right = mid
                    
            return left
        ```
        ```cpp
        #include <iostream>
        #include <vector>
        #include <algorithm>

        int lower_bound(const std::vector<int>& arr, int target) {
            int len = static_cast<int>(arr.size());
            int left = 0;
            int right = len;

            while (left < right) {
                int mid = (left + right) / 2;
                if (arr[mid] < target)
                    left = mid + 1;
                else
                    right = mid;
            }
            return left;
        }
        ```

    2. 상한 검색 (Upper Bound)
        ```python
        def upper_bound(arr, target):
            """target 값보다 큰 첫 번째 위치를 찾음"""
            left, right = 0, len(arr)
            
            while left < right:
                mid = (left + right) // 2
                if arr[mid] <= target:
                    left = mid + 1
                else:
                    right = mid
                    
            return left
        ```
        ```cpp
        #include <iostream>
        #include <vector>
        #include <algorithm>

        int upper_bound(const std::vector<int>& arr, int target) {
            int len = static_cast<int>(arr.size());
            int left = 0;
            int right = len;

            while (left < right) {
                int mid = (left + right) / 2;
                if (arr[mid] <= target)
                    left = mid + 1;
                else
                    right = mid;
            }
            return left;
        }
        ```

* 고급 응용
    1. 범위 검색
        ```python
        def find_range(arr, target):
            """target의 시작과 끝 인덱스를 찾음"""
            first = lower_bound(arr, target)
            last = upper_bound(arr, target) - 1
            
            if first <= last:
                return [first, last]
            return [-1, -1]
        ```
        ```cpp
        #include <iostream>
        #include <vector>
        #include <algorithm>

        std::vector<int> find_range(std::vector<int>& arr, int target) {
            int first = lower_bound(arr, target);
            int last = upper_bound(arr, target) - 1;
            std::vector<int> result;
            if (first <= last) {
                result.push_back(first);
                result.push_back(last);
                return result;
            }
            result.push_back(-1);
            result.push_back(-1);
            return result;
        }
        ```

    2. 순환 배열에서의 검색
        ```python
        def search_rotated(arr, target):
            """회전된 정렬 배열에서 검색"""
            left, right = 0, len(arr) - 1
            
            while left <= right:
                mid = (left + right) // 2
                
                if arr[mid] == target:
                    return mid
                    
                # 왼쪽 부분이 정렬되어 있는 경우
                if arr[left] <= arr[mid]:
                    if arr[left] <= target < arr[mid]:
                        right = mid - 1
                    else:
                        left = mid + 1
                # 오른쪽 부분이 정렬되어 있는 경우
                else:
                    if arr[mid] < target <= arr[right]:
                        left = mid + 1
                    else:
                        right = mid - 1
                        
            return -1
        ```
        ```cpp
        #include <iostream>
        #include <vector>
        #include <algorithm>
        using namespace std;

        int search_rotated(vector<int>& arr, int target) {
            int len = (int)arr.size();
            int left = 0;
            int right = len - 1;

            while (left <= right) {
                int mid = (left + right) / 2;

                if (arr[mid] == target) return mid;

                // 왼쪽 부분이 정렬된 경우
                if (arr[left] <= arr[mid]) {
                    if (arr[left] <= target && target < arr[mid]) {
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                } 
                // 오른쪽 부분이 정렬된 경우
                else {
                    if (arr[mid] < target && target <= arr[right]) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
            }

            return -1;
        }
        ```

* 실수 값에서의 이진 검색
    ```python
    def binary_search_real(func, target, epsilon=1e-9):
        """실수 범위에서 특정 값을 찾는 이진 검색"""
        left, right = 0.0, 1e9
            
        while right - left > epsilon:
            mid = (left + right) / 2
            result = func(mid)
                
            if abs(result - target) < epsilon:
                return mid
            elif result < target:
                left = mid
            else:
                right = mid
                    
        return left
    ```
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <functional>
    #include <cmath>

    double binary_search_real(std::function<double(double)> func,
                        double target,
                        double left = 0.0,
                        double right = 1e9,
                        double epsilon = 1e-9)
    {
        while ((right - left) > epsilon) {
            double mid = (left + right) / 2.0;
            double result = func(mid);

            if (std::fabs(result - target) < epsilon) {
                return mid;
            }
            else if (result < target) {
                left = mid;
            }
            else {
                right = mid;
            }
        }
        return left;
    }
    ```

* 최적화 문제 해결
    ```python
    def find_peak_element(arr):
        """배열에서 peak 요소 찾기"""
        left, right = 0, len(arr) - 1
        
        while left < right:
            mid = (left + right) // 2
            if arr[mid] > arr[mid + 1]:
                right = mid
            else:
                left = mid + 1
                
        return left

    def minimize_maximum(arr, k):
        """최대값을 최소화하는 문제"""
        def can_divide(max_sum):
            count = 1
            current_sum = 0
            for num in arr:
                if current_sum + num > max_sum:
                    count += 1
                    current_sum = num
                else:
                    current_sum += num
            return count <= k

        left = max(arr)
        right = sum(arr)
        result = right
        
        while left <= right:
            mid = (left + right) // 2
            if can_divide(mid):
                result = mid
                right = mid - 1
            else:
                left = mid + 1
                
        return result
    ```
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <numeric>  // std::accumulate

    // 1. Peak element 찾기 (이진 탐색 기반)
    int find_peak_element(const std::vector<int>& arr) {
        int left = 0;
        int right = static_cast<int>(arr.size()) - 1;

        while (left < right) {
            int mid = (left + right) / 2;
            // 만약 arr[mid]가 arr[mid + 1]보다 크다면, peak는 왼쪽 구간에 존재
            if (arr[mid] > arr[mid + 1]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        // left == right일 때가 peak의 인덱스
        return left;
    }

    // 2. 최대 구간 합을 제한하여 K개의 구간으로 나눌 수 있는지 검사하는 함수
    bool can_divide(const std::vector<int>& arr, int max_sum, int k) {
        int current_sum = 0;
        int count = 1;  // 첫 번째 구간 시작
        for (int num : arr) {
            // 현재 구간에 추가할 수 없으면, 새 구간 시작
            if (current_sum + num > max_sum) {
                count++;
                current_sum = num;
                // k개의 구간을 초과하면 false
                if (count > k) return false;
            } else {
                current_sum += num;
            }
        }
        // k개의 구간으로 나눌 수 있으면 true
        return true;
    }

    // 3. 최대 구간 합을 최소화하는 문제 (Binary Search로 해결)
    int minimize_maximum(std::vector<int>& arr, int k) {
        // 각 원소 중 최댓값(왼쪽 범위)과 전체 합(오른쪽 범위) 구하기
        int left = 0;  // max(arr)
        int right = 0; // sum(arr)
        for (int num : arr) {
            left = std::max(left, num);
            right += num;
        }

        int result = right; // 초기값: 전체 합

        while (left <= right) {
            int mid = (left + right) / 2;
            // mid(=max_sum)로 K구간 이하로 나눌 수 있다면
            if (can_divide(arr, mid, k)) {
                result = mid;      // 가능한 답 갱신
                right = mid - 1;   // 더 작은 값이 가능한지 탐색
            } else {
                left = mid + 1;    // mid보다 크게 잡아야 구간 나누기가 가능
            }
        }

        return result;
    }
    ```

* 병렬 처리를 위한 이진 검색
    ```python
    from concurrent.futures import ThreadPoolExecutor
    import threading

    class ParallelBinarySearch:
        def __init__(self, arr):
            self.arr = arr
            self.lock = threading.Lock()
            
        def search_range(self, start, end, target):
            """주어진 범위에서 target 검색"""
            while start <= end:
                mid = (start + end) // 2
                if self.arr[mid] == target:
                    return mid
                elif self.arr[mid] < target:
                    start = mid + 1
                else:
                    end = mid - 1
            return -1
            
        def parallel_search(self, target, num_threads=4):
            n = len(self.arr)
            chunk_size = n // num_threads
            futures = []
            
            with ThreadPoolExecutor(max_workers=num_threads) as executor:
                for i in range(num_threads):
                    start = i * chunk_size
                    end = start + chunk_size - 1 if i < num_threads - 1 else n - 1
                    futures.append(
                        executor.submit(self.search_range, start, end, target)
                    )
                    
            for future in futures:
                result = future.result()
                if result != -1:
                    return result
                    
            return -1
    ```
    ```cpp
    #include <iostream>
    #include <vector>
    #include <thread>
    #include <mutex>
    #include <atomic>
    #include <algorithm>

    // 구간 [start, end]에서 target을 이진 탐색하는 함수
    // 발견 시 해당 인덱스를 반환, 없으면 -1
    int search_range(const std::vector<int>& arr, int start, int end, int target) {
        while (start <= end) {
            int mid = (start + end) / 2;
            if (arr[mid] == target) return mid;
            else if (arr[mid] < target) {
                start = mid + 1;
            }
            else {
                end = mid - 1;
            }
        }
        return -1;
    }

    class ParallelBinarySearch {
    public:
        // 생성자: 배열을 받아서 내부에 저장
        ParallelBinarySearch(const std::vector<int>& arr) : arr_(arr) {}

        // num_threads 개의 스레드로 이진 탐색
        int parallel_search(int target, int num_threads = 4) {
            int n = static_cast<int>(arr_.size());
            if (n == 0) return -1;

            // 각 스레드가 찾은 인덱스를 저장할 원자 (초기 -1: 찾지 못함)
            // 하나라도 찾으면 이 값이 업데이트 됨.
            std::atomic<int> found_index(-1);

            // 스레드를 저장할 벡터
            std::vector<std::thread> threads;
            threads.reserve(num_threads);

            // 구간을 나누어서 할당
            int chunk_size = n / num_threads;

            // 병렬로 각 구간을 탐색
            for (int i = 0; i < num_threads; i++) {
                int start = i * chunk_size;
                int end = (i == num_threads - 1) ? (n - 1) : (start + chunk_size - 1);

                threads.emplace_back([&, start, end, target]() {
                    // 이미 스레드가 찾았다면 굳이 수행할 필요 없지만
                    // (간단하게) 계속 수행해도 되도록 설계.
                    // 필요 시 found_index.load() != -1 조건으로 조기 종료 가능.

                    int local_result = search_range(arr_, start, end, target);
                    if (local_result != -1) {
                        found_index.store(local_result);
                    }
                });
            }

            for (auto &t : threads) {
                t.join();
            }

            return found_index.load();
        }

    private:
        const std::vector<int>& arr_;
    };
    ```

* 이진 검색 트리와의 연계
    ```python
    class BSTNode:
        def __init__(self, value):
            self.value = value
            self.left = None
            self.right = None
            self.count = 1  # 중복 값 처리
            
        def insert(self, value):
            if value == self.value:
                self.count += 1
            elif value < self.value:
                if self.left:
                    self.left.insert(value)
                else:
                    self.left = BSTNode(value)
            else:
                if self.right:
                    self.right.insert(value)
                else:
                    self.right = BSTNode(value)
                    
        def find_kth_element(self, k):
            """k번째 작은 원소 찾기"""
            left_count = 0 if not self.left else self.left.count
            
            if k <= left_count:
                return self.left.find_kth_element(k)
            elif k <= left_count + self.count:
                return self.value
            else:
                return self.right.find_kth_element(k - left_count - self.count)
    ```
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    struct BSTNode {
        int value;         // 노드 값
        int count;         // 중복된 value의 개수
        int subtree_size;  // (왼쪽서브트리 + 오른쪽서브트리 + this->count)
        BSTNode* left;
        BSTNode* right;

        BSTNode(int v)
            : value(v), count(1), subtree_size(1), left(nullptr), right(nullptr) {}

        void update_subtree_size(BSTNode* node) {
            if (!node) return;
            int left_size = (node->left ? node->left->subtree_size : 0);
            int right_size = (node->right ? node->right->subtree_size : 0);
            // 현재 노드의 총 개수 = 왼쪽 서브트리 개수 + 오른쪽 서브트리 개수 + 현재 노드 count
            node->subtree_size = left_size + right_size + node->count;
        }

        BSTNode* insert_node(BSTNode* node, int value) {
            if (!node) {
                // 노드가 없으면 새로 할당
                return new BSTNode(value);
            }

            if (value == node->value) {
                // 동일한 값 -> count 증가
                node->count++;
            }
            else if (value < node->value) {
                // 왼쪽 서브트리에 삽입
                node->left = insert_node(node->left, value);
            }
            else {
                // 오른쪽 서브트리에 삽입
                node->right = insert_node(node->right, value);
            }

            // 서브트리 크기 갱신
            update_subtree_size(node);
            return node;
        }

        int find_kth_element(BSTNode* node, int k) {
            if (!node) {
                // 유효 범위 벗어나면 -1 등으로 에러처리
                return -1;
            }

            int left_size = (node->left ? node->left->subtree_size : 0);

            if (k <= left_size) {
                // 왼쪽 서브트리로
                return find_kth_element(node->left, k);
            } 
            else if (k <= left_size + node->count) {
                // 현재 노드 값이 k번째
                return node->value;
            } 
            else {
                // 오른쪽 서브트리에서 (k - (left_size + count)) 번째
                int new_k = k - (left_size + node->count);
                return find_kth_element(node->right, new_k);
            }
        }
    };

    ```

- 이진 검색의 심화 내용은 실제 문제 해결에서 매우 유용하게 활용됩니다. 특히 최적화 문제나 실수 값을 다루는
문제에서 자주 사용되며, 병렬 처리를 통해 성능을 더욱 향상시킬 수 있습니다.