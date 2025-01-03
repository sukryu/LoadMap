# 시스템 보안

* CPU
    - 입력장치로부터 자료를 받아 연산 후 결과를 출력 장치로 전송하는 과정을 제어하는 핵심 장치(연산, 레지스터, 제어, 버스)

    * 기억장치: 레지스터, 캐시, 주기억장치, 보조기억장치

    * 구성요소:
        1. ALU(연산장치): 산술연산, 논리연산
        2. 레지스터: 소규모 데이터, 중간 결과를 기억해두는 고속 영역
        3. Control Unit(제어장치): 명령어 해석, 제어신호 발생
        4. 내부 CPU 버스: ALU 레지스터간의 데이터 이동

    * 명령 실행 주기
        1. 인출 (Instruction Fetch): 메모리 데이터를 로드하여 레지스터에 적재
        2. 간접 (Indirection): 간접주소 방식 채택 경우 - CPU가 메모리 참조시 메모리 주소를 참조
        3. 실행 (Execution): 명령, 데이터 -> 산술, 논리연산 수행
        4. 인터럽트 (Interrupt): 예기치않은 문제 발생시에도 업무처리가능 하게 하는 기능

    * 레지스터
        * PC(Program Counter): 다음에 수행할 주기억장치 주소 기억
        * MAR(Memory Address Register): 주기억장치에 접근하기 위한 주기억장치 주소 기억
        * MBR(Memory Buffer Register): 주기억 장치 입/출력 자료 기억
        * IR(Instruction Register): 주기억 장치 -> 인출한 명령코드 기억

    * 버스 (입출력에 영향을 미침)
        * 데이터 버스: 데이터 전송 용도
        * 주소 버스: 기억장소 위치, 식별
        * 제어 버스: CPU, 기억장치, I/O 장치사이의 제어신호 전송

* 기억장치 계층구조
    * 레지스터          장치용량    장치비용    속도
    * 캐시              작음        큼         빠름
    * 주기억장치       
    * 보조기억장치       큼          작음       느림

* 캐시메모리
    - CPU와 주기억장치 속도차이 극복을 위한 버퍼 메모리(기억장치)

    * 사상방식
        1. 직접 사상(Direct Mapping): Main Memory를 여러구역으로 분할하여 캐시슬롯과 직접 매핑
        2. 집한 연관사상(Set Associate Mapping): 직접 + 연관 방법 메모리를 세트(블록)으로 분할하여 매핑
        3. 연관 사상(Associate Mapping): Main Memory 블록들이 캐시 슬롯에 어느곳이든 적재 가능

    * 관리 방식 (CPU가 원하는 데이터가 캐시메모리에 적재하도록 관리)
        * 호출기법:
            1. Demand Fetch: 필요시 캐시 인출
            2. Pre-Fetch: 예상되는 데이터를 미리 패치

        * 교체기법:
            * 캐시 메모리 교체 알고리즘
                1. FIFO(First In First Out): 가장 오래 있었던 Page 교체 / 자주 사용되는 페이지가 교체될 수 있음.
                2. LFU(Least Frequently Used): 가장 사용횟수가 적은 Page 교체 / 새로 들어온 페이지가 교체될 수 있음.
                3. LRU(Least Recently Used): 가장 오랫동안 사용되지 않은 Page 교체 / 오버헤드 우려.
                4. NUR(Not Used Recently): 미사용 Page 교체 (참조/수정비트 사용)
                5. SCR(Second chance Replacement): 최초 참조 비트 1, 1 -> 0 두번기회

                * 페이지 교체시 문제점
                    - Page Fault(페이지 부재), DemadPaging, Thrashing(부재가 너무 빈번하여 프로세스 수행보다 페이지 교체 시간소요가 더 소모됨.)


* 가상 메모리(Virtual Memory)
    - Virtual Address Space 사용, 물리적 메모리보다 더 큰용량 제공.

    * 관리 단위 (페이지 Vs 세그먼트): 비연속 할당
        - 페이지: 동일한 크기의 최소 논리 분할 단위 / 내부 단편화
        - 세그먼트: 용도별로 논리적 단위로 나눔 / 외부 단변화
        - 연속할당: 고정분할, 가변 분할

* I/O 인터페이스 ( 주기억장치 - 보조기억장치 입출력 )
    1. CPU 경우 : 프로그램에 의한 I/O, 인터럽트에 의한 I/O
        - 프로그램에 의한 I/O : CPU가 주변장치를 연속 감시하는 Polling 방식
        - 인터럽트에 의한 I/O : 인터럽트 요청 감지시 수행작업을 중지

    2. CPU 비경유 : DMA(Direct Memory Access Controller), Channel I/O
        - DMA: 메모리와 주변장치를 직접 관리, 속도 빠름 (Cycle Stealing: CPU 사용하지 않는 버스 점유, Burst Mode: 점유)
        - 채널 I/O(I/O Processor): I/O 장치의 복잡함으로 DMA 한계를 보완하여 별도 전용 처리기능 프로세서 탐재
            1. Multiplexer Channel: 저속장치, 시분할 방식
            2. Selector: 고속장치, 단일 입출력

* 운영체제
    - 컴퓨터 시스템의 자원들을 효율적으로 관리, 사용자의 컴퓨터 사용 편의성 환경 제공

    * 목적:
        1. 처리능력 향상
        2. 신뢰성 향상
        3. 응답시간의 단축
        4. 자원 활용률 향상
        5. 가용성 향상

    * 주요 자원 관리 기능
        1. 프로세스 관리
        2. 기억장치 관리
        3. 주변장치 관리
        4. 파일 관리

    * 프로세스 관리 (Process Management)
        * 프로세스:
            - 레지스터, 스택, 포인터, 실행중인 프로그램, 데이터 등의 집합체
            - 실행중인 프로그램, PCB 보유, Library Call, 자원할당의 기본 단위

        * 스레드:
            - 제어의 흐름, 프로세스에서 실행의 개념, CPU 작업의 기본 단위, System Call

    * CPU 스케줄링 기법 (:프로세스 상태 전이)
        - 컴퓨터의 자원을 효율적으로 사용하기 위한 정책, 자원을 요청하는 프로세스 순서를 정함

        1. 점유 방식
            1. 선점(Preemptive): 프로세스 CPU 점유 시 다른 프로세스 점유 가능 (Round-robin, SRT)
                - Rount-robin: 각 프로세스는 같은 시간을 CPU에서 할당 받음
                - SRT(Shortest Remaining Time): 수행시간이 짧은 작업부터 CPU에 할당하지만 수행 중 다른 프로세스가 더 짧은시간 일 때 점유 가능.

            2. 비선점(Non-preemtive): 프로세스 CPU 점유시 독점 (FCFS, SJF, HRN)
                - FCFS(First Come First Service): 대기큐에 도착한 순서에 따라 CPU 할당
                - SJF(Short Job First): 수행시간이 짧은 작업부터 CPU 할당
                - HRN(Highest Ratio Next): SJF를 개선하여 프로세스 우선순위로 할당

        2. Multi Level Queue: 여러 종류의 그룹(큐)로 나누어 각자 독자적인 스케줄링 기법을 사용
        3. Multi Level Feedback Queue: 그룹(큐)들을 라운드로빈 + 비선점방식 (Hybrid 스케줄링)

    * 병행성제어
        1. 상호배제(Mutual Exclusion Techniques): 다수의 프로세스 동일 자원 접근 시 무결성 보장, 임계영역 사용
            - 임계영역 (Critical Section): 공유자원의 독점을 보장하는 코드 영역, 병렬컴퓨팅의 일부로도 쓰임, 세마포어 개념 이용
                - 세마포어: 공유자원의 개수를 나타내는 변수

            - 모니터 상호배제 기법: 하나의 프로세스만이 모니터내부의 존재, 모니터 내부의 지역변수로 정의

        2. 교착상태(Dead Lock): 하나 이상의 프로세스가 더 이상 계속할 수 없는 특정 사건을 기다리고 있는 상태
            * 교착 상태 발생 조건
                1. 상호배제: 하나 이상의 프로세스가 자원을 베타점유
                2. 점유와 대기: 부분 할당으로 다른 종류의 자원을 요구하면서 자원 점유
                3. 비선점: 자원이 해제되지 않음.
                4. 환형대기: 프로세스와 자원들이 원형을 이루며 서로 상대방의 자원을 요청

            * 대응 방법(예방, 회피, 발견, 회복)
                1. 예방 (Prevention): 필요 조건을 부정, 교착상태 예방
                    - 점유와 대기 부정: 필요한 자원을 일시에 요청
                    - 비선점 조건의 부정: 자원점유 후 자원 요청 시 자원해제 선 요청
                    - 환형대기 조건 부정: 프로세스들의 자원별로 우선순위 결정
                    - 상호배제 조건 부정: 자원 비공유 전제

                2. 회피 (Avoidence): 가능성을 인정, 회피
                    - 은행원 알고리즘 (안전상태, 불안전상태): 프로세스가 요구한 최대 요구량 만큼 자원을 할당 안전순서서열 존재, 교착상태는 불완전상태에서만 일어남.

                3. 발견 (Detection): 교착상태 발생 허용, 원인을 규명하고 해결
                    - 교착상태 발견 알고리즘: 교착상태 발생 검사 알고리즘, 교착상태 빈도수 파악
                    - 자원할당 그래프: 방향그래프를 이용, 그래프 소거법을 이용하여 교착상태 감지

                4. 회복 (Recovery)
                    - 프로세스 중지
                    - 선점점

    * 장치관리기법
        1. 디스크
            * 접근 시간
                1. 탐색 시간 : 현 위치에서 특정 실린더로 디스크 헤드가 이동하는 데 소요되는 시간
                2. 회전 지연시간: 섹터가 디스크 헤드까지 도달하는 시간
                3. 전송 시간: 데이터 전송 시간

            * 스케줄링 기법
                1. FCFS(First-Come First Served): 먼저 들어온 요청 우선 처리
                2. SSTF(Shortest-Seek-Time First): 탐색거리가 가장 짧은 트랙 요청 우선 처리
                3. SCAN(엘레베이터 알고리즘): Head가 이동하는 모든 요청을 서비스 끝까지 처리 후 역방향 처리
                4. C-SCAN: SCAN에서 바깥쪽에서 안쪽으로 이동
                5. C-LOOK: 진행방향에서 요청 없을 시 헤드를 처음 위치로 이동

        2. 파일 시스템 (File System)
            1. FAT(File Allocation Table)
                1. FAT16: 대부분 MS 호환가능, 2GB, 암호화 및 압축 불가능, 파일명 최대 영문8자, 클러스터 1632KB
                2. FAT32: 2TB, 암호화 및 압축 불가능, 파일명 최대 영문 256자, 클러스터 4KB
                3. NTFS(New Technology File System): 암호화 및 압축 지원, 가변 클러스터

            2. EXT(Extended File System)
                1. EXT: MINIX File System 보완, 최대 2GB, 파일명 255bytes, 단편화문제
                2. EXT2: 2GB, 볼륨 32TB, 오류 수정 지원
                3. EXT3: 저널링 기능, 온라인 파일 시스템 증대, 디스크 조각화 최소화
                4. EXT4: 16GB, 볼륨 16Exabyte, 온라인 조각모음, 저널 체크섬, 하위호환 가능

            3. UFS(Unix File System): 유닉스 파일 시스템 (부트불록, 슈퍼블록, 실린더 그룹, i-node 테이블)
                1. 슈퍼블록: 파일 시스템 크기, i-node 테이블의 크기
                2. I-node 테이블: 파일정보 - 파일크기, 위치, 유형 허가권, 날짜

        3. RAID: 디스크 고장 시 복구를 위해 2개 이상의 디스크에 데이터를 저장하는 기술, 저 가용성 디스크를 배열 구조로 중복 구성
            1. RAID 0: 최소 2개 디스크, 데이터를 나누어 저장, 장애발생 시 복구 불가
            2. RAID 1: 디스크 완전 이중화, 많은 비용 발생, ReadWrite 병렬 가능
            3. RAID 2: Hamming Code를 이용하여 오류 복구
            4. RAID 3: Parity 정보를 별도 디스크에 저장
            5. RAID 4: Parity 정보를 별도 디스크에 블록별 저장 Write 성능 저하
            6. RAID 5: 분산 Parity 구현, 안정성 향상
            7. RAID 6: Parity 다중화, 장애발생 상황에서도 다른 디스크 정상 동작


* 리눅스 서버
    * 핵심 구성요소
        1. 쉘: 명령어 해석기, 명령의 입출력 수행 (Bash, Bourne, C, korn), 프로그램 실행
        2. 커널: 주기억장치에 상주, 사용자 프로그램 관리
        3. 파일 시스템: 정보를 저장하는 기본적 구조, 계층(트리)구조

    * 파일 종류
        1. 루트 파일 시스템: 시스템 프로그램, 디렉터리
        2. 일반 파일: 프로그램, 원시 프로그램 파일, 텍스트 등
        3. 디렉터리 파일: 디렉터리에 관한 정보를 저장하는 논리적인 단위
        4. 특수 파일: 주변 장치에 연결된 파일

    * 부팅
        - Run Level
            0. PROM 감시
            1. 사용자 로그인 불가능한 상태, 암호변경할 때 사용
            2. 공유된 자원이 없는 다중 사용자 단계
            3. 공유 자원을 가진 다중 사용자 단계
            4. 사용 되지 않는 단계
            5. 3단계 기동 후 X-Windows 실행
            6. 재부팅 단계 > 3단계로 재부팅

    