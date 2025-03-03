package main

import (
	"context"
	"fmt"
	"math/rand"
	"time"
)

type Log struct {
	Timestamp time.Time
	Level     string
	Message   string
}

func processLogs(ctx context.Context, logsChan chan Log) (int, []Log) {
	var errorCount int   // ERROR 로그 개수
	var recentLogs []Log // 최근 5초 로그 저장
	done := ctx.Done()   // 컨텍스트 종료 신호

	// 프로듀서: 로그 생성 및 채널 전송
	go func() {
		ticker := time.NewTicker(1 * time.Second) // 1초마다 로그 생성
		defer ticker.Stop()
		defer close(logsChan) // 작업 끝나면 채널 닫기

		levels := []string{"INFO", "ERROR", "WARN"}
		messages := []string{
			"User logged in",
			"Database connection failed",
			"Request processed",
			"Timeout occurred",
		}

		for {
			select {
			case <-done:
				return // 타임아웃 시 종료
			case <-ticker.C:
				// 랜덤 로그 생성
				log := Log{
					Timestamp: time.Now(),
					Level:     levels[rand.Intn(len(levels))],
					Message:   messages[rand.Intn(len(messages))],
				}
				logsChan <- log // 채널로 전송
			}
		}
	}()

	// 컨슈머: 로그 처리
	for {
		select {
		case <-done:
			// 타임아웃 시 현재까지의 결과 반환
			return errorCount, recentLogs
		case log, ok := <-logsChan:
			if !ok {
				// 채널이 닫히면 종료
				return errorCount, recentLogs
			}
			// ERROR 로그 카운트
			if log.Level == "ERROR" {
				errorCount++
			}
			// 최근 5초 로그 유지
			recentLogs = append(recentLogs, log)
			// 5초 지난 로그 제거
			now := time.Now()
			for i := 0; i < len(recentLogs); i++ {
				if now.Sub(recentLogs[i].Timestamp) > 5*time.Second {
					recentLogs = recentLogs[i+1:]
					break
				}
			}
		}
	}
}

func main() {
	rand.Seed(time.Now().UnixNano()) // 랜덤 시드 설정
	ctx, cancel := context.WithTimeout(context.Background(), 15*time.Second)
	defer cancel()

	logsChan := make(chan Log, 5)
	errorCount, recentLogs := processLogs(ctx, logsChan)

	fmt.Printf("Total ERROR logs: %d\n", errorCount)
	fmt.Println("Recent logs (last 5 seconds):")
	for _, log := range recentLogs {
		fmt.Printf("%s %s %q\n", log.Timestamp.Format("2006-01-02 15:04:05"), log.Level, log.Message)
	}
}
