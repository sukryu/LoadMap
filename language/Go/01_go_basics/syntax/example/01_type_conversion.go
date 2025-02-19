package examples

import (
	"fmt"
	"strconv"
)

// TypeConversionExamples demonstrates various type conversion scenarios
// commonly encountered in Go programming
func TypeConversionExamples() {
	// 숫자형 간의 변환
	var integer int = 42
	var float float64 = float64(integer)
	var integer32 int32 = int32(float)

	fmt.Printf("정수: %d, 실수: %f, 32비트 정수: %d\n",
		integer, float, integer32)

	// 문자열 변환
	str := "123"
	num, err := strconv.Atoi(str)
	if err != nil {
		fmt.Println("문자열을 숫자로 변환 중 에러 발생:", err)
		return
	}

	// 숫자를 문자열로 변환
	str = strconv.Itoa(num)
	fmt.Printf("문자열: %s, 숫자: %d\n", str, num)

	// 실수 문자열 처리
	floatStr := "3.14"
	floatNum, err := strconv.ParseFloat(floatStr, 64)
	if err != nil {
		fmt.Println("실수 문자열 변환 중 에러 발생:", err)
		return
	}

	fmt.Printf("파싱된 실수: %f\n", floatNum)
}
