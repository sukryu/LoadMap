다음은 백엔드 개발자와 클라우드 엔지니어를 위한 TypeScript 기반의 새로운 복잡한 문제입니다. 이번 문제는 지금까지 다뤘던 강의 등록 시스템과는 다른 주제로, 클라우드 리소스를 시뮬레이션하고 관리하는 오케스트레이션 엔진을 구현하는 것입니다.

---

## 문제: 클라우드 리소스 오케스트레이션 시뮬레이터

### 문제 개요
클라우드 환경에서는 가상 머신, 로드 밸런서, 데이터베이스 등 여러 리소스를 프로비저닝(생성)하고 종료하는 작업을 효율적으로 관리해야 합니다. 이번 문제에서는 이러한 클라우드 리소스를 시뮬레이션하는 오케스트레이션 엔진을 TypeScript로 구현합니다. 리소스는 비동기적으로 프로비저닝되며, 일정 확률로 실패하는 상황도 시뮬레이션하여 에러 처리 및 로그 기능을 구현해야 합니다.

### 요구 사항

1. **추상 클래스 `CloudResource`**
   - `CloudResource`라는 추상 클래스를 정의합니다.
   - 공통 속성:
     - `id: string` – 리소스 고유 식별자
     - `name: string` – 리소스 이름
     - `status: string` – 현재 상태 (예: `"provisioning"`, `"running"`, `"stopped"`)
   - 추상 메서드:
     - `provision(): Promise<void>` – 리소스를 프로비저닝하는 비동기 메서드
     - `terminate(): Promise<void>` – 리소스를 종료(terminate)하는 비동기 메서드

2. **리소스 클래스 구현**
   - `VirtualMachine`, `LoadBalancer`, `Database` 클래스를 정의하고, 이들은 모두 `CloudResource`를 상속합니다.
   - 각 클래스별 추가 속성:
     - **VirtualMachine**:  
       - `cpu: number`  
       - `memory: number`
     - **LoadBalancer**:  
       - `algorithm: string` (예: `"round-robin"`, `"least-connections"`)
     - **Database**:  
       - `engine: string` (예: `"MySQL"`, `"PostgreSQL"`)  
       - `storage: number`
   - 각 클래스의 `provision()` 메서드:
     - 비동기적으로 프로비저닝을 시뮬레이션 (예: `setTimeout`을 사용해 딜레이 주기)
     - 일정 확률(예: 20% 정도)로 프로비저닝 실패를 시뮬레이션하여 예외를 발생시키고, 이를 catch하여 로그에 기록
     - 성공하면 상태를 `"running"`으로 변경
   - 각 클래스의 `terminate()` 메서드:
     - 비동기적으로 종료 작업을 수행하며, 상태를 `"stopped"`로 변경

3. **리소스 관리자 (`ResourceManager`) 클래스**
   - 클라우드 리소스들을 관리하는 `ResourceManager` 클래스를 구현합니다.
   - 기능:
     - **리소스 추가:**  
       `addResource(resource: CloudResource): void`
     - **리소스 제거:**  
       `removeResource(id: string): void`
     - **전체 리소스 목록 조회:**  
       `listResources(): CloudResource[]`
     - **모든 리소스 프로비저닝:**  
       `provisionAll(): Promise<void>` – 모든 리소스의 `provision()` 메서드를 병렬로 실행
     - **모든 리소스 종료:**  
       `terminateAll(): Promise<void>` – 모든 리소스의 `terminate()` 메서드를 병렬로 실행

4. **비동기 작업과 예외 처리**
   - 각 리소스의 프로비저닝 및 종료 작업은 `async/await`와 `Promise`를 사용하여 구현합니다.
   - 프로비저닝 작업 중 실패를 시뮬레이션하고, 발생한 예외를 적절히 처리하여 에러 로그를 남깁니다.

5. **메인 프로그램**
   - 메인 함수에서는 다음의 작업을 수행합니다.
     - 여러 종류의 리소스(`VirtualMachine`, `LoadBalancer`, `Database`) 인스턴스를 생성합니다.
     - 생성한 리소스들을 `ResourceManager`에 추가합니다.
     - `provisionAll()`을 호출하여 모든 리소스를 동시에 프로비저닝하고, 각 리소스의 상태를 출력합니다.
     - 이후 `terminateAll()`을 호출하여 모든 리소스를 종료하고, 종료 후 상태를 출력합니다.

6. **(선택 사항) Express 서버 연동**
   - 추가적으로, Express.js를 이용해 간단한 RESTful API 서버를 구축합니다.
   - 제공할 API 엔드포인트:
     - `GET /resources` – 전체 리소스 목록과 상태 조회
     - `POST /resources` – 요청 본문에 담긴 리소스 정보를 바탕으로 새로운 리소스 추가
     - `DELETE /resources/:id` – 특정 리소스 종료 및 삭제
   - API 요청에 따라 리소스의 프로비저닝 및 종료 작업을 수행하고, 결과를 JSON 형식으로 반환합니다.

### 구현 시 고려 사항
- **TypeScript 기능 활용:**  
  인터페이스, 추상 클래스, 제네릭, 그리고 비동기 처리를 위한 `async/await`와 `Promise`를 적극적으로 활용할 것.
- **코드 모듈화:**  
  각 기능(리소스 클래스, 리소스 관리자, API 서버 등)을 별도의 모듈 또는 파일로 분리하여 작성하면 유지보수성이 향상됩니다.
- **로깅 및 에러 처리:**  
  리소스 작업 중 발생할 수 있는 예외 상황에 대해 적절한 에러 메시지를 로그로 남기고, 사용자에게도 의미 있는 메시지를 전달할 것.
- **비동기 처리:**  
  모든 리소스의 프로비저닝/종료 작업은 병렬로 처리하고, 각 작업의 완료 여부에 따라 전체 작업의 성공/실패를 판단할 것.

---

이 문제는 기존의 등록 관리나 강의 시스템과는 다른 주제로, 클라우드 리소스 관리라는 현실 세계의 시나리오를 TypeScript와 Node.js 환경에서 구현해보는 도전 과제입니다. 이를 통해 백엔드 개발자는 물론 클라우드 엔지니어로서도 비동기 작업, 객체 지향 설계, 예외 처리, RESTful API 구현 등 다양한 고급 기술을 통합적으로 연습할 수 있습니다.