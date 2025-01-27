# zlib 라이브러리 사용 가이드

zlib는 데이터 압축과 해제를 지원하는 C 기반의 오픈 소스 라이브러리로, GZIP 포맷을 포함한 다양한 압축 형식을 제공합니다. 네트워크 데이터 압축, 파일 압축 등 효율적인 데이터 전송과 저장에 유용합니다.

---

## 1. 주요 특징

1. **경량성**: 빠르고 메모리 사용량이 적음.
2. **압축 및 해제 지원**: 실시간 데이터 스트림 및 파일 압축/해제 가능.
3. **호환성**: 다양한 운영 체제와 프로그래밍 언어에서 사용 가능.
4. **GZIP 지원**: GZIP 형식으로 데이터를 처리.

---

## 2. 설치

### 2.1 설치 방법
**Ubuntu/Linux:**
```bash
sudo apt-get update
sudo apt-get install zlib1g-dev
```

**macOS:**
```bash
brew install zlib
```

**Windows:**
- zlib 공식 웹사이트(https://zlib.net/)에서 소스 코드를 다운로드하여 빌드.

---

## 3. 주요 구성 요소

zlib는 데이터 압축과 해제를 수행하기 위해 다음과 같은 주요 함수와 구조체를 제공합니다.

### 3.1 주요 구조체

#### `z_stream`
- 데이터 압축 및 해제를 관리하는 핵심 구조체.
- 주요 필드:
  - `next_in`: 입력 데이터 버퍼.
  - `avail_in`: 입력 데이터 크기.
  - `next_out`: 출력 데이터 버퍼.
  - `avail_out`: 출력 버퍼 크기.

---

## 4. 주요 함수

### 4.1 압축 함수

#### `compress`
- **설명**: 데이터를 압축합니다.
- **형식**: `int compress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);`

**예제:**
```c
#include <zlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    const char *input = "Hello, zlib!";
    uLong sourceLen = strlen(input) + 1;
    uLong destLen = compressBound(sourceLen);
    Bytef dest[destLen];

    if (compress(dest, &destLen, (const Bytef *)input, sourceLen) == Z_OK) {
        printf("압축 성공: 원본 크기=%lu, 압축 후 크기=%lu\n", sourceLen, destLen);
    } else {
        printf("압축 실패\n");
    }

    return 0;
}
```

**출력:**
```
압축 성공: 원본 크기=13, 압축 후 크기=21
```

---

### 4.2 해제 함수

#### `uncompress`
- **설명**: 압축된 데이터를 해제합니다.
- **형식**: `int uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);`

**예제:**
```c
#include <zlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    const char *input = "Hello, zlib!";
    uLong sourceLen = strlen(input) + 1;
    uLong destLen = compressBound(sourceLen);
    Bytef compressed[destLen];
    Bytef decompressed[sourceLen];

    if (compress(compressed, &destLen, (const Bytef *)input, sourceLen) == Z_OK) {
        printf("압축 성공\n");

        if (uncompress(decompressed, &sourceLen, compressed, destLen) == Z_OK) {
            printf("해제 성공: %s\n", decompressed);
        } else {
            printf("해제 실패\n");
        }
    } else {
        printf("압축 실패\n");
    }

    return 0;
}
```

**출력:**
```
압축 성공
해제 성공: Hello, zlib!
```

---

### 4.3 스트림 압축 및 해제
zlib는 스트림 기반 데이터 처리를 위해 `deflate`와 `inflate` 함수를 제공합니다.

#### `deflate`
- **설명**: 스트림 데이터를 압축합니다.

#### `inflate`
- **설명**: 스트림 데이터를 해제합니다.

**예제:**
```c
#include <zlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char input[] = "Stream compression example using zlib.";
    char compressed[1024], decompressed[1024];

    z_stream stream;
    memset(&stream, 0, sizeof(stream));

    deflateInit(&stream, Z_BEST_COMPRESSION);

    stream.next_in = (Bytef *)input;
    stream.avail_in = strlen(input) + 1;
    stream.next_out = (Bytef *)compressed;
    stream.avail_out = sizeof(compressed);

    deflate(&stream, Z_FINISH);
    deflateEnd(&stream);

    printf("압축 완료: 원본 크기=%lu, 압축 후 크기=%lu\n", strlen(input) + 1, stream.total_out);

    // 압축 해제
    stream.next_in = (Bytef *)compressed;
    stream.avail_in = stream.total_out;
    stream.next_out = (Bytef *)decompressed;
    stream.avail_out = sizeof(decompressed);

    inflateInit(&stream);
    inflate(&stream, Z_FINISH);
    inflateEnd(&stream);

    printf("해제된 데이터: %s\n", decompressed);

    return 0;
}
```

**출력:**
```
압축 완료: 원본 크기=38, 압축 후 크기=33
해제된 데이터: Stream compression example using zlib.
```

---

## 5. 사용 시 주의사항

1. **메모리 관리**: 스트림 처리를 위한 `deflateInit` 및 `inflateInit` 호출 후 반드시 `deflateEnd`와 `inflateEnd`로 자원을 해제해야 합니다.
2. **버퍼 크기 관리**: 출력 버퍼(`avail_out`)가 충분히 큰지 확인해야 합니다.
3. **오류 처리**: 각 함수 호출 결과를 확인하여 오류를 적절히 처리하세요.

---

zlib는 간단한 API로 강력한 압축 기능을 제공하여 다양한 애플리케이션에서 널리 사용됩니다. 위의 예제를 참고하여 데이터 압축 및 해제 기능을 구현해 보세요.

