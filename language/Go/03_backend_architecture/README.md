# 03 Backend Architecture 🏗️

이 디렉토리는 **백엔드 아키텍처 설계**를 다룹니다.  
여기에서는 RESTful API 디자인, gRPC를 활용한 서비스 간 통신, 마이크로서비스 설계 패턴, 그리고 OAuth 2.0 및 JWT 기반의 인증/인가 시스템에 대해 심도 있게 학습할 수 있습니다.

---

## 디렉토리 구조 📁

```plaintext
03-backend-architecture/
├── rest-api/        # RESTful API 설계 및 Best Practice 예제
├── grpc/            # gRPC 활용, 프로토콜 버퍼 및 게이트웨이 설정
├── microservices/   # 마이크로서비스 설계 패턴 및 통신 전략
└── authentication/  # API 인증/인가 (OAuth 2.0, JWT, RBAC 등)
```

- **rest-api/**: HTTP 메서드, URL 설계, 상태 코드, 에러 핸들링 등 REST API의 기본 원칙과 모범 사례를 다룹니다.
- **grpc/**: gRPC의 핵심 개념, Protocol Buffers를 이용한 서비스 정의, 스트리밍 및 양방향 통신 예제 등을 포함합니다.
- **microservices/**: 단일 모놀리식 애플리케이션을 분할하여 확장 가능하고 유지보수하기 쉬운 마이크로서비스 아키텍처로 전환하는 방법을 소개합니다.
- **authentication/**: 안전한 API 인증과 인가를 위해 OAuth 2.0, JWT, RBAC 등의 보안 모델과 실제 구현 방법을 다룹니다.

---

## 학습 목표 🎯

- **RESTful API 디자인**:  
  - API의 핵심 원칙, HTTP 메서드, URL 설계, 상태 코드와 에러 처리 기법을 이해합니다.
  
- **gRPC 활용**:  
  - gRPC와 Protocol Buffers를 통해 강타입의, 효율적인 서비스 간 통신 방식을 구현하는 방법을 배웁니다.
  
- **마이크로서비스 설계**:  
  - 서비스 분리, API 게이트웨이, 서비스 간 통신, 장애 격리 및 스케일 아웃 전략 등 마이크로서비스의 핵심 패턴을 학습합니다.
  
- **인증/인가 시스템**:  
  - OAuth 2.0, JWT 기반의 토큰 발급과 검증, RBAC/ABAC 설계 등을 통해 안전한 백엔드 시스템 구축 방법을 익힙니다.

---

## 학습 방법 및 팁 💡

- **실습 중심 학습**: 각 서브 디렉토리 내의 예제 코드와 실습 자료를 직접 실행해 보며, 구현 원리와 결과를 확인하세요.
- **비교 분석**: REST와 gRPC, 그리고 모놀리식과 마이크로서비스 아키텍처의 차이와 장단점을 비교하여 이해도를 높이세요.
- **보안 강화**: 인증/인가 부분에서는 실무에서 발생할 수 있는 보안 이슈와 모범 사례를 꼼꼼히 확인해 보세요.
- **참고 자료 활용**: 각 주제별 권장 문서와 링크를 통해 더 깊이 있는 학습 자료에 접근하세요.

---

## 시작하기 🚀

1. **프로젝트 클론 및 디렉토리 이동**
   ```bash
   git clone https://github.com/your-username/go-backend-roadmap.git
   cd go-backend-roadmap/03-backend-architecture
   ```

2. **예제 코드 실행**
   - REST API 예제:
     ```bash
     cd rest-api
     go run main.go
     ```
   - gRPC 예제:
     ```bash
     cd ../grpc
     go run server.go
     ```
   - 마이크로서비스 및 인증 예제도 각 폴더 내의 README를 참고하세요.

---

## 추가 자료 & 참고 링크 📚

- [RESTful API Design Guide](https://restfulapi.net/)
- [gRPC Official Documentation](https://grpc.io/docs/)
- [Microservices Patterns by Martin Fowler](https://martinfowler.com/articles/microservices.html)
- [OAuth 2.0 and OpenID Connect](https://oauth.net/2/)

---

Go 백엔드 아키텍처를 잘 이해하고 적용하면, 실제 서비스 환경에서 확장 가능하고 안전한 시스템을 설계할 수 있습니다.  
Happy Building! 🚀