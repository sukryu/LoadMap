package examples

import (
	"fmt"
	"math"
)

// Shape defines the interface for geometric shapes
type Shape interface {
	Area() float64
	Perimeter() float64
}

// Circle implements Shape
type Circle struct {
	Radius float64
}

func (c Circle) Area() float64 {
	return math.Pi * c.Radius * c.Radius
}

func (c Circle) Perimeter() float64 {
	return 2 * math.Pi * c.Radius
}

// Rectangle implements Shape
type Rectangle struct {
	Width  float64
	Height float64
}

func (r Rectangle) Area() float64 {
	return r.Width * r.Height
}

func (r Rectangle) Perimeter() float64 {
	return 2 * (r.Width + r.Height)
}

// PrintShapeInfo prints information about any Shape
func PrintShapeInfo(s Shape) {
	fmt.Printf("도형 정보:\n")
	fmt.Printf("  - 넓이: %.2f\n", s.Area())
	fmt.Printf("  - 둘레: %.2f\n", s.Perimeter())
}

// InterfaceExamples demonstrates interface usage in Go
func InterfaceExamples() {
	// Circle 사용
	circle := Circle{Radius: 5}
	PrintShapeInfo(circle)

	// Rectangle 사용
	rectangle := Rectangle{Width: 4, Height: 6}
	PrintShapeInfo(rectangle)

	// 인터페이스 슬라이스 사용
	shapes := []Shape{circle, rectangle}
	for i, shape := range shapes {
		fmt.Printf("\n도형 %d:\n", i+1)
		PrintShapeInfo(shape)
	}
}
