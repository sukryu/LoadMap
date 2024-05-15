# 웹 프레임워크 Express.js #

### Express.js 소개 ###

- Express.js는 Node.js 웹 애플리케이션 프레임워크이다.
- 웹 애플리케이션 및 API 개발을 위한 다양한 기능을 제공한다.
- 미니멀리즘을 추구하며 간결하고 유연한 구조를 가진다.
- 많은 오픈 소스 미들웨어를 활용하여 기능 확장이 용이하다.

### Express.js 설치 ###

- Node.js가 설치되어 있어야 함.
- 프로젝트 디렉토리에서 다음 명령어를 실행하여 Express.js를 설치한다.

```bash
npm install express
```

- package.json 파일에 Express.js 의존성이 추가됨.

### Express.js 애플리케이션 작성. ###

- Express.js 애플리케이션은 express() 함수를 호출하여 생성함.
- 다음은 간단한 Express.js 애플리케이션의 예제.

```javascript

const express = require("express");
const app = express();

app.get("/", (req, res) => {
  res.send("Hello, Express!");
});

app.listen(3000, () => {
  console.log('Server started on port 3000');
});
```

### 라우팅 ###

- 라우팅은 클라이언트 요청에 대해 애플리케이션이 응답하는 방법을 결정하는 것이다.
- Express.js에서는 app.get(), app.post(), app.put(), app.delete()등의 메서드를 사용하여 라우트를 정의한다.
- 라우트 경로에는 문자열, 정규식, 와일드카드 등을 사용할 수 있다.
- 라우트 핸들러 함수는 요청 객체 (req)와 응답 객체(res)를 매개변수로 받는다.
- 다음은 라우팅의 예제이다.

```javascript
app.get('/', (req, res) => {
  res.send('Hello, World!');
});

app.get('/users/:id', (req, res) => {
  const userId = req.params.id;
  res.send(`User ID: ${userId}`);
});

app.post('/users', (req, res) => {
  // 사용자 생성 로직
  res.send('User created');
});
```

### 미들웨어 ###

- 미들웨어는 요청과 응답 사이에서 실행되는 함수이다.
- 미들웨어는 요청 객체(req), 응답 객체(res), 다음 미들웨어 함수(next)에 접근할 수 있다.
- 미들웨어는 요청 처리 파이프라인에 기능을 추가하거나 요청/응답을 조작할 수 있다.
- Express.js에서는 app.use() 메서드를 사용하여 미들웨어를 등록한다.
- 다음은 미들웨어의 예제이다.

```javascript
// 로깅 미들웨어
app.use((req, res, next) => {
  console.log(`[${new Date().toISOString()}] ${req.method} ${req.url}`);
  next();
});

// JSON 파싱 미들웨어
app.use(express.json());

// 정적 파일 제공 미들웨어
app.use(express.static('public'));
```

### 템플릿 엔진 ###

- 템플릿 엔진은 동적으로 HTML 페이지를 생성하는 데 사용된다.
- Express.js에서는 EJS, Pug, Handlebars 등의 다양한 템플릿 엔진을 지원한다.
- 템플릿 엔진을 사용하려면 해당 템플릿 엔진 모듈을 설치하고 Express.js 애플리케이션에 설정해야 한다.
- 다음은 EJS 템플릿 엔진을 사용하는 예제이다.
```javascript
app.set('view engine', 'ejs');

app.get('/', (req, res) => {
  const data = { title: 'Express.js', message: 'Hello, EJS!' };
  res.render('index', data);
});
```

### 에러 처리 ###

- Express.js에서는 에러 처리를 위한 미들웨어를 제공한다.
- 에러 처리 미들웨어는 일반 미들웨어 뒤에 등록해야 한다.
- 에러 처리 미들웨어는 err, req, res, next 네 개의 매개변수를 가진다.
- 다음은 에러 처리 미들웨어의 예제이다.

```javascript
app.use((err, req, res, next) => {
  console.error(err.stack);
  res.status(500).send('Something broke!');
});
```

### Express.js 애플리케이션의 구조화 ###

- 대규모 애플리케이션의 경우 코드를 모듈화하고 구조화하는 것이 중요하다.
- Express.js 애플리케이션을 구조화하는 일반적인 방법은 다음과 같다.
  - 라우트를 별도의 파일로 분리하여 관리.
  - 컨트롤러를 사용하여 라우트 핸들러 로직을 분리.
  - 비즈니스 로직을 서비스 계층으로 분리.
  - 데이터베이스 연동을 위한 모델 또는 리포지토리 계층 사용.
  - 환경 변수를 사용하여 구성 관리.

- 다음은 Express.js 애플리케이션 구조의 예이다.

```
- app.js
- controllers/
  - userController.js
- models/
  - userModel.js
- routes/
  - userRoutes.js
- services/
  - userService.js
- config/
  - database.js
```

### Express.js 보안 ###

- 웹 애플리케이션 개발 시 보안은 매우 중요한 고려사항임.
- Express.js에서는 다음과 같은 보안 조치를 취할 수 있음.
  - Helmet 미들웨어를 사용하여 HTTP 헤더 보안 설정.
  - HTTPS를 사용하여 데이터 암호화.
  - CSRF 공격 방지를 위해 csurf 미들웨어 사용.
  - XSS 공격 방지를 위해 사용자 입력 데이터 검증 및 이스케이프 처리.
  - SQL 인젝션 방지를 위해 파라미터화된 쿼리 또는 ORM 사용.
  - 안전한 세션 관리를 위해 express-session 미들웨어 사용.

- 다음은 Helmet 미들웨어를 사용하는 예제.
```javascript
// use helmet
const helmet = require("helmet");
app.use(helmet());

// use HTTPS
const https = require('https');
const fs = require('fs');

const options = {
  key: fs.readFileSync('key.pem'),
  cert: fs.readFileSync('cert.pem')
};

https.createServer(options, app).listen(443);

// csurf
const csrf = require('csurf');
app.use(csrf());

// 사용자 입력 검증.
const { body, validationResult } = require('express-validator');

app.post('/users', 
  body('email').isEmail(),
  body('password').isLength({ min: 6 }),
  (req, res) => {
    const errors = validationResult(req);
    if (!errors.isEmpty()) {
      return res.status(400).json({ errors: errors.array() });
    }
    // 사용자 생성 로직
  }
);

// 안전한 세션 관리
const session = require('express-session');

app.use(session({
  secret: 'your-secret-key',
  resave: false,
  saveUninitialized: true,
  cookie: {
    secure: true, // HTTPS에서만 쿠키 전송
    httpOnly: true // 클라이언트 JavaScript에서 쿠키 접근 방지
  }
}));
```

### Express.js 테스팅 ###

- Express.js 애플리케이션은 자동화된 테스트를 통해 품질을 보장할 수 있음.
- 테스트 프레임워크로는 Jest, Mocha, Chai 등이 널리 사용됨.
- 테스트 대상으로는 라우트, 미들웨어, 컨트롤러, 서비스 등이 있음.
- 테스트는 단위 테스트, 통합 테스트, E2E 테스트로 구분할 수 있음.
- 다음은 Jest를 사용한 Express.js 라우트 테스트의 예제임.

```javascript
const request = require("supertest");
const app = require("./app");

describe('GET /', () => {
    it('should respond with "Hello, Express!"', async () => {
      const response = await request(app).get('/');
      expect(response.status).toBe(200);
      expect(response.text).toBe('Hello, Express!');
    });
  });
```


### Express.js 서버의 라이프사이클 ###

- Express.js 서버는 다음과 같은 라이프사이클을 가집니다.
  1. 서버 설정: express() 함수를 호출하여 Express.js 애플리케이션 객체를 생성하고, 필요한 미들웨어와 라우트를 설정.

  2. 서버 시작: app.listen()메서드를 호출하여 지정된 포트에서 서버를 시작한다. 이때 서버는 클라이언트의 요청을 받을 준비를 함.

  3. 요청 수신: 클라이언트로부터 요청이 도착하면 Express.js는 요청 객체(req)와 응답 객체(res)를 생성하고, 미들웨어 스택을 실행한다.

  4. 미들웨어 실행: 등록된 미들웨어들이 순차적으로 실행된다. 각 미들웨어는 요청 객체와 응답 객체를 조작하거나 다음 미들웨어로 제어를 전달할 수 있다.

  5. 라우트 처리: 요청 URL과 HTTP 메서드에 매칭되는 라우트 핸들러가 실행된다. 라우트 핸들러는 요청을 처리하고 응답을 생성한다.

  6. 응답 전송: 라우트 핸들러 또는 미들웨어에서 res.send(), res.json(), res.render() 등의 메서드를 호출하여 클라이언트에게 응답을 전송한다.

  7. 서버 종료: 서버를 종료하려면 process.exit()를 호출하거나 컨트롤 + C를 눌러 프로세스를 중단한다.

### 미들웨어 사용 시점 ###

- Express.js에서 미들웨어는 요청 처리 파이프라인의 중간에 위치하며, 다양한 기능을 수행할 수 있다. 미들웨어를 사용하는 일반적인 시점은 다음과 같다.
  1. 애플리케이션 레벨 미들웨어: 모든 요청에 대해 실행되어야 하는 미들웨어는 애플리케이션 레벨에서 정의한다. 예를 들어 로깅, 보안, 파싱 등의 미들웨어가 이에 해당한다.
  ```javascript
  app.use(express.json());
  app.use(express.urlencoded({ extended: true }));
  app.use(cors());
  app.use(helmet());
  ```

  2. 라우터 레벨 미들웨어: 특정 라우트에 대해서만 실행되어야 하는 미들웨어는 라우터 레벨에서 정의한다. 예를 들어 인증, 권한 확인, 유효성 검사 등의 미들웨어가 이에 해당한다.
  ```javascript
  const authMiddleware = (req, res, next) => {
    // 인증 로직
    if (authenticated) {
      next();
    } else {
      res.status(401).send('Unauthorized');
    }
  };

  app.get('/protected', authMiddleware, (req, res) => {
    res.send('Protected resource');
  });
  ```

  3. 오류 처리 미들웨어: 오류 처리 미들웨어는 요청 처리 중 발생한 오류를 캡처하고 처리하는 데 사용된다. 오류 처리 미들웨어는 항상 다른 미들웨어와 라우트 핸들러 이후에 정의해야 한다.
  ```javascript
  app.use((err, req, res, next) => {
    console.error(err);
    res.status(500).send('Internal Server Error');
  });
  ```

- 미들웨어의 실행 순서는 정의된 순서대로 이루어진다. 따라서 미들웨어의 배치 순서를 적절하게 고려해야 한다.

### 마무리 ###
- Express.js는 Node.js 웹 개발에서 가장 널리 사용되는 프레임워크 중 하나이다. 간결하고 유연한 구조, 다양한 미들웨어 지원, 큰 생태계 등의 장점이 있다.