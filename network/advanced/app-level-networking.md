# 애플리케이션 레벨 네트워킹

1. RESTful API 설계 및 구현
    1. REST 아키텍처 원칙
        1. 리소스 중심 설계
            ```plaintext
            # 좋은 URL 설계 예시
            GET    /users           # 사용자 목록 조회
            POST   /users           # 새 사용자 생성
            GET    /users/{id}      # 특정 사용자 조회
            PUT    /users/{id}      # 사용자 정보 수정
            DELETE /users/{id}      # 사용자 삭제
            ```

        2. HTTP 메서드 활용
            ```python
            from flask import Flask, request
            app = Flask(__name__)

            @app.route('/users', methods=['GET'])
            def get_users():
                return {'users': users_list}

            @app.route('/users/<int:user_id>', methods=['PUT'])
            def update_user(user_id):
                user = request.get_json()
                # 사용자 정보 업데이트 로직
                return {'status': 'success'}
            ```
    
    2. API 버저닝
        1. URL 기반 버저닝
            ```plaintext
            /api/v1/users
            /api/v2/users
            ```

        2. 헤더 기반 버저닝
            ```python
            @app.route('/api/users')
            def get_users():
                version = request.headers.get('API-Version', '1')
                if version == '1':
                    return v1_response()
                elif version == '2':
                    return v2_response()
            ```

4. gRPC 구현
    1. Protocol Buffers 정의
        ```protobuf
        syntax = "proto3";

        package user;

        service UserService {
            rpc GetUser (UserRequest) returns (UserResponse) {}
            rpc ListUsers (ListUsersRequest) returns (stream UserResponse) {}
            rpc UpdateUser (UpdateUserRequest) returns (UserResponse) {}
        }

        message UserRequest {
            string user_id = 1;
        }

        message UserResponse {
            string user_id = 1;
            string name = 2;
            string email = 3;
        }
        ```

    2. gRPC 서버 구현
        ```python
        from concurrent import futures
        import grpc
        import user_pb2
        import user_pb2_grpc

        class UserService(user_pb2_grpc.UserServiceServicer):
            def GetUser(self, request, context):
                user = find_user(request.user_id)
                return user_pb2.UserResponse(
                    user_id=user.id,
                    name=user.name,
                    email=user.email
                )

            def ListUsers(self, request, context):
                users = get_users()
                for user in users:
                    yield user_pb2.UserResponse(
                        user_id=user.id,
                        name=user.name,
                        email=user.email
                    )

        def serve():
            server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
            user_pb2_grpc.add_UserServiceServicer_to_server(
                UserService(), server)
            server.add_insecure_port('[::]:50051')
            server.start()
            server.wait_for_termination()
        ```

3. WebSocket 통신
    1. WebSocket 서버 구현
        ```python
        from fastapi import FastAPI, WebSocket
        from typing import List

        app = FastAPI()

        class ConnectionManager:
            def __init__(self):
                self.active_connections: List[WebSocket] = []

            async def connect(self, websocket: WebSocket):
                await websocket.accept()
                self.active_connections.append(websocket)

            async def broadcast(self, message: str):
                for connection in self.active_connections:
                    await connection.send_text(message)

        manager = ConnectionManager()

        @app.websocket("/ws")
        async def websocket_endpoint(websocket: WebSocket):
            await manager.connect(websocket)
            try:
                while True:
                    data = await websocket.receive_text()
                    await manager.broadcast(f"Message: {data}")
            except WebSocketDisconnect:
                manager.active_connections.remove(websocket)
        ```

    2. WebSocket 클라이언트
        ```javascript
        const ws = new WebSocket('ws://localhost:8000/ws');

        ws.onopen = () => {
            console.log('Connected to WebSocket');
        };

        ws.onmessage = (event) => {
            console.log('Received:', event.data);
        };

        ws.onerror = (error) => {
            console.error('WebSocket error:', error);
        };

        ws.onclose = () => {
            console.log('Disconnected from WebSocket');
        };

        // 메시지 전송
        function sendMessage(message) {
            ws.send(JSON.stringify(message));
        }
        ```

4. GraphQL API
    1. 스키마 정의
        ```graphql
        type User {
            id: ID!
            name: String!
            email: String!
            posts: [Post!]!
        }

        type Post {
            id: ID!
            title: String!
            content: String!
            author: User!
        }

        type Query {
            user(id: ID!): User
            users: [User!]!
            post(id: ID!): Post
            posts: [Post!]!
        }

        type Mutation {
            createUser(name: String!, email: String!): User!
            createPost(title: String!, content: String!, authorId: ID!): Post!
        }
        ```

    2. GraphQL 서버 구현
        ```python
        from ariadne import QueryType, MutationType, make_executable_schema
        from ariadne.asgi import GraphQL

        query = QueryType()
        mutation = MutationType()

        @query.field("users")
        async def resolve_users(*_):
            return await User.objects.all()

        @query.field("user")
        async def resolve_user(*_, id):
            return await User.objects.get(id=id)

        @mutation.field("createUser")
        async def resolve_create_user(*_, name, email):
            user = await User.objects.create(name=name, email=email)
            return user

        schema = make_executable_schema(type_defs, [query, mutation])
        app = GraphQL(schema, debug=True)
        ```

    3. GraphQL 클라이언트
        ```javascript
        async function fetchUser(id) {
            const query = `
                query GetUser($id: ID!) {
                    user(id: $id) {
                        id
                        name
                        email
                        posts {
                            id
                            title
                        }
                    }
                }
            `;
            
            const response = await fetch('/graphql', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({
                    query,
                    variables: { id },
                }),
            });
            
            return response.json();
        }
        ```

5. 성능 최적화
    1. 캐싱 전략
        1. HTTP 캐싱
            ```python
            from flask import Flask, make_response

            @app.route('/api/data')
            def get_data():
                response = make_response(json.dumps(data))
                response.headers['Cache-Control'] = 'public, max-age=300'
                response.headers['ETag'] = generate_etag(data)
                return response
            ```

        2. 애플리케이션 캐싱
            ```python
            from functools import lru_cache

            @lru_cache(maxsize=1000)
            def get_user_data(user_id):
                return database.query(f"SELECT * FROM users WHERE id = {user_id}")
            ```

    2. 연결 풀링
        ```python
        import psycopg2
        from psycopg2 import pool

        connection_pool = psycopg2.pool.SimpleConnectionPool(
            minconn=1,
            maxconn=10,
            database="mydb",
            user="user",
            password="password",
            host="localhost"
        )

        def execute_query(query):
            conn = connection_pool.getconn()
            try:
                with conn.cursor() as cur:
                    cur.execute(query)
                    return cur.fetchall()
            finally:
                connection_pool.putconn(conn)
        ```

6. 에러 처리와 로깅
    1. 에러 처리
        ```python
        from fastapi import FastAPI, HTTPException
        from typing import Optional

        app = FastAPI()

        class CustomError(Exception):
            def __init__(self, message: str, code: str):
                self.message = message
                self.code = code

        @app.exception_handler(CustomError)
        async def custom_error_handler(request, exc):
            return JSONResponse(
                status_code=400,
                content={
                    "error": {
                        "code": exc.code,
                        "message": exc.message
                    }
                }
            )

        @app.get("/users/{user_id}")
        async def get_user(user_id: int):
            user = await find_user(user_id)
            if not user:
                raise CustomError(
                    message="User not found",
                    code="USER_NOT_FOUND"
                )
            return user
        ```

    2. 구조화된 로깅
        ```python
        import structlog
        import logging

        logger = structlog.get_logger()

        def configure_logging():
            logging.basicConfig(level=logging.INFO)
            structlog.configure(
                processors=[
                    structlog.processors.TimeStamper(fmt="iso"),
                    structlog.processors.JSONRenderer()
                ],
                context_class=dict,
                logger_factory=structlog.PrintLoggerFactory(),
                wrapper_class=structlog.BoundLogger,
                cache_logger_on_first_use=True,
            )

        @app.middleware("http")
        async def logging_middleware(request, call_next):
            logger.info(
                "request_started",
                path=request.url.path,
                method=request.method
            )
            
            response = await call_next(request)
            
            logger.info(
                "request_finished",
                path=request.url.path,
                status_code=response.status_code
            )
            
            return response
        ```

7. Key Takeaways
    1. API 설계 원칙
        - 명확한 리소스 구조
        - 적절한 HTTP 메서드 사용
        - 버저닝 전략 수립

    2. 프로토콜 선택
        - REST: 범용적이고 단순한 통신
        - gRPC: 고성능 마이크로서비스 통신
        - WebSocket: 실시간 양방향 통신
        - GraphQL: 유연한 데이터 쿼리

    3. 성능과 안정성
        - 적절한 캐싱 전략
        - 연결 풀링 활용
        - 구조화된 에러 처리
        - 체계적인 로깅