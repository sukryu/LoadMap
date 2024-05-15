# 웹의 기초 #

* 인터넷과 웹
 - 인터넷: 전 세계적으로 연결된 컴퓨터 네트워크
 - 웹(World Wide Web): 인터넷을 기반으로 동작하는 정보 시스템.

* HTTP(Hypertext transfer Protocol)
  - 웹 브라우저와 웹 서버 간의 통신 프로토콜
  - 클라이언트 - 서버 모델을 기반으로 동작
  - 요청(Request)와 응답(Response)으로 구성.
  - HTTP 메서드:
    - GET,
    - POST,
    - PUT,
    - DELETE
    - etc..

* URL(Uniform Resource Locator)
  - 웹 상의 자원의 위치를 나타내는 주소.
  - 구성 요소: 프로토콜, 도메인 이름, 포트번호, 경로, 쿼리 문자열, 프래그먼트 식별자.

* HTML(Hypertext Markup Language)
  - 웹 페이지의 구조와 내용을 정의하는 마크업 언어.
  - 태그를 사용하여 문서의 구조를 표현.
  - 시맨틱 태그를 사용하여 의미론적 구조를 표현.

* CSS(Cascading Style Sheets)
  - HTML 문서의 스타일과 레이아웃을 정의하는 스타일시트 언어.
  - 선택자를 사용하여 HTML 요소에 스타일을 적용.
  - 박스 모델, 플렉스 박스, 그리드 등의 레이아웃 기능을 제공.

* JavaScript
  - 웹 페이지에 동적인 기능을 추가하는 프로그래밍 언어.
  - 브라우저에서 실행되며, DOM(Document Object Model)을 조작.
  - 이벤트 처리, 비동기 통신, 애니메이션 등의 기능 제공.

* 웹 브라우저
  - 사용자가 웹 페이지를 탐색하고 상호작용하는 소프트웨어 애플리케이션
  - 렌더링 엔진을 사용하여 HTML, CSS, JavaScript를 해석하고 화면에 표시
  - 주요 웹 브라우저: Chrome, Firefox, Safari, Edge등


# 웹의 고급 내용 #

* 웹 서버
  - HTTP 요청을 처리하고 응답을 반환하는 소프트웨어.
  - 정적 파일 제공, 서버 사이드 프로그래밍 언어 실행.
  - 데이터베이스 연동 등의 기능 제공.
  - 주요 웹 서버: Apache, Nginx, IIS 등.

* 웹 서버에서 실행되는 프로그래밍 언어와 프레임워크
  - 동적인 웹 페이지 생성
  - 데이터베이스 조작
  - 비즈니스 로직 처리 등의 기능 제공
  - 주요 서버 사이드 프로그래밍 언어: PHP, Python, Ruby, Java, Node.js 등

* 데이터베이스
  - 웹 애플리케이션의 데이터를 저장하고 관리하는 시스템
  - 관계형 데이터베이스(RDBMS), NoSQL 데이터베이스로 분류
  - 주요 데이터베이스: MySQL, PostgreSQL, MongoDB, Redis 등

* REST(Representational State Transfer)API
  - 웹 서비스를 구축하기 위한 아키텍처 스타일
  - 자원(Resource), HTTP메서드, 표현(Representation)등의 개념 사용.
  - 상태 없는 (Stateless)통신, 캐시 가능(Cacheable), 계층화(Layered System)등의 특징.

* 웹 보안
  - 웹 애플리케이션의 보안을 위협하는 취약점과 공격 유형
  - XSS(Cross-Site Scripting)
  - CSRF(Cross-Site Request Forgery)
  - SQL Injection
  - 보안 대책:
    - 입력 유효성 검사
    - 출력 인코딩
    - 안전한 세션 관리
    - HTTPS 사용

* 웹 성능 최적화
  - 웹 페이지의 로딩 속도와 사용자 경험을 개선하는 기술
    - 최소화(Minification)
    - 압축(Compression)
    - 캐싱(Caching)
    - CDN(Content Delivery Network)
  - 성능 측정 도구:
    - Google Lighthouse, WebPageTest등

* 프론트엔드 프레임워크
  - 웹 애플레이션의 사용자 인터페이스를 구축하기 위한 라이브러리와 도구
    - 컴포넌트 기반 개발
    - 상태 관리
    - 라우팅 등의 기능 제공.

  - 주요 프론트엔드 프레임워크
    - React
    - Angular
    - Vue.js

* 반응형 웹 디자인(Responsive Web Design)
  - 다양한 화면 크기와 디바이스에 최적화된 웹 페이지를 설계하는 기술.
    - 미디어 쿼리, 유연한 그리드 레이아웃, 유동적인 이미지 사용

* 웹 접근성(Web Accessibility)
  - 장애인, 고령자 등 모든 사용자가 웹 콘텐츠에 접근하고 사용할 수 있도록 보장하는 것
    - 시맨틱 마크업
    - 키보드 네비게이션
    - 대체 텍스트 제공

* PWA(Progressive Web Apps)
  - 웹과 네이티브 앱의 장점을 결합한 웹 애플리케이션
    - 오프라인 동작,
    - 푸시 알림
    - 홈 화면 설치 등의 기능 제공
      - Service Worker
      - Web App Manifest
      - HTTPS 등의 기술 사용.
