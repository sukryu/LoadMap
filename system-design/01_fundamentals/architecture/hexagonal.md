# Hexagonal Architecture

이 문서에서는 **헥사고날 아키텍처**의 기본 개념과 특징, 발생할 수 있는 문제 상황 및 해결 방안, 실제 구현 방법과 베스트 프랙티스, 그리고 추가 고려 사항을 다룹니다.

---

## 1. 개념 개요

헥사고날 아키텍처는 **포트와 어댑터(Ports & Adapters)** 패턴으로도 알려져 있으며, 애플리케이션의 비즈니스 로직(도메인)을 외부의 입출력(사용자 인터페이스, 데이터베이스, 메시지 브로커 등)과 분리하여, 내부와 외부의 의존성을 느슨하게 만드는 설계 방식입니다.

- **정의:**  
  - 애플리케이션의 **핵심 비즈니스 로직**(도메인)이 중심에 위치하며, 외부와의 상호작용은 **포트**(인터페이스)를 통해 이루어지고, 이 포트를 구현하는 **어댑터**가 외부 시스템과의 연결 역할을 합니다.
  
- **특징:**  
  - **비즈니스 로직의 독립성:**  
    - 핵심 도메인 로직은 외부 시스템의 변화에 영향을 받지 않습니다.
  - **유연한 확장성:**  
    - 새로운 외부 인터페이스(예: 웹, CLI, 메시징 시스템 등)를 추가할 때, 도메인 로직을 변경하지 않고 어댑터만 구현하면 됩니다.
  - **테스트 용이성:**  
    - 도메인 로직을 외부 의존성으로부터 분리하여 단위 테스트를 수행하기 용이합니다.
  - **유지보수:**  
    - 각 어댑터는 독립적으로 관리되므로, 변경 사항이 도메인 로직에 미치는 영향을 최소화할 수 있습니다.

---

## 2. 문제 상황과 해결 방안

### 2.1. 문제 상황

- **외부 시스템 의존성:**  
  - 기존의 애플리케이션은 데이터베이스, 웹 프레임워크 등 외부 시스템에 비즈니스 로직이 섞여 있어, 변경이나 확장이 어려운 문제가 발생할 수 있습니다.
  
- **테스트 어려움:**  
  - 비즈니스 로직이 외부 라이브러리나 인프라에 의존하면, 단위 테스트가 복잡해지고 모킹(mocking) 작업이 증가합니다.
  
- **변경 관리:**  
  - 사용자 인터페이스나 데이터 접근 방식이 변경될 때, 도메인 로직과의 결합도로 인해 전체 애플리케이션 변경이 필요할 수 있습니다.

### 2.2. 해결 방안

- **포트와 어댑터 분리:**  
  - 도메인 로직(핵심 비즈니스 규칙)과 외부 시스템 간의 인터페이스(포트)를 명확히 구분하여, 외부 변경이 내부에 미치는 영향을 최소화합니다.
  
- **의존성 역전 원칙 적용:**  
  - 상위 계층(도메인)이 하위 계층(인프라)에 직접 의존하지 않고, 추상화된 인터페이스(포트)를 통해 의존성을 관리합니다.
  
- **테스트 환경 분리:**  
  - 어댑터를 모킹(mocking)하거나 별도의 테스트 더블(test double)을 사용하여, 도메인 로직을 독립적으로 테스트할 수 있습니다.

---

## 3. 구체적 구현 방법 및 베스트 프랙티스

### 3.1. 기본 디렉토리 구조 예시

아래는 Node.js 기반의 헥사고날 아키텍처 예시 구조입니다.

```plaintext
hexagonal-app/
├── src/
│   ├── domain/                # 핵심 비즈니스 로직 (엔티티, 도메인 서비스)
│   │   ├── user.js            # 도메인 모델 예시
│   │   └── userService.js     # 도메인 서비스 예시
│   ├── ports/                 # 도메인과 외부 시스템 간의 인터페이스 (포트)
│   │   └── userRepositoryPort.js  # 사용자 저장소 인터페이스
│   ├── adapters/              # 포트를 구현하는 어댑터 (데이터베이스, API 등)
│   │   └── userRepository.js  # 사용자 저장소 어댑터 (인메모리 또는 DB 연동)
│   ├── interfaces/            # 외부와의 인터페이스 (웹, CLI 등)
│   │   └── http/
│   │       ├── controllers/
│   │       │   └── userController.js
│   │       └── routes/
│   │           └── userRoutes.js
│   ├── app.js                 # 애플리케이션 초기화
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

*src/domain/userService.js*
```javascript
// userService는 포트(인터페이스)를 통해 외부 저장소와 상호작용합니다.
const createUser = async (userData, userRepository) => {
  // 비즈니스 로직: 간단한 데이터 검증
  if (!userData.name || !userData.email) {
    throw new Error('Invalid user data');
  }
  // 도메인 모델 생성
  const id = Date.now().toString();
  const User = require('./user');
  const user = new User(id, userData.name, userData.email);
  // 포트를 통해 외부 저장소에 사용자 저장
  await userRepository.saveUser(user);
  return user;
};

const getUser = async (id, userRepository) => {
  return await userRepository.findUserById(id);
};

module.exports = { createUser, getUser };
```

#### 3.2.2. 포트 정의

*src/ports/userRepositoryPort.js*
```javascript
// 사용자 저장소 인터페이스 (포트)
// 실제 구현은 어댑터에서 제공됨
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

#### 3.2.3. 어댑터 구현

*src/adapters/userRepository.js*
```javascript
// 간단한 인메모리 저장소 구현 예시
const UserRepositoryPort = require('../ports/userRepositoryPort');

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

#### 3.2.4. 외부 인터페이스 (HTTP API)

*src/interfaces/http/controllers/userController.js*
```javascript
const userService = require('../../../domain/userService');
const InMemoryUserRepository = require('../../../adapters/userRepository');
const userRepository = new InMemoryUserRepository();

const createUser = async (req, res) => {
  try {
    const user = await userService.createUser(req.body, userRepository);
    res.status(201).json(user);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
};

const getUser = async (req, res) => {
  try {
    const user = await userService.getUser(req.params.id, userRepository);
    if (!user) {
      return res.status(404).json({ message: 'User not found' });
    }
    res.json(user);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
};

module.exports = { createUser, getUser };
```

*src/interfaces/http/routes/userRoutes.js*
```javascript
const express = require('express');
const { createUser, getUser } = require('../controllers/userController');

const router = express.Router();

router.post('/', createUser);
router.get('/:id', getUser);

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
  console.log(`Hexagonal app is running on port ${PORT}`);
});
```

### 베스트 프랙티스

- **포트와 어댑터의 명확한 분리:**  
  - 도메인 로직은 외부 시스템의 변화에 영향을 받지 않도록, 포트를 통한 인터페이스를 정의하고 어댑터에서 구체적인 구현을 제공합니다.
  
- **의존성 역전 원칙 준수:**  
  - 상위 계층(도메인)이 하위 계층(어댑터)에 직접 의존하지 않고, 추상화된 포트를 통해 의존성을 관리합니다.
  
- **테스트 용이성:**  
  - 도메인 로직을 독립적으로 단위 테스트할 수 있으며, 어댑터는 모킹(mocking)하여 통합 테스트를 진행할 수 있습니다.
  
- **유연한 확장:**  
  - 새로운 외부 인터페이스(예: 다른 데이터베이스, 메시지 브로커 등)를 도입할 때, 기존 도메인 로직을 변경하지 않고 추가 어댑터를 구현할 수 있습니다.

---

## 4. 추가 고려 사항

- **버전 관리와 이벤트 스키마:**  
  - 어댑터가 제공하는 인터페이스(포트)의 변경이 도메인 로직에 영향을 주지 않도록, 인터페이스 정의와 버전 관리를 철저히 해야 합니다.
  
- **성능 최적화:**  
  - 어댑터에서 발생할 수 있는 병목 현상(예: 데이터베이스 연결, 네트워크 지연 등)을 모니터링하고 최적화합니다.
  
- **보안:**  
  - 외부 시스템과의 통신에 있어 적절한 인증, 암호화, 입력 검증 등의 보안 메커니즘을 도입합니다.
  
- **운영 및 모니터링:**  
  - 전체 시스템의 로그, 성능, 에러를 모니터링할 수 있는 관찰성 도구를 활용하여, 장애 상황에 신속하게 대응할 수 있도록 합니다.

---

## 5. 결론

헥사고날 아키텍처는 **비즈니스 도메인 로직과 외부 시스템 간의 결합을 느슨하게 하여**  
- 도메인 로직의 독립성과 테스트 용이성을 보장하고,  
- 외부 인터페이스 변경 시에도 비즈니스 규칙을 그대로 유지할 수 있도록 도와줍니다.

**장점:**  
- 비즈니스 로직과 인프라의 분리로 인해 유지보수와 확장이 용이합니다.  
- 각 어댑터를 독립적으로 교체하거나 추가할 수 있어, 다양한 기술 스택을 활용할 수 있습니다.

**단점:**  
- 초기 설계 및 구현 시, 포트와 어댑터를 명확히 정의하는 작업이 추가되므로 복잡도가 증가할 수 있습니다.  
- 전체 시스템의 아키텍처를 이해하는 데 추가적인 학습 비용이 발생할 수 있습니다.

따라서, 헥사고날 아키텍처는 장기적인 유지보수와 확장성을 고려하는 엔터프라이즈 애플리케이션에서 매우 유용하며, 초기 설계 단계에서 체계적인 구조를 마련하는 것이 중요합니다.