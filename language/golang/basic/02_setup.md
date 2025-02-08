# Go 언어 개발 환경 설정 (Environment Setup)

## 1. Go 설치

### 1.1 공식 배포판 설치

**Windows:**
1. Go 다운로드 페이지에서 Windows MSI 인스톨러 다운로드
2. 인스톨러 실행 및 기본 설정으로 설치
3. 설치 확인:
```bash
go version
```

**macOS**
1. Homebrew를 통한 설치:
```bash
brew install go
```

2. 또는 공식 패키지 다운로드 후 설치
3. 설치 확인:
```bash
go version
```

**Linux (Ubuntu/Debian)**
```bash
# apt를 통한 설치
sudo apt update
sudo apt install golang

# 설치 확인
go version
```

### 1.2 버전 관리 도구 설치 (선택사항)

**goenv를 사용하여 여러 Go 버전을 관리할 수 있음**
```bash
# macOS (Homebrew)
brew install goenv

# Linux
git clone https://github.com/syndbg/goenv.git ~/.goenv
```

## 2. 주요 환경 변수 설정

### 2.1 주요 환경 변수
- **GOROOT:** Go 설치 위치
- **GOPATH:** 작업 공간 위치
- **GOBIN:** Go 바이너리 설치 위치

### 2.2 환경 변수 설정 방법

**Windows**

시스템 환경 변수에 추가
```plaintext
GOPATH=%USERPROFILE%\go
PATH=%PATH%;%GOROOT%\bin;%GOPATH%\bin
```

**Linux**
```bash
# ~/.bashrc 또는 ~/.zshrc에 추가
export GOPATH=$HOME/go
export PATH=$PATH:$GOROOT/bin:$GOPATH/bin
```

### 2.3 환경 확인
```bash
# 모든 Go 환경 변수 확인
go env

# 특정 변수 확인
go env GOPATH
```

## 3. Go Modules 설정

Go 1.11부터 도입된 **Go Modules**는 의존성 관리를 위한 공식 방법입니다.

### 3.1 새 프로젝트 시작
```bash
# 새 디렉토리 생성 및 이동
mkdir myproject
cd myproject

# 모듈 초기화
go mod init github.com/username/myproject
# go.mod 파일이 생성됨
```

### 3.2 기존 프로젝트에 모듈 추가
```bash
# 현재 디렉토리에서 모듈 초기화
go mod init

# 의존성 정리
go tidy
```

## 4. IDE/에디터 설정

### 4.1 VSCode

1. VSCode 설치
2. Go 확장 설치:
  - VSCode 확장 마켓플레이스에서 "Go"검색
  - 또는 커맨드라인에서:
    ```bash
    code --install-extension golang.go
    ```
3. 필요한 Go 도구 자동 설치:
  - `Ctrl + Shift + P`(또는 `Cmd + Shift + P`)
  - "Go: Install/Update Tools" 선택
  - 모든 도구 선택 후 설치

**주요 기능**
- 자동 완성
- 코드 네비게이션
- 실시간 오류 검사
- 자동 포맷팅(gofmt)
- 디버깅 지원

### 4.2 GoLand

**JetBrains의 Go 전용 IDE:**
1. GoLand 다운로드
2. 설치 및 실행
3. 새 프로젝트 생성 시 Go Modules 사용 선택

**주요 기능:**
- 강력한 코드 완성
- 리팩토링 도구
- 통합 디버거
- 데이터베이스 도구
- 버전 관리 통합

### 4.3 Vim/Neovim 설정

**vim-go 플러그인 설치:**
```vim
" vim-plug 사용 시
Plug 'fatih/vim-go'

" 설치 후 실행
:GoInstallBinaries
```

## 5. 기본 개발 도구

### 5.1 필수 Go 도구
```bash
# 코드 포맷팅
go fmt ./...

# 코드 검사
go vet ./...

# 테스트 실행
go test ./...

# 의존성 관리
go mod tidy
```

### 5.2 추가 개발 도구 설치
```bash
# golangci-lint 설치
go install github.com/golangci/golangci-lint/cmd/golangci-lint@latest

# 문서화 도구
go install golang.org/x/tools/cmd/godoc@latest

# 의존성 그래프 시각화
go install golang.org/x/tools/cmd/godepgraph@latest
```

## 6. 프로젝트 구조 예시

**기본적인 Go 프로젝트 구조**
```plaintext
myproject/
  ├── cmd/
  │   └── myapp/
  │       └── main.go
  ├── internal/
  │   └── pkg/
  ├── pkg/
  ├── go.mod
  ├── go.sum
  └── README.md
```

## 7. Key Points
- Go 1.11 이상에서는 **Go Modules**를 사용하여 의존성 관리
- **GOPATH**는 더 이상 필수가 아님(**Go Modules** 사용 시)
- VSCode 또는 GoLand가 가장 많이 사용되는 IDE
- `go fmt`, `go vet`등의 도구를 적극 활용
- 프로젝트는 모듈 기반으로 구성

## 8. 문제 해결

### 8.1 일반적인 문제

**1. GOPATH 관련 오류**
```bash
# GOPATH 확인
go env GOPATH

# 필요한 경우 설정
export GOPATH=$HOME/go
```

**2. 모듈 관련 오류**
```bash
# 모듈 캐시 정리
go clean -modcache

# 의존성 다시 다운로드
go mod download
```

### 8.2 IDE 문제 해결

1. VSCode GO 확장 도구 재설치
2. GOROOT, GOPATH 환경 변수 확인
3. **Go Modules** 활성화 확인(`GO111MODULE` 환경변수)