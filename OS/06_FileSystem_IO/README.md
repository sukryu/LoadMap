# 06_FileSystem_IO

이 디렉토리는 **파일 시스템**과 **디스크 I/O** 관리를 다룹니다.  
운영체제에서 어떻게 파일을 구조화하고 저장하는지, 그리고 디스크 스케줄링 및 최적화가 어떤 원리로 이루어지는지 살펴봅니다.

---

## 이 디렉토리에서 다루는 내용

1. **`filesystem.md`**  
   - **파일 시스템**의 기본 개념: 파일, 디렉토리 구조, Inode, 데이터 블록  
   - 대표적인 파일 시스템 예시: FAT, ext4, NTFS, XFS  
   - 할당 방식(연속 할당, 연결 할당, 인덱스 할당), 디렉토리 구현  
   - 저널링(Journaling) 파일 시스템과 Write-ahead logging, Copy-on-write(ZFS, Btrfs 등)

2. **`disk_io_scheduler.md`**  
   - **디스크 스케줄링** 알고리즘  
     - 전통 HDD 기반: FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK  
     - 리눅스 커널의 CFQ, Deadline, BFQ 등 현대 I/O 스케줄러  
   - **SSD 환경**에서의 스케줄링 변화 (임의 접근 속도가 빠른 구조)  
   - 캐시, 버퍼링 기법 (페이지 캐시, 버퍼 캐시)

3. **`raid.md`**
   - RAID 레벨(0, 1, 5, 6, 10 등)  
   - 병렬 처리로 인한 성능 향상, 중복(미러링)으로 인한 안정성 확보  
   - 소프트웨어 RAID(mdadm)와 하드웨어 RAID 비교

4. **`vfs_layer.md`**  
   - **VFS(Virtual File System)** 개념: 리눅스가 ext4, XFS, NTFS 등을 단일 인터페이스로 다루는 원리  
   - inode, dentry, superblock 구조  
   - 실제 파일 시스템 드라이버와의 연계

---

## 학습 포인트

- **파일 시스템 구조**  
  - 파일·디렉토리·인덱스 블록 설계, 저널링을 통한 장애 복구  
- **디스크 I/O 스케줄링**  
  - 전통적 HDD 스케줄링(헤드 시킹 최적화) vs SSD 최적화 방식  
- **RAID**  
  - 데이터 무결성, 성능·복원성, 파리티를 통한 장애 대응  
- **VFS**  
  - 리눅스 커널에서 파일 시스템을 추상화하는 계층(선택적으로 심화 학습)

---

## 참고 자료

- [OSTEP - File Systems & I/O](http://pages.cs.wisc.edu/~remzi/OSTEP/)  
- [Linux Kernel Source - `fs/` 디렉토리](https://github.com/torvalds/linux/tree/master/fs)  
- [ext4 문서 (Kernel Docs)](https://www.kernel.org/doc/html/latest/filesystems/ext4/index.html)  
- [RAID 관련 자료(mdadm, LVM 등)](https://raid.wiki.kernel.org/)

---

## 앞으로의 계획

- 이 폴더의 내용을 통해 **운영체제가 파일과 디스크를 어떻게 관리**하는지 이해합니다.  
- 이후, **07_Concurrency_IPC** 폴더에서 **동기화와 프로세스 간 통신(IPC)**에 대해 살펴볼 예정입니다.  
- 전체 로드맵은 [OS/README.md](../README.md)을 참고하세요.

---

파일 시스템과 디스크 I/O 구조를 알면,  
**데이터 저장·검색·읽기/쓰기 최적화**에 대한 이해도가 높아집니다.  
현대 시스템 성능 병목의 상당 부분은 I/O 영역이니, 꼼꼼히 살펴보세요!  
