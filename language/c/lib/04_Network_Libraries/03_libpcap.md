# libpcap 라이브러리 사용 가이드

libpcap은 패킷 캡처 및 네트워크 트래픽 분석을 위한 강력한 라이브러리입니다. 네트워크 인터페이스에서 실시간 트래픽을 캡처하거나 저장된 패킷 데이터를 분석하는 애플리케이션 개발에 사용됩니다.

---

## 1. 주요 특징

1. **실시간 패킷 캡처**: 네트워크 인터페이스에서 패킷을 실시간으로 캡처.
2. **다양한 필터 지원**: Berkeley Packet Filter(BPF)를 사용하여 특정 트래픽 필터링.
3. **크로스 플랫폼 지원**: Linux, macOS, Windows 등에서 동작.
4. **PCAP 파일 처리**: 저장된 패킷 파일 읽기 및 작성.

---

## 2. 설치

### 2.1 설치 방법

**Ubuntu/Linux:**
```bash
sudo apt-get update
sudo apt-get install libpcap-dev
```

**macOS:**
```bash
brew install libpcap
```

**Windows:**
- WinPcap 또는 Npcap 설치 필요 (https://npcap.com/).

---

## 3. 주요 함수

### 3.1 기본 초기화

#### `pcap_findalldevs`
- **설명**: 사용 가능한 네트워크 디바이스 목록을 가져옵니다.
- **형식**: `int pcap_findalldevs(pcap_if_t **alldevsp, char *errbuf);`

**예제:**
```c
#include <pcap.h>
#include <stdio.h>

int main() {
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "디바이스 찾기 오류: %s\n", errbuf);
        return 1;
    }

    for (pcap_if_t *d = alldevs; d; d = d->next) {
        printf("네트워크 디바이스: %s\n", d->name);
    }

    pcap_freealldevs(alldevs);
    return 0;
}
```

**출력:**
```
네트워크 디바이스: eth0
네트워크 디바이스: wlan0
```

---

### 3.2 패킷 캡처

#### `pcap_open_live`
- **설명**: 네트워크 디바이스에서 실시간 패킷을 캡처할 수 있도록 설정.
- **형식**: `pcap_t *pcap_open_live(const char *device, int snaplen, int promisc, int to_ms, char *errbuf);`

**예제:**
```c
pcap_t *handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);
if (handle == NULL) {
    fprintf(stderr, "pcap_open_live 실패: %s\n", errbuf);
    return 1;
}
```

---

### 3.3 패킷 처리

#### `pcap_loop`
- **설명**: 지정된 패킷 수만큼 캡처를 반복합니다.
- **형식**: `int pcap_loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user);`

#### `pcap_handler`
- **설명**: 캡처된 패킷을 처리하기 위한 콜백 함수 타입.
- **형식**: `typedef void (*pcap_handler)(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes);`

**예제:**
```c
#include <pcap.h>
#include <stdio.h>

void packet_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    printf("패킷 길이: %d\n", h->len);
    printf("패킷 데이터: \n");
    for (int i = 0; i < h->len; i++) {
        printf("%02x ", bytes[i]);
    }
    printf("\n\n");
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);

    if (handle == NULL) {
        fprintf(stderr, "pcap_open_live 실패: %s\n", errbuf);
        return 1;
    }

    pcap_loop(handle, 10, packet_handler, NULL);
    pcap_close(handle);
    return 0;
}
```

**출력:**
```
패킷 길이: 60
패킷 데이터:
00 1a a0 b0 c0 d0 e0 f0 01 02 ...
```

---

### 3.4 필터 설정

#### `pcap_compile`와 `pcap_setfilter`
- **설명**: BPF 필터를 컴파일하고 적용합니다.
- **형식**:
  - `int pcap_compile(pcap_t *p, struct bpf_program *fp, const char *str, int optimize, bpf_u_int32 netmask);`
  - `int pcap_setfilter(pcap_t *p, struct bpf_program *fp);`

**예제:**
```c
struct bpf_program filter;
if (pcap_compile(handle, &filter, "tcp port 80", 0, PCAP_NETMASK_UNKNOWN) == -1) {
    fprintf(stderr, "필터 컴파일 실패\n");
    return 1;
}

if (pcap_setfilter(handle, &filter) == -1) {
    fprintf(stderr, "필터 설정 실패\n");
    return 1;
}
```

---

### 3.5 저장된 파일 읽기

#### `pcap_open_offline`
- **설명**: 저장된 PCAP 파일을 읽습니다.
- **형식**: `pcap_t *pcap_open_offline(const char *fname, char *errbuf);`

**예제:**
```c
pcap_t *handle = pcap_open_offline("capture.pcap", errbuf);
if (handle == NULL) {
    fprintf(stderr, "파일 열기 실패: %s\n", errbuf);
    return 1;
}

pcap_loop(handle, 0, packet_handler, NULL);
pcap_close(handle);
```

---

## 4. 실습 예제

### 특정 IP 주소 필터링 및 패킷 출력
**코드:**
```c
#include <pcap.h>
#include <stdio.h>
#include <arpa/inet.h>

void packet_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    printf("패킷 길이: %d\n", h->len);
    printf("패킷 데이터: \n");
    for (int i = 0; i < h->len; i++) {
        printf("%02x ", bytes[i]);
    }
    printf("\n\n");
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);

    if (handle == NULL) {
        fprintf(stderr, "pcap_open_live 실패: %s\n", errbuf);
        return 1;
    }

    struct bpf_program filter;
    if (pcap_compile(handle, &filter, "src host 192.168.1.1", 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "필터 컴파일 실패\n");
        return 1;
    }

    if (pcap_setfilter(handle, &filter) == -1) {
        fprintf(stderr, "필터 설정 실패\n");
        return 1;
    }

    pcap_loop(handle, 10, packet_handler, NULL);
    pcap_close(handle);
    return 0;
}
```

**출력:**
```
192.168.1.1에서 전송된 패킷만 캡처하여 출력합니다.
```

---

## 5. 사용 시 주의사항

1. **권한 문제**: 네트워크 인터페이스 접근에는 관리자 권한이 필요할 수 있습니다.
2. **필터 최적화**: 불필요한 데이터를 줄이기 위해 BPF 필터를 사용하세요.
3. **캡처 성능**: 높은 트래픽 환경에서 패킷 손실을 방지하려면 충분한 버퍼 크기를 설정하세요.

---

libpcap은 네트워크 트래픽 분석과 패킷 캡처를 위한 강력한 도구입니다. 위의 예제를 활용하여 네트워크 데이터를 효과적으로 처리할 수 있습니다.