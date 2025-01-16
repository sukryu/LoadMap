# 운영체제(Operating System) 학습 로드맵

이 저장소(Repository)는 **운영체제** 전반에 대한 기초부터 심화 주제까지 폭넓게 학습하고 정리하기 위해 만들어졌습니다.  
**부팅 과정(UEFI/ACPI), 커널 내부 구조, 프로세스·스레드·스케줄링, 메모리 관리, 파일 시스템, 동기화·IPC, 보안·가상화, 그리고 최신/고급 토픽**까지 단계별로 정리할 예정입니다.

---

## 목표

1. **운영체제의 동작 원리**를 체계적으로 이해
2. **리눅스 커널** 구조 분석과 **커널 소스 실습** 경험
3. Python / Go / C++ 개발자로서, **시스템 레벨 이해도**를 높여 성능·병목 문제를 해결할 수 있는 역량 갖추기
4. AI/클라우드 시대에도 사라지지 않는 **OS 기반 역량** 확보

---

## 목차

아래는 대략적인 학습 순서 및 디렉토리 구성입니다. 각 폴더에는 세부 주제별 **README.md**와 문서, 실습 예제 등을 담고 있습니다.

1. [01_Introduction](./01_Introduction/README.md)  
   - 운영체제 정의, 역사, 분류, OS를 배우는 이유 등

2. [02_BootProcess](./02_BootProcess/README.md)  
   - BIOS vs UEFI, 부트로더, ACPI, QEMU 실습 등 부팅 과정 전반

3. [03_KernelInternals](./03_KernelInternals/README.md)  
   - 커널 구조(모놀리식·마이크로·하이브리드), 드라이버 모델, 장치 등록 등

4. [04_Process_Thread_Scheduling](./04_Process_Thread_Scheduling/README.md)  
   - 프로세스·스레드 개념, 스케줄링 알고리즘, 리눅스 CFS 등

5. [05_MemoryManagement](./05_MemoryManagement/README.md)  
   - 가상 메모리, 페이지 테이블 구조, 교체 알고리즘, NUMA 등

6. [06_FileSystem_IO](./06_FileSystem_IO/README.md)  
   - 파일시스템(VFS, ext4 등), 디스크 I/O 스케줄링, RAID

7. [07_Concurrency_IPC](./07_Concurrency_IPC/README.md)  
   - 동기화(세마포어, 뮤텍스, 스핀락)와 병행성, 인터프로세스 통신(IPC)

8. [08_Security_Virtualization](./08_Security_Virtualization/README.md)  
   - OS 보안(SELinux, UAC 등), 가상화(KVM, Docker), 컨테이너 vs VM

9. [09_AdvancedTopics](./09_AdvancedTopics/README.md)  
   - RTOS, GPU 스케줄링, 클라우드·컨테이너 기반 OS, NUMA 고급 주제

10. [10_Lab_Examples](./10_Lab_Examples/README.md)  
   - 실제 커널 코드 분석(`start_kernel()`, 스케줄러), Minix/xv6 실습, 간단한 부트로더·LKM 예제

---

## 진행 방식

1. 각 디렉토리마다 **README.md**를 작성해, 해당 파트의 **주요 내용**과 **세부 문서/파일**을 안내합니다.
2. **이론 정리** + **실습/코드** 병행으로, 개념과 실제 구현 간의 간극을 줄입니다.
3. 가능하면 **스크린샷**, **다이어그램**, **코드 스니펫** 등을 통해 시각화합니다.  
   - 이미지는 `assets/images/` 폴더에 저장하고, 본문에서 링크로 참조.
   - 샘플 코드는 `assets/code_snippets/` 또는 각 폴더 내에 적절히 관리.
4. 정리가 끝난 후에도, **업데이트**와 **피드백**을 이어가며 최신 정보를 반영할 예정입니다.

---

## 참고 & 참조 자료

- **Operating Systems: Three Easy Pieces (OSTEP)** - 무료 PDF로 기초 개념 + 실제 사례 학습
- **리눅스 커널 소스코드** - [Github mirror](https://github.com/torvalds/linux)
- **OS 개발 커뮤니티 (OSDev.org, OSDev Wiki)**  
- **공식 문서**
  - [UEFI](https://uefi.org/), [ACPI Spec](https://uefi.org/specs/acpi), [SELinux Docs](https://selinuxproject.org/)
- **MIT xv6, Minix3** - 교육용 미니 OS로 구조 파악하기 좋음

---

## 기여 & 라이선스

- 본 저장소는 공부 과정에서 개인적으로 정리한 자료이며, 일부 내용은 **공식 문서/교과서/오픈소스** 참고 자료를 요약하거나 인용했습니다.  
- 저작권이나 라이선스 관련 문제가 있을 경우, [이슈](#)나 이메일로 알려주세요. 즉시 조치하겠습니다.

---

## 향후 계획 / TODO

- [ ] **Bootloader 예제**: 간단한 x86 부트 로더 코드와 함께 QEMU로 부팅 실습  
- [ ] **Kernel Code**: 리눅스 스케줄러 코드(`fair.c`) 부분 분석  
- [ ] **가상화 실습**: Docker + cgroups + namespaces 실습, KVM/QEMU VM 구성  
- [ ] **RTOS**: FreeRTOS, Zephyr 등 임베디드 환경 스케줄링 사례 추가  

학습 진행 상황에 따라 계속 업데이트할 예정입니다.  
문의나 제안 사항은 언제든 **이슈** 혹은 **PR**로 부탁드립니다!

---

**즐거운 운영체제 학습** 되시길 바랍니다. 언제든 환영입니다! 
