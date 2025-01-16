# 07_Concurrency_IPC

이 디렉토리는 **동기화(Concurrency)**와 **프로세스 간 통신(IPC)**을 중점적으로 다룹니다.  
운영체제가 여러 프로세스(또는 스레드)가 동시에 실행될 때 발생할 수 있는 문제(경쟁 상태, 교착 상태)를 어떻게 예방/해결하는지, 그리고 서로 다른 프로세스들이 데이터를 주고받는 메커니즘을 살펴봅니다.

---

## 이 디렉토리에서 다루는 내용

1. **`synchronization.md`**  
   - **경쟁 상태(Race Condition)** 개념  
   - 상호 배제(Mutual Exclusion)를 위한 기법  
     - **세마포어(Semaphore)**, 뮤텍스(Mutex), 모니터(Monitor), 스핀락(Spinlock)  
   - 교착 상태(Deadlock) 발생 조건 & 해결/회피/예방 기법  
   - 기아(Starvation), 우선순위 역전(Priority Inversion)

2. **`ipc.md`**  
   - **프로세스 간 통신(IPC)** 개요  
   - **파이프(Pipe), FIFO(Named Pipe)**, 메모리 공유(Shared Memory), 메시지 큐(Message Queue), 소켓(Sockets) 등 주요 기법  
   - 실무 예시: Unix 도메인 소켓, SysV IPC vs POSIX IPC 차이  
   - OS가 IPC 자원을 어떻게 관리(커널 공간 할당, 키 식별 등)하는지

3. **`deadlock_handling.md`**
   - 교착 상태(Deadlock) 조건(상호 배제, 점유 대기, 비선점, 환형 대기)  
   - 예방, 회피(은행가 알고리즘), 탐지 및 복구 등 구체적인 방법론  
   - 실무/시스템 관점에서 데드락을 줄이기 위한 설계 패턴

---

## 학습 포인트

- **동시성 제어**: 여러 스레드/프로세스가 공유 자원을 안전하게 사용하기 위한 기법들  
- **상호 배제 구현**: 세마포어 vs 뮤텍스, 스핀락, 모니터 등 각 방식의 장단점, 사용 사례  
- **IPC 메커니즘**: 프로세스 간 데이터를 교환하는 다양한 방법(파이프, 메시지 큐, 소켓 등)  
- **교착 상태**: OS에서 교착 상태를 어떻게 예방·회피·탐지하고, 복구는 어떻게 하는지

---

## 참고 자료

- [OSTEP - Concurrency & Synchronization](http://pages.cs.wisc.edu/~remzi/OSTEP/)  
- [Linux Kernel Synchronization Primitives](https://www.kernel.org/doc/html/latest/core-api/syncing.html)  
- [POSIX IPC (man7.org)](https://man7.org/linux/man-pages/man7/ipc.7.html)  
- [Unix Network Programming - W. Richard Stevens](https://en.wikipedia.org/wiki/UNIX_Network_Programming) (소켓 IPC 관련)

---

## 앞으로의 계획

- 이 폴더를 학습하면서 **동시성 문제**(경쟁 상태, 교착 상태)와 **IPC 기법**을 익힙니다.  
- 이후, **08_Security_Virtualization** 폴더에서 **운영체제 보안 및 가상화(하이퍼바이저, 컨테이너)** 주제를 다룰 예정입니다.  
- 전체 로드맵은 [OS/README.md](../README.md)에서 확인하세요.

---

동시성 제어와 IPC는 **멀티프로세싱/멀티스레딩 환경**에서 필수적인 개념입니다.  
프로세스 간 협력과 충돌 방지 방법을 잘 이해하면,  
안정적이고 효율적인 시스템을 구축할 수 있을 것입니다! 
