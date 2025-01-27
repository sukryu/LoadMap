# 09. Build Systems and Continuous Integration

## 1. 빌드 시스템의 개요

### 빌드 시스템이란?
빌드 시스템은 소스 코드로부터 실행 파일, 라이브러리 등을 생성하는 과정을 자동화하는 도구와 프로세스를 말합니다. 이를 통해 복잡한 프로젝트에서도 일관성 있는 빌드와 관리가 가능합니다.

### 빌드 시스템의 주요 기능
1. **컴파일**: 소스 파일을 객체 파일로 변환.
2. **링킹**: 객체 파일을 실행 가능한 바이너리로 결합.
3. **종속성 관리**: 파일 간의 의존성을 파악하여 필요한 경우에만 빌드.
4. **자동화**: 반복적인 작업을 자동으로 처리.

---

## 2. Makefile 심화

### Makefile이란?
Makefile은 GNU Make 도구를 사용하여 빌드를 자동화하기 위한 설정 파일입니다. 빌드 규칙과 파일 간의 종속성을 정의합니다.

### Makefile의 기본 구조
#### 예제: 간단한 Makefile
```makefile
# 변수 정의
CC = gcc
CFLAGS = -Wall -g

# 빌드 대상 및 규칙
target: main.o utils.o
	$(CC) $(CFLAGS) -o target main.o utils.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o target
```

### 주요 요소
1. **변수 정의**: `CC`, `CFLAGS` 등 재사용 가능한 값을 정의.
2. **규칙**: 빌드 대상과 생성 방법을 정의.
3. **종속성**: 각 파일의 의존 관계를 명시.
4. **명령**: 규칙에 따라 실행되는 명령어.

### Makefile 개선
#### 의존성 자동 생성
```makefile
# 의존성 파일 자동 생성
deps = $(patsubst %.c, %.d, $(wildcard *.c))
-include $(deps)

%.d: %.c
	$(CC) -MM $< > $@
```

---

## 3. CMake를 활용한 빌드 자동화

### CMake란?
CMake는 플랫폼과 컴파일러에 독립적인 빌드 시스템 생성 도구입니다. 프로젝트를 구조화하고 관리하는 데 유용합니다.

### CMakeLists.txt 기본 구조
#### 예제: 간단한 CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_C_STANDARD 11)

# 소스 파일 추가
set(SOURCES main.c utils.c)

# 실행 파일 생성
add_executable(MyProject ${SOURCES})
```

### CMake 명령어
1. **`cmake`**: CMake 구성 파일 처리.
   ```bash
   cmake -S . -B build
   ```
2. **`cmake --build`**: 빌드 실행.
   ```bash
   cmake --build build
   ```

### CMake 고급 기능
1. **라이브러리 추가**:
   ```cmake
   add_library(my_lib STATIC utils.c)
   target_link_libraries(MyProject PRIVATE my_lib)
   ```
2. **빌드 타입 설정**:
   ```bash
   cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
   ```

---

## 4. CI/CD의 개념과 역할

### CI/CD란?
- **CI (Continuous Integration)**: 코드 변경 시 자동으로 빌드, 테스트, 통합하는 프로세스.
- **CD (Continuous Deployment)**: CI를 통해 검증된 코드를 자동으로 배포.

### CI/CD의 주요 장점
1. **자동화**: 반복 작업을 자동화하여 시간을 절약.
2. **품질 보장**: 코드 변경 시마다 테스트를 통해 안정성 확인.
3. **빠른 피드백**: 오류를 빠르게 식별하고 해결.

---

## 5. GitHub Actions를 활용한 CI 설정

### GitHub Actions란?
GitHub Actions는 GitHub 저장소에서 워크플로우(빌드, 테스트 등)를 자동화하는 도구입니다.

### 기본 워크플로우 예제
#### 파일: `.github/workflows/build.yml`
```yaml
name: C Build and Test

on:
  push:
    branches:
      - main

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
    - name: Checkout repository
      uses: actions/checkout@v3

    - name: Set up GCC
      run: sudo apt-get install -y build-essential

    - name: Build
      run: |
        gcc -o program main.c utils.c

    - name: Test
      run: |
        ./program
```

---

## 6. Jenkins를 활용한 CI 설정

### Jenkins란?
Jenkins는 오픈소스 CI/CD 서버로, 소프트웨어 빌드, 테스트, 배포를 자동화하는 데 사용됩니다.

### Jenkins 파이프라인 설정
#### Jenkinsfile 예제
```groovy
pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Build') {
            steps {
                sh 'gcc -o program main.c utils.c'
            }
        }

        stage('Test') {
            steps {
                sh './program'
            }
        }
    }
}
```

---

## 7. 실습: 멀티플랫폼 빌드 시스템 구축

### 요구 사항
- Windows와 Linux에서 동일한 소스 코드를 빌드.
- CMake와 GitHub Actions를 사용하여 빌드 자동화.

#### CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.10)
project(MultiPlatform)

set(CMAKE_C_STANDARD 11)

if(WIN32)
    set(SOURCES main.c windows_specific.c)
elseif(UNIX)
    set(SOURCES main.c linux_specific.c)
endif()

add_executable(MultiPlatform ${SOURCES})
```

#### GitHub Actions 워크플로우
```yaml
name: Multi-Platform Build

on:
  push:
    branches:
      - main

jobs:
  build-linux:
    runs-on: ubuntu-latest

    steps:
    - name: Checkout repository
      uses: actions/checkout@v3

    - name: Build on Linux
      run: |
        cmake -S . -B build
        cmake --build build

  build-windows:
    runs-on: windows-latest

    steps:
    - name: Checkout repository
      uses: actions/checkout@v3

    - name: Build on Windows
      run: |
        cmake -S . -B build
        cmake --build build
```

---

빌드 시스템과 CI/CD는 소프트웨어 개발의 효율성을 극대화하는 중요한 도구입니다. 위에서 설명한 Makefile, CMake, GitHub Actions, Jenkins 등의 도구를 활용하여 빌드와 배포를 자동화하고 생산성을 높이세요.

