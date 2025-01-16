# 08_Security_Virtualization

이 디렉토리는 **운영체제 보안**과 **가상화**에 대해 집중적으로 학습합니다.  
OS가 어떤 메커니즘을 통해 시스템 자원과 사용자 데이터를 보호하는지, 그리고 가상머신·컨테이너 등 가상화 기술이 어떻게 OS 위에서 동작하는지를 살펴봅니다.

---

## 이 디렉토리에서 다루는 내용

1. **`security.md`**  
   - **접근 제어(Access Control)**: 인증(Authentication), 인가(Authorization)  
   - **리눅스 보안 모듈(LSM)**: SELinux, AppArmor 등 Mandatory Access Control(MAC) 모델  
   - **Windows UAC**, 유닉스 계열 SUID/SGID, RBAC(Role-Based Access Control)  
   - **보안 위협(멀웨어, 루트킷, 권한 상승 등)**과 대응 기법(시스템 콜 필터링, seccomp 등)

2. **`virtualization.md`**  
   - **가상화 개념**: 전가상화(Full Virtualization), 반가상화(Paravirtualization)  
   - **하이퍼바이저** (Type 1, Type 2), 예: KVM, VMware ESXi, Hyper-V  
   - **컨테이너**: 리눅스 네임스페이스(Namespaces), cgroups, 도커(Docker) 아키텍처  
   - **가상화 vs 컨테이너**: 차이점과 장단점

3. **`kernel_security_features.md`**
   - **ASLR(Address Space Layout Randomization)**, NX-Bit(Execute Disable), Stack Protector 등  
   - 커널 레벨 방어 기법, 모듈 서명, Secure Boot 연계

4. **`cloud_native_sec.md`**
   - 클라우드 시대에 요구되는 OS 보안: “Immutable Infrastructure”, “Zero Trust” 개념  
   - Kubernetes에서 컨테이너 보안을 어떻게 다루는지(네트워크 정책, Pod Security 등)

---

## 학습 포인트

- **OS 보안 기초**  
  - 권한 모델(Discretionary/Mandatory Access Control), 사용자/그룹/프로세스 권한 관리  
  - 공격 벡터(멀웨어, 루트킷 등)와 OS 차원에서의 방어 기법
- **가상화 기술**  
  - CPU의 하드웨어 가상화 지원(인텔 VT-x, AMD-V)  
  - 하이퍼바이저 구조(Type 1 vs Type 2)와 주요 제품(KVM, VMware, Hyper-V)  
  - 컨테이너(Docker, LXC) 작동 원리 - 네임스페이스, cgroups, 오버레이 FS
- **컨테이너 vs VM**  
  - 리소스 격리, 성능, 보안, 운영 편의성 측면에서의 비교
- **보안 확장**  
  - Secure Boot, TPM(Trusted Platform Module), UEFI 보안 체인

---

## 참고 자료

- [Linux Security Modules (LSM)](https://www.kernel.org/doc/html/latest/admin-guide/LSM/index.html)  
- [SELinux Docs](https://github.com/SELinuxProject) / [AppArmor Docs](https://gitlab.com/apparmor/apparmor/-/wikis/home)  
- [Docker 공식 문서](https://docs.docker.com/)  
- [KVM (Kernel-based Virtual Machine)](https://www.linux-kvm.org/page/Main_Page)  
- [Intel VT-x/AMD-V 설명 (Intel/AMD Developer Manuals)](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)

---

## 앞으로의 계획

- 이 폴더에서 **OS 보안 메커니즘** 및 **가상화(하이퍼바이저, 컨테이너)** 개념을 체계적으로 익힙니다.  
- 이후, **09_AdvancedTopics** 폴더에서 **실시간 OS, NUMA, 클라우드 OS** 등 고급 주제를 다룰 예정입니다.  
- 전체 로드맵은 [OS/README.md](../README.md)에서 확인하세요.

---

보안과 가상화는 현대 컴퓨팅 환경에서  
**“시스템 안정성, 분산·클라우드 인프라”**를 구성하는 핵심 기술입니다.  
꼼꼼히 학습하여 안전하고 유연한 환경을 설계해 보세요! 
