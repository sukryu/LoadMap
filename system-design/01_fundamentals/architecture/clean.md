# Clean Architecture

이 문서에서는 **클린 아키텍처**의 기본 개념과 특징, 발생할 수 있는 문제 상황 및 해결 방안, 실제 구현 방법과 베스트 프랙티스, 추가 고려 사항을 다룹니다.

---

## 1. 개념 개요

클린 아키텍처는 **도메인 중심 설계**와 **의존성 역전 원칙(Dependency Inversion Principle)** 을 핵심으로 하여, 애플리케이션의 핵심 비즈니스 로직(도메인)이 외부의 변화(데이터베이스, UI, 프레임워크 등)에 영향을 받지 않도록 계층을 분리하는 설계 방식입니다.

- **정의:**  
  - 애플리케이션을 여러 계층(예: 엔티티, 유스케이스, 인터페이스, 프레임워크)으로 분리하여, **내부 계층은 외부 계층에 의존하지 않고** 추상화된 인터페이스를 통해 상호작용하도록 설계합니다.
  
- **특징:**  
  - **도메인 중심:** 핵심 비즈니스 로직(엔티티, 도메인 서비스)을 가장 내부에 배치하여, 시스템의 핵심 가치를 보호합니다.
  - **의존성 역전:** 외부의 세부 사항(프레임워크, 데이터베이스 등)에 대한 의존성을 제거하고, 상위 계층이 하위 계층의 구체적인 구현에 의존하지 않도록 합니다.
  - **테스트 용이성:** 도메인 로직을 외부 의존성으로부터 분리하여, 단위 테스트 및 통합 테스트 수행이 용이합니다.
  - **유지보수 및 확장성:** 각 계층의 역할이 명확하므로, 변경 사항이 특정 계층에 국한되고 전체 시스템에 미치는 영향을 최소화합니다.

---

## 2. 문제 상황과 해결 방안

### 2.1. 문제 상황

- **외부 의존성 증가:**  
  - 기존 애플리케이션에서는 UI, 데이터베이스, 프레임워크 등 외부 기술 요소에 비즈니스 로직이 섞여 있어, 외부 변경에 따른 도메인 로직의 손상이 발생할 수 있습니다.
  
- **테스트 어려움:**  
  - 비즈니스 로직과 외부 인프라가 강하게 결합되어 있어, 단위 테스트와 통합 테스트 수행 시 모킹 및 설정 비용이 증가합니다.
  
- **유지보수 및 확장성 제약:**  
  - 도메인 로직과 인프라스트럭처 코드가 뒤섞이면, 시스템 변경 시 어느 부분에 영향을 미치는지 파악하기 어렵고, 리팩토링이 힘들어집니다.

### 2.2. 해결 방안

- **계층 분리와 명확한 역할 정의:**  
  - 도메인(엔티티), 유스케이스(애플리케이션 서비스), 인터페이스(어댑터), 프레임워크/인프라 등으로 계층을 분리하여, 각 계층의 책임을 명확히 합니다.
  
- **의존성 역전 원칙 적용:**  
  - 내부 계층(도메인, 유스케이스)은 외부 계층의 구체적 구현에 의존하지 않고, 추상화된 인터페이스(포트)를 통해 상호작용하도록 설계합니다.
  
- **테스트와 문서화 강화:**  
  - 각 계층을 독립적으로 테스트할 수 있도록 단위 테스트를 작성하고, 계층 간 인터페이스와 역할에 대해 문서화를 철저히 합니다.

---

## 3. 구체적 구현 방법 및 베스트 프랙티스

### 3.1. 기본 디렉토리 구조 예시

아래는 Node.js를 활용한 클린 아키텍처 예시 구조입니다.

```plaintext
clean-architecture-app/
├── src/
│   ├── domain/                # 핵심 비즈니스 로직 (엔티티, 도메인 서비스)
│   │   ├── user.js            # 사용자 엔티티
│   │   └── userDomainService.js  # 도메인 서비스 (비즈니스 규칙)
│   ├── usecases/              # 유스케이스 (애플리케이션 서비스)
│   │   └── userUseCase.js     # 사용자 관련 유스케이스
│   ├── ports/                 # 추상화된 인터페이스 (포트)
│   │   └── userRepositoryPort.js  # 사용자 저장소 인터페이스
│   ├── adapters/              # 포트를 구현하는 어댑터 (DB, 외부 API 등)
│   │   └── userRepository.js  # 사용자 저장소 어댑터 (인메모리 또는 DB 연동)
│   ├── interfaces/            # 외부 인터페이스 (웹, CLI, API 등)
│   │   └── http/
│   │       ├── controllers/
│   │       │   └── userController.js
│   │       └── routes/
│   │           └── userRoutes.js
│   ├── config/                # 설정 파일 (DB, 서버 설정 등)
│   └── app.js                 # 애플리케이션 초기화
├── tests/                     # 단위 및 통합 테스트
├── package.json
└── README.md
```

### 3.2. 코드 예시

#### 3.2.1. 도메인 계층

*src/domain/user.js*
```javascript
class User {
  constructor(id, name, email) {
    this.id = id;
    this.name = name;
    this.email = email;
  }
}

module.exports = User;
```

*src/domain/userDomainService.js*
```javascript
// 도메인 서비스: 비즈니스 규칙과 정책 구현
const validateUser = (user) => {
  if (!user.name || !user.email) {
    throw new Error('User must have a name and email');
  }
  // 추가 비즈니스 검증 로직 구현
};

module.exports = { validateUser };
```

#### 3.2.2. 유스케이스 계층

*src/usecases/userUseCase.js*
```javascript
const { validateUser } = require('../domain/userDomainService');
const User = require('../domain/user');

// 유스케이스: 사용자 생성 및 조회 로직 구현 (포트를 통해 외부 저장소와 상호작용)
const createUser = async (userData, userRepository) => {
  // 도메인 서비스로 비즈니스 규칙 검증
  const tempUser = new User(Date.now().toString(), userData.name, userData.email);
  validateUser(tempUser);
  
  // 저장소 포트를 통해 사용자 저장
  await userRepository.saveUser(tempUser);
  return tempUser;
};

const getUser = async (id, userRepository) => {
  return await userRepository.findUserById(id);
};

module.exports = { createUser, getUser };
```

#### 3.2.3. 포트 정의

*src/ports/userRepositoryPort.js*
```javascript
// 사용자 저장소 인터페이스 (포트)
class UserRepositoryPort {
  async saveUser(user) {
    throw new Error('Not implemented');
  }

  async findUserById(id) {
    throw new Error('Not implemented');
  }
}

module.exports = UserRepositoryPort;
```

#### 3.2.4. 어댑터 구현

*src/adapters/userRepository.js*
```javascript
const UserRepositoryPort = require('../ports/userRepositoryPort');

// 간단한 인메모리 저장소 어댑터 예시
class InMemoryUserRepository extends UserRepositoryPort {
  constructor() {
    super();
    this.users = new Map();
  }

  async saveUser(user) {
    this.users.set(user.id, user);
  }

  async findUserById(id) {
    return this.users.get(id);
  }
}

module.exports = InMemoryUserRepository;
```

#### 3.2.5. 외부 인터페이스 (HTTP API)

*src/interfaces/http/controllers/userController.js*
```javascript
const { createUser, getUser } = require('../../../usecases/userUseCase');
const InMemoryUserRepository = require('../../../adapters/userRepository');
const userRepository = new InMemoryUserRepository();

const createUserController = async (req, res) => {
  try {
    const user = await createUser(req.body, userRepository);
    res.status(201).json(user);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
};

const getUserController = async (req, res) => {
  try {
    const user = await getUser(req.params.id, userRepository);
    if (!user) {
      return res.status(404).json({ message: 'User not found' });
    }
    res.json(user);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
};

module.exports = { createUserController, getUserController };
```

*src/interfaces/http/routes/userRoutes.js*
```javascript
const express = require('express');
const { createUserController, getUserController } = require('../controllers/userController');

const router = express.Router();

router.post('/', createUserController);
router.get('/:id', getUserController);

module.exports = router;
```

*src/app.js*
```javascript
const express = require('express');
const userRoutes = require('./interfaces/http/routes/userRoutes');

const app = express();
app.use(express.json());

app.use('/api/users', userRoutes);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Clean Architecture app is running on port ${PORT}`);
});
```

### 베스트 프랙티스

- **계층 분리와 의존성 역전:**  
  - 도메인, 유스케이스, 포트, 어댑터, 인터페이스 계층을 명확하게 분리하여, 각 계층이 독립적으로 관리되고 변경되어도 다른 계층에 영향을 주지 않도록 합니다.
  
- **테스트 용이성:**  
  - 도메인 및 유스케이스 계층은 외부 의존성이 제거되어 단위 테스트가 용이하며, 어댑터는 모킹(mocking)하여 통합 테스트를 진행합니다.
  
- **인터페이스 문서화:**  
  - 각 계층 간의 인터페이스(포트)를 명확하게 문서화하고, 버전 관리를 통해 변경 이력을 관리합니다.
  
- **코드 리뷰와 지속적 리팩토링:**  
  - 정기적인 코드 리뷰와 리팩토링을 통해 계층 간 결합도를 낮추고, 유지보수성을 향상시킵니다.

---

## 4. 추가 고려 사항

- **확장성:**  
  - 클린 아키텍처는 초기 설계 시 부담이 있을 수 있으나, 시스템 규모가 커지더라도 도메인 로직 보호와 확장이 용이합니다.
  
- **보안:**  
  - 각 계층에서 적절한 입력 검증, 인증 및 권한 관리, 데이터 암호화 등의 보안 메커니즘을 적용하여, 외부 공격에 대비합니다.
  
- **운영 및 모니터링:**  
  - 로그, 모니터링, 에러 추적 시스템을 통해 각 계층의 상태를 지속적으로 관찰하고, 장애 발생 시 신속하게 대응할 수 있도록 설계합니다.

---

## 5. 결론

클린 아키텍처는 **도메인 중심 설계**와 **의존성 역전 원칙**을 바탕으로, 비즈니스 로직과 외부 인프라 간의 결합을 최소화하여, 유지보수와 확장성이 뛰어난 시스템을 구현할 수 있도록 돕습니다.

- **장점:**  
  - 핵심 비즈니스 로직이 외부 변화에 영향을 받지 않아, 안정적이고 테스트 가능한 시스템을 구축할 수 있습니다.  
  - 각 계층이 명확히 분리되어 있어, 기능 확장이나 변경 시 영향을 최소화할 수 있습니다.
  
- **단점:**  
  - 초기 설계 및 구현 단계에서 계층 분리와 인터페이스 정의 등 추가 작업이 필요하여 복잡도가 증가할 수 있습니다.
  
따라서, 클린 아키텍처는 장기적인 유지보수와 확장성을 고려하는 엔터프라이즈 애플리케이션에서 매우 유용하며, 초기 설계 단계에서 체계적인 구조를 마련하는 것이 중요합니다.