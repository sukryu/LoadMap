# 09_AdvancedTopics

이 디렉토리는 **운영체제** 관련 **최신·고급 주제**들을 다룹니다.  
기본적인 프로세스·메모리·파일시스템·보안·가상화 등을 이해했다면, 한 단계 더 나아가 **실시간 OS, NUMA, 클라우드 네이티브 OS, GPU 스케줄링** 같은 특별한 요구사항 및 최적화 개념도 살펴볼 수 있습니다.

---

## 이 디렉토리에서 다루는 내용

1. **`rtos.md`** (실시간 OS)  
   - **RTOS(Real-Time Operating System)** 개요  
   - 경성 실시간 vs 연성 실시간  
   - 스케줄링 알고리즘(EDF, RM 등)  
   - 임베디드·산업용 장비, 자동차(ECU), 항공(Avionics) 등 활용 사례

2. **`numa.md`** (NUMA 아키텍처)  
   - **NUMA(Non-Uniform Memory Access)**: 멀티소켓 환경에서 노드 간 메모리 접근 시간이 다른 구조  
   - NUMA-aware 스케줄러와 메모리 할당  
   - 리눅스에서 NUMA 설정( `numactl` ) 및 성능 개선 사례

3. **`gpu_scheduling.md`**
   - GPU, GPGPU(General-Purpose GPU)에서의 **스케줄링·리소스 관리**  
   - CUDA, OpenCL, ROCm 등 프레임워크가 OS와 상호작용하는 방식  
   - CPU-GPU 간 메모리 전송(PCIe), 0copy, Unified Memory 모델

4. **`cloud_native_os.md`**
   - **Cloud-native** 환경에 특화된 OS(CoreOS, RancherOS, Bottlerocket 등)  
   - 컨테이너 최적화, 최소화된 베이스 이미지를 사용하는 이유  
   - Immutable Infrastructure, 자동 업데이트, 마이크로커널 트렌드

5. **(추가 주제)**  
   - **MicroVM**(Firecracker, Kata Containers)  
   - **Distributed OS**(분산 운영체제, 클라우드 스케줄링)  
   - **Edge Computing**의 OS 요구사항 등  

(위 파일들은 예시이며, 관심사에 따라 더 나누거나 하나로 합쳐도 좋습니다.)

---

## 학습 포인트

- **RTOS**: 실시간 제약이 있는 환경에서 OS가 시간 결정을 어떻게 보장하고, 태스크 스케줄링을 어떻게 처리하는가  
- **NUMA**: 대규모 서버·HPC 환경에서 멀티소켓 CPU와 메모리 구성을 최적화하는 방식  
- **GPU 스케줄링**: GPU가 일반 계산(딥러닝, HPC 등)에서 CPU와 어떻게 협업하고 스케줄링되는지  
- **클라우드 네이티브 OS**: 컨테이너 중심 아키텍처, 자동화된 업데이트, 최소화된 OS 설계  
- **기타 첨단 주제**: 확장 가능성 (MicroVM, 분산 커널, Edge 등)

---

## 참고 자료

- **RTOS**  
  - [FreeRTOS](https://www.freertos.org/), [Zephyr Project](https://zephyrproject.org/)  
  - “Real-Time Systems” by Jane W. S. Liu
- **NUMA**  
  - [numactl docs](https://man7.org/linux/man-pages/man8/numactl.8.html)  
  - [Linux Kernel NUMA Subsystem](https://github.com/torvalds/linux/tree/master/mm/numa.c)
- **GPU Computing**  
  - [NVIDIA CUDA Docs](https://docs.nvidia.com/cuda/)  
  - [AMD ROCm Docs](https://rocmdocs.amd.com/)  
- **Cloud-native OS**  
  - [CoreOS FAQ](https://coreos.com/docs/), [Bottlerocket (AWS)](https://aws.amazon.com/bottlerocket/)  
  - [RancherOS Docs](https://rancher.com/docs/os/)
  
---

## 앞으로의 계획

- 이 폴더를 통해 **운영체제의 특별한 활용 분야** 및 **최신 흐름**을 살펴봅니다.  
- 이후, **10_Lab_Examples** 폴더에서 **실습과 예제 코드**(미니 OS, 커널 모듈, 부트로더 등)를 통해 이론을 직접 적용해볼 수 있습니다.  
- 전체 로드맵은 [OS/README.md](../README.md)에서 확인하세요.

---

이러한 고급/특수 주제를 공부하면,  
**“단순히 OS를 아는 수준”**을 넘어, 특정 환경(실시간·대규모 서버·클라우드·GPU 등)에서  
운영체제가 어떤 식으로 **문제 해결**을 하는지 더 깊이 이해할 수 있게 됩니다.  
흥미롭고 도전적인 영역이니, 재미있게 학습해 보세요!
