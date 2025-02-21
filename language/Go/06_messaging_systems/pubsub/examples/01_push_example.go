// 01_push_example.go
//
// 이 파일은 Google Cloud Pub/Sub의 Push Subscription 방식을 이용하여,
// HTTP 서버를 통해 푸시 메시지를 수신하는 예제입니다.
// Pub/Sub에서 전송하는 메시지는 JSON 형식으로 전달되며, 이 예제에서는
// 해당 JSON 페이로드를 파싱하여 메시지 내용과 관련 속성들을 로그로 출력합니다.
//
// 사용 예:
//   go run 01_push_example.go
//
// 주의: 이 코드는 Google Cloud Pub/Sub에서 푸시 메시지를 받을 수 있도록
//          적절한 엔드포인트(예: 외부에서 접근 가능한 도메인 또는 터널링 환경)를 구성해야 합니다.

package main

import (
	"encoding/base64"
	"encoding/json"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"time"
)

// PubSubPushMessage는 Pub/Sub 푸시 메시지 내부의 메시지 구조를 정의합니다.
type PubSubPushMessage struct {
	Data        string            `json:"data"`        // Base64로 인코딩된 메시지 데이터
	Attributes  map[string]string `json:"attributes"`  // 메시지와 함께 전송되는 속성들
	MessageID   string            `json:"messageId"`   // 메시지 ID
	PublishTime string            `json:"publishTime"` // 메시지가 게시된 시간 (RFC3339 형식)
}

// PubSubPushRequest는 Pub/Sub 푸시 메시지 전체 구조를 정의합니다.
type PubSubPushRequest struct {
	Message      PubSubPushMessage `json:"message"`      // 실제 메시지 내용
	Subscription string            `json:"subscription"` // 구독 ID
}

// pushExampleHandler는 HTTP POST 요청으로 전달된 Pub/Sub 푸시 메시지를 처리합니다.
func pushExampleHandler(w http.ResponseWriter, r *http.Request) {
	// 요청 본문을 모두 읽어들임
	bodyBytes, err := ioutil.ReadAll(r.Body)
	if err != nil {
		http.Error(w, "요청 본문 읽기 실패", http.StatusBadRequest)
		log.Printf("요청 본문 읽기 실패: %v", err)
		return
	}
	defer r.Body.Close()

	// 로그에 수신된 원본 페이로드 출력
	log.Printf("수신된 원본 메시지: %s", string(bodyBytes))

	// Pub/Sub 푸시 메시지 구조체에 JSON 디코딩
	var pushReq PubSubPushRequest
	if err := json.Unmarshal(bodyBytes, &pushReq); err != nil {
		http.Error(w, "JSON 파싱 실패", http.StatusBadRequest)
		log.Printf("JSON 파싱 실패: %v", err)
		return
	}

	// 메시지 데이터(Base64)를 디코딩
	decodedData, err := base64.StdEncoding.DecodeString(pushReq.Message.Data)
	if err != nil {
		http.Error(w, "메시지 데이터 디코딩 실패", http.StatusBadRequest)
		log.Printf("메시지 데이터 디코딩 실패: %v", err)
		return
	}

	// 디코딩된 메시지와 관련 속성들을 로그로 출력
	log.Printf("푸시 메시지 수신 - ID: %s, PublishedAt: %s", pushReq.Message.MessageID, pushReq.Message.PublishTime)
	log.Printf("푸시 메시지 내용: %s", string(decodedData))
	if len(pushReq.Message.Attributes) > 0 {
		log.Printf("푸시 메시지 속성: %v", pushReq.Message.Attributes)
	} else {
		log.Println("푸시 메시지 속성이 없습니다.")
	}

	// HTTP 응답으로 성공 상태 전송
	w.WriteHeader(http.StatusOK)
	w.Write([]byte("메시지 수신 성공"))
}

// startPushServer는 지정된 포트에서 HTTP 서버를 시작하여, Pub/Sub 푸시 메시지를 수신합니다.
func startPushServer(port string) {
	// "/pubsub" 경로에 대해 pushExampleHandler를 등록합니다.
	http.HandleFunc("/pubsub", pushExampleHandler)

	// 서버 시작 로그 출력
	log.Printf("Push Subscription 서버 시작: 포트 %s에서 수신 대기 중...", port)

	// 지정된 포트에서 HTTP 서버 시작 (예: ":8080")
	if err := http.ListenAndServe(":"+port, nil); err != nil {
		log.Fatalf("HTTP 서버 시작 실패: %v", err)
	}
}

func Push_example() {
	// 서버가 수신할 포트 설정 (환경 변수에서 가져오거나 기본값 사용)
	serverPort := os.Getenv("PUSH_SERVER_PORT")
	if serverPort == "" {
		serverPort = "8080"
	}

	// 서버 시작
	startPushServer(serverPort)

	// 추가적으로, 서버가 종료되지 않도록 무한 대기 (실제 환경에서는 필요 없음)
	for {
		time.Sleep(1 * time.Hour)
	}
}
