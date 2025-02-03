# 캐싱 전략 (Caching Strategy)

---

## 1. 개념 개요

캐싱 전략은 **데이터 접근 속도를 향상시키고, 시스템 부하를 줄이기 위해** 자주 사용되는 데이터를 임시 저장소(캐시)에 저장하여 빠르게 제공하는 기법입니다.

- **정의:**  
  - 캐시는 데이터의 복사본을 저장하여, 원본 데이터에 접근하기 전에 캐시에서 데이터를 조회함으로써 응답 속도를 높이고, 데이터베이스나 원격 API 호출 부하를 줄이는 기술입니다.
  
- **특징:**  
  - **빠른 응답 속도:**  
    - 캐시된 데이터는 메모리 기반 저장소에서 조회되므로, 디스크나 네트워크를 거치는 것보다 훨씬 빠른 응답을 제공합니다.
  - **부하 감소:**  
    - 데이터베이스나 백엔드 시스템의 요청 빈도를 낮추어, 전체 시스템의 부하를 감소시킵니다.
  - **일관성 관리:**  
    - 데이터 변경 시 캐시 무효화(Invalidation) 전략을 적용하여, 최신 데이터와의 일관성을 유지해야 합니다.
  - **다양한 적용 분야:**  
    - 웹 애플리케이션, API, CDN, 분산 시스템 등 다양한 환경에서 활용됩니다.

---

## 2. 문제 상황과 해결 방안

### 2.1. 문제 상황

- **데이터베이스 부하:**  
  - 트래픽 증가나 대용량 데이터 조회 시, 데이터베이스에 과도한 요청이 몰려 성능 저하가 발생할 수 있습니다.
  
- **응답 지연:**  
  - 원본 데이터 소스에서 데이터를 가져오는 시간이 길어, 사용자 응답 시간이 증가할 수 있습니다.
  
- **비용 증가:**  
  - 빈번한 데이터베이스 조회로 인해 클라우드 비용이나 서버 리소스 사용량이 증가할 수 있습니다.

### 2.2. 해결 방안

- **캐시 도입:**  
  - 자주 사용되는 데이터를 메모리 기반 캐시(예: Redis, Memcached)에 저장하여 빠르게 제공함으로써, 원본 데이터 소스의 부하를 줄입니다.
  
- **적절한 만료 시간 설정:**  
  - 캐시 데이터의 TTL(Time-To-Live)을 설정하여, 일정 시간 이후 자동으로 무효화되도록 관리합니다.
  
- **캐시 무효화 전략:**  
  - 데이터 변경 시, 캐시를 업데이트하거나 삭제하는 무효화(invalidation) 전략을 도입하여 데이터 일관성을 유지합니다.
  
- **계층 캐싱:**  
  - 애플리케이션 내부 캐시, 분산 캐시, CDN 등 여러 계층으로 캐싱을 적용하여, 다양한 데이터 접근 요구에 대응합니다.

---

## 3. 구체적 구현 방법 및 베스트 프랙티스

### 3.1. 기본 디렉토리 구조 예시

아래는 Node.js와 Redis를 활용한 캐싱 전략을 적용한 간단한 애플리케이션 예시 디렉토리 구조입니다.

```plaintext
caching-app/
├── app.js             # 애플리케이션 진입점
├── controllers/       # 요청 처리 로직
├── services/          # 비즈니스 로직 (캐싱 로직 포함)
├── routes/            # API 라우팅 설정
├── utils/             # Redis 클라이언트 등 공통 유틸리티
└── package.json
```

### 3.2. 코드 예시: Redis를 활용한 간단한 캐싱 구현

*utils/redisClient.js*
```javascript
const redis = require('redis');
const client = redis.createClient({
  host: process.env.REDIS_HOST || 'localhost',
  port: process.env.REDIS_PORT || 6379
});

client.on('error', (err) => {
  console.error('Redis 에러:', err);
});

module.exports = client;
```

*services/userService.js*
```javascript
const client = require('../utils/redisClient');
const db = require('../models/userModel'); // 데이터베이스 접근 모듈

// 사용자 정보를 캐시하고, 캐시된 데이터가 없으면 데이터베이스에서 조회 후 캐시 저장
const getUserById = async (userId) => {
  const cacheKey = `user:${userId}`;
  
  // 캐시 조회
  const cachedUser = await new Promise((resolve, reject) => {
    client.get(cacheKey, (err, data) => {
      if (err) return reject(err);
      resolve(data ? JSON.parse(data) : null);
    });
  });
  
  if (cachedUser) {
    console.log('캐시 히트!');
    return cachedUser;
  }
  
  // 캐시 미스: 데이터베이스에서 조회
  console.log('캐시 미스, 데이터베이스 조회...');
  const user = await db.findUserById(userId);
  
  if (user) {
    // 캐시 저장 (TTL 60초)
    client.setex(cacheKey, 60, JSON.stringify(user));
  }
  
  return user;
};

module.exports = { getUserById };
```

*controllers/userController.js*
```javascript
const userService = require('../services/userService');

const getUserController = async (req, res) => {
  try {
    const user = await userService.getUserById(req.params.id);
    if (!user) {
      return res.status(404).json({ message: 'User not found' });
    }
    res.json(user);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
};

module.exports = { getUserController };
```

*routes/userRoutes.js*
```javascript
const express = require('express');
const { getUserController } = require('../controllers/userController');

const router = express.Router();
router.get('/:id', getUserController);

module.exports = router;
```

*app.js*
```javascript
const express = require('express');
const userRoutes = require('./routes/userRoutes');

const app = express();
app.use(express.json());

app.use('/api/users', userRoutes);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
```

### 베스트 프랙티스

- **적절한 TTL 설정:**  
  - 캐시 데이터의 만료 시간을 비즈니스 요구사항에 맞게 조정하여, 데이터 일관성과 성능 사이의 균형을 유지합니다.
  
- **캐시 무효화 전략:**  
  - 데이터 업데이트 시 관련 캐시를 즉시 삭제하거나 갱신하는 메커니즘을 도입하여, 오래된 데이터 제공을 방지합니다.
  
- **다계층 캐싱 적용:**  
  - 애플리케이션 내부 캐시, 분산 캐시, CDN 등 다양한 계층에서 캐싱을 적용하여, 최적의 응답 속도를 구현합니다.
  
- **모니터링 및 로깅:**  
  - 캐시 히트율, 미스율, 응답 시간 등을 모니터링하여 캐시 전략의 효과를 지속적으로 평가하고 최적화합니다.
  
- **캐시 일관성 고려:**  
  - 데이터베이스와 캐시 간의 일관성을 유지하기 위해, 이벤트 기반 무효화 또는 정기적 동기화 전략을 도입합니다.

---

## 4. 추가 고려 사항

- **데이터 일관성:**  
  - 캐시와 원본 데이터 소스 간의 일관성 문제를 해결하기 위한 전략(예: Write-Through, Write-Behind, Cache Aside 등)을 선택해야 합니다.
  
- **캐시 공간 관리:**  
  - 캐시 저장 공간이 한정되어 있으므로, LRU(Least Recently Used) 등 효율적인 캐시 교체 알고리즘을 사용하여 불필요한 데이터를 제거합니다.
  
- **보안:**  
  - 민감한 데이터를 캐시에 저장할 경우, 암호화와 접근 제어를 통해 보안을 강화해야 합니다.
  
- **분산 환경:**  
  - 분산 캐시 시스템(Redis Cluster, Memcached 등)을 활용하여, 대규모 시스템에서도 일관된 캐시 서비스를 제공할 수 있도록 설계합니다.

---

## 5. 결론

**캐싱 전략**은 시스템의 응답 속도를 향상시키고, 데이터베이스 부하를 줄이며, 전체 시스템의 비용 효율성을 높이는 중요한 기법입니다.

- **장점:**  
  - 빠른 데이터 접근과 응답 시간 개선  
  - 데이터베이스 및 백엔드 시스템 부하 감소  
  - 사용자 경험 향상 및 비용 절감
  
- **단점:**  
  - 데이터 일관성 유지에 따른 추가 복잡성  
  - 캐시 무효화 및 관리 전략 미흡 시, 오래된 데이터 제공 위험
  
따라서, 캐싱 전략을 도입할 때는 **적절한 TTL, 무효화 정책, 다계층 캐싱** 등의 베스트 프랙티스를 철저히 적용하고, 모니터링과 보안을 강화하여 최적의 성능과 일관성을 유지하는 것이 중요합니다.