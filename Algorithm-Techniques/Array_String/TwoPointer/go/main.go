package twopointer

/*
 * 이 파일은 코딩 테스트에서 투 포인터 기법을 활용하여 다양한 문제 유형을 해결하는 예제 함수를 포함합니다.
 * 각 함수는 문제 해결을 위한 최적의 접근법을 제공하며, 시간/공간 복잡도를 고려한 구현입니다.
 * 주석을 매우 상세하게 작성하여 코드만 보더라도 이해할 수 있도록 구성하였습니다.
 *
 * 포함된 함수:
 * 1. findMinSubarrayLength:
 *      - 문제: 양의 정수 배열에서 합이 target 이상이 되는 최소 연속 부분 배열의 길이 찾기
 *      - 기법: 슬라이딩 윈도우 (투 포인터)
 * 2. mergeSortedArrays:
 *      - 문제: 정렬된 두 배열을 하나의 정렬된 배열로 병합하기
 *      - 기법: 두 배열의 포인터를 이용한 병합
 * 3. removeDuplicates:
 *      - 문제: 정렬된 배열에서 중복을 제거하여 유니크한 원소들만 남기기 (in-place)
 *      - 기법: 두 포인터를 이용한 중복 제거
 * 4. findPairWithSum:
 *      - 문제: 정렬된 배열에서 두 수의 합이 target이 되는 쌍 찾기
 *      - 기법: 양쪽 끝에서 시작하는 투 포인터 탐색
 *
 * 주의: main 함수는 포함되어 있지 않으므로, 이 파일은 함수들의 모음집으로 사용됩니다.
 */

/*
 * 함수: findMinSubarrayLength
 * --------------------------------
 * 설명:
 *   주어진 양의 정수 배열 arr와 목표 합 target에 대해, 연속된 부분 배열 중
 *   합이 target 이상이 되는 최소 길이를 반환합니다.
 *   슬라이딩 윈도우(투 포인터) 기법을 사용하여 O(n) 시간 복잡도로 문제를 해결합니다.
 *
 * 매개변수:
 *   arr    - 입력 배열 (양의 정수)
 *   n      - 배열의 길이
 *   target - 목표 합
 *
 * 반환:
 *   조건을 만족하는 최소 부분 배열의 길이.
 *   만약 해당하는 부분 배열이 없으면 0을 반환.
 *
 * 시간 복잡도: O(n)
 * 공간 복잡도: O(1)
 */
func findMinSubarrayLength(arr []int, n int, target int) int {
	minLength := n + 1 // 가능한 최대 길이보다 1 큰 값으로 초기화
	currentSum := 0    // 현재 윈도우의 합
	left := 0          // 슬라이딩 윈도우의 왼쪽 포인터

	// right 포인터가 배열을 순회하면서 윈도우에 원소를 추가합니다.
	for right := 0; right < n; right++ {
		currentSum += arr[right] // 오른쪽 포인터가 가리키는 원소를 합에 추가

		// 현재 합이 target 이상이면, 윈도우를 축소해 최소 길이를 찾습니다.
		for currentSum >= target {
			currentLength := right - left + 1 // 현재 윈도우의 길이
			if currentLength < minLength {
				minLength = currentLength // 최소 길이 갱신
			}
			currentSum -= arr[left] // 왼쪽 포인터 원소를 제거하여 윈도우 축소
			left++
		}
	}
	// 최소 길이가 초기값과 동일하면 조건을 만족하는 부분 배열이 없음을 의미
	if minLength == n+1 {
		return 0
	}
	return minLength
}

/*
 * 함수: mergeSortedArrays
 * --------------------------------
 * 설명:
 *   두 개의 정렬된 배열 arr1과 arr2를 하나의 정렬된 배열로 병합합니다.
 *   두 포인터를 사용하여 각 배열의 원소를 비교하고 결과 배열에 순서대로 삽입합니다.
 *
 * 매개변수:
 *   arr1 - 첫 번째 정렬된 배열
 *   n    - 첫 번째 배열의 길이
 *   arr2 - 두 번째 정렬된 배열
 *   m    - 두 번째 배열의 길이
 *
 * 반환:
 *   동적 할당된 병합된 배열(슬라이스)의 포인터.
 *   Go에서는 메모리 할당 실패 시 panic이 발생할 수 있으며, 일반적으로 nil을 확인하지 않아도 됩니다.
 *
 * 시간 복잡도: O(n + m)
 * 공간 복잡도: O(n + m)
 */
func mergeSortedArrays(arr1 []int, n int, arr2 []int, m int) []int {
	// 병합된 결과를 저장할 슬라이스를 동적 할당합니다.
	merged := make([]int, n+m)

	i, j, k := 0, 0, 0

	// 두 배열의 포인터가 모두 유효한 동안, 작은 값을 선택하여 병합 배열에 추가합니다.
	for i < n && j < m {
		if arr1[i] <= arr2[j] {
			merged[k] = arr1[i]
			i++
		} else {
			merged[k] = arr2[j]
			j++
		}
		k++
	}

	// 남은 원소들을 복사합니다.
	for i < n {
		merged[k] = arr1[i]
		i++
		k++
	}
	for j < m {
		merged[k] = arr2[j]
		j++
		k++
	}

	return merged
}

/*
 * 함수: removeDuplicates
 * --------------------------------
 * 설명:
 *   정렬된 배열에서 중복된 원소를 제거하여 유일한 원소들만 남깁니다.
 *   두 포인터(빠른 포인터와 느린 포인터)를 사용하여 in-place로 배열을 수정합니다.
 *
 * 매개변수:
 *   arr - 정렬된 배열 (중복이 있을 수 있음)
 *   n   - 배열의 길이
 *
 * 반환:
 *   중복 제거 후 배열의 새로운 길이.
 *
 * 시간 복잡도: O(n)
 * 공간 복잡도: O(1)
 */
func removeDuplicates(arr []int, n int) int {
	if n == 0 {
		return 0
	}

	j := 0 // 느린 포인터: 유일한 원소의 마지막 위치

	// 빠른 포인터 i가 배열을 순회하면서 중복이 아닌 원소를 찾습니다.
	for i := 1; i < n; i++ {
		if arr[i] != arr[j] {
			j++
			arr[j] = arr[i]
		}
	}
	// 유일 원소의 수는 j + 1
	return j + 1
}

/*
 * 함수: findPairWithSum
 * --------------------------------
 * 설명:
 *   정렬된 배열에서 두 수의 합이 주어진 target과 일치하는 쌍을 찾습니다.
 *   왼쪽과 오른쪽 끝에서 시작하여 두 포인터를 이동시키며 조건을 검사합니다.
 *
 * 매개변수:
 *   arr    - 정렬된 배열
 *   n      - 배열의 길이
 *   target - 목표 합
 *
 * 반환:
 *   조건을 만족하는 쌍을 찾으면 true와 해당 쌍을 반환합니다.
 *   쌍을 찾지 못하면 false와 0, 0을 반환합니다.
 *
 * 시간 복잡도: O(n)
 * 공간 복잡도: O(1)
 */
func findPairWithSum(arr []int, n int, target int) (bool, int, int) {
	left := 0      // 배열의 시작 위치
	right := n - 1 // 배열의 끝 위치

	// 두 포인터가 교차할 때까지 반복
	for left < right {
		currentSum := arr[left] + arr[right]

		// 목표 합을 만족하는 경우
		if currentSum == target {
			return true, arr[left], arr[right]
		} else if currentSum < target {
			// 현재 합이 목표보다 작으면 왼쪽 포인터를 이동하여 합을 증가시킴
			left++
		} else {
			// 현재 합이 목표보다 크면 오른쪽 포인터를 이동하여 합을 감소시킴
			right--
		}
	}
	// 조건에 맞는 쌍을 찾지 못한 경우
	return false, 0, 0
}

/*
 * End of converted Go code
 *
 * 이 파일은 코딩 테스트에서 투 포인터 기법을 사용하여 다양한 문제를 해결하는 예제 함수들을 Go 언어로 변환한 코드입니다.
 * 각 함수는 상세한 주석을 통해 문제 유형, 알고리즘 동작 원리, 및 시간/공간 복잡도에 대해 설명하고 있습니다.
 */
