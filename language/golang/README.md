# Go 언어 정리

## Go 기본 ~ 고급 개념
[Go 기본 ~ 고급 개념](go.md)

## Go STL 사용법 & 예시
[Go 사용법 & 예시](go-stl.md)

## 백엔드 프레임워크

### Gin

* 장점:
    - 가벼운 라우팅 엔진 (httprouter 기반)
    - 빠른 성능과 간단한 API
    - 미들웨어 체인, 그룹 라우팅 등 편의 기능
    - JSON 바인딩, 인증 등에 필요한 기본 기능 제공

* 단점:
    - 완전한 MVC 프레임워크는 아니며, 필요한 기능은 플러그인 형태로 추가해야 함

[Gin](gin.md)

### Echo

* 장점:
    - Gin과 유사하게 성능 좋고, API가 간결
    - 그룹 라우팅, 미들웨어, 템플릿 렌더링 등 지원
    - WebSocket이나 HTTP/2, Server-Sent Events(SSE)도 쉽게 처리 가능

* 단점:
    - 좀 더 "직관적인 API"와 "자동 바인딩"을 원한다면 Gin을 더 선호할 수도 있음

### Fiber

* 장점:
    - Express.js(노드)와 유사한 API 콘셉트
    - 매우 빠른 성능(운영환경에서 높은 RPS 가능)
    - 간단한 미들웨어와 라우팅 설정

* 단점:
    - 아직 Gin, Echo만큼 대중적이지 않을 수 있음
    - Go "net/http"와 약간 다른 구조이므로 적응 필요

### Buffalo

* 장점:
    - "Rails"-like (Ruby on Rails 스타일) 프레임워크
    - 스캐폴딩, ORM(Pop), 프런트엔드 자산 관리(Webpack) 등의 풀스택 지원
    - 빠른 프로토타이핑

* 단점:
    - 비교적 러닝 커브가 있을 수 있음
    - 가볍게 시작하기엔 Gin/Echo에 비해 무겁다고 느껴질 수 있음

### Kratos, go-micro 등 마이크로서비스 프레임워크

* Kratos: Bilibili(중국 스트리밍 기업) 주도로 만든 마이크로서비스 프레임워크
* go-micro: 플러그인 기반으로 디스커버리, 트랜스포트, broker, codec 등을 자유롭게 교체 가능

* 장점:
    - 마이크로서비스 환경에서 필요한 RPC, service registry, config 관리 등을 내장
    - gRPC, ETCD, NATS 등 통합 지원

* 단점:
    - 프레임워크에 대한 의존도 증가
    - 학습 비용


- 정리: 간단한 RESTful API를 빠르게 구축하려면 Gin이나 Echo가 대표적. "Rails처럼 모놀리식 + 스캐폴딩"을 원한다면 Buffalo, 본격적인 마이크로서비스 지향이면 go-micro나 Kratos를 검토해볼 만함.