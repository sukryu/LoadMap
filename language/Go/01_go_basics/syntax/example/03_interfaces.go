package examples

import (
	"fmt"
	"math"
)

// Shape defines the interface for geometric shapes.
// K8s 스타일: 인터페이스 명세는 간결하고 명확하게 정의.
type Shape interface {
	Area() float64
	Perimeter() float64
}

// Circle implements Shape.
// K8s 스타일: 구조체는 필요한 필드만 포함.
type Circle struct {
	Radius float64
}

// Area calculates the area of a Circle.
func (c Circle) Area() float64 {
	return math.Pi * c.Radius * c.Radius
}

// Perimeter calculates the perimeter of a Circle.
func (c Circle) Perimeter() float64 {
	return 2 * math.Pi * c.Radius
}

// Rectangle implements Shape.
type Rectangle struct {
	Width  float64
	Height float64
}

// Area calculates the area of a Rectangle.
func (r Rectangle) Area() float64 {
	return r.Width * r.Height
}

// Perimeter calculates the perimeter of a Rectangle.
func (r Rectangle) Perimeter() float64 {
	return 2 * (r.Width + r.Height)
}

// PrintShapeInfo prints information about any Shape.
// K8s 스타일: 재사용 가능한 유틸리티 함수는 명확한 책임을 가짐.
func PrintShapeInfo(s Shape) {
	fmt.Printf("도형 정보:\n")
	fmt.Printf("  - 넓이: %.2f\n", s.Area())
	fmt.Printf("  - 둘레: %.2f\n", s.Perimeter())
}

// ShapeAnalyzer는 Shape 인터페이스의 타입 단언과 빈 인터페이스를 분석하는 구조체입니다.
// K8s 스타일: 관련 로직을 구조체로 묶어 관리.
type ShapeAnalyzer struct{}

// NewShapeAnalyzer는 새로운 ShapeAnalyzer 인스턴스를 생성합니다.
// K8s 스타일: 생성자 함수는 'New'를 접두사로 사용.
func NewShapeAnalyzer() *ShapeAnalyzer {
	return &ShapeAnalyzer{}
}

// AnalyzeShape는 Shape 인터페이스를 받아 타입 단언(Type Assertion)을 통해 구체적 타입을 확인합니다.
// K8s 스타일: 메서드는 단일 책임을 가지며 동작을 상세히 주석으로 설명.
func (sa *ShapeAnalyzer) AnalyzeShape(s Shape) {
	// 기본 정보 출력.
	PrintShapeInfo(s)

	// 타입 단언(Type Assertion)으로 구체적 타입 확인.
	if circle, ok := s.(Circle); ok {
		fmt.Printf("  - 타입: Circle, 반지름: %.2f\n", circle.Radius)
	} else if rect, ok := s.(Rectangle); ok {
		fmt.Printf("  - 타입: Rectangle, 폭: %.2f, 높이: %.2f\n", rect.Width, rect.Height)
	} else {
		fmt.Println("  - 알 수 없는 Shape 타입")
	}
}

// ProcessAny는 빈 인터페이스(interface{})를 받아 동적으로 처리합니다.
// K8s 스타일: 동작의 목적과 제한 사항을 주석으로 명시.
// 주의: 빈 인터페이스는 타입 안전성이 떨어지므로 필요한 경우에만 사용.
func (sa *ShapeAnalyzer) ProcessAny(data interface{}) {
	switch v := data.(type) {
	case string:
		fmt.Printf("빈 인터페이스 입력 - 문자열: %s\n", v)
	case int:
		fmt.Printf("빈 인터페이스 입력 - 정수: %d\n", v)
	case Shape:
		fmt.Printf("빈 인터페이스 입력 - Shape 타입:\n")
		sa.AnalyzeShape(v)
	default:
		fmt.Println("빈 인터페이스 입력 - 처리할 수 없는 타입")
	}
}

// InterfaceExamples demonstrates interface usage, type assertion, and empty interface in Go.
func InterfaceExamples() {
	// ShapeAnalyzer 인스턴스 생성.
	analyzer := NewShapeAnalyzer()

	// Circle 사용.
	circle := Circle{Radius: 5}
	fmt.Println("=== Circle 예제 ===")
	analyzer.AnalyzeShape(circle)

	// Rectangle 사용.
	rectangle := Rectangle{Width: 4, Height: 6}
	fmt.Println("\n=== Rectangle 예제 ===")
	analyzer.AnalyzeShape(rectangle)

	// 인터페이스 슬라이스 사용.
	shapes := []Shape{circle, rectangle}
	for i, shape := range shapes {
		fmt.Printf("\n=== 도형 %d ===", i+1)
		analyzer.AnalyzeShape(shape)
	}

	// 빈 인터페이스(interface{}) 활용 예제.
	fmt.Println("\n=== 빈 인터페이스 예제 ===")
	analyzer.ProcessAny("Hello, Go!")
	analyzer.ProcessAny(42)
	analyzer.ProcessAny(circle)
	analyzer.ProcessAny([]int{1, 2, 3}) // 처리되지 않는 타입 예시.
}
