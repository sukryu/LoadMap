# 04_Process_Thread_Scheduling

이 디렉토리에서는 **프로세스와 스레드**의 개념, 그리고 **CPU 스케줄링 알고리즘**을 심도 있게 다룹니다.  
운영체제에서 핵심이 되는 프로세스 관리, 문맥 전환, 스레드 모델, 그리고 스케줄러 동작 원리에 대해 학습합니다.

---

## 이 디렉토리에서 다루는 내용

1. **`process_thread.md`**  
   - **프로세스**(Process) vs. **스레드**(Thread) 기본 개념  
   - 프로세스 제어 블록(PCB, `task_struct`), 스레드 제어 블록(TCB)  
   - 프로세스 상태(Ready, Running, Blocked 등)와 전이(스케줄링 이벤트, 인터럽트 등)  
   - 사용자 수준 스레드(User-Level Thread) vs 커널 수준 스레드(Kernel-Level Thread) vs 혼합(M:N) 모델

2. **`scheduling.md`**  
   - **CPU 스케줄링** 기초  
     - FCFS, SJF, Round Robin, 우선순위 스케줄링 등 고전 알고리즘  
   - **현대 OS 스케줄러**  
     - 예) 리눅스 CFS(Completely Fair Scheduler): vruntime, 레드-블랙 트리 구조  
     - 우선순위와 nice 값이 실제로 어떻게 계산되는지  
   - **멀티코어 스케줄링**, 스레드 부하분산(Load Balancing), NUMA-aware 스케줄링 등

3. **`context_switch.md`**  
   - 문맥 전환(Context Switch)의 과정과 비용(오버헤드)  
   - 저장·복원되는 레지스터, 커널 스택, CPU 모드 전환  
   - 리눅스 커널의 `__switch_to()`(x86) 코드 구조 등

---

## 학습 포인트

- **프로세스/스레드 구조**: 운영체제가 실행 단위를 어떻게 관리하고 구분하는지  
- **스케줄링 알고리즘**: CPU 자원을 여러 프로세스/스레드에게 공정하고 효율적으로 분배하기 위한 방식  
- **리눅스 CFS**: vruntime, 레드-블랙 트리를 이용한 “공정성” 추구  
- **문맥 전환**: 어떤 이벤트가 문맥 전환을 유발하고, 스레드 간 전환 시 어떤 작업이 필요한지  
- **멀티코어 환경**: CPU 코어가 여러 개인 경우, 스케줄링과 부하분산은 어떻게 달라지는지

---

## 참고 자료

- [OSTEP - CPU Scheduling](http://pages.cs.wisc.edu/~remzi/OSTEP/)  
- [리눅스 커널 소스의 `kernel/sched/fair.c`](https://github.com/torvalds/linux/tree/master/kernel/sched) (CFS 구현)  
- [Windows Internals 관련 문서](https://docs.microsoft.com/en-us/sysinternals/) (Windows의 스케줄러 구조)  
- [Modern Operating Systems - Andrew S. Tanenbaum](https://en.wikipedia.org/wiki/Andrew_S._Tanenbaum)

---

## 앞으로의 계획

- 이 폴더의 자료를 통해 **프로세스·스레드**를 구분하고, **스케줄링 로직**을 이해합니다.  
- 이후, **05_MemoryManagement** 폴더에서 **메모리 관리와 가상 메모리**로 학습을 확장할 예정입니다.  
- 전체 로드맵은 [OS/README.md](../README.md)를 참고하세요.

---

프로세스와 스레드, 그리고 스케줄링을 제대로 이해하면,  
**멀티태스킹 환경**에서 OS가 CPU 시간을 어떻게 분배하고 관리하는지 명확해집니다.  
이해도 향상에 많은 도움이 되길 바랍니다!
