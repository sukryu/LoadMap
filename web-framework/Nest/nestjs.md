# 웹 프레임워크 Nestjs #

### NestJS 소개 ###

- NestJS는 Angular의 아키텍처와 디자인 패턴에서 영감을 받아 만들어진 프레임워크이다.
- 모듈, 컨트롤러, 서비스, 의존성 주입 등의 개념을 사용하여 코드를 구조화한다.
- TypeScript를 기본 언어로 사용하여 타입 안정성과 개발 생산성을 높인다.
- Express.js나 Fastify.js와 같은 프레임워크 위에서 동작한다.

### NestJS 설치 및 프로젝트 생성 ###

- NestJS를 시작하려면 먼저 NestJS CLI를 설치해야 한다.
```bash
npm install -g @nestjs/cli
```

- NestJS CLI를 사용하여 새로운 프로젝트를 생성한다.
```bash
nest new my-project
```

- 프로젝트가 생성되면 다음 명령어로 애플리케이션을 실행할 수 있다.
```bash
cd my-project
npm run start
```

### NestJS 애플리케이션 라이프사이클 ###

- NestJS 애플리케이션의 요청 처리 흐름은 다음과 같다.

  1. 인커밍 요청(Incoming Request)
  2. 미들웨어 (Middleware)
  3. 가드 (Guards)
  4. 인터셉터 (pre-controller)(Interceptors (pre-controller))
  5. 파이프(Pipes)
  6. 컨트롤러 핸들러 (Controller Handler)
  7. 서비스 (Services)
  8. 인터셉터 (post-request)(Interceptors(post-request))
  9. 응답 (Response)

### 미들웨어(Middleware) ###

- 미들웨어는 라우트 핸들러 이전에 실행되는 함수.
- 요청 객체와 응답 객체에 접근하여 데이터를 조작하거나 유효성을 검사할 수 있음.
- 미들웨어는 @Injectable() 데코레이터로 선언된 클래스에 NestMiddleware 인터페이스를 구현한다.
- 미들웨어는 모듈의 configure()메서드에서 설정됨.
```typescript
import { Injectable, NestMiddleware } from '@nestjs/common';
import { Request, Response, NextFunction } from 'express';

@Injectable()
export class LoggerMiddleware implements NestMiddleware {
  use(req: Request, res: Response, next: NextFunction) {
    console.log('Request...');
    next();
  }
}
```

### 가드(Guards) ###

- 가드는 인증 및 인가를 처리하는 역할을 한다.
- @Injectable() 데코레이터로 선언된 클래스에 CanActivate 인터페이스를 구현한다.
- 가드는 @UseGuards() 데코레이터를 사용하여 바인딩된다.
```typescript
import { CanActivate, ExecutionContext, Injectable } from '@nestjs/common';
import { Observable } from 'rxjs';

@Injectable()
export class AuthGuard implements CanActivate {
  canActivate(
    context: ExecutionContext,
  ): boolean | Promise<boolean> | Observable<boolean> {
    // 인증 로직
    return true;
  }
}
```

### 인터셉터 (Interceptors) ###

- 인터셉터는 컨트롤러 메서드 실행 전후에 로직을 삽입할 수 있다.
- @Injectable() 데코레이터로 선언된 클래스에 NestInterceptor 인터페이스를 구현한다.
- 인터셉터는 @UseInterceptors() 데코레이터를 사용하여 바인딩된다.
```typescript
import { CallHandler, ExecutionContext, Injectable, NestInterceptor } from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap } from 'rxjs/operators';

@Injectable()
export class LoggingInterceptor implements NestInterceptor {
  intercept(context: ExecutionContext, next: CallHandler): Observable<any> {
    console.log('Before...');
    const now = Date.now();
    return next
      .handle()
      .pipe(
        tap(() => console.log(`After... ${Date.now() - now}ms`)),
      );
  }
}
```

### 파이프 (Pipes) ###

- 파이프는 컨트롤러 라우트 핸들러로 진입하기 전에 요청 데이터의 유효성 검사와 변환을 수행한다.
- @Injectable() 데코레이터로 선언된 클래스에 PipeTransform 인터페이스를 구현한다.
- 파이프는 @UsePipes() 데코레이터를 통해 바인딩된다.
```typescript
import { ArgumentMetadata, Injectable, PipeTransform } from '@nestjs/common';

@Injectable()
export class ValidationPipe implements PipeTransform {
  transform(value: any, metadata: ArgumentMetadata) {
    // 유효성 검사 로직
    return value;
  }
}
```

### 예외 필터 (Exception Filters) ###

- 예외 필터는 애플리케이션에서 발생하는 예외를 처리하고 클라이언트에게 적절한 응답을 반환한다.
- @Catch() 데코레이터를 사용하여 예외 필터를 생성한다.
- 예외 필터는 @UseFilters() 데코레이터를 통해 바인딩된다.
```typescript
import { ExceptionFilter, Catch, ArgumentsHost, HttpException } from '@nestjs/common';
import { Request, Response } from 'express';

@Catch(HttpException)
export class HttpExceptionFilter implements ExceptionFilter {
  catch(exception: HttpException, host: ArgumentsHost) {
    const ctx = host.switchToHttp();
    const response = ctx.getResponse<Response>();
    const request = ctx.getRequest<Request>();
    const status = exception.getStatus();

    response
      .status(status)
      .json({
        statusCode: status,
        timestamp: new Date().toISOString(),
        path: request.url,
      });
  }
}
```

### 커스텀 데코레이터 ###

- NestJS에서는 커스텀 데코레이터를 만들어 사용할 수 있다.
- 커스텀 데코레이터는 메타데이터를 정의하고 런타임에 활용할 수 있다.
- 파라미터 데코레이터, 메서드 데코레이터, 클래스 데코레이터 등을 생성할 수 있다.
```typescript
import { createParamDecorator, ExecutionContext } from '@nestjs/common';

export const User = createParamDecorator(
  (data: unknown, ctx: ExecutionContext) => {
    const request = ctx.switchToHttp().getRequest();
    return request.user;
  },
);
```

### 모듈 (Modules) ###

- NestJS의 모듈은 애플리케이션의 구조를 구성하는 기본 단위이다.
- @Module() 데코레이터를 사용하여 모듈을 정의한다.
- 모듈은 providers, controllers, imports, exports 속성을 가질 수 있다.
```typescript
import { Module } from '@nestjs/common';
import { CatsController } from './cats.controller';
import { CatsService } from './cats.service';

@Module({
  controllers: [CatsController],
  providers: [CatsService],
})
export class CatsModule {}
```

### 의존성 주입 (Dependency Injection) ###

- NestJS는 의존성 주입 패턴을 사용하여 객체 간의 의존성을 관리함.
- @Injectable() 데코레이터를 통해 주입 가능한 서비스를 정의함.
- 생성자 주입을 통해 의존성을 주입 받음.
```typescript
import { Injectable } from '@nestjs/common';

@Injectable()
export class CatsService {
  private readonly cats: Cat[] = [];

  findAll(): Cat[] {
    return this.cats;
  }
}

@Controller('cats')
export class CatsController {
  constructor(private readonly catsService: CatsService) {}

  @Get()
  async findAll(): Promise<Cat[]> {
    return this.catsService.findAll();
  }
}
```

### 프로바이더 (Providers) ###

- NestJS의 프로바이더는 의존성 주입을 위한 객체를 생성하고 관리함.
- 프로바이더는 서비스, 레포지토리, 팩토리, 헬퍼 등 다양한 형태로 사용됨.
- @Injectable() 데코레이터를 사용하여 프로바이더를 정의함.
```typescript
import { Injectable } from '@nestjs/common';

@Injectable()
export class CatsService {
  private readonly cats: Cat[] = [];

  create(cat: Cat) {
    this.cats.push(cat);
  }

  findAll(): Cat[] {
    return this.cats;
  }
}
```

### 컨트롤러 (Controller) ###

- NestJS의 컨트롤러는 들어오는 HTTP 요청을 처리하고 클라이언트에게 응답을 반환함.
- @Controller() 데코레이터를 통해 컨트롤러를 정의함.
- 컨트롤러는 @Get(), @Post(), @Put(), @Delete() 등의 데코레이터를 사용하여 라우트 핸들러를 정의함.
```typescript
import { Controller, Get, Post, Body } from '@nestjs/common';

@Controller('cats')
export class CatsController {
  @Get()
  findAll(): string {
    return 'This action returns all cats';
  }

  @Post()
  create(@Body() createCatDto: CreateCatDto) {
    return 'This action adds a new cat';
  }
}
```

### 서비스 (Services) ###

- NestJS의 서비스는 애플리케이션의 비즈니스 로직을 캡슐화하고 관리함.
- @Injectable() 데코레이터를 주입하여 서비스를 정의함.
- 서비스는 컨트롤러에 주입되어 사용되며, 데이터베이스 작업, 외부 API 호출 등의 작업을 수행함.
```typescript
import { Injectable } from '@nestjs/common';
import { Cat } from './interfaces/cat.interface';

@Injectable()
export class CatsService {
  private readonly cats: Cat[] = [];

  create(cat: Cat) {
    this.cats.push(cat);
  }

  findAll(): Cat[] {
    return this.cats;
  }
}
```

### 리포지토리 (Repositories) ###

- NestJS의 리포지토리는 데이터 저장소와 상호 작용하는 역할을 함.
- 리포지토리는 데이터베이스 쿼리, 데이터 조작 등의 작업을 수행함.
- @Injectable() 데코레이터를 사용하여 리포지토리를 정의함.
- TypeORM, Sequelize, Mongoose 등의 ORM/ODM 라이브러리와 함께 사용됨.
```typescript
import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { Cat } from './entities/cat.entity';

@Injectable()
export class CatsRepository {
  constructor(
    @InjectRepository(Cat)
    private readonly catsRepository: Repository<Cat>,
  ) {}

  async findAll(): Promise<Cat[]> {
    return this.catsRepository.find();
  }

  async create(cat: Cat): Promise<Cat> {
    return this.catsRepository.save(cat);
  }
}
```

### DTO (Data Transfer Objects) ###

- NestJS의 DTO는 네트워크를 통해 전송되는 데이터의 구조를 정의함.
- DTO는 요청과 응답의 데이터 형식을 지정하고 유효성 검사에 사용됨.
- 클래스 기반의 DTO를 사용하며, 속성에 대한 타입과 유효성 검사 규칙을 정의함.
```typescript
export class CreateCatDto {
  @IsString()
  name: string;

  @IsInt()
  age: number;

  @IsString()
  breed: string;
}
```

### 유효성 검사 (Validation) ###

- NestJS는 요청 데이터의 유효성 검사를 위한 파이프를 제공함.
- class-validator 라이브러리를 사용하여 DTO에 유효성 검사 규칙을 정의함.
- ValidationPipe를 사용하여 요청 데이터의 유효성을 검사함.
```typescript
@Controller('cats')
export class CatsController {
  @Post()
  @UsePipes(ValidationPipe)
  async create(@Body() createCatDto: CreateCatDto) {

  }
}
```

### 인증 및 인가 (Authentication & Authorization) ###

- NestJS는 인증과 인가를 처리하기 위한 가드와 전략을 제공함.
- Passport 라이브러리를 사용하여 인증 전략을 구현할 수 있음.
- JWT(Json Web Token)를 사용한 인증 예시

```typescript

import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { ExtractJwt, Strategy } from 'passport-jwt';

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy) {
  constructor() {
    super({
      jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
      secretOrKey: 'secretkey',
    });
  }

  async validate(payload: any) {
    return { userId: payload.sub, username: payload.username };
  }
}
```

- 가드를 사용하여 인증된 사용자만 엑세스할 수 있도록 제어 할 수 있음.
```typescript
import { Injectable, CanActivate, ExecutionContext } from '@nestjs/common';
import { AuthService } from './auth.service';

@Injectable()
export class AuthGuard implements CanActivate {
  constructor(private readonly authService: AuthService) {}

  async canActivate(context: ExecutionContext): Promise<boolean> {
    const request = context.switchToHttp().getRequest();
    const token = request.headers.authorization;
    const user = await this.authService.validateToken(token);
    request.user = user;
    return true;
  }
}
```

### 로깅 (Logging) ###

- NestJS는 로깅을 위한 내장 로거를 제공함.
- Winston 라이브러리를 사용하여 커스텀 로거를 구현할 수 있음.
```typescript
async function bootstrap() {
  const app = await NestFactory.create(AppModule, {
    logger: new Logger(),
  });

  await app.listen(3000);
}
bootstrap();
```

### 구성 (Configuration) ###

- NestJS는 애플리케이션 구성을 위한 ConfigModule을 제공함.
- dotenv 라이브러리를 사용하여 환경 변수 파일 (.env)에서 구성 값을 로드할 수 있음.
```typescript
import { Module } from '@nestjs/common';
import { ConfigModule } from '@nestjs/config';

@Module({
  imports: [
    ConfigModule.forRoot({
      envFilePath: '.env',
    }),
  ],
})
export class AppModule {}
```

### 테스팅 (Testing) ###

- NestJS는 Jest 테스트 프레임워크를 사용하여 단위 테스트와 통합 테스트를 작성할 수 있음.
- @nestjs/testing 패키지를 사용하여 테스트에 필요한 유틸리키와 모듈을 제공함.
```typescript
import { Test, TestingModule } from '@nestjs/testing';
import { CatsController } from './cats.controller';
import { CatsService } from './cats.service';

describe('CatsController', () => {
  let controller: CatsController;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [CatsController],
      providers: [CatsService],
    }).compile();

    controller = module.get<CatsController>(CatsController);
  });

  it('should return an array cats', () => {
    const result = ['cat1', 'cat2'];
    jest.spyOn(controller, 'findAll').mockImplementation(() => result);
    expect(controller.findAll()),toBe(result);
  });
});
```

### Open API(Swagger) ###

- NestJS는 OpenAPI(Swagger) 문서 생성을 지원함.
- @nestjs/swagger 패키지를 사용하여 API 문서를 자동으로 생성할 수 있음.
- 컨트롤러와 DTO에 적절한 데코레이터를 추가하여 API문서를 보강할 수 있음.
- 아래처럼 작성후 localhost:3000/docs에 진입하면 API 문서를 볼 수 있음.
```typescript
import { NestFactory } from '@nestjs/core';
import { SwaggerModule, DocumentBuilder } from '@nestjs/swagger';
import { AppModule } from './app.module';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);

  const config = new DocumentBuilder()
    .setTitle('Cats example')
    .setDescription('The cats API description')
    .setVersion('1.0')
    .addTag('cats')
    .build();

  const document = SwaggerModule.createDocument(app, config);
  SwaggerModule.setup('api', app, document);

  await app.listen(3000);
}
bootstrap();
```

### GraphQL ###

- NestJS는 GraphQL API 구축을 지원함.
- @nestjs/graphql 패키지를 사용하여 GraphQL 스키마, 리졸버, 모듈을 정의할 수 있음.
- Apollo Server와 통합되어 GraphQL 서버를 쉽게 구성할 수 있음.
```typescript
import { Module } from '@nestjs/common';
import { GraphQLModule } from '@nestjs/graphql';
import { CatsModule } from './cats/cats.module';

@Module({
  imports: [
    GraphQLModule.forRoot({
      autoSchemaFile: 'schema.gql',
    }),
    CatsModule,
  ],
})
export class AppModule {}
```

### 웹 소켓 (WebSocket) ###

- NestJS는 웹 소켓을 사용한 실시간 통신을 지원함.
- @nestjs/websockets 패키지를 사용하여 웹 소켓 게이트웨이와 이벤트 핸들러를 정의할 수 있음.
- Socket.IO 라이브러리와 통합되어 웹 소켓 서버를 구성할 수 있음.
```typescript
import { SubscribeMessage, WebSocketGateway } from '@nestjs/websockets';

@WebSocketGateway()
export class EventsGateway {
  @SubscribeMessage('events')
  handleEvent(client: any, data: any): string {
    return data;
  }
}
```

### CQRS (Command Query Responsibility Segregation) ###

- NestJS는 CQRS 패턴을 지원함.
- @nestjs/cqrs 패키지를 사용하여 Command, Query, EventBus등의 개념을 구현할 수 있음.
- CQRS 패턴을 통해 읽기와 쓰기 책임을 분리하고 확장성과 유지보수성을 향상시킬 수 있음.
```typescript
import { Module } from '@nestjs/common';
import { CqrsModule } from '@nestjs/cqrs';
import { CommandHandlers } from './commands/handlers';
import { QueryHandlers } from './queries/handlers';
import { EventHandlers } from './events/handlers';

@Module({
  imports: [CqrsModule],
  providers: [...CommandHandlers, ...QueryHandlers, ...EventHandlers],
})
export class AppModule {}
```

### 마이크로서비스 (Microservices) ###

- NestJS는 마이크로서비스 아키텍처를 지원함.
- @nestjs/microservices 패키지를 사용하여 마이크로서비스 간 통신을 구현할 수 있음.
- TCP, Redis, NATS, RabbitMQ, Kafka 등 다양한 전송 방식을 사용할 수 있음.
```typescript
import { NestFactory } from '@nestjs/core';
import { Transport, MicroserviceOptions } from '@nestjs/microservices';
import { AppModule } from './app.module';

async function bootstrap() {
  const app = await NestFactory.createMicroservices<MicroserviceOptions>(
    AppModule,
    {
      transport: Transport.TCP,
    },
  );
  await app.listen();
}
bootstrap();
```

### 마무리 ###

- NestJS는 Angular의 아키텍처와 디자인 패턴에서 영감을 받아 만들어진 프레임워크로, 모듈화, 의존성 주입, 데코레이터 등의 개념을 사용하여 확장 가능하고 유지보수하기 쉬운 서버 사이드 애플리케이션을 구축할 수 있음.

- NestJS의 장점은 TypeScript를 기본으로 사용하여 타입 안전성을 제공하고, Express & Fastify와 같은 강력한 웹 프레임워크 위에서 동작하며, 다양한 플러그인과 라이브러리를 통해 기능을 확장할 수 있다는 점.

- NestJS는 테스팅, 로깅, 구성, OpenAPI 문서 생성, GraphQL, 웹 소켓, CQRS, 마이크로서비스 등 다양한 기능을 지원하며 엔터프라이즈급 애플리케이션 개발에 적합함.

- NestJS를 사용하면 코드의 재사용성을 높이고, 애플리케이션의 구조를 명확하게 유지하며, 테스트 가능한 코드를 작성할 수 있음. 또한 활발한 커뮤니티와 풍부한 생태계를 지녀 개발자들이 쉽게 학습하고 적용할 수 있다.

- 실제 프로젝트에서는 NestJS의 공식 문서를 참조하고 모범 사례를 따르며, 팀의 요구사항에 맞게 아키텍처와 패턴을 적용하는 것이 중요. NestJS의 모듈화된 구조와 의존성 주입 패턴을 활용하여 느슨한 결합과 높은 응집력을 갖는 코드를 작성하고, 테스트 주도 개발(TDD)을 통해 코드의 품질을 유지하는 것이 좋다.