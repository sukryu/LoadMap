# 02_BootProcess

이 디렉토리는 **컴퓨터 부팅 과정**을 다루며, 전원이 켜진 직후부터 운영체제가 로드되기까지의 과정을 집중적으로 살펴봅니다.  
BIOS/UEFI가 하드웨어를 초기화하고 부트로더를 통해 커널을 메모리에 적재한 뒤, 커널이 실행되는 전반적인 **부팅 시퀀스**를 이해하는 데 목적이 있습니다.

---

## 이 디렉토리에서 다루는 내용

1. **`boot_process.md`**  
   - **BIOS vs UEFI**: 전통적인 BIOS 방식 부팅과 현대적인 UEFI 방식의 차이점  
   - **부트로더**(GRUB, LILO 등)의 역할 및 단계별 동작  
   - 커널 로딩 후 `start_kernel()` 호출 전까지 개략적인 흐름  

2. **`uefi_acpi.md`**  
   - **UEFI**가 OS에게 제공하는 인터페이스(SMBIOS, Secure Boot 등)  
   - **ACPI**(Advanced Configuration and Power Interface)를 통해 OS가 전원 관리·하드웨어 설정 정보를 전달받는 구조  
   - S3/S4/S5 등 다양한 전원 상태(슬립·절전·완전 종료)와 ACPI 테이블

3. **`bootloader_example/`**
   - **간단한 x86 부트로더** 소스코드 (어셈블리/Makefile)  
   - QEMU로 테스트하는 방법(커맨드, 디스크 이미지 생성 등)  
   - 직접 부트 섹터 코드를 작성해 보며, “부트로더 → 커널 점프” 과정을 체험

---

## 학습 포인트

- **부팅 시퀀스**: 전원이 켜진 후 CPU 레지스터 초기화, 메모리 맵 설정, 인터럽트 벡터 테이블 준비 등  
- **BIOS vs UEFI** 구분  
  - BIOS 메모리 한계(실모드 vs 보호모드 전환), MBR 파티션 방식  
  - UEFI GPT 파티션, Secure Boot, 펌웨어 인터페이스 표준  
- **ACPI**를 통한 전원/장치 관리  
  - ACPI 테이블(DSDT, FADT 등), OS가 이를 해석하여 하드웨어 제어  
- **부트로더 구현**  
  - 1단계/2단계 부트로더, 커널 이미지 적재, 커맨드라인 파라미터 전달  
  - 실습(QEMU)으로 간단히 확인해 보기

---

## 참고 링크 / 자료

- [OSDev Wiki - Bootloader](https://wiki.osdev.org/Bootloader)  
- [UEFI 공식 문서](https://uefi.org/)  
- [ACPI 스펙](https://uefi.org/specs/acpi)  
- [GNU GRUB 문서](https://www.gnu.org/software/grub/manual/)  

---

## 앞으로의 계획

- **부트 로더 예시 코드**(`bootloader_example/`)를 간단히 빌드 & 실행해 보고, 실제 부팅 과정을 체험  
- 이후, **03_KernelInternals** 폴더로 넘어가 **커널 구조**와 초기화 루틴(`start_kernel()` 등)을 구체적으로 분석할 예정  
- 전체 로드맵은 [OS/README.md](../README.md)를 참고하세요.

---

부팅 과정에 대한 이해는 **운영체제가 어떻게 실행 준비를 마치는지**를 파악하는 중요한 단계입니다.  
꼭 필요한 개념들을 꼼꼼히 살펴보세요!
