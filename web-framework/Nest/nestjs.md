<h1>웹 프레임워크 Nestjs</h1>
<h3>NestJS 소개</h3>
<ul>
  <li>NestJS는 Angular의 아키텍처와 디자인 패턴에서 영감을 받아 만들어진 프레임워크이다.</li>
  <li>모듈, 컨트롤러, 서비스, 의존성 주입 등의 개념을 사용하여 코드를 구조화한다.</li>
  <li>TypeScript를 기본 언어로 사용하여 타입 안정성과 개발 생산성을 높인다.</li>
  <li>Express.js나 Fastify.js와 같은 프레임워크 위에서 동작한다.</li>
</ul>
<h3>NestJS 설치 및 프로젝트 생성</h3>
<ul>
  <li>NestJS를 시작하려면 먼저 NestJS CLI를 설치해야 한다.</li>
</ul>
<pre><code class="language-bash">npm install -g @nestjs/cli</code></pre>
<ul>
  <li>NestJS CLI를 사용하여 새로운 프로젝트를 생성한다.</li>
</ul>
<pre><code class="language-bash">nest new my-project</code></pre>
<ul>
  <li>프로젝트가 생성되면 다음 명령어로 애플리케이션을 실행할 수 있다.</li>
</ul>
<pre><code class="language-bash">cd my-project
npm run start</code></pre>
<h3>NestJS 애플리케이션 라이프사이클</h3>
<ul>
  <li>NestJS 애플리케이션의 요청 처리 흐름은 다음과 같다.
    <ol>
      <li>인커밍 요청(Incoming Request)</li>
      <li>미들웨어 (Middleware)</li>
      <li>가드 (Guards)</li>
      <li>인터셉터 (pre-controller)(Interceptors (pre-controller))</li>
      <li>파이프(Pipes)</li>
      <li>컨트롤러 핸들러 (Controller Handler)</li>
      <li>서비스 (Services)</li>
      <li>인터셉터 (post-request)(Interceptors(post-request))</li>
      <li>응답 (Response)</li>
    </ol>
  </li>
</ul>
<h3>미들웨어(Middleware)</h3>
<ul>
  <li>미들웨어는 라우트 핸들러 이전에 실행되는 함수.</li>
  <li>요청 객체와 응답 객체에 접근하여 데이터를 조작하거나 유효성을 검사할 수 있음.</li>
  <li>미들웨어는 @Injectable() 데코레이터로 선언된 클래스에 NestMiddleware 인터페이스를 구현한다.</li>
  <li>미들웨어는 모듈의 configure() 메서드에서 설정됨.</li>
</ul>
<pre><code class="language-typescript">import { Injectable, NestMiddleware } from '@nestjs/common';
import { Request, Response, NextFunction } from 'express';

@Injectable()
export class LoggerMiddleware implements NestMiddleware {
  use(req: Request, res: Response, next: NextFunction) {
    console.log('Request...');
    next();
  }
}</code></pre>
<h3>가드(Guards)</h3>
<ul>
  <li>가드는 인증 및 인가를 처리하는 역할을 한다.</li>
  <li>@Injectable() 데코레이터로 선언된 클래스에 CanActivate 인터페이스를 구현한다.</li>
  <li>가드는 @UseGuards() 데코레이터를 사용하여 바인딩된다.</li>
</ul>
<pre><code class="language-typescript">import { CanActivate, ExecutionContext, Injectable } from '@nestjs/common';
import { Observable } from 'rxjs';

@Injectable()
export class AuthGuard implements CanActivate {
  canActivate(
    context: ExecutionContext,
  ): boolean | Promise&lt;boolean&gt; | Observable&lt;boolean&gt; {
    // 인증 로직
    return true;
  }
}</code></pre>
<h3>인터셉터 (Interceptors)</h3>
<ul>
  <li>인터셉터는 컨트롤러 메서드 실행 전후에 로직을 삽입할 수 있다.</li>
  <li>@Injectable() 데코레이터로 선언된 클래스에 NestInterceptor 인터페이스를 구현한다.</li>
  <li>인터셉터는 @UseInterceptors() 데코레이터를 사용하여 바인딩된다.</li>
</ul>
<pre><code class="language-typescript">import { CallHandler, ExecutionContext, Injectable, NestInterceptor } from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap } from 'rxjs/operators';

@Injectable()
export class LoggingInterceptor implements NestInterceptor {
  intercept(context: ExecutionContext, next: CallHandler): Observable&lt;any&gt; {
    console.log('Before...');
    const now = Date.now();
    return next
      .handle()
      .pipe(
        tap(() =&gt; console.log(`After... ${Date.now() - now}ms`)),
      );
  }
}</code></pre>
<h3>파이프 (Pipes)</h3>
<ul>
  <li>파이프는 컨트롤러 라우트 핸들러로 진입하기 전에 요청 데이터의 유효성 검사와 변환을 수행한다.</li>
  <li>@Injectable() 데코레이터로 선언된 클래스에 PipeTransform 인터페이스를 구현한다.</li>
  <li>파이프는 @UsePipes() 데코레이터를 통해 바인딩된다.</li>
</ul>
<pre><code class="language-typescript">import { ArgumentMetadata, Injectable, PipeTransform } from '@nestjs/common';

@Injectable()
export class ValidationPipe implements PipeTransform {
  transform(value: any, metadata: ArgumentMetadata) {
    // 유효성 검사 로직
    return value;
  }
}</code></pre>
<h3>예외 필터 (Exception Filters)</h3>
<ul>
  <li>예외 필터는 애플리케이션에서 발생하는 예외를 처리하고 클라이언트에게 적절한 응답을 반환한다.</li>
  <li>@Catch() 데코레이터를 사용하여 예외 필터를 생성한다.</li>
  <li>예외 필터는 @UseFilters() 데코레이터를 통해 바인딩된다.</li>
</ul>
<pre><code class="language-typescript">import { ExceptionFilter, Catch, ArgumentsHost, HttpException } from '@nestjs/common';
import { Request, Response } from 'express';

@Catch(HttpException)
export class HttpExceptionFilter implements ExceptionFilter {
  catch(exception: HttpException, host: ArgumentsHost) {
    const ctx = host.switchToHttp();
    const response = ctx.getResponse&lt;Response&gt;();
    const request = ctx.getRequest&lt;Request&gt;();
    const status = exception.getStatus();

    response
      .status(status)
      .json({
        statusCode: status,
        timestamp: new Date().toISOString(),
        path: request.url,
      });
  }
}</code></pre>
<h3>커스텀 데코레이터</h3>
<ul>
  <li>NestJS에서는 커스텀 데코레이터를 만들어 사용할 수 있다.</li>
  <li>커스텀 데코레이터는 메타데이터를 정의하고 런타임에 활용할 수 있다.</li>
  <li>파라미터 데코레이터, 메서드 데코레이터, 클래스 데코레이터 등을 생성할 수 있다.</li>
</ul>
<pre><code class="language-typescript">import { createParamDecorator, ExecutionContext } from '@nestjs/common';

export const User = createParamDecorator(
  (data: unknown, ctx: ExecutionContext) =&gt; {
    const request = ctx.switchToHttp().getRequest();
    return request.user;
  },
);</code></pre>
<h3>모듈 (Modules)</h3>
<ul>
  <li>NestJS의 모듈은 애플리케이션의 구조를 구성하는 기본 단위이다.</li>
  <li>@Module() 데코레이터를 사용하여 모듈을 정의한다.</li>
  <li>모듈은 providers, controllers, imports, exports 속성을 가질 수 있다.</li>
</ul>
<pre><code class="language-typescript">import { Module } from '@nestjs/common';
import { CatsController } from './cats.controller';
import { CatsService } from './cats.service';

@Module({
  controllers: [CatsController],
  providers: [CatsService],
})
export class CatsModule {}</code></pre>
<h3>의존성 주입 (Dependency Injection)</h3>
<ul>
  <li>NestJS는 의존성 주입 패턴을 사용하여 객체 간의 의존성을 관리함.</li>
  <li>@Injectable() 데코레이터를 통해 주입 가능한 서비스를 정의함.</li>
  <li>생성자 주입을 통해 의존성을 주입 받음.</li>
</ul>
<pre><code class="language-typescript">import { Injectable } from '@nestjs/common';

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
  async findAll(): Promise&lt;Cat[]&gt; {
    return this.catsService.findAll();
  }
}</code></pre>
<h3>프로바이더 (Providers)</h3>
<ul>
  <li>NestJS의 프로바이더는 의존성 주입을 위한 객체를 생성하고 관리함.</li>
  <li>프로바이더는 서비스, 레포지토리, 팩토리, 헬퍼 등 다양한 형태로 사용됨.</li>
  <li>@Injectable() 데코레이터를 사용하여 프로바이더를 정의함.</li>
</ul>
<pre><code class="language-typescript">import { Injectable } from '@nestjs/common';

@Injectable()
export class CatsService {
  private readonly cats: Cat[] = [];

  create(cat: Cat) {
    this.cats.push(cat);
  }

  findAll(): Cat[] {
    return this.cats;
  }
}</code></pre>
<h3>컨트롤러 (Controller)</h3>
<ul>
  <li>NestJS의 컨트롤러는 들어오는 HTTP 요청을 처리하고 클라이언트에게 응답을 반환함.</li>
  <li>@Controller() 데코레이터를 통해 컨트롤러를 정의함.</li>
  <li>컨트롤러는 @Get(), @Post(), @Put(), @Delete() 등의 데코레이터를 사용하여 라우트 핸들러를 정의함.</li>
</ul>
<pre><code class="language-typescript">import { Controller, Get, Post, Body } from '@nestjs/common';

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
}</code></pre>
<h3>서비스 (Services)</h3>
<ul>
  <li>NestJS의 서비스는 애플리케이션의 비즈니스 로직을 캡슐화하고 관리함.</li>
  <li>@Injectable() 데코레이터를 주입하여 서비스를 정의함.</li>
  <li>서비스는 컨트롤러에 주입되어 사용되며, 데이터베이스 작업, 외부 API 호출 등의 작업을 수행함.</li>
</ul>
<pre><code class="language-typescript">import { Injectable } from '@nestjs/common';
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
}</code></pre>
<h3>리포지토리 (Repositories)</h3>
<ul>
  <li>NestJS의 리포지토리는 데이터 저장소와 상호 작용하는 역할을 함.</li>
  <li>리포지토리는 데이터베이스 쿼리, 데이터 조작 등의 작업을 수행함.</li>
  <li>@Injectable() 데코레이터를 사용하여 리포지토리를 정의함.</li>
  <li>TypeORM, Sequelize, Mongoose 등의 ORM/ODM 라이브러리와 함께 사용됨.</li>
</ul>
<pre><code class="language-typescript">import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { Cat } from './entities/cat.entity';

@Injectable()
export class CatsRepository {
  constructor(
    @InjectRepository(Cat)
    private readonly catsRepository: Repository&lt;Cat&gt;,
  ) {}

  async findAll(): Promise&lt;Cat[]&gt; {
    return this.catsRepository.find();
  }

  async create(cat: Cat): Promise&lt;Cat&gt; {
    return this.catsRepository.save(cat);
  }
}</code></pre>
<h3>
DTO (Data Transfer Objects)</h3>
<ul>
  <li>NestJS의 DTO는 네트워크를 통해 전송되는 데이터의 구조를 정의함.</li>
  <li>DTO는 요청과 응답의 데이터 형식을 지정하고 유효성 검사에 사용됨.</li>
  <li>클래스 기반의 DTO를 사용하며, 속성에 대한 타입과 유효성 검사 규칙을 정의함.</li>
</ul>
<pre><code class="language-typescript">export class CreateCatDto {
  @IsString()
  name: string;

  @IsInt()
  age: number;

  @IsString()
  breed: string;
}</code></pre>
<h3>유효성 검사 (Validation)</h3>
<ul>
  <li>NestJS는 요청 데이터의 유효성 검사를 위한 파이프를 제공함.</li>
  <li>class-validator 라이브러리를 사용하여 DTO에 유효성 검사 규칙을 정의함.</li>
  <li>ValidationPipe를 사용하여 요청 데이터의 유효성을 검사함.</li>
</ul>
<pre><code class="language-typescript">@Controller('cats')
export class CatsController {
  @Post()
  @UsePipes(ValidationPipe)
  async create(@Body() createCatDto: CreateCatDto) {
    // ...
  }
}</code></pre>
<h3>인증 및 인가 (Authentication &amp; Authorization)</h3>
<ul>
  <li>NestJS는 인증과 인가를 처리하기 위한 가드와 전략을 제공함.</li>
  <li>Passport 라이브러리를 사용하여 인증 전략을 구현할 수 있음.</li>
  <li>JWT(Json Web Token)를 사용한 인증 예시</li>
</ul>
<pre><code class="language-typescript">import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { ExtractJwt, Strategy } from 'passport-jwt';

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy) {
  constructor() {
    super({
      jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
      secretOrKey: 'secretKey',
    });
  }

  async validate(payload: any) {
    return { userId: payload.sub, username: payload.username };
  }
}</code></pre>
<ul>
  <li>가드를 사용하여 인증된 사용자만 엑세스할 수 있도록 제어 할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { Injectable, CanActivate, ExecutionContext } from '@nestjs/common';
import { AuthService } from './auth.service';

@Injectable()
export class AuthGuard implements CanActivate {
  constructor(private readonly authService: AuthService) {}

  async canActivate(context: ExecutionContext): Promise&lt;boolean&gt; {
    const request = context.switchToHttp().getRequest();
    const token = request.headers.authorization;
    const user = await this.authService.validateToken(token);
    request.user = user;
    return true;
  }
}</code></pre>
<h3>로깅 (Logging)</h3>
<ul>
  <li>NestJS는 로깅을 위한 내장 로거를 제공함.</li>
  <li>Winston 라이브러리를 사용하여 커스텀 로거를 구현할 수 있음.</li>
</ul>
<pre><code class="language-typescript">async function bootstrap() {
  const app = await NestFactory.create(AppModule, {
    logger: new Logger(),
  });

  await app.listen(3000);
}
bootstrap();</code></pre>
<h3>구성 (Configuration)</h3>
<ul>
  <li>NestJS는 애플리케이션 구성을 위한 ConfigModule을 제공함.</li>
  <li>dotenv 라이브러리를 사용하여 환경 변수 파일(.env)에서 구성 값을 로드할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { Module } from '@nestjs/common';
import { ConfigModule } from '@nestjs/config';

@Module({
  imports: [
    ConfigModule.forRoot({
      envFilePath: '.env',
    }),
  ],
})
export class AppModule {}</code></pre>
<h3>테스팅 (Testing)</h3>
<ul>
  <li>NestJS는 Jest 테스트 프레임워크를 사용하여 단위 테스트와 통합 테스트를 작성할 수 있음.</li>
  <li>@nestjs/testing 패키지를 사용하여 테스트에 필요한 유틸리티와 모듈을 제공함.</li>
</ul>
<pre><code class="language-typescript">import { Test, TestingModule } from '@nestjs/testing';
import { CatsController } from './cats.controller';
import { CatsService } from './cats.service';

describe('CatsController', () =&gt; {
  let controller: CatsController;

  beforeEach(async () =&gt; {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [CatsController],
      providers: [CatsService],
    }).compile();

    controller = module.get&lt;CatsController&gt;(CatsController);
  });

  it('should return an array of cats', () =&gt; {
    const result = ['cat1', 'cat2'];
    jest.spyOn(controller, 'findAll').mockImplementation(() =&gt; result);
    expect(controller.findAll()).toBe(result);
  });
});</code></pre>
<h3>OpenAPI (Swagger)</h3>
<ul>
  <li>NestJS는 OpenAPI(Swagger) 문서 생성을 지원함.</li>
  <li>@nestjs/swagger 패키지를 사용하여 API 문서를 자동으로 생성할 수 있음.</li>
  <li>컨트롤러와 DTO에 적절한 데코레이터를 추가하여 API 문서를 보강할 수 있음.</li>
  <li>아래처럼 작성 후 <code>localhost:3000/docs</code>에 진입하면 API 문서를 볼 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { NestFactory } from '@nestjs/core';
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
bootstrap();</code></pre>
<h3>GraphQL</h3>
<ul>
  <li>NestJS는 GraphQL API 구축을 지원함.</li>
  <li>@nestjs/graphql 패키지를 사용하여 GraphQL 스키마, 리졸버, 모듈을 정의할 수 있음.</li>
  <li>Apollo Server와 통합되어 GraphQL 서버를 쉽게 구성할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { Module } from '@nestjs/common';
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
export class AppModule {}</code></pre>
<h3>웹 소켓 (WebSocket)</h3>
<ul>
  <li>NestJS는 웹 소켓을 사용한 실시간 통신을 지원함.</li>
  <li>@nestjs/websockets 패키지를 사용하여 웹 소켓 게이트웨이와 이벤트 핸들러를 정의할 수 있음.</li>
  <li>Socket.IO 라이브러리와 통합되어 웹 소켓 서버를 구성할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { SubscribeMessage, WebSocketGateway } from '@nestjs/websockets';

@WebSocketGateway()
export class EventsGateway {
  @SubscribeMessage('events')
  handleEvent(client: any, data: any): string {
    return data;
  }
}</code></pre>
<h3>CQRS (Command Query Responsibility Segregation)</h3>
<ul>
  <li>NestJS는 CQRS 패턴을 지원함.</li>
  <li>@nestjs/cqrs 패키지를 사용하여 Command, Query, EventBus 등의 개념을 구현할 수 있음.</li>
  <li>CQRS 패턴을 통해 읽기와 쓰기 책임을 분리하고 확장성과 유지보수성을 향상시킬 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { Module } from '@nestjs/common';
import { CqrsModule } from '@nestjs/cqrs';
import { CommandHandlers } from './commands/handlers';
import { QueryHandlers } from './queries/handlers';
import { EventHandlers } from './events/handlers';

@Module({
  imports: [CqrsModule],
  providers: [...CommandHandlers, ...QueryHandlers, ...EventHandlers],
})
export class AppModule {}</code></pre>
<h3>마이크로서비스 (Microservices)</h3>
<ul>
  <li>NestJS는 마이크로서비스 아키텍처를 지원함.</li>
  <li>@nestjs/microservices 패키지를 사용하여 마이크로서비스 간 통신을 구현할 수 있음.</li>
  <li>TCP, Redis, NATS, RabbitMQ, Kafka 등 다양한 전송 방식을 사용할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { NestFactory } from '@nestjs/core';
import { Transport, MicroserviceOptions } from '@nestjs/microservices';
import { AppModule } from './app.module';

async function bootstrap() {
  const app = await NestFactory.createMicroservice&lt;MicroserviceOptions&gt;(
    AppModule,
    {
      transport: Transport.TCP,
    },
  );
  await app.listen();
}
bootstrap();</code></pre>
<h3>서버 사이드 렌더링 (Server-Side Rendering)</h3>
<ul>
  <li>NestJS는 서버 사이드 렌더링을 지원함.</li>
  <li>@nestjs/platform-express 패키지를 사용하여 Express.js 기반의 서버를 구성할 수 있음.</li>
  <li>Next.js, Nuxt.js 등의 프레임워크와 통합하여 서버 사이드 렌더링을 구현할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { NestExpressApplication } from '@nestjs/platform-express';
import { join } from 'path';

async function bootstrap() {
  const app = await NestFactory.create&lt;NestExpressApplication&gt;(AppModule);

  app.useStaticAssets(join(__dirname, '..', 'public'));
  app.setBaseViewsDir(join(__dirname, '..', 'views'));
  app.setViewEngine('hbs');

  await app.listen(3000);
}
bootstrap();</code></pre>
<h3>Health Checks</h3>
<ul>
  <li>NestJS는 애플리케이션의 Health Check 기능을 제공함.</li>
  <li>@nestjs/terminus 패키지를 사용하여 Health Check 엔드포인트를 구성할 수 있음.</li>
  <li>데이터베이스, 외부 서비스 등의 상태를 확인하고 모니터링할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { Controller, Get } from '@nestjs/common';
import { HealthCheck, HealthCheckService, TypeOrmHealthIndicator, MemoryHealthIndicator } from '@nestjs/terminus';

@Controller('health')
export class HealthController {
  constructor(
    private health: HealthCheckService,
    private db: TypeOrmHealthIndicator,
    private memory: MemoryHealthIndicator,
  ) {}

  @Get()
  @HealthCheck()
  check() {
    return this.health.check([
      () =&gt; this.db.pingCheck('database'),
      () =&gt; this.memory.checkHeap('memory_heap', 200 * 1024 * 1024),
    ]);
  }
}</code></pre>
<h3>GRPC</h3>
<ul>
  <li>NestJS는 GRPC를 지원함.</li>
  <li>@grpc/grpc-js 및 @grpc/proto-loader 패키지를 사용하여 GRPC 서버와 클라이언트를 구현할 수 있음.</li>
  <li>프로토콜 버퍼(Protocol Buffers)를 사용하여 서비스 정의와 데이터 직렬화를 처리함.</li>
</ul>
<pre><code class="language-typescript">import { Controller } from '@nestjs/common';
import { GrpcMethod } from '@nestjs/microservices';

interface IHeroService {
  findOne(data: { id: number }): Hero;
}

@Controller()
export class HeroController implements IHeroService {
  @GrpcMethod('HeroService', 'FindOne')
  findOne(data: { id: number }): Hero {
    const items = [
      { id: 1, name: 'John' },
      { id: 2, name: 'Doe' },
    ];
    return items.find(({ id }) =&gt; id === data.id);
  }
}</code></pre>
<h3>Task Scheduling</h3>
<ul><li>NestJS는 작업 스케줄링 기능을 제공함.</li>
  <li>@nestjs/schedule 패키지를 사용하여 cron 작업, 간격 작업 등을 정의할 수 있음.</li>
  <li>데이터 정리, 알림 발송, 백그라운드 작업 등에 활용할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { Injectable, Logger } from '@nestjs/common';
import { Cron, CronExpression, Interval, Timeout } from '@nestjs/schedule';

@Injectable()
export class TasksService {
  private readonly logger = new Logger(TasksService.name);

  @Cron(CronExpression.EVERY_30_SECONDS)
  handleCron() {
    this.logger.debug('Called every 30 seconds');
  }

  @Interval(10000)
  handleInterval() {
    this.logger.debug('Called every 10 seconds');
  }

  @Timeout(5000)
  handleTimeout() {
    this.logger.debug('Called once after 5 seconds');
  }
}</code></pre>
<h3>파일 업로드</h3>
<ul>
  <li>NestJS는 파일 업로드 기능을 제공함.</li>
  <li>multer 미들웨어를 사용하여 파일 업로드를 처리할 수 있음.</li>
  <li>@UseInterceptors(FileInterceptor()) 데코레이터를 사용하여 컨트롤러 메서드에 파일 업로드 기능을 추가할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { Controller, Post, UploadedFile, UseInterceptors } from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import { diskStorage } from 'multer';

@Controller('upload')
export class UploadController {
  @Post()
  @UseInterceptors(FileInterceptor('file', {
    storage: diskStorage({
      destination: './uploads',
      filename: (req, file, cb) =&gt; {
        const randomName = Array(32).fill(null).map(() =&gt; (Math.round(Math.random() * 16)).toString(16)).join('');
        cb(null, `${randomName}${extname(file.originalname)}`);
      }
    })
  }))
  uploadFile(@UploadedFile() file) {
    console.log(file);
  }
}</code></pre>
<h3>국제화 (i18n)</h3>
<ul>
  <li>NestJS는 국제화(i18n)를 지원함.</li>
  <li>@nestjs/i18n 패키지를 사용하여 다국어 지원을 구현할 수 있음.</li>
  <li>JSON, YAML, PO 파일 등 다양한 형식의 번역 파일을 사용할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { Controller, Get } from '@nestjs/common';
import { I18n, I18nContext, I18nService } from 'nestjs-i18n';

@Controller()
export class AppController {
  constructor(private readonly i18n: I18nService) {}

  @Get()
  getHello(@I18n() i18n: I18nContext): string {
    return i18n.t('hello');
  }
}</code></pre>
<h3>압축 (Compression)</h3>
<ul>
  <li>NestJS는 응답 압축 기능을 제공함.</li>
  <li>compression 미들웨어를 사용하여 응답 데이터를 압축할 수 있음.</li>
  <li>Gzip, Deflate 등의 압축 알고리즘을 지원함.</li>
</ul>
<pre><code class="language-typescript">import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import * as compression from 'compression';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  app.use(compression());
  await app.listen(3000);
}
bootstrap();</code></pre>
<h3>보안 (Security)</h3>
<ul>
  <li>NestJS는 다양한 보안 기능을 제공함.</li>
  <li>Helmet 미들웨어를 사용하여 일반적인 웹 취약점을 방어할 수 있음.</li>
  <li>CORS(Cross-Origin Resource Sharing) 미들웨어를 사용하여 교차 출처 리소스 공유를 제어할 수 있음.</li>
  <li>CSRF(Cross-Site Request Forgery) 방어를 위한 토큰 기반 보호 기능을 제공함.</li>
  <li>Express의 다양한 보안 미들웨어와 함께 사용할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import * as helmet from 'helmet';
import * as csurf from 'csurf';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  app.use(helmet());
  app.enableCors();
  app.use(csurf());
  await app.listen(3000);
}
bootstrap();</code></pre>
<h3>로깅 (Logging)</h3>
<ul>
  <li>NestJS는 로깅을 위한 내장 로거를 제공함.</li>
  <li>winston, bunyan, pino 등 다양한 로깅 라이브러리와 통합할 수 있음.</li>
  <li>로그 레벨, 출력 형식, 로그 저장소 등을 커스터마이징할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { WinstonModule, utilities as nestWinstonModuleUtilities } from 'nest-winston';
import * as winston from 'winston';

async function bootstrap() {
  const app = await NestFactory.create(AppModule, {
    logger: WinstonModule.createLogger({
      transports: [
        new winston.transports.Console({
          format: winston.format.combine(
            winston.format.timestamp(),
            nestWinstonModuleUtilities.format.nestLike(),
          ),
        }),
        new winston.transports.File({ filename: 'application.log' }),
      ],
    }),
  });
  await app.listen(3000);
}
bootstrap();</code></pre>
<h3>모니터링 (Monitoring)</h3>
<ul>
  <li>NestJS 애플리케이션의 모니터링을 위해 다양한 도구와 서비스를 사용할 수 있음.</li>
  <li>Prometheus, Grafana, Datadog, New Relic 등의 모니터링 도구와 연동할 수 있음.</li>
  <li>@nestjs/terminus를 사용하여 Health Check 엔드포인트를 구성하고 모니터링할 수 있음.</li>
</ul>
<pre><code class="language-typescript">import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { PrometheusModule } from '@willsoto/nestjs-prometheus';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  const prometheus = app.get(PrometheusModule);
  prometheus.collectDefaultMetrics();
  await app.listen(3000);
}
bootstrap();</code></pre>

<ol>
  <li>Passport를 사용한 소셜 로그인 (OAuth)
    <ul>
      <li>Passport는 Node.js에서 인증을 위해 사용되는 미들웨어로, NestJS에서도 활용할 수 있음.</li>
      <li>@nestjs/passport 패키지를 사용하여 Passport 기반 인증을 구현할 수 있음.</li>
      <li>Google, Facebook, Twitter 등의 소셜 로그인을 지원하며, OAuth 1.0, OAuth 2.0 프로토콜을 사용함.</li>
    </ul>
    <pre><code class="language-typescript">import { UseGuards } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
@UseGuards(AuthGuard('google'))
@Get('google')
async googleAuth(@Req() req) {
// 구글 인증 처리
}
@UseGuards(AuthGuard('google'))
@Get('google/redirect')
googleAuthRedirect(@Req() req) {
return this.authService.googleLogin(req);
}</code></pre>
  </li>
  <li>Bull을 사용한 작업 큐 (Job Queue)
    <ul>
      <li>Bull은 Node.js에서 작업 큐를 구현하기 위한 라이브러리로, NestJS에서도 사용할 수 있음.</li>
      <li>@nestjs/bull 패키지를 사용하여 Bull 기반의 작업 큐를 구현할 수 있음.</li>
      <li>이메일 발송, 파일 처리, 배치 작업 등 백그라운드에서 실행되어야 하는 작업들을 큐에 저장하고 처리할 수 있음.</li>
    </ul>
    <pre><code class="language-typescript">import { Process, Processor } from '@nestjs/bull';
import { Job } from 'bull';
@Processor('audio')
export class AudioProcessor {
@Process()
async transcode(job: Job<unknown>) {
let progress = 0;
for (let i = 0; i < 100; i++) {
await doSomething(job.data);
progress += 10;
job.progress(progress);
}
return {};
}
}</code></pre>
  </li>
  <li>TypeORM/Sequelize/Mongoose를 사용한 데이터베이스 통합
    <ul>
      <li>NestJS에서는 다양한 데이터베이스 통합을 위한 패키지를 제공함.</li>
      <li>@nestjs/typeorm, @nestjs/sequelize, @nestjs/mongoose 패키지를 사용하여 각 ORM/ODM 라이브러리와 통합할 수 있음.</li>
      <li>데이터베이스 연결, 엔티티 정의, 리포지토리 패턴 등을 손쉽게 구현할 수 있음.</li>
    </ul>
    <pre><code class="language-typescript">// TypeORM 예시
import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';
@Entity()
export class User {
@PrimaryGeneratedColumn()
id: number;
@Column()
firstName: string;
@Column()
lastName: string;
@Column()
email: string;
}</code></pre>
  </li>
  <li>gRPC를 사용한 마이크로서비스 간 통신
    <ul>
      <li>gRPC는 고성능 RPC 프레임워크로, NestJS에서도 마이크로서비스 간 통신에 사용할 수 있음.</li>
      <li>@nestjs/microservices 패키지를 사용하여 gRPC 기반의 마이크로서비스를 구현할 수 있음.</li>
      <li>Protocol Buffers를 사용하여 서비스 인터페이스를 정의하고, 효율적인 데이터 직렬화와 높은 성능을 제공함.</li>
    </ul>
    <pre><code class="language-typescript">// gRPC 컨트롤러 예시
@Controller()
export class AppController {
  @GrpcMethod('AppController', 'Ping')
  ping(data: PingRequest, metadata: Metadata, call: ServerUnaryCall&lt;PingRequest, PingResponse&gt;): PingResponse {
    const { message } = data;
    return { message: `Pong ${message}` };
  }
}</code></pre>
  </li>
  <li>Redis를 사용한 캐싱
    <ul>
      <li>Redis는 인메모리 데이터 스토어로, NestJS 애플리케이션의 캐싱 솔루션으로 사용할 수 있음.</li>
      <li>@nestjs/common의 Cache 모듈을 사용하여 Redis 기반의 캐싱을 구현할 수 있음.</li>
      <li>자주 사용되는 데이터나 계산 결과를 캐싱하여 애플리케이션의 성능을 향상시킬 수 있음.</li>
    </ul>
    <pre><code class="language-typescript">import { CACHE_MANAGER, Inject } from '@nestjs/common';
import { Cache } from 'cache-manager';
constructor(@Inject(CACHE_MANAGER) private cacheManager: Cache) {}
async getCachedData(key: string) {
const cachedData = await this.cacheManager.get(key);
if (cachedData) {
return cachedData;
}
const data = await this.fetchData();
await this.cacheManager.set(key, data);
return data;
}</code></pre>
  </li>
  <li>Swagger를 사용한 API 문서 자동 생성
    <ul>
      <li>Swagger는 RESTful API의 문서화를 위한 오픈소스 도구로, NestJS에서도 활용할 수 있음.</li>
      <li>@nestjs/swagger 패키지를 사용하여 API 문서를 자동으로 생성할 수 있음.</li>
      <li>컨트롤러, DTO 등에 적절한 어노테이션을 추가하면 문서가 자동으로 생성되어 유지보수와 협업이 용이해짐.</li>
    </ul>
    <pre><code class="language-typescript">import { ApiProperty } from '@nestjs/swagger';
export class CreateCatDto {
@ApiProperty({ description: 'The name of the cat' })
name: string;
@ApiProperty({ description: 'The age of the cat' })
age: number;
@ApiProperty({ description: 'The breed of the cat' })
breed: string;
}</code></pre>
  </li>
  <li>Jest를 사용한 단위 테스트 및 E2E 테스트
    <ul>
      <li>Jest는 JavaScript 테스팅 프레임워크로, NestJS 애플리케이션의 테스트에 사용할 수 있음.</li>
      <li>@nestjs/testing 패키지를 사용하여 단위 테스트와 E2E 테스트를 작성할 수 있음.</li>
      <li>테스트 주도 개발(TDD)을 통해 애플리케이션의 품질과 안정성을 높일 수 있음.</li>
    </ul>
    <pre><code class="language-typescript">// 단위 테스트 예시
describe('CatsController', () =&gt; {
  let catsController: CatsController;
  let catsService: CatsService;
beforeEach(async () => {
const moduleRef = await Test.createTestingModule({
controllers: [CatsController],
providers: [CatsService],
}).compile();
catsService = moduleRef.get&lt;CatsService&gt;(CatsService);
catsController = moduleRef.get&lt;CatsController&gt;(CatsController);
});
describe('findAll', () => {
it('should return an array of cats', async () => {
const result = ['test'];
jest.spyOn(catsService, 'findAll').mockImplementation(() => result);
expect(await catsController.findAll()).toBe(result);
});
});
});</code></pre>
  </li>
  <li>PM2/Forever를 사용한 프로세스 관리
    <ul>
      <li>PM2와 Forever는 Node.js 애플리케이션의 프로세스 관리를 위한 도구로, NestJS에서도 사용할 수 있음.</li>
      <li>PM2 또는 Forever를 사용하여 애플리케이션을 백그라운드에서 실행하고, 프로세스 모니터링, 자동 재시작 등의 기능을 활용할 수 있음.</li>
    </ul>
    <pre><code class="language-bash"># PM2 사용 예시
pm2 start dist/main.js --name my-app
pm2 stop my-app
pm2 restart my-app
pm2 delete my-app</code></pre>
  </li>
  <li>Elasticsearch를 사용한 검색 기능 구현
    <ul>
      <li>Elasticsearch는 분산형 검색 및 분석 엔진으로, NestJS 애플리케이션에 강력한 검색 기능을 추가할 수 있음.</li>
      <li>@nestjs/elasticsearch 패키지를 사용하여 Elasticsearch와 통합할 수 있음.</li>
      <li>데이터 색인, 검색, 집계 등의 기능을 활용하여 사용자에게 풍부한 검색 경험을 제공할 수 있음.</li>
    </ul>
    <pre><code class="language-typescript">import { Injectable } from '@nestjs/common';
import { ElasticsearchService } from '@nestjs/elasticsearch';
@Injectable()
export class SearchService {
constructor(private readonly elasticsearchService: ElasticsearchService) {}
async search(text: string) {
const result = await this.elasticsearchService.search({
index: 'products',
body: {
query: {
multi_match: {
query: text,
fields: ['title', 'description']
}
}
}
});
return result.hits.hits;
}
}</code></pre>
  </li>
  <li>AWS Lambda, GCP Functions, Azure Functions 등 서버리스 환경에서의 NestJS 활용
    <ul>
      <li>NestJS 애플리케이션은 서버리스 환경에서도 실행될 수 있음.</li>
      <li>@nestjs/serverless 패키지를 사용하여 AWS Lambda, GCP Functions, Azure Functions 등에 배포할 수 있음.</li>
      <li>서버리스 환경에서 NestJS의 모듈화된 구조와 의존성 주입 등의 기능을 그대로 활용할 수 있음.</li>
    </ul>
    <pre><code class="language-typescript">// serverless.yml 파일 예시
service: my-nest-app
provider:
name: aws
runtime: nodejs14.x
functions:
main:
handler: dist/lambda.handler
events:
- http:
path: /
method: ANY
- http:
path: /{proxy+}
method: ANY</code></pre>
  </li>
</ol>
<h3>마무리</h3>
<ul>
  <li>NestJS는 Angular의 아키텍처와 디자인 패턴에서 영감을 받아 만들어진 프레임워크로, 모듈화, 의존성 주입, 데코레이터 등의 개념을 사용하여 확장 가능하고 유지보수하기 쉬운 서버 사이드 애플리케이션을 구축할 수 있음.</li>
  <li>NestJS의 장점은 TypeScript를 기본으로 사용하여 타입 안전성을 제공하고, Express &amp; Fastify와 같은 강력한 웹 프레임워크 위에서 동작하며, 다양한 플러그인과 라이브러리를 통해 기능을 확장할 수 있다는 점.</li>
  <li>NestJS는 테스팅, 로깅, 구성, OpenAPI 문서 생성, GraphQL, 웹 소켓, CQRS, 마이크로서비스 등 다양한 기능을 지원하며 엔터프라이즈급 애플리케이션 개발에 적합함.</li>
  <li>NestJS를 사용하면 코드의 재사용성을 높이고, 애플리케이션의 구조를 명확하게 유지하며, 테스트 가능한 코드를 작성할 수 있음. 또한 활발한 커뮤니티와 풍부한 생태계를 지녀 개발자들이 쉽게 학습하고 적용할 수 있음.</li>
  <li>실제 프로젝트에서는 NestJS의 공식 문서를 참조하고 모범 사례를 따르며, 팀의 요구사항에 맞게 아키텍처와 패턴을 적용하는 것이 중요. NestJS의 모듈화된 구조와 의존성 주입 패턴을 활용하여 느슨한 결합과 높은 응집력을 갖는 코드를 작성하고, 테스트 주도 개발(TDD)을 통해 코드의 품질을 유지하는 것이 좋음.</li>
</ul>