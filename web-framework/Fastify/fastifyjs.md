# 웹 프레임워크 Fastify.js #

### Fastify 소개 ###

- Fastify는 Node.js 웹 프레임워크로, 높은 성능과 낮은 오버헤드를 목표로 함.
- Express.js와 유사한 구조를 가지고 있지만, 더 빠른 속도와 효율성을 제공함.
- 플러그인 아키텍처를 사용하여 기능을 확장할 수 있음.
- JSON 스키마 기반의 요청/응답 검증을 지원함.
- TypeScript를 기본적으로 지원함.

### 설치 및 사용법 ###

- Fastify를 시작하려면 먼저 프로젝트에 Fastify를 설치해야 함.
```bash
npm install fastify
```

- Fastify 애플리케이션을 생성하고 시작하는 기본 코드는 다음과 같다.
```javascript
const fastify = require('fastify')();

fastify.get('/', (request, reply) => {
  reply.send({ hello: 'world' });
});

fastify.listen(3000, (err, address) => {
  if (err) {
    fastify.log.error(err);
    process.exit(1);
  }
  console.log(`Server listening on ${address}`);
});
```

### 라우팅 ###

- Fastify에서 라우팅은 HTTP 메서드에 해당하는 메서드를 사용하여 정의함.
- 라우트는 경로와 핸들러 함수로 구성됨.
- 라우트 핸들러 함수는 request와 reply 객체를 매개변수로 받음.
- 라우트 매개변수, 쿼리 매개변수, 와일드카드 등을 사용할 수 있음.
```javascript
fastify.get('/users/:id', (request, reply) => {
  const { id } = request.params;
  reply.send({ userId: id });
});

fastify.post('/users', (request, reply) => {
  const { name, email } = request.body;
  // 사용자 생성 로직
  reply.send({ message: 'User created' });
});
```

### 요청 검증 ###

- Fastify는 JSON 스키마를 사용하여 요청 데이터의 유효성을 검사할 수 있다.
- 스키마는 라우트 옵션의 schema 속성에 정의한다.
- 요청 본문(body), 쿼리 매개변수(querystring), 매개변수(params), 헤더(headers) 등에 대한 스키마를 정의할 수 있다.

```javascript
const postSchema = {
  schema: {
    body: {
      type: 'object',
      required: ['title', 'content'],
      properties: {
        title: { type: 'string' },
        content: { type: 'string' }
      }
    }
  }
};

fastify.post('/posts', postSchema, (request, reply) => {
  const { title, content } = request.body;
  // 게시물 생성 로직
  reply.send({ message: 'Post created' });
});
```

### 플러그인 ###

- Fastify는 플러그인 아키텍처를 사용하여 기능을 확장할 수 있다.
- 플러그인은 fastify.register() 메서드를 사용하여 등록한다.
- 플러그인은 애플리케이션의 기능을 모듈화하고 재사용성을 높인다.
- Fastify 생태계에는 다양한 써드파티 플러그인이 존재한다.

```javascript
const fastifyPlugin = require('fastify-plugin');

async function myPlugin(fastify, options) {
  fastify.decorate('myFunction', () => {
    console.log('Hello from plugin');
  });
}

module.exports = fastifyPlugin(myPlugin);

// other file
fastify.register(require('./myPlugin'));

fastify.get('/', (request, reply) => {
  fastify.myFunction();
  reply.send({ hello: 'world' });
});
```

### 미들웨어 ###

- Fastify에서 미들웨어는 훅(hook)으로 구현한다.
- 훅은 요청/응답 라이프사이클의 특정 시점에 실행되는 함수이다.
- 대표적인 훅으로는 onRequest, preHandler, onSend, onResponse 등이 있다.
- 미들웨어는 fastify.addHook() 메서드를 사용하여 등록한다.
```javascript
fastify.addHook('onRequest', (request, reply, done) => {
  console.log('Received request:', request.url);
  done();
});

fastify.addHook('preHandler', (request, reply, done) => {
  // 요청 전처리 로직
  done();
});
```

### 에러 처리 ###

- Fastify는 에러 처리를 위한 메커니즘을 제공한다.
- 에러는 reply.send(new Error()) 형태로 전송할 수 있다.
- 에러 처리기는 setErrorHandler() 메서드를 사용하여 등록한다.
- 에러 처리기는 모든 라우트 및 플러그인에 적용된다.
```javascript
fastify.setErrorHandler((error, request, reply) => {
  console.error(error);
  reply.status(500).send({ message: 'Internal Server Error' });
});

fastify.get('/', (request, reply) => {
  throw new Error('Something went wrong');
});
```

### 로깅 ###

- Fastify는 내장된 로거인 Pino를 사용하여 로깅 기능을 제공한다.
- 로거는 request, reply, error 등의 이벤트에 대한 로그를 자동으로 생성한다.
- 로그 레벨을 설정하여 로그 출력을 제어할 수 있다.
- 커스텀 로그 포맷터를 사용하여 로그 출력을 사용자 정의할 수 있다.
```javascript
const fastify = require('fastify')({
  logger: {
    level: 'info',
    prettyPrint: true
  }
});

fastify.get('/', (request, reply) => {
  request.log.info('Hello from route');
  reply.send({ hello: 'world' });
});
```

### 테스팅 ###

- Fastify는 테스트 프레임워크와 쉽게 통합할 수 있다.
- Tap, Jest, Mocha 등의 테스트 프레임워크를 사용할 수 있다.
- Fastify의 inject() 메서드를 사용하여 HTTP 요청을 시뮬레이션할 수 있다.

```javascript
// Tap
const tap = require('tap');
const fastify = require('fastify')();

fastify.get('/', (request, reply) => {
  reply.send({ hello: 'world' });
});

tap.test('GET /', async (t) => {
  const response = await fastify.inject({
    method: 'GET',
    url: '/'
  });
  t.equal(response.statusCode, 200);
  t.deepEqual(response.json(), { hello: 'world' });
});
```

### 디플로이먼트 ###

- Fastify 애플리케이션은 다양한 방법으로 배포할 수 있다.
- PM2, Docker, Kubernetes 등을 사용하여 애플리케이션을 배포할 수 있다.
- 프로덕션 환경에서는 HTTPS를 사용하고, 적절한 보안 설정을 해야 한다.
- 로드 밸런싱, 오토스케일링 등의 기술을 활용하여 확장성과 가용성을 확보할 수 있다.

- Fastify는 고성능과 확장성을 중점으로 둔 Node.js 웹 프레임워크입니다. Express.js와 유사한 구조를 가지고 있지만, 더 빠른 속도와 효율성을 제공함. 플러그인 아키텍처, JSON 스키마 기반의 요청 검증, 훅을 사용한 미들웨어 구현 등의 특징이 있다.

- Fastify를 사용하여 웹 애플리케이션을 개발할 때는 공식 문서를 참조하고, 제공되는 API와 플러그인을 적극 활용하는 것이 좋다. 또한 Fastify의 성능을 최적화하기 위해 비동기 처리, 캐싱, 압축 등의 기술을 적용할 수 있다.