# 📂 Docker Compose 학습 개요

> **목표:**  
> - **Docker Compose의 개념과 실무 적용 방법을 학습**한다.  
> - **멀티 컨테이너 애플리케이션을 구축하고 관리하는 방법을 익힌다.**  
> - **기본 개념과 명령어를 학습한 후, 고급 기능 및 실무 활용 전략을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Docker Compose 학습을 기본(Basic)과 고급(Advanced)으로 나누어 진행합니다.**  

```
compose/
├── docker-compose-basics.md  # Docker Compose 기본 개념 및 활용
├── multi-container-apps.md   # 멀티 컨테이너 애플리케이션 구축
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Docker Compose는 여러 개의 컨테이너를 한 번에 정의하고 관리할 수 있는 오케스트레이션 도구입니다.**

- ✅ **서비스(Service):** 컨테이너를 실행하는 단위  
- ✅ **볼륨(Volumes):** 컨테이너 간 데이터 공유 및 지속성을 제공  
- ✅ **네트워크(Networks):** 컨테이너 간 통신을 가능하게 하는 가상 네트워크  
- ✅ **환경 변수(Environment Variables):** 애플리케이션 설정을 위한 변수 관리  

---

## 🏗 **2. 학습 내용**
### 📌 Docker Compose Basics (기본 개념 및 활용)
- **docker-compose.yml 파일 구조 이해**
- **단일 및 멀티 컨테이너 환경 설정**
- **볼륨과 네트워크 설정 및 활용**

### 📌 Multi-Container Applications (멀티 컨테이너 애플리케이션 구축)
- **웹 서버 + 데이터베이스 연동 예제**
- **Docker Compose를 활용한 마이크로서비스 아키텍처 구축**
- **환경 변수 및 시크릿 관리**

---

## 🚀 **3. 실전 예제**
> **Docker Compose를 활용한 간단한 웹 애플리케이션 환경 구성**

```yaml
version: '3.8'
services:
  web:
    image: nginx
    ports:
      - "8080:80"
    networks:
      - mynetwork
  db:
    image: mysql:5.7
    restart: always
    environment:
      MYSQL_ROOT_PASSWORD: example
    volumes:
      - db_data:/var/lib/mysql
    networks:
      - mynetwork
volumes:
  db_data:
networks:
  mynetwork:
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Docker Compose 개념과 구조 이해  
2. **도구 실습** → 기본 및 고급 기능을 실습하며 익히기  
3. **프로젝트 적용** → 실제 프로젝트에서 Docker Compose 활용  
4. **최적화 연구** → 성능, 보안, 네트워크 설정 최적화  

---

## 📚 **5. 추천 리소스**
- **Docker Compose 공식 문서:**  
  - [Docker Compose Docs](https://docs.docker.com/compose/)  

- **Docker Compose 예제 및 템플릿:**  
  - [Awesome Docker](https://github.com/veggiemonk/awesome-docker)  
  - [Docker Samples](https://github.com/docker/awesome-compose)  

---

## ✅ **마무리**
이 문서는 **Docker Compose의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 Docker Compose를 효과적으로 활용하는 방법**을 다룹니다. 🚀