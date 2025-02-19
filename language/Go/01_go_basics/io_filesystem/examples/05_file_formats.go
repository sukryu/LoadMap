/*
이 예제는 다양한 파일 형식(CSV, JSON, XML)의 읽기/쓰기 작업을 수행하는 방법을 보여줍니다.
주요 기능:
1. CSV 파일 처리:
   - 데이터를 CSV 형식으로 직렬화하여 파일에 저장하고, 다시 읽어 파싱하는 기능.
2. JSON 파일 처리:
   - 구조체 데이터를 JSON 형식으로 인코딩하여 파일에 저장하고, 파일에서 디코딩하는 기능.
3. XML 파일 처리:
   - XML 형식의 데이터를 생성하고, 파일에 기록한 후 다시 읽어 구조체로 파싱하는 기능.
각 기능은 실제 업무에서 사용되는 데이터 형식 처리를 위한 모범 사례와 함께, 에러 처리 및 리소스 관리를 포함합니다.
*/

package examples

import (
	"encoding/csv"
	"encoding/json"
	"encoding/xml"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

// ----------------------------
// CSV 파일 처리
// ----------------------------

// CSVRecord는 CSV 파일에서 다룰 데이터를 나타내는 구조체입니다.
type CSVRecord struct {
	ID    string
	Name  string
	Email string
}

// WriteCSVFile는 records 데이터를 CSV 형식으로 파일에 저장합니다.
func WriteCSVFile(filePath string, records []CSVRecord) error {
	// 파일 생성 (없으면 새로 생성)
	file, err := os.Create(filePath)
	if err != nil {
		return fmt.Errorf("CSV 파일 생성 실패: %w", err)
	}
	defer file.Close()

	// csv.Writer 생성
	writer := csv.NewWriter(file)
	defer writer.Flush()

	// 헤더 작성 (옵션)
	if err := writer.Write([]string{"ID", "Name", "Email"}); err != nil {
		return fmt.Errorf("헤더 쓰기 실패: %w", err)
	}

	// 각 레코드를 문자열 슬라이스로 변환하여 작성
	for _, rec := range records {
		line := []string{rec.ID, rec.Name, rec.Email}
		if err := writer.Write(line); err != nil {
			return fmt.Errorf("레코드 쓰기 실패: %w", err)
		}
	}
	fmt.Printf("CSV 파일 저장 완료: %s\n", filePath)
	return nil
}

// ReadCSVFile는 CSV 파일을 읽어 CSVRecord 슬라이스로 반환합니다.
func ReadCSVFile(filePath string) ([]CSVRecord, error) {
	// 파일 열기
	file, err := os.Open(filePath)
	if err != nil {
		return nil, fmt.Errorf("CSV 파일 열기 실패: %w", err)
	}
	defer file.Close()

	reader := csv.NewReader(file)
	var records []CSVRecord

	// 헤더 건너뛰기
	if _, err := reader.Read(); err != nil {
		return nil, fmt.Errorf("헤더 읽기 실패: %w", err)
	}

	// 각 라인을 읽어 CSVRecord로 변환
	for {
		line, err := reader.Read()
		if err == io.EOF {
			break
		}
		if err != nil {
			return nil, fmt.Errorf("CSV 파일 읽기 실패: %w", err)
		}
		if len(line) < 3 {
			continue // 데이터 형식이 올바르지 않으면 건너뜁니다.
		}
		rec := CSVRecord{
			ID:    line[0],
			Name:  line[1],
			Email: line[2],
		}
		records = append(records, rec)
	}
	return records, nil
}

// ----------------------------
// JSON 파일 처리
// ----------------------------

// Person는 JSON 파일에서 다룰 데이터를 나타내는 구조체입니다.
type Person struct {
	ID    int    `json:"id"`
	Name  string `json:"name"`
	Age   int    `json:"age"`
	Email string `json:"email"`
}

// WriteJSONFile는 데이터를 JSON 형식으로 인코딩하여 파일에 저장합니다.
func WriteJSONFile(filePath string, data interface{}) error {
	// 파일 생성
	file, err := os.Create(filePath)
	if err != nil {
		return fmt.Errorf("JSON 파일 생성 실패: %w", err)
	}
	defer file.Close()

	encoder := json.NewEncoder(file)
	encoder.SetIndent("", "  ") // 보기 좋게 들여쓰기 설정

	if err := encoder.Encode(data); err != nil {
		return fmt.Errorf("JSON 인코딩 실패: %w", err)
	}
	fmt.Printf("JSON 파일 저장 완료: %s\n", filePath)
	return nil
}

// ReadJSONFile는 JSON 파일을 읽어 주어진 인터페이스로 디코딩합니다.
func ReadJSONFile(filePath string, v interface{}) error {
	// 파일 열기
	file, err := os.Open(filePath)
	if err != nil {
		return fmt.Errorf("JSON 파일 열기 실패: %w", err)
	}
	defer file.Close()

	decoder := json.NewDecoder(file)
	if err := decoder.Decode(v); err != nil {
		return fmt.Errorf("JSON 디코딩 실패: %w", err)
	}
	return nil
}

// ----------------------------
// XML 파일 처리
// ----------------------------

// XMLNote는 XML 데이터 구조를 나타내는 구조체입니다.
type XMLNote struct {
	XMLName xml.Name `xml:"note"`
	To      string   `xml:"to"`
	From    string   `xml:"from"`
	Heading string   `xml:"heading"`
	Body    string   `xml:"body"`
}

// WriteXMLFile는 데이터를 XML 형식으로 인코딩하여 파일에 저장합니다.
func WriteXMLFile(filePath string, data interface{}) error {
	// 파일 생성
	file, err := os.Create(filePath)
	if err != nil {
		return fmt.Errorf("XML 파일 생성 실패: %w", err)
	}
	defer file.Close()

	// XML 인코더 생성
	encoder := xml.NewEncoder(file)
	encoder.Indent("", "  ") // 들여쓰기 설정

	// XML 헤더 작성
	if _, err := file.WriteString(xml.Header); err != nil {
		return fmt.Errorf("XML 헤더 쓰기 실패: %w", err)
	}

	if err := encoder.Encode(data); err != nil {
		return fmt.Errorf("XML 인코딩 실패: %w", err)
	}
	fmt.Printf("XML 파일 저장 완료: %s\n", filePath)
	return nil
}

// ReadXMLFile는 XML 파일을 읽어 주어진 인터페이스로 디코딩합니다.
func ReadXMLFile(filePath string, v interface{}) error {
	// 파일 열기
	file, err := os.Open(filePath)
	if err != nil {
		return fmt.Errorf("XML 파일 열기 실패: %w", err)
	}
	defer file.Close()

	decoder := xml.NewDecoder(file)
	if err := decoder.Decode(v); err != nil {
		return fmt.Errorf("XML 디코딩 실패: %w", err)
	}
	return nil
}

// ----------------------------
// FileFormatsDemo: 전체 파일 형식 데모 실행 함수
// ----------------------------

// FileFormatsDemo는 CSV, JSON, XML 파일 형식 처리 기능을 통합적으로 데모합니다.
func FileFormatsDemo() {
	// 데모를 위한 기본 디렉토리 생성
	baseDir := "./data/file_formats"
	os.MkdirAll(baseDir, 0755)

	// --- CSV 데모 ---
	csvFilePath := filepath.Join(baseDir, "demo.csv")
	csvRecords := []CSVRecord{
		{"1", "Alice", "alice@example.com"},
		{"2", "Bob", "bob@example.com"},
		{"3", "Charlie", "charlie@example.com"},
	}
	fmt.Println("==== CSV 파일 처리 데모 시작 ====")
	if err := WriteCSVFile(csvFilePath, csvRecords); err != nil {
		fmt.Printf("CSV 파일 쓰기 오류: %v\n", err)
	} else {
		records, err := ReadCSVFile(csvFilePath)
		if err != nil {
			fmt.Printf("CSV 파일 읽기 오류: %v\n", err)
		} else {
			fmt.Println("CSV 파일 읽기 결과:")
			for _, r := range records {
				fmt.Printf("ID: %s, Name: %s, Email: %s\n", r.ID, r.Name, r.Email)
			}
		}
	}
	fmt.Println("==== CSV 파일 처리 데모 종료 ====")

	// --- JSON 데모 ---
	jsonFilePath := filepath.Join(baseDir, "demo.json")
	persons := []Person{
		{ID: 1, Name: "David", Age: 28, Email: "david@example.com"},
		{ID: 2, Name: "Eva", Age: 32, Email: "eva@example.com"},
	}
	fmt.Println("==== JSON 파일 처리 데모 시작 ====")
	if err := WriteJSONFile(jsonFilePath, persons); err != nil {
		fmt.Printf("JSON 파일 쓰기 오류: %v\n", err)
	} else {
		var readPersons []Person
		if err := ReadJSONFile(jsonFilePath, &readPersons); err != nil {
			fmt.Printf("JSON 파일 읽기 오류: %v\n", err)
		} else {
			fmt.Println("JSON 파일 읽기 결과:")
			for _, p := range readPersons {
				fmt.Printf("ID: %d, Name: %s, Age: %d, Email: %s\n", p.ID, p.Name, p.Age, p.Email)
			}
		}
	}
	fmt.Println("==== JSON 파일 처리 데모 종료 ====")

	// --- XML 데모 ---
	xmlFilePath := filepath.Join(baseDir, "demo.xml")
	note := XMLNote{
		To:      "Tove",
		From:    "Jani",
		Heading: "Reminder",
		Body:    "Don't forget me this weekend!",
	}
	fmt.Println("==== XML 파일 처리 데모 시작 ====")
	if err := WriteXMLFile(xmlFilePath, note); err != nil {
		fmt.Printf("XML 파일 쓰기 오류: %v\n", err)
	} else {
		var readNote XMLNote
		if err := ReadXMLFile(xmlFilePath, &readNote); err != nil {
			fmt.Printf("XML 파일 읽기 오류: %v\n", err)
		} else {
			fmt.Println("XML 파일 읽기 결과:")
			fmt.Printf("To: %s, From: %s, Heading: %s, Body: %s\n",
				readNote.To, readNote.From, readNote.Heading, readNote.Body)
		}
	}
	fmt.Println("==== XML 파일 처리 데모 종료 ====")
}
