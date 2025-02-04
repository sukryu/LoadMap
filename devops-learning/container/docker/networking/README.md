# 📂 Docker Networking 학습 개요

> **목표:**  
> - **Docker 네트워킹의 개념과 실무 적용 방법을 학습**한다.  
> - **컨테이너 간 통신을 구성하고, 네트워크 드라이버를 활용하는 방법을 익힌다.**  
> - **기본 개념과 명령어를 학습한 후, 고급 기능 및 실무 활용 전략을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Docker 네트워킹 학습을 기본(Basic)과 고급(Advanced)으로 나누어 진행합니다.**  

```
networking/
├── docker-networking-basics.md # Docker 네트워크 개요 및 설정
├── advanced-networking.md      # 고급 네트워크 구성
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Docker 네트워크는 컨테이너 간의 통신을 가능하게 하며, 다양한 네트워크 드라이버를 제공합니다.**

- ✅ **Bridge Network:** 기본적으로 컨테이너 간 통신을 허용하는 네트워크  
- ✅ **Host Network:** 컨테이너가 호스트 네트워크와 동일한 네트워크 인터페이스를 공유  
- ✅ **Overlay Network:** 여러 Docker 호스트 간 컨테이너 네트워크를 연결하는 방식  
- ✅ **Macvlan Network:** 컨테이너가 물리적 네트워크 인터페이스를 직접 사용하는 방식  
- ✅ **None Network:** 네트워크가 비활성화된 컨테이너 환경  

---

## 🏗 **2. 학습 내용**
### 📌 Docker Networking Basics (기본 개념 및 활용)
- **Docker 네트워크의 기본 개념 이해**
- **Bridge, Host, None 네트워크 드라이버 활용**
- **컨테이너 간 통신 설정 및 네트워크 구성**

### 📌 Advanced Networking (고급 네트워크 설정)
- **Overlay 네트워크를 활용한 분산 환경 구축**
- **Macvlan을 이용한 물리 네트워크 통합**
- **Docker Compose를 활용한 네트워크 설정 자동화**

---

## 🚀 **3. 실전 예제**
> **Docker 네트워크를 활용하여 컨테이너 간 통신을 설정하는 실습**

```sh
# Bridge 네트워크 생성
docker network create my_bridge_network

# 네트워크에 연결된 컨테이너 실행
docker run -d --name container1 --network my_bridge_network nginx

docker run -d --name container2 --network my_bridge_network alpine sleep 3600

# 컨테이너 간 통신 테스트
docker exec -it container2 ping container1
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Docker 네트워크 개념과 구조 이해  
2. **도구 실습** → 기본 및 고급 네트워크 구성 실습  
3. **프로젝트 적용** → 실제 프로젝트에서 Docker 네트워크 활용  
4. **최적화 연구** → 성능, 보안, 네트워크 설정 최적화  

---

## 📚 **5. 추천 리소스**
- **Docker 네트워크 공식 문서:**  
  - [Docker Networking Docs](https://docs.docker.com/network/)  

- **Docker 네트워크 예제 및 템플릿:**  
  - [Awesome Docker](https://github.com/veggiemonk/awesome-docker)  
  - [Docker Samples](https://github.com/docker/docker-samples)  

---

## ✅ **마무리**
이 문서는 **Docker 네트워크의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 Docker 네트워크를 효과적으로 활용하는 방법**을 다룹니다. 🚀

