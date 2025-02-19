/*
이 예제는 Go에서 파이프라인 패턴을 구현하는 포괄적인 예시를 제공합니다. 파이프라인 패턴은 데이터가 여러 처리 단계를 순차적으로 거치면서 변환되는 과정을 구현할 때 특히 유용합니다. 주요 컴포넌트와 특징은 다음과 같습니다:

데이터 구조: DataItem 구조체는 파이프라인을 통해 흐르는 데이터를 표현하며, 처리 과정에서의 에러 추적과 성능 모니터링을 위한 필드들을 포함합니다.
파이프라인 구조: Pipeline 구조체는 전체 파이프라인의 생명주기와 상태를 관리합니다. 컨텍스트를 통한 취소 기능과 성능 메트릭 수집을 지원합니다.
처리 단계: 각 단계(stage)는 독립적인 고루틴으로 실행되며, 입력 채널에서 데이터를 받아 처리한 후 출력 채널로 전달합니다. 이 예제에서는 다음과 같은 단계들을 구현했습니다:

Generator: 초기 데이터를 생성하여 파이프라인에 주입
Stage 1: 문자열을 대문자로 변환
Stage 2: 처리된 문자열에 접두사 추가
Stage 3: 결과의 유효성 검증
Collector: 최종 결과 수집


에러 처리: 각 단계에서 발생할 수 있는 에러를 추적하고 전파하는 메커니즘을 구현했습니다. 에러가 발생한 항목도 파이프라인을 완전히 통과할 수 있도록 합니다.
성능 모니터링: 각 데이터 항목의 처리 시간을 추적하여 파이프라인의 성능을 모니터링할 수 있습니다.

이 패턴은 다음과 같은 상황에서 특히 유용합니다:

데이터 변환 및 가공 작업
이미지 또는 비디오 처리
로그 처리 및 분석
ETL(Extract, Transform, Load) 작업

파이프라인 패턴의 주요 장점은 다음과 같습니다:

각 처리 단계의 독립성 보장
처리 단계 간의 결합도 감소
병렬 처리를 통한 성능 향상
에러 처리와 취소 메커니즘의 일관성
*/

package examples

import (
	"context"
	"fmt"
	"log"
	"strings"
	"time"
)

// DataItem represents a single item of data flowing through the pipeline
// 파이프라인에서 처리되는 개별 데이터 항목을 나타냅니다.
type DataItem struct {
	ID      int
	Content string
	// 데이터 처리 과정에서 발생한 에러를 추적합니다.
	Error error
	// 처리 시작 시간을 기록하여 성능 모니터링에 활용합니다.
	StartTime time.Time
}

// Pipeline represents a series of data processing stages
// 전체 파이프라인의 구성과 동작을 관리하는 구조체입니다.
type Pipeline struct {
	ctx    context.Context
	cancel context.CancelFunc
	// 파이프라인의 각 단계별 처리 시간을 추적합니다.
	metrics map[string]time.Duration
}

// NewPipeline creates a new pipeline instance with cancellation support
// 새로운 파이프라인 인스턴스를 생성하고 초기화합니다.
func NewPipeline() *Pipeline {
	ctx, cancel := context.WithCancel(context.Background())
	return &Pipeline{
		ctx:     ctx,
		cancel:  cancel,
		metrics: make(map[string]time.Duration),
	}
}

// generator creates and sends data items into the pipeline
// 파이프라인의 첫 번째 단계로, 데이터를 생성하여 전송합니다.
func (p *Pipeline) generator(data []string) <-chan DataItem {
	out := make(chan DataItem)

	go func() {
		defer close(out)

		for i, content := range data {
			// 컨텍스트 취소 여부를 확인합니다.
			select {
			case <-p.ctx.Done():
				log.Println("Generator: context cancelled")
				return
			case out <- DataItem{
				ID:        i + 1,
				Content:   content,
				StartTime: time.Now(),
			}:
				log.Printf("Generator: sent item %d", i+1)
			}
		}
	}()

	return out
}

// stage1 converts content to uppercase
// 첫 번째 처리 단계: 문자열을 대문자로 변환합니다.
func (p *Pipeline) stage1(in <-chan DataItem) <-chan DataItem {
	out := make(chan DataItem)

	go func() {
		defer close(out)

		for item := range in {
			// 이전 단계에서 에러가 발생했다면 에러를 전파합니다.
			if item.Error != nil {
				out <- item
				continue
			}

			// 처리 로직을 실행하고 결과를 다음 단계로 전달합니다.
			log.Printf("Stage 1: processing item %d", item.ID)
			item.Content = strings.ToUpper(item.Content)

			select {
			case <-p.ctx.Done():
				return
			case out <- item:
			}
		}
	}()

	return out
}

// stage2 adds prefix to content
// 두 번째 처리 단계: 문자열에 접두사를 추가합니다.
func (p *Pipeline) stage2(in <-chan DataItem) <-chan DataItem {
	out := make(chan DataItem)

	go func() {
		defer close(out)

		for item := range in {
			if item.Error != nil {
				out <- item
				continue
			}

			log.Printf("Stage 2: processing item %d", item.ID)
			item.Content = fmt.Sprintf("Processed_%s", item.Content)

			select {
			case <-p.ctx.Done():
				return
			case out <- item:
			}
		}
	}()

	return out
}

// stage3 validates the content length
// 세 번째 처리 단계: 결과의 유효성을 검증합니다.
func (p *Pipeline) stage3(in <-chan DataItem) <-chan DataItem {
	out := make(chan DataItem)

	go func() {
		defer close(out)

		for item := range in {
			if item.Error != nil {
				out <- item
				continue
			}

			log.Printf("Stage 3: validating item %d", item.ID)
			if len(item.Content) > 30 {
				item.Error = fmt.Errorf("content too long: %d characters", len(item.Content))
			}

			select {
			case <-p.ctx.Done():
				return
			case out <- item:
			}
		}
	}()

	return out
}

// collector gathers results from the pipeline
// 파이프라인의 마지막 단계로, 결과를 수집하고 처리 시간을 측정합니다.
func (p *Pipeline) collector(in <-chan DataItem) []DataItem {
	var results []DataItem

	for item := range in {
		// 전체 처리 시간을 계산합니다.
		processTime := time.Since(item.StartTime)
		log.Printf("Collector: received item %d (processing time: %v)",
			item.ID, processTime)

		results = append(results, item)
	}

	return results
}

// Execute runs the pipeline with the given input data
// 파이프라인의 전체 실행을 관리하고 결과를 반환합니다.
func (p *Pipeline) Execute(data []string) []DataItem {
	// 각 단계를 연결하여 파이프라인을 구성합니다.
	stage1Input := p.generator(data)
	stage2Input := p.stage1(stage1Input)
	stage3Input := p.stage2(stage2Input)

	// 결과를 수집하고 반환합니다.
	return p.collector(stage3Input)
}

// Stop gracefully shuts down the pipeline
// 파이프라인을 정상적으로 종료합니다.
func (p *Pipeline) Stop() {
	p.cancel()
}

// PipelineExample demonstrates the usage of the pipeline pattern
func PipelineExample() {
	// 테스트 데이터 준비
	inputData := []string{
		"hello",
		"pipeline",
		"pattern",
		"in",
		"go",
	}

	// 파이프라인 생성 및 실행
	pipeline := NewPipeline()
	log.Println("Starting pipeline processing...")

	results := pipeline.Execute(inputData)

	// 결과 출력
	log.Println("\nProcessing Results:")
	for _, result := range results {
		if result.Error != nil {
			log.Printf("Item %d: Error - %v", result.ID, result.Error)
		} else {
			log.Printf("Item %d: %s", result.ID, result.Content)
		}
	}

	pipeline.Stop()
}
