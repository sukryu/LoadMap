# 운영체제 공부 확장 계획

1. 부팅 과정(Boot Process) 및 펌웨어/UEFI/ACPI
    1. 부팅 시퀀스
        - BIOS 또는 UEFI가 하드웨어 초기화 -> 부트로더(GRUB, LILO 등)로딩 -> 커널 로딩 -> 커널 초기화 루틴 -> `init/systemd` 실행
        - 레지스터 설정, 메모리 맵 확인, 인터럽트 벡터 테이블 설정 등 실제 부팅 단계에서 일어나는 주요 작업

    2. UEFI와 ACPI
        - UEFI(펌웨어)에서 OS에게 전달되는 시스템 정보, Secure Boot 개념
        - ACPI(Advanced Configuration and Power Interface)를 통해 전원 관리, 하드웨어 정보(테이블) 등이 어떻게 OS에 제공되는지
        - S3/S4/S5와 같은 슬립/절전 상태(파워 스테이트) 전환 방식

    3. Bootloader 구조
        - 부트로더가 커널 이미지를 메모리에 적재 후 제어권을 넘기는 과정
        - 간단한 부트로더 작성 예시, QEMU 등으로 테스트

2. 커널 내부 구조 & 초기화 루틴
    1. start_kernel() 분석(리눅스 기준)
        - 커널이 처음 실행될 때 어떤 순서로 하드웨어/메모리/장치를 초기화하는지
        - CPU-메모리-디바이스-파일시스템-네트워크 서브시스템 초기화 개요

    2. 하이브리드 커널 vs 마이크로커널 vs 모놀리식 커널
        - 실제 OS(Windows NT, Linux, mac OS XNU)의 구조 비교
        - 모듈/드라이버 로딩 메커니즘

    3. 드라이버 모델과 장치 등록
        - 리눅스 커널에서 device tree(주로 ARM 계열)나 PCI/ACPI 기반으로 디바이스 열거(Enumeration)
        - 드라이버가 장치를 인식하고 등록하는 과정

3. 프로세스/스레드 & CPU 스케줄링 심화
    1. 리눅스 CFS(Completely Fair Schedular)
        - 가상 런타임(vruntime), 레드블랙 트리(red-black tree) 기반 스케줄링 구조
        - 프로세스 스케줄링 결정 과정, 우선순위와 Nice 값 등이 실제로 어떻게 계산되는지

    2. 프로세스 내부 구조
        - `task_struct`, `mm_struct` 등 커널의 자료구조
        - 문맥 전환(context switch) 시 레지스터 저장/복원, 커널 스택 사용 구조

    3. 스레드 모델
        - 사용자 수준 스레드(U-LT) vs 커널 수준 스레드(K-LT) vs 혼합(M:N) 모델
        - POSIX Threads가 커널과 어떻게 연결되는지

4. 가상 메모리 & 메모리 관리 구체화
    1. 리눅스의 가상 메모리 구조
        - x86_64 기준 4단계 페이지 테이블, `pgd -> pud -> pmd -> pte`
        - 유저 스페이스 / 커널 스페이스 분리, `vm_area_struct`를 통한 영역 관리

    2. 페이지 교체 알고리즘 심화
        - CLOCK, LFU, MFU, 또는 리눅스에서 실제로 쓰는 `LRU` 변형 알고리즘들
        - Swapping(프로세스 전체를 디스크에 내리는 기법)의 역사적 개념

    3. NUMA(Non-Uniform Memory Access)
        - 멀티소켓 시스템에서 노드 간 메모리 접근 지연, NUMA-aware 스케줄링, 영역 바인딩 등

5. 파일 시스템 & 디스크 I/O 스택 확장
    1. VFS(Virtual File System) 레이어
        - ext4, XFS 등 실제 파일시스템 드라이버가 VFS를 통해 커널에 연결되는 방식
        - inode, dentry 캐시, 버퍼 캐시 개념

    2. 저널링(Journaling) 파일 시스템
        - ext4, NTFS, APFS, btrfs 등에서 장애 복구를 위한 저널 구조
        - Write-ahead logging, Copy-on-write 방식 등

    3. 디스크 스케줄링
        - HDD 시대 대표 알고리즘: FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOk
        - CFQ, Deadline 등 리눅스 커널의 I/O 스케줄러(SSD 환경에서의 변경 사항 포함)

    4. RAID 레벨
        - RAID 0, 1, 5, 6, 10 등 디스크 병렬 구성 방식
        - 블록 분산, 미러링, 패리티 개념

6. 동기화/병행성/IPC 구체화
    1. 스핀락(Spinlock), 뮤텍스(Mutex), 리드-라이트 락
        - 여러 동기화 기법의 내부 구현 및 사용 시나리오
        - 세마포어 vs 뮤텍스 차이, 각 기법이 커널/유저 모드에서 어떻게 동작하는지

    2. 인터럽트 컨텍스트와 동기화
        - 인터럽트 핸들러가 공유 자원을 건드릴 때 어떻게 보호해야 하는지
        - 리눅스 커널에서 softirq, tasklet 등 처리 방식

    3. IPC(Inter-Process Communication) 기법
        - 공유 메모리, 파이프, FIFO, 소켓, 메시지 큐 등 실무 응용 사례
        - 리눅스 커널 내에서 해당 자원들을 어떻게 관리하는지

7. 보안/보호 및 가상화
    1. 리눅스 보안 모듈(LSM)
        - SELinux, AppArmor 등 Mandatory Access Control 구현
        - Hook 기반으로 커널에서 액세스 제어 수행

    2. 가상화(Virtualization)
        - 하이퍼바이저 타입1/타입2, KVM, QEMU, VMware, Hyper-V 원리
        - 네임스페이스, cgroups, chroot 등을 활용한 컨테이너(도커, LXC 등)와 가상머신 차이

    3. OS 레벨 보안 기법
        - UAC(Windows), SUID/SGID(Unix), RBAC(Role-Based Access Control)
        - 시스템 콜 필터링(secccomp 등)

8. 실제 커널 코드/실습 접근
    1. 리눅스 커널 코드
        - `Documentation/` 폴더, `init/main.c`의 `start_kernel()` 등
        - 부팅 루틴, 스케줄러(cfs/), 메모리(mm/), 디렉터리 파악

    2. 미니 OS, 교육용 커널
        - xv6(MIT), Minix, OS/161 등에서 프로세스/파일시스템/스케줄러 구현 읽어보기
        - 코드를 직접 빌드/실행(QEMU 사용)하며 디버깅

    3. LKM(Linux Kernel Module) 작성
        - "Hello Kernel" 모듈, 간단한 캐릭터 디바이스 드라이버, `/proc` 인터페이스 추가해보기
        - 실제 커널 함수(`printk`, `kmalloc`, `copy_to_user`등)와 연동 실습

9. 최신/고급 토픽
    1. GPU 스케줄링 및 이종 프로세서(Heterogeneous Computing)
        - CUDA, OpenCL, ROCm 등에서 OS가 어떻게 리소스를 분배/관리하는지 개념적으로 파악
    
    2. RTOS(Real-Time OS) 세부
        - 경성 실시간(딱 맞춰야 함) vs 연성 실시간(약간의 오차 허용), 임베디드 분야 스케줄링(EDF, RM 등)

    3. NUMA-aware Kernel Tuning
        - 멀티소켓 환경에서의 CPU/메모리 바인딩, UMA vs NUMA 성능 차이

    4. Cloud-native OS 개념
        - Container OS(CoreOS, Bottlerocket, RancherOS 등)들이 어떻게 경량화하고 컨테이너 최적화를 하는지