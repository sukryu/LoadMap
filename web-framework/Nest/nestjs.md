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

