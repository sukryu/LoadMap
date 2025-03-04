package examples

import (
	"fmt"
	"reflect"
)

// SliceManager는 슬라이스 작업을 관리하는 구조체입니다.
// K8s 스타일: 슬라이스 관련 로직을 모듈화하여 재사용성과 유지보수성을 높임.
type SliceManager struct{}

// NewSliceManager는 새로운 SliceManager 인스턴스를 생성합니다.
// K8s 스타일: 생성자 함수는 'New'를 접두사로 사용하며 초기화 캡슐화.
func NewSliceManager() *SliceManager {
	return &SliceManager{}
}

// DemonstrateThreeIndexSlicing은 3인덱스 슬라이싱(slice[start:end:cap])을 보여줍니다.
// K8s 스타일: 메서드는 단일 책임을 가지며 동작을 상세히 주석으로 설명.
func (sm *SliceManager) DemonstrateThreeIndexSlicing() {
	// 초기 슬라이스 생성: 길이 5, 용량 10.
	// K8s 스타일: 초기화 상태를 명확히 로깅.
	original := make([]int, 5, 10)
	for i := 0; i < len(original); i++ {
		original[i] = i + 1 // 1, 2, 3, 4, 5
	}
	fmt.Printf("원본 슬라이스: %v, len: %d, cap: %d\n", original, len(original), cap(original))

	// 3인덱스 슬라이싱: start:end:cap으로 용량 제한.
	// 슬라이스 [2, 3, 4]를 추출하되, 용량을 4로 제한.
	limited := original[1:4:4]
	fmt.Printf("3인덱스 슬라이싱: %v, len: %d, cap: %d\n", limited, len(limited), cap(limited))

	// 슬라이스 수정 시 원본 반영 확인.
	limited[0] = 99
	fmt.Printf("제한된 슬라이싱 수정 후 원본: %v\n", original)

	// 용량 초과 시도: append로 용량 증가 확인.
	// K8s 스타일: 동작의 결과와 제한 사항 설명.
	limited = append(limited, 6)
	fmt.Printf("append 후 제한된 슬라이싱: %v, len: %d, cap: %d\n", limited, len(limited), cap(limited))
	fmt.Printf("append 후 원본 (영향 없음): %v\n", original)
	// 주의: 용량이 제한되었으므로 append는 새 배열을 생성하며 원본과 분리됨.
}

// CreateMultiDimensionalSlice는 다차원 슬라이스를 생성하고 초기화합니다.
// K8s 스타일: 함수는 단일 목적을 가지며 반환값으로 결과 제공.
func (sm *SliceManager) CreateMultiDimensionalSlice(rows, cols int) [][]int {
	// 2D 슬라이스 생성: rows x cols 크기.
	// K8s 스타일: 메모리 할당과 초기화 로직을 명확히 분리.
	matrix := make([][]int, rows)
	for i := range matrix {
		// 각 행에 대해 cols 크기의 슬라이스 초기화.
		// K8s 스타일: 용량을 미리 지정해 재할당 최소화.
		matrix[i] = make([]int, cols)
		for j := range matrix[i] {
			// 간단한 패턴으로 값 채움 (행+열 번호 기반).
			matrix[i][j] = i*cols + j + 1
		}
	}
	return matrix
}

// PrintMatrix는 2D 슬라이스의 내용을 보기 좋게 출력합니다.
// K8s 스타일: 재사용 가능한 유틸리티 함수로 분리.
func (sm *SliceManager) PrintMatrix(matrix [][]int, label string) {
	fmt.Printf("%s:\n", label)
	for _, row := range matrix {
		fmt.Printf("  %v\n", row)
	}
}

// DemonstrateMultiDimensionalSlice는 다차원 슬라이스의 생성과 조작을 보여줍니다.
// K8s 스타일: 동작과 결과의 의미를 주석으로 상세히 설명.
func (sm *SliceManager) DemonstrateMultiDimensionalSlice(rows, cols int) {
	// 2D 슬라이스 생성.
	matrix := sm.CreateMultiDimensionalSlice(rows, cols)
	sm.PrintMatrix(matrix, "초기 2D 슬라이스")

	// 슬라이스 내부 구조 분석: reflect.SliceHeader 사용.
	// K8s 스타일: 내부 동작 이해를 위한 디버깅 정보 제공.
	for i, row := range matrix {
		header := reflect.SliceHeader{
			Data: uintptr(reflect.ValueOf(row).Pointer()),
			Len:  len(row),
			Cap:  cap(row),
		}
		fmt.Printf("행 %d의 SliceHeader - Data: %d, Len: %d, Cap: %d\n", i, header.Data, header.Len, header.Cap)
	}

	// 조작 예시: 특정 요소 수정.
	// K8s 스타일: 변경 전후 상태를 명확히 로깅.
	if rows > 1 && cols > 1 {
		fmt.Printf("\n수정 전: matrix[1][1] = %d\n", matrix[1][1])
		matrix[1][1] = 99
		fmt.Printf("수정 후: matrix[1][1] = %d\n", matrix[1][1])
		sm.PrintMatrix(matrix, "수정된 2D 슬라이스")
	}

	// 용량 확장 예시: 한 행에 append 수행.
	// K8s 스타일: 동작의 제한 사항(독립성) 명시.
	if len(matrix) > 0 {
		originalRow := matrix[0]
		extendedRow := append(matrix[0], rows*cols+1)
		fmt.Printf("append 후 행 0: %v, len: %d, cap: %d\n", extendedRow, len(extendedRow), cap(extendedRow))
		fmt.Printf("원본 행 0 (영향 없음): %v\n", originalRow)
		// 주의: append는 새 슬라이스를 생성하므로 원본 행과 분리됨.
	}
}

// SliceAdvanced demonstrates advanced slice usage including three-index slicing and multi-dimensional slices.
// K8s 스타일: 메인 함수는 각 데모를 독립적으로 호출하며 실행 흐름을 명확히 보여줌.
func SliceAdvanced() {
	// SliceManager 인스턴스 생성.
	manager := NewSliceManager()

	// 데모 1: 3인덱스 슬라이싱.
	fmt.Println("=== 3인덱스 슬라이싱 데모 ===")
	manager.DemonstrateThreeIndexSlicing()

	// 데모 2: 다차원 슬라이스.
	fmt.Println("\n=== 다차원 슬라이스 데모 ===")
	manager.DemonstrateMultiDimensionalSlice(3, 4)
}
