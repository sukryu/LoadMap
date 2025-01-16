# 03_KernelInternals

이 디렉토리는 **커널 내부 구조**를 중점적으로 학습합니다.  
운영체제가 부팅된 뒤, 커널이 어떤 식으로 하드웨어와 소통하고, 각 서브시스템(메모리, 프로세스 관리, 파일시스템, 네트워크 등)을 초기화하며 관리하는지 살펴봅니다.

---

## 이 디렉토리에서 다루는 내용

1. **`kernel_structure.md`**  
   - **커널 아키텍처**  
     - 모놀리식 커널, 마이크로커널, 하이브리드 커널의 개념 및 대표 예시(리눅스, Windows NT, macOS XNU 등)  
   - **서브시스템 개요**  
     - 프로세스 스케줄링, 메모리 관리자, 파일시스템 계층(VFS), 네트워크 스택 등 각 영역의 대략적인 역할  
   - **커널 모듈, 드라이버 로딩 구조**  
     - 리눅스 커널에서 `insmod`, `rmmod`, `modprobe` 등으로 모듈을 동적으로 탑재하는 원리  

2. **`driver_model.md`**  
   - **장치 드라이버 모델**(리눅스 기준)  
     - `device`, `driver`, `bus` 구조  
     - PCI/USB/ACPI/Device Tree 등을 통한 장치 열거(Enumeration)  
   - **드라이버 등록 과정**  
     - 플러그 앤 플레이(PnP), Udev, Sysfs, procfs 등 리눅스 고유의 장치 관리 방식  
   - **하드웨어 추상화**  
     - 사용자 공간에서는 파일 인터페이스(`/dev/xxx`)로 접근하고, 커널 공간에서 드라이버가 실질적 제어를 담당

3. **`start_kernel_analysis.md`**  
   - 리눅스 커널 `init/main.c`의 `start_kernel()` 함수 초기화 순서  
   - CPU/메모리/디바이스/파일시스템/네트워크 서브시스템 초기화 흐름 개략  
   - 기본 커널 파라미터(커맨드 라인 옵션) 처리가 어떻게 이뤄지는지  

---

## 학습 포인트

- **커널 아키텍처 차이**: 왜 리눅스는 모놀리식, Windows는 하이브리드, macOS는 마이크로 + BSD 혼합인지  
- **드라이버 모델**: 장치가 부팅 시 자동으로 인식·등록되며, 어떤 계층을 통해 사용자 공간과 연결되는가  
- **초기화 루틴**: 커널이 메모리·디바이스를 준비하고, 각 서브시스템을 기동하는 단계별 순서  
- **메모리 구조 & 접근 방법**: 커널 공간(kspace) vs 사용자 공간(usize), 시스템 콜 인터페이스, IRQ/exception 처리 등

---

## 참고 링크 / 자료

- [Linux Kernel Source](https://github.com/torvalds/linux)
  - `init/main.c` 내의 `start_kernel()` 주석 참조
- [Linux Device Drivers (LDD3)](https://lwn.net/Kernel/LDD3/) (다소 오래되었지만 드라이버 기초 개념에 여전히 유용)
- [Windows Internals](https://docs.microsoft.com/en-us/sysinternals/) (Windows NT 커널 구조 참고)
- [macOS XNU Source (Apple Open Source)](https://opensource.apple.com/source/xnu/) (부분 공개된 코드로 구조 파악 가능)

---

## 앞으로의 계획

- 이 폴더의 자료로 **커널이 하드웨어 & OS 자원을 어떤 구조로 관리**하는지 큰 틀을 익힙니다.  
- 이후, **04_Process_Thread_Scheduling** 폴더에서 **프로세스와 스레드, 스케줄링**을 더 자세히 파고듭니다.  
- 전체 로드맵은 [OS/README.md](../README.md)를 참고하세요.

---

커널 내부 구조를 이해하면, 어떤 언어나 환경에서 개발하더라도  
**“시스템 레벨”**에서 일어나는 일을 보다 잘 파악할 수 있습니다.  
하드웨어와의 연계, 드라이버 모델, 초기화 과정 등을 꼼꼼히 살펴봅시다!
