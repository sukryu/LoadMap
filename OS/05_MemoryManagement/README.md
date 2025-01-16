# 05_MemoryManagement

이 디렉토리는 **메모리 관리** 전반을 다룹니다.  
운영체제가 메모리를 어떻게 추상화하고(가상 메모리), 각 프로세스에 안전하게 할당·보호하는지, 그리고 페이지 교체나 NUMA 등의 심화 주제를 학습합니다.

---

## 이 디렉토리에서 다루는 내용

1. **`virtual_memory.md`**  
   - **가상 메모리**의 개념: 논리 주소 공간 vs 물리 주소 공간  
   - 페이징(Paging), 세그멘테이션(Segmentation)  
   - 다단계 페이지 테이블 구조(예: x86_64의 4단계 페이지 테이블)  
   - TLB(Translation Lookaside Buffer) 역할

2. **`page_replacement.md`**
   - 페이지 교체 알고리즘  
     - FIFO, LRU, LFU, CLOCK 등 고전 알고리즘  
     - 리눅스 커널에서 사용하는 변형 LRU (Active list, Inactive list)  
   - **Swapping** 개념(프로세스 통째로 디스크로 내리는 전통적 기법 vs 현대 VM 스왑)

3. **`memory_alloc.md`**
   - 동적 메모리 할당(커널/유저 레벨에서의 `malloc`, `kmalloc`)  
   - buddy system, slab/slub allocator (리눅스)  
   - 가변 분할, 고정 분할 등 고전적 메모리 관리 기법

4. **`numa.md`**
   - NUMA(Non-Uniform Memory Access) 아키텍처  
   - 멀티소켓 환경에서의 메모리 접근 지연, NUMA-aware 스케줄링  
   - 실제 시스템에서 NUMA 노드를 확인(`numactl`, `/sys/devices/system/node/` 등)


---

## 학습 포인트

- **가상 메모리**: 물리 메모리보다 큰 주소 공간 사용, 프로세스 간 메모리 보호 및 격리  
- **페이지 테이블**: 다단계 구조와 TLB 동작, 페이지 폴트 처리 과정  
- **페이지 교체**: 메모리가 부족할 때 어떤 페이지를 디스크로 내보낼지 결정하는 알고리즘들  
- **메모리 할당 기법**: buddy system, slab/slub allocator 등 리눅스 커널 할당자 작동 원리  
- **NUMA**: 멀티소켓 환경에서의 메모리 접근 특성, NUMA-aware 스케줄링/할당

---

## 참고 자료

- [Operating Systems: Three Easy Pieces (OSTEP)](http://pages.cs.wisc.edu/~remzi/OSTEP/) - 메모리 관리 챕터  
- [Linux Kernel Source - `mm/` 디렉토리](https://github.com/torvalds/linux/tree/master/mm) (페이지 교체, 메모리 할당자 구현)  
- [Intel Software Developer’s Manual](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html) - x86 가상 메모리 구조  
- [numactl & Linux NUMA docs](https://man7.org/linux/man-pages/man8/numactl.8.html)

---

## 앞으로의 계획

- 이 폴더의 문서들을 통해 **운영체제가 메모리를 어떻게 추상화하고 관리**하는지 파악합니다.  
- 이후, **06_FileSystem_IO** 폴더에서 **파일 시스템과 디스크 I/O** 관리로 학습 범위를 확장할 예정입니다.  
- 전체 로드맵은 [OS/README.md](../README.md)에서 확인하세요.

---

메모리 관리는 OS의 핵심 중 하나입니다.  
**가상 메모리와 페이지 교체**를 잘 이해하면, 프로그램이 어떤 원리로 “무한에 가까운 주소 공간”을 사용하는지 명확히 알게 될 것입니다!
