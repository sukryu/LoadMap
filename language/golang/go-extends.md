# Go 확장 기능

1. WebSocket 구현
    1. WebSocket 핸들러
        ```go
        // internal/handlers/websocket.go
        package handlers

        import (
            "github.com/gin-gonic/gin"
            "github.com/gorilla/websocket"
            "sync"
        )

        var upgrader = websocket.Upgrader{
            ReadBufferSize:  1024,
            WriteBufferSize: 1024,
            CheckOrigin: func(r *http.Request) bool {
                return true // 실제 환경에서는 적절한 origin 체크 필요
            },
        }

        type WSHandler struct {
            // 연결된 모든 클라이언트 관리
            clients map[*websocket.Conn]bool
            // 브로드캐스트 메시지 채널
            broadcast chan []byte
            // 동시성 제어를 위한 mutex
            mutex sync.RWMutex
        }

        func NewWSHandler() *WSHandler {
            return &WSHandler{
                clients:   make(map[*websocket.Conn]bool),
                broadcast: make(chan []byte),
            }
        }

        // WebSocket 연결 처리
        func (h *WSHandler) HandleWebSocket(c *gin.Context) {
            conn, err := upgrader.Upgrade(c.Writer, c.Request, nil)
            if err != nil {
                c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
                return
            }
            
            // 클라이언트 등록
            h.mutex.Lock()
            h.clients[conn] = true
            h.mutex.Unlock()

            // 연결 종료 시 정리
            defer func() {
                h.mutex.Lock()
                delete(h.clients, conn)
                h.mutex.Unlock()
                conn.Close()
            }()

            // 메시지 읽기 루프
            go h.readPump(conn)
            // 메시지 쓰기 루프
            go h.writePump(conn)
        }

        // 클라이언트로부터 메시지 읽기
        func (h *WSHandler) readPump(conn *websocket.Conn) {
            for {
                _, message, err := conn.ReadMessage()
                if err != nil {
                    if websocket.IsUnexpectedCloseError(err, websocket.CloseGoingAway, websocket.CloseAbnormalClosure) {
                        log.Printf("error: %v", err)
                    }
                    break
                }
                // 브로드캐스트 채널로 메시지 전송
                h.broadcast <- message
            }
        }

        // 브로드캐스트 메시지 전송
        func (h *WSHandler) writePump(conn *websocket.Conn) {
            for message := range h.broadcast {
                h.mutex.RLock()
                for client := range h.clients {
                    if err := client.WriteMessage(websocket.TextMessage, message); err != nil {
                        log.Printf("write error: %v", err)
                        client.Close()
                        delete(h.clients, client)
                    }
                }
                h.mutex.RUnlock()
            }
        }
        ```

    2. 실시간 채팅 구현
        ```go
        // internal/websocket/chat.go
        package websocket

        type ChatMessage struct {
            Type    string `json:"type"`
            Content string `json:"content"`
            User    string `json:"user"`
            Room    string `json:"room"`
        }

        type ChatRoom struct {
            Name     string
            Clients  map[*websocket.Conn]*Client
            Messages chan *ChatMessage
        }

        type Client struct {
            Conn     *websocket.Conn
            User     string
            Room     *ChatRoom
            Send     chan []byte
        }

        type ChatHub struct {
            Rooms    map[string]*ChatRoom
            Register chan *Client
            Messages chan *ChatMessage
            mutex    sync.RWMutex
        }

        func NewChatHub() *ChatHub {
            return &ChatHub{
                Rooms:    make(map[string]*ChatRoom),
                Register: make(chan *Client),
                Messages: make(chan *ChatMessage),
            }
        }

        func (h *ChatHub) Run() {
            for {
                select {
                case client := <-h.Register:
                    h.mutex.Lock()
                    room, exists := h.Rooms[client.Room.Name]
                    if !exists {
                        room = &ChatRoom{
                            Name:     client.Room.Name,
                            Clients:  make(map[*websocket.Conn]*Client),
                            Messages: make(chan *ChatMessage),
                        }
                        h.Rooms[room.Name] = room
                        go h.handleRoom(room)
                    }
                    room.Clients[client.Conn] = client
                    h.mutex.Unlock()

                case message := <-h.Messages:
                    h.mutex.RLock()
                    if room, ok := h.Rooms[message.Room]; ok {
                        room.Messages <- message
                    }
                    h.mutex.RUnlock()
                }
            }
        }

        func (h *ChatHub) handleRoom(room *ChatRoom) {
            for message := range room.Messages {
                data, err := json.Marshal(message)
                if err != nil {
                    continue
                }
                
                for _, client := range room.Clients {
                    select {
                    case client.Send <- data:
                    default:
                        close(client.Send)
                        delete(room.Clients, client.Conn)
                    }
                }
            }
        }
        ```

2. gRPC 통합
    1. Protocol Buffers 정의
        ```protobuf
        // proto/service.proto
        syntax = "proto3";

        package api;

        option go_package = "./proto";

        service UserService {
            rpc GetUser (GetUserRequest) returns (User);
            rpc CreateUser (CreateUserRequest) returns (User);
            rpc UpdateUser (UpdateUserRequest) returns (User);
            rpc DeleteUser (DeleteUserRequest) returns (DeleteUserResponse);
            rpc ListUsers (ListUsersRequest) returns (ListUsersResponse);
        }

        message User {
            uint64 id = 1;
            string username = 2;
            string email = 3;
            string created_at = 4;
            string updated_at = 5;
        }

        message GetUserRequest {
            uint64 id = 1;
        }

        message CreateUserRequest {
            string username = 1;
            string email = 2;
            string password = 3;
        }

        message UpdateUserRequest {
            uint64 id = 1;
            string username = 2;
            string email = 3;
        }

        message DeleteUserRequest {
            uint64 id = 1;
        }

        message DeleteUserResponse {
            bool success = 1;
        }

        message ListUsersRequest {
            int32 page = 1;
            int32 per_page = 2;
        }

        message ListUsersResponse {
            repeated User users = 1;
            int32 total = 2;
        }
        ```

    2. gRPC 서버 구현
        ```go
        // internal/grpc/server.go
        package grpc

        import (
            "context"
            "google.golang.org/grpc"
            pb "myapp/proto"
        )

        type GRPCServer struct {
            pb.UnimplementedUserServiceServer
            userService UserService
        }

        func NewGRPCServer(userService UserService) *GRPCServer {
            return &GRPCServer{
                userService: userService,
            }
        }

        func (s *GRPCServer) GetUser(ctx context.Context, req *pb.GetUserRequest) (*pb.User, error) {
            user, err := s.userService.GetUser(uint(req.Id))
            if err != nil {
                return nil, err
            }

            return &pb.User{
                Id:        uint64(user.ID),
                Username:  user.Username,
                Email:     user.Email,
                CreatedAt: user.CreatedAt.Format(time.RFC3339),
                UpdatedAt: user.UpdatedAt.Format(time.RFC3339),
            }, nil
        }

        func (s *GRPCServer) CreateUser(ctx context.Context, req *pb.CreateUserRequest) (*pb.User, error) {
            user, err := s.userService.CreateUser(&CreateUserInput{
                Username: req.Username,
                Email:    req.Email,
                Password: req.Password,
            })
            if err != nil {
                return nil, err
            }

            return &pb.User{
                Id:        uint64(user.ID),
                Username:  user.Username,
                Email:     user.Email,
                CreatedAt: user.CreatedAt.Format(time.RFC3339),
                UpdatedAt: user.UpdatedAt.Format(time.RFC3339),
            }, nil
        }

        // gRPC 서버 시작
        func StartGRPCServer(userService UserService) error {
            lis, err := net.Listen("tcp", ":50051")
            if err != nil {
                return err
            }

            s := grpc.NewServer()
            pb.RegisterUserServiceServer(s, NewGRPCServer(userService))
            
            log.Printf("gRPC server listening on :50051")
            return s.Serve(lis)
        }
        ```

3. GraphQL 통합
    1. GraphQL 스키마 정의
        ```graphql
        # schemas/schema.graphql
        type User {
            id: ID!
            username: String!
            email: String!
            posts: [Post!]!
            createdAt: String!
            updatedAt: String!
        }

        type Post {
            id: ID!
            title: String!
            content: String!
            author: User!
            comments: [Comment!]!
            createdAt: String!
            updatedAt: String!
        }

        type Comment {
            id: ID!
            content: String!
            author: User!
            post: Post!
            createdAt: String!
        }

        type Query {
            user(id: ID!): User
            users(page: Int, perPage: Int): [User!]!
            post(id: ID!): Post
            posts(page: Int, perPage: Int): [Post!]!
        }

        type Mutation {
            createUser(input: CreateUserInput!): User!
            updateUser(id: ID!, input: UpdateUserInput!): User!
            deleteUser(id: ID!): Boolean!
            
            createPost(input: CreatePostInput!): Post!
            updatePost(id: ID!, input: UpdatePostInput!): Post!
            deletePost(id: ID!): Boolean!
        }

        input CreateUserInput {
            username: String!
            email: String!
            password: String!
        }

        input UpdateUserInput {
            username: String
            email: String
        }

        input CreatePostInput {
            title: String!
            content: String!
        }

        input UpdatePostInput {
            title: String
            content: String
        }
        ```

    2. GraphQL 리졸버
        ```go
        // internal/graphql/resolvers.go
        package graphql

        type Resolver struct {
            userService  UserService
            postService  PostService
        }

        func (r *Resolver) User() UserResolver {
            return &userResolver{r}
        }

        func (r *Resolver) Post() PostResolver {
            return &postResolver{r}
        }

        type userResolver struct{ *Resolver }

        func (r *userResolver) Posts(ctx context.Context, obj *models.User) ([]*models.Post, error) {
            return r.postService.GetUserPosts(obj.ID)
        }

        type postResolver struct{ *Resolver }

        func (r *postResolver) Author(ctx context.Context, obj *models.Post) (*models.User, error) {
            return r.userService.GetUser(obj.UserID)
        }

        func (r *postResolver) Comments(ctx context.Context, obj *models.Post) ([]*models.Comment, error) {
            return r.postService.GetPostComments(obj.ID)
        }

        // Query 리졸버
        func (r *Resolver) Query() QueryResolver {
            return &queryResolver{r}
        }

        type queryResolver struct{ *Resolver }

        func (r *queryResolver) User(ctx context.Context, id string) (*models.User, error) {
            userID, err := strconv.ParseUint(id, 10, 64)
            if err != nil {
                return nil, err
            }
            return r.userService.GetUser(uint(userID))
        }

        func (r *queryResolver) Users(ctx context.Context, page *int, perPage *int) ([]*models.User, error) {
            p := 1
            if page != nil {
                p = *page
            }
            pp := 10
            if perPage != nil {
                pp = *perPage
            }
            return r.userService.ListUsers(p, pp)
        }

        // Mutation 리졸버
        func (r *Resolver) Mutation() MutationResolver {
            return &mutationResolver{r}
        }

        type mutationResolver struct{ *Resolver }

        func (r *mutationResolver) CreateUser(ctx context.Context, input CreateUserInput) (*models.User, error) {
            return r.userService.CreateUser(&input)
        }

        func (r *mutationResolver) UpdateUser(ctx context.Context, id string, input UpdateUserInput) (*models.User, error) {
            userID, err := strconv.ParseUint(id, 10, 64)
            if err != nil {
                return nil, err
            }
            return r.userService.UpdateUser(uint(userID), &input)
        }
        ```

4. 이벤트 소싱
    1. 이벤트 구조
        ```go
        package events

        type Event struct {
            ID        string
            Type      string
            Data      interface{}
            Timestamp time.Time
            Version   int
        }

        type EventStore interface {
            SaveEvent(event *Event) error
            GetEvents(aggregateID string) ([]*Event, error)
        }

        // 카프카 이벤트 스토어 구현
        type KafkaEventStore struct {
            producer sarama.SyncProducer
            consumer sarama.Consumer
            topic    string
        }

        func NewKafkaEventStore(brokers []string, topic string) (*KafkaEventStore, error) {
            config := sarama.NewConfig()
            config.Producer.Return.Successes = true
            
            producer, err := sarama.NewSyncProducer(brokers, config)
            if err != nil {
                return nil, err
            }
            
            consumer, err := sarama.NewConsumer(brokers, nil)
            if err != nil {
                return nil, err
            }
            
            return &KafkaEventStore{
                producer: producer,
                consumer: consumer,
                topic:    topic,
            }, nil
        }

        // 카프카 이벤트 스토어 구현
        func (s *KafkaEventStore) SaveEvent(event *Event) error {
            data, err := json.Marshal(event)
            if err != nil {
                return err
            }
            
            _, _, err = s.producer.SendMessage(&sarama.ProducerMessage{
                Topic: s.topic,
                Key:   sarama.StringEncoder(event.ID),
                Value: sarama.ByteEncoder(data),
            })
            return err
        }

        func (s *KafkaEventStore) GetEvents(aggregateID string) ([]*Event, error) {
            consumer, err := s.consumer.ConsumePartition(s.topic, 0, sarama.OffsetOldest)
            if err != nil {
                return nil, err
            }
            defer consumer.Close()

            var events []*Event
            for message := range consumer.Messages() {
                var event Event
                if err := json.Unmarshal(message.Value, &event); err != nil {
                    return nil, err
                }
                if event.ID == aggregateID {
                    events = append(events, &event)
                }
            }

            return events, nil
        }

        // 이벤트 핸들러
        type EventHandler interface {
            HandleEvent(event *Event) error
        }

        type EventBus struct {
            handlers map[string][]EventHandler
            mutex    sync.RWMutex
        }

        func NewEventBus() *EventBus {
            return &EventBus{
                handlers: make(map[string][]EventHandler),
            }
        }

        func (b *EventBus) Subscribe(eventType string, handler EventHandler) {
            b.mutex.Lock()
            defer b.mutex.Unlock()

            b.handlers[eventType] = append(b.handlers[eventType], handler)
        }

        func (b *EventBus) Publish(event *Event) error {
            b.mutex.RLock()
            defer b.mutex.RUnlock()

            if handlers, exists := b.handlers[event.Type]; exists {
                for _, handler := range handlers {
                    if err := handler.HandleEvent(event); err != nil {
                        return err
                    }
                }
            }
            return nil
        }

        // 예시 이벤트 핸들러
        type UserCreatedHandler struct {
            userService UserService
        }

        func (h *UserCreatedHandler) HandleEvent(event *Event) error {
            if event.Type != "UserCreated" {
                return nil
            }

            userData, ok := event.Data.(map[string]interface{})
            if !ok {
                return fmt.Errorf("invalid event data format")
            }

            // 사용자 생성 처리
            return h.userService.CreateUser(&CreateUserInput{
                Username: userData["username"].(string),
                Email:    userData["email"].(string),
            })
        }
        ```

5. 작업 큐 구현
    ```go
    // internal/queue/worker.go
    package queue

    type Job struct {
        ID      string
        Type    string
        Payload interface{}
        Status  string
        Error   error
    }

    type Worker struct {
        ID          string
        JobQueue    chan *Job
        Done        chan bool
        JobHandlers map[string]JobHandler
    }

    type JobHandler func(*Job) error

    func NewWorker(id string, jobQueue chan *Job) *Worker {
        return &Worker{
            ID:          id,
            JobQueue:    jobQueue,
            Done:        make(chan bool),
            JobHandlers: make(map[string]JobHandler),
        }
    }

    func (w *Worker) RegisterHandler(jobType string, handler JobHandler) {
        w.JobHandlers[jobType] = handler
    }

    func (w *Worker) Start() {
        go func() {
            for {
                select {
                case job := <-w.JobQueue:
                    w.processJob(job)
                case <-w.Done:
                    return
                }
            }
        }()
    }

    func (w *Worker) processJob(job *Job) {
        handler, exists := w.JobHandlers[job.Type]
        if !exists {
            job.Status = "failed"
            job.Error = fmt.Errorf("no handler for job type: %s", job.Type)
            return
        }

        job.Status = "processing"
        if err := handler(job); err != nil {
            job.Status = "failed"
            job.Error = err
        } else {
            job.Status = "completed"
        }
    }

    // 작업 큐 관리자
    type WorkerPool struct {
        workers   []*Worker
        jobQueue  chan *Job
        maxWorkers int
    }

    func NewWorkerPool(maxWorkers int) *WorkerPool {
        return &WorkerPool{
            workers:    make([]*Worker, 0, maxWorkers),
            jobQueue:   make(chan *Job, maxWorkers*10),
            maxWorkers: maxWorkers,
        }
    }

    func (p *WorkerPool) Start() {
        for i := 0; i < p.maxWorkers; i++ {
            worker := NewWorker(fmt.Sprintf("worker-%d", i), p.jobQueue)
            p.workers = append(p.workers, worker)
            worker.Start()
        }
    }

    func (p *WorkerPool) Submit(job *Job) {
        p.jobQueue <- job
    }

    func (p *WorkerPool) Stop() {
        for _, worker := range p.workers {
            worker.Done <- true
        }
    }
    ```

6. 캐싱 계층 구현
    ```go
    // internal/cache/multilevel.go
    package cache

    type MultilevelCache struct {
        l1     Cache  // 메모리 캐시 (빠름)
        l2     Cache  // Redis 캐시 (중간)
        l3     Cache  // 디스크 캐시 (느림)
        stats  *Stats
    }

    type Stats struct {
        L1Hits     uint64
        L1Misses   uint64
        L2Hits     uint64
        L2Misses   uint64
        L3Hits     uint64
        L3Misses   uint64
    }

    func NewMultilevelCache(l1, l2, l3 Cache) *MultilevelCache {
        return &MultilevelCache{
            l1:    l1,
            l2:    l2,
            l3:    l3,
            stats: &Stats{},
        }
    }

    func (c *MultilevelCache) Get(key string) (interface{}, error) {
        // L1 캐시 확인
        if value, err := c.l1.Get(key); err == nil {
            atomic.AddUint64(&c.stats.L1Hits, 1)
            return value, nil
        }
        atomic.AddUint64(&c.stats.L1Misses, 1)

        // L2 캐시 확인
        if value, err := c.l2.Get(key); err == nil {
            atomic.AddUint64(&c.stats.L2Hits, 1)
            // L1 캐시 업데이트
            c.l1.Set(key, value, time.Minute)
            return value, nil
        }
        atomic.AddUint64(&c.stats.L2Misses, 1)

        // L3 캐시 확인
        if value, err := c.l3.Get(key); err == nil {
            atomic.AddUint64(&c.stats.L3Hits, 1)
            // L1, L2 캐시 업데이트
            c.l1.Set(key, value, time.Minute)
            c.l2.Set(key, value, time.Hour)
            return value, nil
        }
        atomic.AddUint64(&c.stats.L3Misses, 1)

        return nil, ErrKeyNotFound
    }

    func (c *MultilevelCache) Set(key string, value interface{}, expiration time.Duration) error {
        // 모든 레벨에 동시 쓰기
        errChan := make(chan error, 3)

        go func() {
            errChan <- c.l1.Set(key, value, expiration)
        }()

        go func() {
            errChan <- c.l2.Set(key, value, expiration)
        }()

        go func() {
            errChan <- c.l3.Set(key, value, expiration)
        }()

        // 에러 수집
        var errs []error
        for i := 0; i < 3; i++ {
            if err := <-errChan; err != nil {
                errs = append(errs, err)
            }
        }

        if len(errs) > 0 {
            return fmt.Errorf("cache set errors: %v", errs)
        }
        return nil
    }
    ```

7. 서비스 디스커버리
    ```go
    // internal/discovery/consul.go
    package discovery

    import (
        "github.com/hashicorp/consul/api"
    )

    type ServiceRegistry struct {
        client *api.Client
    }

    func NewServiceRegistry(addr string) (*ServiceRegistry, error) {
        config := api.DefaultConfig()
        config.Address = addr

        client, err := api.NewClient(config)
        if err != nil {
            return nil, err
        }

        return &ServiceRegistry{client: client}, nil
    }

    func (r *ServiceRegistry) Register(serviceName, serviceID string, port int) error {
        registration := &api.AgentServiceRegistration{
            ID:      serviceID,
            Name:    serviceName,
            Port:    port,
            Tags:    []string{"go", "gin"},
            Check: &api.AgentServiceCheck{
                HTTP:     fmt.Sprintf("http://localhost:%d/health", port),
                Interval: "10s",
                Timeout:  "5s",
            },
        }

        return r.client.Agent().ServiceRegister(registration)
    }

    func (r *ServiceRegistry) Deregister(serviceID string) error {
        return r.client.Agent().ServiceDeregister(serviceID)
    }

    func (r *ServiceRegistry) GetService(serviceName string) ([]*api.ServiceEntry, error) {
        services, _, err := r.client.Health().Service(serviceName, "", true, nil)
        if err != nil {
            return nil, err
        }
        return services, nil
    }

    // 서비스 디스커버리 미들웨어
    func ServiceDiscoveryMiddleware(registry *ServiceRegistry) gin.HandlerFunc {
        return func(c *gin.Context) {
            serviceName := c.GetHeader("X-Service-Name")
            if serviceName == "" {
                c.Next()
                return
            }

            services, err := registry.GetService(serviceName)
            if err != nil {
                c.AbortWithStatusJSON(http.StatusInternalServerError, gin.H{
                    "error": "service discovery failed",
                })
                return
            }

            if len(services) == 0 {
                c.AbortWithStatusJSON(http.StatusNotFound, gin.H{
                    "error": "service not found",
                })
                return
            }

            // 라운드 로빈 또는 랜덤 선택으로 서비스 선택
            service := services[rand.Intn(len(services))]
            c.Set("service", service)
            c.Next()
        }
    }
    ```

8. 파일 업로드/다운로드 최적화
    ```go
    // internal/storage/storage.go
    package storage

    import (
    "context"
    "io"
    "mime/multipart"
    "sync"
    )

    type StorageProvider interface {
    Upload(ctx context.Context, file *multipart.FileHeader) (string, error)  
    Download(ctx context.Context, path string) (io.ReadCloser, error)
    Delete(ctx context.Context, path string) error
    }

    // 청크 기반 파일 업로드 처리
    type ChunkedUploader struct {
    chunkSize int64
    provider  StorageProvider
    tempDir   string
    chunks    map[string][]*Chunk
    mutex     sync.RWMutex
    }

    type Chunk struct {
    ID       int
    Data     []byte
    Size     int64
    Complete bool
    }

    func NewChunkedUploader(provider StorageProvider, chunkSize int64) *ChunkedUploader {
    return &ChunkedUploader{
        provider:  provider,
        chunkSize: chunkSize,
        chunks:    make(map[string][]*Chunk),
    }
    }

    func (u *ChunkedUploader) UploadChunk(fileID string, chunkID int, data []byte) error {
    u.mutex.Lock()
    defer u.mutex.Unlock()

    if _, exists := u.chunks[fileID]; !exists {
        u.chunks[fileID] = make([]*Chunk, 0)
    }

    chunk := &Chunk{
        ID:       chunkID,
        Data:     data,
        Size:     int64(len(data)),
        Complete: true,
    }

    u.chunks[fileID] = append(u.chunks[fileID], chunk)

    // 모든 청크가 완료되었는지 확인
    if u.isUploadComplete(fileID) {
        return u.mergeChunks(fileID)
    }

    return nil
    }

    func (u *ChunkedUploader) isUploadComplete(fileID string) bool {
    chunks := u.chunks[fileID]
    if len(chunks) == 0 {
        return false
    }

    for _, chunk := range chunks {
        if !chunk.Complete {
            return false
        }
    }
    return true
    }

    func (u *ChunkedUploader) mergeChunks(fileID string) error {
    chunks := u.chunks[fileID]
    
    // 청크 정렬
    sort.Slice(chunks, func(i, j int) bool {
        return chunks[i].ID < chunks[j].ID
    })

    // 임시 파일 생성
    tmpFile, err := os.CreateTemp(u.tempDir, "upload-*")
    if err != nil {
        return err
    }
    defer os.Remove(tmpFile.Name())

    // 청크 병합
    for _, chunk := range chunks {
        if _, err := tmpFile.Write(chunk.Data); err != nil {
            return err
        }
    }

    // 파일 업로드
    if _, err := u.provider.Upload(context.Background(), tmpFile.Name()); err != nil {
        return err
    }

    // 청크 정리
    delete(u.chunks, fileID)
    return nil
    }

    // 스트리밍 다운로드 처리
    type StreamingDownloader struct {
    provider StorageProvider
    bufSize  int
    }

    func NewStreamingDownloader(provider StorageProvider, bufSize int) *StreamingDownloader {
    return &StreamingDownloader{
        provider: provider,
        bufSize:  bufSize,
    }
    }

    func (d *StreamingDownloader) Stream(ctx context.Context, path string, w io.Writer) error {
    reader, err := d.provider.Download(ctx, path)
    if err != nil {
        return err
    }
    defer reader.Close()

    buf := make([]byte, d.bufSize)
    for {
        select {
        case <-ctx.Done():
            return ctx.Err()
        default:
            n, err := reader.Read(buf)
            if n > 0 {
                if _, err := w.Write(buf[:n]); err != nil {
                    return err
                }
            }
            if err == io.EOF {
                return nil
            }
            if err != nil {
                return err
            }
        }
    }
    }
    ```

9. 실시간 알림 시스템
    ```go
    // internal/notifications/notification.go
    package notifications

    type NotificationType string

    const (
    NotificationTypeInfo    NotificationType = "info"
    NotificationTypeWarning NotificationType = "warning"
    NotificationTypeError   NotificationType = "error"
    )

    type Notification struct {
    ID        string           `json:"id"`
    Type      NotificationType `json:"type"`
    Title     string           `json:"title"`
    Message   string           `json:"message"`
    UserID    uint            `json:"user_id"`
    Read      bool            `json:"read"`
    CreatedAt time.Time       `json:"created_at"`
    }

    type NotificationService struct {
    repo        NotificationRepository
    broadcaster *NotificationBroadcaster
    }

    func NewNotificationService(repo NotificationRepository) *NotificationService {
    return &NotificationService{
        repo:        repo,
        broadcaster: NewNotificationBroadcaster(),
    }
    }

    func (s *NotificationService) SendNotification(notification *Notification) error {
    // 저장
    if err := s.repo.Create(notification); err != nil {
        return err
    }

    // 브로드캐스트
    s.broadcaster.Broadcast(notification)
    return nil
    }

    // SSE 브로드캐스터
    type NotificationBroadcaster struct {
    clients    map[uint]map[chan *Notification]bool
    register   chan *client
    unregister chan *client
    mutations  chan *Notification
    mutex      sync.RWMutex
    }

    type client struct {
    userID uint
    ch     chan *Notification
    }

    func NewNotificationBroadcaster() *NotificationBroadcaster {
    b := &NotificationBroadcaster{
        clients:    make(map[uint]map[chan *Notification]bool),
        register:   make(chan *client),
        unregister: make(chan *client),
        mutations:  make(chan *Notification),
    }
    go b.run()
    return b
    }

    func (b *NotificationBroadcaster) run() {
    for {
        select {
        case client := <-b.register:
            b.mutex.Lock()
            if _, exists := b.clients[client.userID]; !exists {
                b.clients[client.userID] = make(map[chan *Notification]bool)
            }
            b.clients[client.userID][client.ch] = true
            b.mutex.Unlock()

        case client := <-b.unregister:
            b.mutex.Lock()
            if _, exists := b.clients[client.userID]; exists {
                delete(b.clients[client.userID], client.ch)
                close(client.ch)
            }
            b.mutex.Unlock()

        case notification := <-b.mutations:
            b.mutex.RLock()
            if channels, exists := b.clients[notification.UserID]; exists {
                for ch := range channels {
                    ch <- notification
                }
            }
            b.mutex.RUnlock()
        }
    }
    }
    ```

10. 분산 캐시 구현 (Redis Cluster)
    ```go
    // internal/cache/distributed.go
    package cache

    import (
    "context"
    "encoding/json"
    "time"

    "github.com/go-redis/redis/v8"
    )

    type DistributedCache struct {
    client  *redis.ClusterClient
    ctx     context.Context
    options *DistributedCacheOptions
    }

    type DistributedCacheOptions struct {
    DefaultTTL     time.Duration
    PrefetchBuffer int
    MaxRetries     int
    }

    func NewDistributedCache(addrs []string, opts *DistributedCacheOptions) (*DistributedCache, error) {
    client := redis.NewClusterClient(&redis.ClusterOptions{
        Addrs:        addrs,
        MaxRetries:   opts.MaxRetries,
        PoolSize:     10,
        MinIdleConns: 5,
    })

    cache := &DistributedCache{
        client:  client,
        ctx:     context.Background(),
        options: opts,
    }

    // 연결 테스트
    if err := client.Ping(cache.ctx).Err(); err != nil {
        return nil, err
    }

    return cache, nil
    }

    // 캐시 조회 with 프리페칭
    func (c *DistributedCache) GetWithPrefetch(key string, fetch func() (interface{}, error)) (interface{}, error) {
    // 캐시 조회
    val, err := c.Get(key)
    if err == nil {
        // 만료 시간이 가까우면 백그라운드에서 프리페치
        ttl, err := c.client.TTL(c.ctx, key).Result()
        if err == nil && ttl < time.Minute {
            go c.prefetch(key, fetch)
        }
        return val, nil
    }

    // 캐시 미스: 데이터 가져오기
    val, err = fetch()
    if err != nil {
        return nil, err
    }

    // 캐시 저장
    if err := c.Set(key, val, c.options.DefaultTTL); err != nil {
        return nil, err
    }

    return val, nil
    }

    func (c *DistributedCache) prefetch(key string, fetch func() (interface{}, error)) {
    val, err := fetch()
    if err != nil {
        return
    }

    c.Set(key, val, c.options.DefaultTTL)
    }

    // 원자적 카운터
    func (c *DistributedCache) Increment(key string) (int64, error) {
    return c.client.Incr(c.ctx, key).Result()
    }

    // 분산 락
    type DistributedLock struct {
    cache    *DistributedCache
    key      string
    token    string
    duration time.Duration
    }

    func (c *DistributedCache) NewLock(key string, duration time.Duration) *DistributedLock {
    return &DistributedLock{
        cache:    c,
        key:      "lock:" + key,
        token:    uuid.New().String(),
        duration: duration,
    }
    }

    func (l *DistributedLock) Acquire() (bool, error) {
    return l.cache.client.SetNX(l.cache.ctx, l.key, l.token, l.duration).Result()
    }

    func (l *DistributedLock) Release() error {
    // Lua 스크립트를 사용한 안전한 락 해제
    script := `
        if redis.call("get", KEYS[1]) == ARGV[1] then
            return redis.call("del", KEYS[1])
        else
            return 0
        end
    `
    
    cmd := l.cache.client.Eval(l.cache.ctx, script, []string{l.key}, l.token)
    _, err := cmd.Result()
    return err
    }
    ```

11. 메시지 큐 통합 (Kafka)
    ```go
    // internal/queue/rabbitmq.go
    type MessageQueue struct {
    conn    *amqp.Connection
    channel *amqp.Channel
    queues  map[string]amqp.Queue
    mutex   sync.RWMutex
    }

    func NewMessageQueue(url string) (*MessageQueue, error) {
    conn, err := amqp.Dial(url)
    if err != nil {
        return nil, err
    }

    ch, err := conn.Channel()
    if err != nil {
        conn.Close()
        return nil, err
    }

    return &MessageQueue{
        conn:    conn,
        channel: ch,
        queues:  make(map[string]amqp.Queue),
    }, nil
    }

    func (mq *MessageQueue) DeclareQueue(name string) error {
    mq.mutex.Lock()
    defer mq.mutex.Unlock()

    queue, err := mq.channel.QueueDeclare(
        name,  // 큐 이름
        true,  // durable
        false, // autoDelete
        false, // exclusive
        false, // noWait
        nil,   // arguments
    )
    if err != nil {
        return err
    }

    mq.queues[name] = queue
    return nil
    }

    func (mq *MessageQueue) Publish(queueName string, body interface{}) error {
    data, err := json.Marshal(body)
    if err != nil {
        return err
    }

    return mq.channel.Publish(
        "",       // exchange
        queueName, // routing key
        false,    // mandatory
        false,    // immediate
        amqp.Publishing{
            ContentType: "application/json",
            Body:       data,
        },
    )
    }

    func (mq *MessageQueue) Consume(queueName string, handler func([]byte) error) error {
    msgs, err := mq.channel.Consume(
        queueName, // queue
        "",      // consumer
        false,   // auto-ack
        false,   // exclusive
        false,   // no-local
        false,   // no-wait
        nil,     // args
    )
    if err != nil {
        return err
    }

    go func() {
        for msg := range msgs {
            if err := handler(msg.Body); err != nil {
                // 에러 발생 시 메시지 재큐
                msg.Reject(true)
                continue
            }
            msg.Ack(false)
        }
    }()

    return nil
    }
    ```

12. Full-Text 검색 통합 (Elasticsearch)
    ```go
    // internal/search/elasticsearch.go
    package search

    import (
    "context"
    "encoding/json"
    "github.com/olivere/elastic/v7"
    )

    type SearchService struct {
    client *elastic.Client
    index  string
    }

    func NewSearchService(url, index string) (*SearchService, error) {
    client, err := elastic.NewClient(
        elastic.SetURL(url),
        elastic.SetSniff(false),
        elastic.SetHealthcheck(false),
    )
    if err != nil {
        return nil, err
    }

    return &SearchService{
        client: client,
        index:  index,
    }, nil
    }

    func (s *SearchService) CreateIndex() error {
    ctx := context.Background()
    
    // 인덱스 매핑 설정
    mapping := `{
        "settings": {
            "number_of_shards": 3,
            "number_of_replicas": 2
        },
        "mappings": {
            "properties": {
                "title": {
                    "type": "text",
                    "analyzer": "standard"
                },
                "content": {
                    "type": "text",
                    "analyzer": "standard"
                },
                "tags": {
                    "type": "keyword"
                },
                "created_at": {
                    "type": "date"
                }
            }
        }
    }`

    _, err := s.client.CreateIndex(s.index).BodyString(mapping).Do(ctx)
    return err
    }

    func (s *SearchService) Index(doc interface{}, id string) error {
    ctx := context.Background()
    _, err := s.client.Index().
        Index(s.index).
        Id(id).
        BodyJson(doc).
        Do(ctx)
    return err
    }

    func (s *SearchService) Search(query string, from, size int) (*elastic.SearchResult, error) {
    ctx := context.Background()

    // 복합 쿼리 생성
    multiQuery := elastic.NewMultiMatchQuery(query, "title^2", "content").
        Type("most_fields").
        Fuzziness("AUTO")

    // 검색 실행
    result, err := s.client.Search().
        Index(s.index).
        Query(multiQuery).
        From(from).
        Size(size).
        Sort("_score", false).
        Sort("created_at", true).
        Do(ctx)

    return result, err
    }

    // 검색 미들웨어
    func SearchMiddleware(searchService *SearchService) gin.HandlerFunc {
    return func(c *gin.Context) {
        if q := c.Query("q"); q != "" {
            page := parseInt(c.Query("page"), 1)
            size := parseInt(c.Query("size"), 10)
            from := (page - 1) * size

            results, err := searchService.Search(q, from, size)
            if err != nil {
                c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
                c.Abort()
                return
            }

            c.Set("searchResults", results)
        }
        c.Next()
    }
    }
    ```

13. 레이트 리미팅 (with Redis)
    ```go
    // internal/middleware/ratelimit.go
    type RateLimiter struct {
    redis  *redis.Client
    limit  int
    window time.Duration
    }

    func NewRateLimiter(redis *redis.Client, limit int, window time.Duration) *RateLimiter {
    return &RateLimiter{
        redis:  redis,
        limit:  limit,
        window: window,
    }
    }

    func (rl *RateLimiter) RateLimit() gin.HandlerFunc {
    return func(c *gin.Context) {
        key := fmt.Sprintf("ratelimit:%s:%s", 
            c.ClientIP(),
            time.Now().Format("2006-01-02-15-04"),
        )

        ctx := context.Background()
        pipe := rl.redis.Pipeline()

        incr := pipe.Incr(ctx, key)
        pipe.Expire(ctx, key, rl.window)

        _, err := pipe.Exec(ctx)
        if err != nil {
            c.AbortWithStatus(http.StatusInternalServerError)
            return
        }

        if incr.Val() > int64(rl.limit) {
            c.AbortWithStatusJSON(http.StatusTooManyRequests, gin.H{
                "error": "Rate limit exceeded",
                "reset": time.Now().Add(rl.window).Unix(),
            })
            return
        }

        // 헤더 설정
        c.Header("X-RateLimit-Limit", strconv.Itoa(rl.limit))
        c.Header("X-RateLimit-Remaining", strconv.FormatInt(int64(rl.limit)-incr.Val(), 10))
        c.Header("X-RateLimit-Reset", strconv.FormatInt(time.Now().Add(rl.window).Unix(), 10))

        c.Next()
    }
    }

    // IP별 차등 레이트 리밋
    type DynamicRateLimiter struct {
    redis  *redis.Client
    limits map[string]int
    window time.Duration
    }

    func (rl *DynamicRateLimiter) SetLimit(ip string, limit int) {
    rl.limits[ip] = limit
    }

    func (rl *DynamicRateLimiter) GetLimit(ip string) int {
    if limit, ok := rl.limits[ip]; ok {
        return limit
    }
    return rl.defaultLimit
    }
    ```

14. Circuit Breaker 패턴
    ```go
    // internal/breaker/circuit.go
    package breaker

    import (
        "errors"
        "sync"
        "time"
    )

    type State int

    const (
        StateClosed State = iota    // 정상 작동
        StateHalfOpen              // 일부 요청 허용
        StateOpen                  // 모든 요청 차단
    )

    type CircuitBreaker struct {
        mutex sync.RWMutex
        
        state                 State
        failureThreshold     int
        resetTimeout         time.Duration
        halfOpenSuccessLimit int
        
        failures            int
        lastFailureTime     time.Time
        halfOpenSuccesses   int
    }

    func NewCircuitBreaker(failureThreshold int, resetTimeout time.Duration) *CircuitBreaker {
        return &CircuitBreaker{
            state:              StateClosed,
            failureThreshold:  failureThreshold,
            resetTimeout:      resetTimeout,
            halfOpenSuccesses: 0,
        }
    }

    func (cb *CircuitBreaker) Execute(fn func() error) error {
        if !cb.isAllowed() {
            return errors.New("circuit breaker is open")
        }

        err := fn()
        cb.recordResult(err)
        return err
    }

    func (cb *CircuitBreaker) isAllowed() bool {
        cb.mutex.RLock()
        defer cb.mutex.RUnlock()

        switch cb.state {
        case StateClosed:
            return true
        case StateOpen:
            if time.Since(cb.lastFailureTime) > cb.resetTimeout {
                cb.mutex.RUnlock()
                cb.mutex.Lock()
                cb.state = StateHalfOpen
                cb.mutex.Unlock()
                cb.mutex.RLock()
                return true
            }
            return false
        case StateHalfOpen:
            return true
        default:
            return false
        }
    }

    func (cb *CircuitBreaker) recordResult(err error) {
        cb.mutex.Lock()
        defer cb.mutex.Unlock()

        if err != nil {
            cb.failures++
            cb.lastFailureTime = time.Now()

            if cb.state == StateClosed && cb.failures >= cb.failureThreshold {
                cb.state = StateOpen
            } else if cb.state == StateHalfOpen {
                cb.state = StateOpen
            }
        } else {
            if cb.state == StateHalfOpen {
                cb.halfOpenSuccesses++
                if cb.halfOpenSuccesses >= cb.halfOpenSuccessLimit {
                    cb.state = StateClosed
                    cb.failures = 0
                    cb.halfOpenSuccesses = 0
                }
            }
        }
    }

    // Circuit Breaker 미들웨어
    func CircuitBreakerMiddleware(breaker *CircuitBreaker) gin.HandlerFunc {
        return func(c *gin.Context) {
            err := breaker.Execute(func() error {
                c.Next()
                if len(c.Errors) > 0 {
                    return c.Errors[0]
                }
                return nil
            })

            if err != nil {
                c.AbortWithStatusJSON(http.StatusServiceUnavailable, gin.H{
                    "error": "Service temporarily unavailable",
                })
            }
        }
    }
    ```

15. API 버저닝
    ```go
    // internal/api/versioning.go
    package api

    type VersionedRouter struct {
        *gin.Engine
        versions map[string]*gin.RouterGroup
    }

    func NewVersionedRouter() *VersionedRouter {
        return &VersionedRouter{
            Engine:   gin.New(),
            versions: make(map[string]*gin.RouterGroup),
        }
    }

    func (vr *VersionedRouter) Group(version string) *gin.RouterGroup {
        if group, exists := vr.versions[version]; exists {
            return group
        }

        group := vr.Engine.Group(fmt.Sprintf("/api/%s", version))
        vr.versions[version] = group
        return group
    }

    // API 버전 미들웨어
    func VersionMiddleware() gin.HandlerFunc {
        return func(c *gin.Context) {
            // Accept 헤더에서 버전 추출
            accept := c.GetHeader("Accept")
            version := extractVersion(accept)
            
            // 버전이 없으면 기본값 사용
            if version == "" {
                version = "v1"
            }
            
            c.Set("api_version", version)
            c.Next()
        }
    }

    func extractVersion(accept string) string {
        // application/vnd.myapp.v1+json 형식 파싱
        if strings.Contains(accept, "application/vnd.myapp.") {
            parts := strings.Split(accept, ".")
            if len(parts) > 2 {
                return strings.Split(parts[2], "+")[0]
            }
        }
        return ""
    }
    ```

16. 마이크로서비스 통신
    ```go
    // internal/microservices/client.go
    package microservices

    import (
    "context"
    "encoding/json"
    "fmt"
    "net/http"
    "time"
    )

    type ServiceClient struct {
    baseURL     string
    client      *http.Client
    breaker     *CircuitBreaker
    rateLimiter *RateLimiter
    }

    func NewServiceClient(baseURL string, options ...ServiceOption) *ServiceClient {
    client := &ServiceClient{
        baseURL: baseURL,
        client: &http.Client{
            Timeout: time.Second * 10,
        },
    }

    for _, option := range options {
        option(client)
    }

    return client
    }

    type ServiceOption func(*ServiceClient)

    func WithCircuitBreaker(breaker *CircuitBreaker) ServiceOption {
    return func(sc *ServiceClient) {
        sc.breaker = breaker
    }
    }

    func WithRateLimiter(limiter *RateLimiter) ServiceOption {
    return func(sc *ServiceClient) {
        sc.rateLimiter = limiter
    }
    }

    // HTTP 요청 래퍼
    func (sc *ServiceClient) Request(ctx context.Context, method, path string, body interface{}) ([]byte, error) {
    if sc.rateLimiter != nil {
        if err := sc.rateLimiter.Wait(ctx); err != nil {
            return nil, err
        }
    }

    if sc.breaker != nil {
        return nil, sc.breaker.Execute(func() error {
            return sc.doRequest(ctx, method, path, body)
        })
    }

    return sc.doRequest(ctx, method, path, body)
    }

    // gRPC 서비스 디스커버리와 통신
    type ServiceRegistry struct {
    services map[string]*ServiceInfo
    mutex    sync.RWMutex
    }

    type ServiceInfo struct {
    Name     string
    Endpoint string
    Weight   int
    }

    func NewServiceRegistry() *ServiceRegistry {
    return &ServiceRegistry{
        services: make(map[string]*ServiceInfo),
    }
    }

    func (sr *ServiceRegistry) Register(service *ServiceInfo) {
    sr.mutex.Lock()
    defer sr.mutex.Unlock()
    sr.services[service.Name] = service
    }

    func (sr *ServiceRegistry) GetService(name string) (*ServiceInfo, error) {
    sr.mutex.RLock()
    defer sr.mutex.RUnlock()
    
    if service, exists := sr.services[name]; exists {
        return service, nil
    }
    return nil, fmt.Errorf("service %s not found", name)
    }

    // 이벤트 기반 통신
    type EventBus struct {
    subscribers map[string][]EventHandler
    mutex       sync.RWMutex
    }

    type EventHandler func(event Event) error

    type Event struct {
    Type    string
    Payload interface{}
    Source  string
    Time    time.Time
    }

    func NewEventBus() *EventBus {
    return &EventBus{
        subscribers: make(map[string][]EventHandler),
    }
    }

    func (eb *EventBus) Subscribe(eventType string, handler EventHandler) {
    eb.mutex.Lock()
    defer eb.mutex.Unlock()
    eb.subscribers[eventType] = append(eb.subscribers[eventType], handler)
    }

    func (eb *EventBus) Publish(event Event) error {
    eb.mutex.RLock()
    handlers, exists := eb.subscribers[event.Type]
    eb.mutex.RUnlock()

    if !exists {
        return nil
    }

    for _, handler := range handlers {
        if err := handler(event); err != nil {
            return err
        }
    }
    return nil
    }

    // 서비스 간 동기화
    type Synchronizer struct {
    lock      *DistributedLock
    eventBus  *EventBus
    registry  *ServiceRegistry
    }

    func (s *Synchronizer) SyncOperation(ctx context.Context, operation string, data interface{}) error {
    // 분산 락 획득
    acquired, err := s.lock.Acquire()
    if err != nil {
        return err
    }
    if !acquired {
        return fmt.Errorf("failed to acquire lock for operation: %s", operation)
    }
    defer s.lock.Release()

    // 이벤트 발행
    event := Event{
        Type:    fmt.Sprintf("%s.sync", operation),
        Payload: data,
        Time:    time.Now(),
    }

    return s.eventBus.Publish(event)
    }
    ```

17. 메트릭스 수집과 모니터링
    ```go
    // internal/metrics/collector.go
    package metrics

    import (
    "github.com/prometheus/client_golang/prometheus"
    "time"
    )

    type MetricsCollector struct {
    httpRequestsTotal     *prometheus.CounterVec
    httpRequestDuration   *prometheus.HistogramVec
    httpRequestSize       *prometheus.HistogramVec
    httpResponseSize      *prometheus.HistogramVec
    databaseQueryDuration *prometheus.HistogramVec
    cacheHitTotal        *prometheus.CounterVec
    cacheMissTotal       *prometheus.CounterVec
    goroutinesGauge      prometheus.Gauge
    memoryUsageGauge     prometheus.Gauge
    }

    func NewMetricsCollector() *MetricsCollector {
    mc := &MetricsCollector{
        httpRequestsTotal: prometheus.NewCounterVec(
            prometheus.CounterOpts{
                Name: "http_requests_total",
                Help: "Total number of HTTP requests",
            },
            []string{"method", "path", "status"},
        ),
        
        httpRequestDuration: prometheus.NewHistogramVec(
            prometheus.HistogramOpts{
                Name:    "http_request_duration_seconds",
                Help:    "HTTP request duration in seconds",
                Buckets: prometheus.DefBuckets,
            },
            []string{"method", "path"},
        ),

        httpRequestSize: prometheus.NewHistogramVec(
            prometheus.HistogramOpts{
                Name:    "http_request_size_bytes",
                Help:    "HTTP request size in bytes",
                Buckets: prometheus.ExponentialBuckets(100, 10, 8),
            },
            []string{"method", "path"},
        ),

        httpResponseSize: prometheus.NewHistogramVec(
            prometheus.HistogramOpts{
                Name:    "http_response_size_bytes",
                Help:    "HTTP response size in bytes",
                Buckets: prometheus.ExponentialBuckets(100, 10, 8),
            },
            []string{"method", "path"},
        ),

        databaseQueryDuration: prometheus.NewHistogramVec(
            prometheus.HistogramOpts{
                Name:    "database_query_duration_seconds",
                Help:    "Database query duration in seconds",
                Buckets: prometheus.DefBuckets,
            },
            []string{"query", "table"},
        ),

        cacheHitTotal: prometheus.NewCounterVec(
            prometheus.CounterOpts{
                Name: "cache_hit_total",
                Help: "Total number of cache hits",
            },
            []string{"cache"},
        ),

        cacheMissTotal: prometheus.NewCounterVec(
            prometheus.CounterOpts{
                Name: "cache_miss_total",
                Help: "Total number of cache misses",
            },
            []string{"cache"},
        ),

        goroutinesGauge: prometheus.NewGauge(
            prometheus.GaugeOpts{
                Name: "goroutines_total",
                Help: "Total number of goroutines",
            },
        ),

        memoryUsageGauge: prometheus.NewGauge(
            prometheus.GaugeOpts{
                Name: "memory_usage_bytes",
                Help: "Current memory usage in bytes",
            },
        ),
    }

    // 메트릭스 등록
    prometheus.MustRegister(
        mc.httpRequestsTotal,
        mc.httpRequestDuration,
        mc.httpRequestSize,
        mc.httpResponseSize,
        mc.databaseQueryDuration,
        mc.cacheHitTotal,
        mc.cacheMissTotal,
        mc.goroutinesGauge,
        mc.memoryUsageGauge,
    )

    // 시스템 메트릭스 수집 시작
    go mc.collectSystemMetrics()

    return mc
    }

    func (mc *MetricsCollector) collectSystemMetrics() {
    ticker := time.NewTicker(15 * time.Second)
    defer ticker.Stop()

    for range ticker.C {
        // 고루틴 수 업데이트
        mc.goroutinesGauge.Set(float64(runtime.NumGoroutine()))

        // 메모리 사용량 업데이트
        var mem runtime.MemStats
        runtime.ReadMemStats(&mem)
        mc.memoryUsageGauge.Set(float64(mem.Alloc))
    }
    }

    // 메트릭스 미들웨어
    func MetricsMiddleware(mc *MetricsCollector) gin.HandlerFunc {
    return func(c *gin.Context) {
        start := time.Now()
        path := c.FullPath()
        method := c.Request.Method

        // 요청 크기 기록
        if c.Request.ContentLength > 0 {
            mc.httpRequestSize.WithLabelValues(method, path).
                Observe(float64(c.Request.ContentLength))
        }

        // 응답 Writer 래핑
        writer := &responseWriter{ResponseWriter: c.Writer}
        c.Writer = writer

        c.Next()

        // 요청 완료 후 메트릭스 수집
        duration := time.Since(start).Seconds()
        status := fmt.Sprintf("%d", writer.Status())

        mc.httpRequestsTotal.WithLabelValues(method, path, status).Inc()
        mc.httpRequestDuration.WithLabelValues(method, path).Observe(duration)
        
        if writer.Size() > 0 {
            mc.httpResponseSize.WithLabelValues(method, path).
                Observe(float64(writer.Size()))
        }
    }
    }

    // Custom Response Writer
    type responseWriter struct {
    gin.ResponseWriter
    size int
    }

    func (w *responseWriter) Write(data []byte) (int, error) {
    n, err := w.ResponseWriter.Write(data)
    w.size += n
    return n, err
    }

    func (w *responseWriter) Size() int {
    return w.size
    }
    ```

18. 데이터 스트리밍