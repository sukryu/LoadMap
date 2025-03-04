# 10_Lab_Examples

이 디렉토리는 **운영체제 이론**을 실제 코드나 프로젝트로 확인해 보는 **실습·예제**들을 다룹니다.  
간단한 부트로더, 커널 모듈, 교육용 미니 OS, 또는 리눅스 커널 특정 부분 분석 등을 통해 학습한 개념을 손으로 익혀볼 수 있습니다.

---

## 이 디렉토리에서 다루는 내용

1. **`kernel_code_analysis.md`**  
   - 리눅스 커널 일부 코드(`init/main.c`의 `start_kernel()`, 스케줄러 `fair.c`, 메모리 관리자 `mm/` 등)를 분석한 결과 정리  
   - 주요 자료구조(task_struct, mm_struct, vfsmount 등)나 함수 흐름을 간단히 살펴보기  
   - 빌드 & 디버그 환경 설정(예: QEMU, GDB) 및 팁

2. **`mini_os_practice.md`**  
   - **교육용 OS**(xv6, Minix, OS/161 등) 빌드 및 실행, 코드 구조 분석  
   - 프로세스 생성, 파일 시스템, 스케줄러, 메모리 관리자 등이 간단히 구현된 예제 살펴보기  
   - QEMU, Bochs 등 에뮬레이터 활용 방법

3. **`bootloader_example/`**
   - 간단한 **x86 부트로더**(어셈블리, Makefile) 코드  
   - “Hello OS” 수준으로 부트 섹터에서 메시지 출력 후 커널 혹은 세컨드 스테이지 로더로 점프  
   - QEMU로 부팅 테스트하는 방법

4. **`lkm_examples/`**
   - **리눅스 커널 모듈**(LKM) 작성 실습  
   - “Hello Kernel” 모듈, 간단한 캐릭터 디바이스 드라이버, `/proc` 인터페이스 추가 예시  
   - `make` & `insmod/rmmod` & `dmesg` 로그 확인으로 동작 시험

(위 목록은 예시이며, 각자 원하는 주제·실습 예제를 자유롭게 추가하거나 구조를 바꿀 수 있습니다.)

---

## 학습 포인트

- **OS 이론**을 직접 코드로 확인하고 실습함으로써, 추상적 개념을 더 깊이 이해  
- **커널 빌드 & 디버그** 경험(리눅스 커널, 미니 OS)  
- **부트로더 / 커널 모듈 / 교육용 OS** 등 실제 예제 프로젝트를 통해 저수준 시스템 프로그래밍 감각 기르기  
- QEMU, Bochs, VirtualBox 등 **가상머신·에뮬레이터** 사용 방법 익히기

---

## 참고 자료

- [OSDev Wiki](https://wiki.osdev.org/) - 부트로더, 미니 OS 개발에 유용한 문서  
- [xv6 (MIT)](https://github.com/mit-pdos/xv6-public), [OS/161 (Harvard)](http://os161.eecs.harvard.edu/)  
- [Linux Device Drivers (LDD3)](https://lwn.net/Kernel/LDD3/) - 커널 모듈 관련  
- [Kernel Newbies](https://kernelnewbies.org/) - 리눅스 커널 학습 커뮤니티

---

## 앞으로의 활용

1. **이 폴더 내 예제**들을 학습 순서에 맞춰 차근차근 해보며, 코드를 빌드 & 실행 & 디버깅  
2. 필요하다면 신규 실습 프로젝트(예: 간단한 파일시스템, TCP/UDP 소켓 드라이버 등)를 추가  
3. 이론 파트에서 다룬 주제를 여기서 **직접 구현·분석**하면서 연결 고리를 찾음

---

실습을 통해 **운영체제 구조**를 실제로 체득하면,  
시스템 프로그래밍 역량과 문제 해결 능력을 한층 더 높일 수 있습니다.  
호기심을 가지고 **자유롭게 코드를 뜯어보고 실험**해 보세요!  
