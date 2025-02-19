/*
이 예제는 파일 압축과 해제 작업을 다룹니다.
주요 기능:
1. gzip 압축 및 해제:
   - 단일 파일을 gzip 형식으로 압축하고, 압축 파일을 해제하는 기능을 구현합니다.
   - 압축 레벨(gzip.BestSpeed, gzip.BestCompression, gzip.DefaultCompression 등)을 조정할 수 있습니다.
2. zip 아카이브 생성 및 추출:
   - 여러 파일을 포함하는 zip 아카이브를 생성하고, 해당 아카이브의 파일들을 추출하는 기능을 제공합니다.
   - 파일의 상대 경로를 보존하여 아카이브 내부의 디렉토리 구조를 유지합니다.

각 기능은 실제 업무에서 자주 발생하는 압축 및 아카이브 작업에 대한 모범 사례를 제공하며, 자세한 주석을 통해 동작 원리와 사용 방법을 설명합니다.
*/

package examples

import (
	"archive/zip"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

// ----------------------------
// gzip 압축 및 해제
// ----------------------------

// GzipCompressFile은 srcPath의 파일을 gzip 압축하여 dstPath로 저장합니다.
// compressionLevel은 gzip 압축 레벨을 지정합니다.
func GzipCompressFile(srcPath, dstPath string, compressionLevel int) error {
	// 원본 파일 열기
	srcFile, err := os.Open(srcPath)
	if err != nil {
		return fmt.Errorf("원본 파일 열기 실패: %w", err)
	}
	defer srcFile.Close()

	// 대상 파일 생성
	dstFile, err := os.Create(dstPath)
	if err != nil {
		return fmt.Errorf("압축 파일 생성 실패: %w", err)
	}
	defer dstFile.Close()

	// gzip.Writer 생성: 압축 레벨 설정
	gzipWriter, err := gzip.NewWriterLevel(dstFile, compressionLevel)
	if err != nil {
		return fmt.Errorf("gzip.Writer 생성 실패: %w", err)
	}
	defer gzipWriter.Close()

	// 파일 데이터를 읽어 gzip.Writer로 복사 (압축 수행)
	_, err = io.Copy(gzipWriter, srcFile)
	if err != nil {
		return fmt.Errorf("파일 압축 중 오류 발생: %w", err)
	}

	fmt.Printf("파일 %s가 %s로 압축되었습니다.\n", srcPath, dstPath)
	return nil
}

// GzipDecompressFile은 gzip 압축된 파일을 해제하여 dstPath로 저장합니다.
func GzipDecompressFile(srcPath, dstPath string) error {
	// 압축 파일 열기
	srcFile, err := os.Open(srcPath)
	if err != nil {
		return fmt.Errorf("압축 파일 열기 실패: %w", err)
	}
	defer srcFile.Close()

	// gzip.Reader 생성
	gzipReader, err := gzip.NewReader(srcFile)
	if err != nil {
		return fmt.Errorf("gzip.Reader 생성 실패: %w", err)
	}
	defer gzipReader.Close()

	// 대상 파일 생성
	dstFile, err := os.Create(dstPath)
	if err != nil {
		return fmt.Errorf("해제 파일 생성 실패: %w", err)
	}
	defer dstFile.Close()

	// gzip 데이터를 읽어 대상 파일에 복사 (해제 수행)
	_, err = io.Copy(dstFile, gzipReader)
	if err != nil {
		return fmt.Errorf("파일 해제 중 오류 발생: %w", err)
	}

	fmt.Printf("압축 파일 %s가 %s로 해제되었습니다.\n", srcPath, dstPath)
	return nil
}

// DemonstrateGzipCompression은 gzip 압축 및 해제 기능을 데모합니다.
func DemonstrateGzipCompression() {
	fmt.Println("==== gzip 압축/해제 데모 시작 ====")

	// 데모를 위한 파일 경로 설정 및 data 디렉토리 생성
	os.MkdirAll("./data", 0755)
	srcPath := "./data/compression_src.txt"
	gzipPath := "./data/compression_src.txt.gz"
	decompressedPath := "./data/compression_decompressed.txt"

	// 원본 파일 생성: 간단한 텍스트 데이터 작성
	content := "이 파일은 gzip 압축 예제용 데이터입니다.\n여러 줄의 텍스트가 포함되어 있습니다.\n"
	err := os.WriteFile(srcPath, []byte(content), 0644)
	if err != nil {
		fmt.Printf("원본 파일 생성 실패: %v\n", err)
		return
	}

	// gzip 압축 수행 (gzip.DefaultCompression 사용)
	err = GzipCompressFile(srcPath, gzipPath, gzip.DefaultCompression)
	if err != nil {
		fmt.Printf("gzip 압축 실패: %v\n", err)
		return
	}

	// gzip 해제 수행
	err = GzipDecompressFile(gzipPath, decompressedPath)
	if err != nil {
		fmt.Printf("gzip 해제 실패: %v\n", err)
		return
	}

	// 해제된 파일 내용 확인
	data, err := os.ReadFile(decompressedPath)
	if err != nil {
		fmt.Printf("해제 파일 읽기 실패: %v\n", err)
		return
	}
	fmt.Println("해제된 파일 내용:")
	fmt.Println(string(data))

	fmt.Println("==== gzip 압축/해제 데모 종료 ====")
}

// ----------------------------
// zip 아카이브 생성 및 추출
// ----------------------------

// CreateZipArchive는 files에 포함된 파일들을 zip 아카이브로 생성하여 archivePath에 저장합니다.
func CreateZipArchive(files []string, archivePath string) error {
	// zip 파일 생성
	zipFile, err := os.Create(archivePath)
	if err != nil {
		return fmt.Errorf("zip 파일 생성 실패: %w", err)
	}
	defer zipFile.Close()

	// zip.Writer 생성
	zipWriter := zip.NewWriter(zipFile)
	defer zipWriter.Close()

	// 파일 목록 순회하며 아카이브에 추가
	for _, filePath := range files {
		// 파일 내용 읽기
		data, err := os.ReadFile(filePath)
		if err != nil {
			return fmt.Errorf("파일 읽기 실패 (%s): %w", filePath, err)
		}

		// 파일의 상대 경로 계산 (아카이브 내부 경로로 사용)
		relPath, err := filepath.Rel(filepath.Dir(archivePath), filePath)
		if err != nil {
			relPath = filepath.Base(filePath)
		}

		// zip 파일 내 새 항목 생성
		f, err := zipWriter.Create(relPath)
		if err != nil {
			return fmt.Errorf("zip 항목 생성 실패 (%s): %w", filePath, err)
		}

		// 항목에 데이터 쓰기
		_, err = f.Write(data)
		if err != nil {
			return fmt.Errorf("zip 항목에 데이터 쓰기 실패 (%s): %w", filePath, err)
		}
		fmt.Printf("파일 %s를 아카이브에 추가함.\n", filePath)
	}

	fmt.Printf("zip 아카이브 생성 완료: %s\n", archivePath)
	return nil
}

// ExtractZipArchive는 archivePath의 zip 아카이브를 destDir 디렉토리에 추출합니다.
func ExtractZipArchive(archivePath, destDir string) error {
	// zip 아카이브 열기
	r, err := zip.OpenReader(archivePath)
	if err != nil {
		return fmt.Errorf("zip 아카이브 열기 실패: %w", err)
	}
	defer r.Close()

	// 대상 디렉토리 생성 (없으면)
	os.MkdirAll(destDir, 0755)

	// 각 항목 추출
	for _, f := range r.File {
		filePath := filepath.Join(destDir, f.Name)
		// 디렉토리인 경우 생성 후 건너뜀
		if f.FileInfo().IsDir() {
			os.MkdirAll(filePath, f.Mode())
			continue
		}

		// 상위 디렉토리 생성
		os.MkdirAll(filepath.Dir(filePath), 0755)

		// 항목 열기
		inFile, err := f.Open()
		if err != nil {
			return fmt.Errorf("zip 항목 열기 실패 (%s): %w", f.Name, err)
		}

		// 대상 파일 생성
		outFile, err := os.OpenFile(filePath, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, f.Mode())
		if err != nil {
			inFile.Close()
			return fmt.Errorf("출력 파일 생성 실패 (%s): %w", filePath, err)
		}

		// 데이터 복사
		_, err = io.Copy(outFile, inFile)
		inFile.Close()
		outFile.Close()
		if err != nil {
			return fmt.Errorf("파일 추출 실패 (%s): %w", filePath, err)
		}
		fmt.Printf("추출된 파일: %s\n", filePath)
	}

	fmt.Printf("zip 아카이브 추출 완료: %s -> %s\n", archivePath, destDir)
	return nil
}

// DemonstrateZipArchiveCreation은 zip 아카이브 생성 및 추출 기능을 데모합니다.
func DemonstrateZipArchiveCreation() {
	fmt.Println("\n==== zip 아카이브 생성/추출 데모 시작 ====")

	// 데모를 위한 디렉토리 및 파일 생성
	baseDir := "./data/zip_demo"
	os.MkdirAll(baseDir, 0755)
	fileContents := []struct {
		Name    string
		Content string
	}{
		{"file1.txt", "첫 번째 파일 내용\n"},
		{"file2.txt", "두 번째 파일 내용\n"},
		{"notes/file3.txt", "세 번째 파일은 하위 디렉토리에 위치합니다.\n"},
	}

	var files []string
	for _, fc := range fileContents {
		filePath := filepath.Join(baseDir, fc.Name)
		// 상위 디렉토리 생성
		os.MkdirAll(filepath.Dir(filePath), 0755)
		err := os.WriteFile(filePath, []byte(fc.Content), 0644)
		if err != nil {
			fmt.Printf("파일 생성 실패 (%s): %v\n", filePath, err)
			return
		}
		files = append(files, filePath)
	}

	// zip 아카이브 생성
	archivePath := "./data/zip_demo_archive.zip"
	err := CreateZipArchive(files, archivePath)
	if err != nil {
		fmt.Printf("zip 아카이브 생성 실패: %v\n", err)
		return
	}

	// zip 아카이브 추출
	extractDir := "./data/zip_extracted"
	err = ExtractZipArchive(archivePath, extractDir)
	if err != nil {
		fmt.Printf("zip 아카이브 추출 실패: %v\n", err)
		return
	}

	fmt.Println("==== zip 아카이브 생성/추출 데모 종료 ====")
}

// ----------------------------
// Compression Demo: 전체 압축 관련 기능 데모
// ----------------------------

// CompressionDemo는 gzip 압축/해제와 zip 아카이브 기능을 통합적으로 데모합니다.
func CompressionDemo() {
	fmt.Println("==== 파일 압축/아카이브 데모 시작 ====")

	// 1. gzip 압축 및 해제 데모
	DemonstrateGzipCompression()

	// 2. zip 아카이브 생성 및 추출 데모
	DemonstrateZipArchiveCreation()

	fmt.Println("==== 파일 압축/아카이브 데모 종료 ====")
}
