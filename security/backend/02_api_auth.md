# API 인증/인가 (Authentication & Authorization for APIs)

현대 웹 애플리케이션에서 **API 인증과 인가**는 보안의 핵심 요소입니다.  
이 문서에서는 API 보안의 기본 개념부터 실제 구현 방법, 그리고 모범 사례까지 상세히 다룹니다.

> 최근 업데이트: 2025-01-16  
> API 인증/인가 구현 가이드 v1.0

---

## 1. 들어가기 (Introduction)

### 1.1 문서의 목적

API 인증과 인가는 현대 웹/모바일 애플리케이션의 근간을 이루는 핵심 보안 요소입니다. 특히 마이크로서비스 아키텍처와 클라우드 네이티브 환경에서는 더욱 중요해졌습니다. 이 문서는 다음을 목표로 합니다:

- API 인증/인가의 **기본 개념과 원리** 이해
- 다양한 인증 방식(**JWT, OAuth2, API Key** 등)의 특징과 활용
- 실제 프로젝트에 적용 가능한 **구체적인 구현 방법**
- 보안 위협에 대한 **방어 전략과 모범 사례**

### 1.2 왜 API 보안이 중요한가?

최근 API는 다음과 같은 다양한 환경에서 활용되고 있습니다:

- 웹/모바일 클라이언트
- IoT 디바이스
- 서버-서버 간 통신
- 서드파티 통합

이러한 환경에서 API 보안이 취약할 경우 다음과 같은 위험이 있습니다:

- 무단 데이터 접근 및 유출
- 서비스 오남용
- 권한 상승 공격
- 중요 기능의 무단 실행

### 1.3 학습 목표

이 문서를 통해 다음을 학습할 수 있습니다:

1. 인증과 인가의 기본 개념 이해
2. 토큰 기반 인증(JWT) 구현 방법
3. OAuth2/OpenID Connect 활용 방법
4. 접근 제어 전략 수립
5. 실제 프레임워크에서의 구현 기법

---

## 2. 인증/인가 기초 (Basic Concepts)

### 2.1 인증(Authentication) vs 인가(Authorization)

#### 2.1.1 개념 비교

**인증(Authentication)**
- "당신이 누구인지" 확인하는 과정
- 사용자의 신원을 검증하는 절차
- 예: 로그인, 생체인증, 인증서 확인

**인가(Authorization)**
- "무엇을 할 수 있는지" 결정하는 과정
- 특정 리소스에 대한 접근 권한 검증
- 예: 관리자 권한, 읽기/쓰기 권한

#### 2.1.2 처리 순서
1. 인증(Authentication) 먼저 수행
2. 인증 성공 시 인가(Authorization) 진행
3. 인가 성공 시 요청된 리소스/기능 접근 허용

### 2.2 세션 기반 vs 토큰 기반

#### 2.2.1 세션 기반 인증

**특징**
- 서버 측에 세션 정보 저장
- 클라이언트는 세션 ID만 보관
- 상태 유지(Stateful) 방식

**장점**
- 구현이 상대적으로 단순
- 세션 데이터 즉시 무효화 가능
- 메모리에서 빠른 조회 가능

**단점**
- 서버 확장성 제한
- 메모리 부하 발생
- 클러스터링 환경에서 세션 공유 필요

#### 2.2.2 토큰 기반 인증

**특징**
- 클라이언트가 토큰 보관
- 서버는 상태 정보 저장하지 않음
- 상태 비저장(Stateless) 방식

**장점**
- 서버 확장성 우수
- 다양한 클라이언트 지원 용이
- 마이크로서비스 아키텍처에 적합

**단점**
- 토큰 크기가 세션 ID보다 큼
- 토큰 노출 시 보안 위험
- 즉시 무효화가 어려움

### 2.3 API Key와 Basic Auth

#### 2.3.1 API Key 인증

**구현 방식**
```http
GET /api/resource HTTP/1.1
Host: api.example.com
X-API-Key: abcd1234-efgh5678
```

**특징**
- 단순하고 구현이 쉬움
- 주로 서버-서버 간 통신에 사용
- 키 노출 시 보안 위험 높음

**사용 사례**
- 공개 API 서비스
- 개발자 포털
- 결제 게이트웨이

### 2.3.2 Basic Authentication

**구현 방식**
```http
GET /api/resource HTTP/1.1
Host: api.example.com
Authorization: Basic dXNlcjpwYXNzd29yZA==
```

**특징**
- Base64로 인코딩 된 사용자명:비밀번호
- HTTPS 필수
- 구현이 매우 간단

**제안사항**
- 보안 수준이 낮음
- 자격 증명이 매 요청마다 전송
- 세션 관리 기능 없음

--- 

## 3. 토큰 기반 인증

### 3.1 JWT (JSON Web Token)

#### 3.1.1 JWT 구조
JWT는 세 부분으로 구성되며, 각 부분은 점(.)으로 구분됩니다:

**Header (헤더)**
```json
{
  "alg": "HS256",
  "typ": "JWT"
}
```

**Payload(페이로드)**
```json
{
  "sub": "1234567890",
  "name": "John Doe",
  "iat": 1516239022,
  "exp": 1516242622
}
```

**Signature(서명)**
- 헤더와 페이로드를 기반으로 생성
- 비밀키를 사용하여 생성되므로 위변조 방지

### 3.1.2 JWT 장단점

**장점**
- 자가수용적(self-contained): 필요한 정보를 토큰 자체에 포함
- 상태 비저장(Stateless): 서버에 별도 저장소 불필요
- 확장성이 좋음: 분산 시스템에서 효과적

**단점**
- 토큰 크기가 상대적으로 큼
- 한번 발급된 토큰의 즉시 무효화가 어려움
- 페이로드 정보는 암호화되지 않음 (Base64 인코딩만 됨)

### 3.2 Access Token & Refresh Token

#### 3.2.1 토큰 유형별 특징

**Access Token**
- 실제 리소스 접근에 사용
- 비교적 짧은 유효기간 (15분 ~ 2시간)
- 모든 API 요청에 포함

**Refresh Token**
- Access Token 재발급용
- 긴 유효기간 (14일 ~ 30일)
- 안전한 저장소에 보관 필요

#### 3.2.2 구현 예시
```java
@Service
public class TokenService {
    
    @Value("${jwt.secret}")
    private String secretKey;
    
    public String generateAccessToken(User user) {
        return Jwts.builder()
            .setSubject(user.getUsername())
            .claim("roles", user.getRoles())
            .setIssuedAt(new Date())
            .setExpiration(new Date(System.currentTimeMillis() + 3600000)) // 1시간
            .signWith(SignatureAlgorithm.HS256, secretKey)
            .compact();
    }
    
    public String generateRefreshToken(User user) {
        return Jwts.builder()
            .setSubject(user.getUsername())
            .setIssuedAt(new Date())
            .setExpiration(new Date(System.currentTimeMillis() + 1209600000)) // 14일
            .signWith(SignatureAlgorithm.HS256, secretKey)
            .compact();
    }
}
```

### 3.3 토큰 만료/리프레시 설계

#### 3.3.1 토큰 갱신 프로세스

1. Access Token 만료 확인
2. Refresh Token 유효성 검증
3. 새로운 Access Token 발금
4. (선택적) Refresh Token 재발급

```java
@Service
public class TokenRefreshService {
    
    private final TokenService tokenService;
    private final RefreshTokenRepository refreshTokenRepository;
    
    public TokenResponse refreshAccessToken(String refreshToken) {
        // 1. Refresh Token 검증
        if (!tokenService.validateToken(refreshToken)) {
            throw new InvalidTokenException("Invalid refresh token");
        }
        
        // 2. Refresh Token DB 확인
        RefreshToken storedToken = refreshTokenRepository
            .findByToken(refreshToken)
            .orElseThrow(() -> new TokenNotFoundException());
            
        // 3. 사용자 정보 조회
        User user = storedToken.getUser();
        
        // 4. 새로운 Access Token 발급
        String newAccessToken = tokenService.generateAccessToken(user);
        
        // 5. (선택적) Refresh Token 재발급
        if (shouldRotateRefreshToken(storedToken)) {
            String newRefreshToken = tokenService.generateRefreshToken(user);
            refreshTokenRepository.delete(storedToken);
            refreshTokenRepository.save(new RefreshToken(newRefreshToken, user));
            return new TokenResponse(newAccessToken, newRefreshToken);
        }
        
        return new TokenResponse(newAccessToken, null);
    }
    
    private boolean shouldRotateRefreshToken(RefreshToken token) {
        // Refresh Token 교체 정책 구현
        return token.getCreatedAt()
            .plusDays(7)
            .isBefore(LocalDateTime.now());
    }
}
```

#### 3.3.2 토큰 무효화 전략

**Blacklist 방식**
```java
@Service
public class TokenBlacklistService {
    private final RedisTemplate<String, String> redisTemplate;
    
    public void blacklistToken(String token, Date expiryDate) {
        long ttl = expiryDate.getTime() - System.currentTimeMillis();
        redisTemplate.opsForValue()
            .set(token, "blacklisted", ttl, TimeUnit.MILLISECONDS);
    }
    
    public boolean isBlacklisted(String token) {
        return redisTemplate.hasKey(token);
    }
}
```

---

## 4. OAuth2 / OpenID Connect

### 4.1 OAuth2 개념과 역할

#### 4.1.1 주요 구성 요소

**Resource Owner (자원 소유자)**
- 보호된 자원의 소유자
- 일반적으로 최종 사용자
- 자원 접근 권한을 부여하는 주체

**Client (클라이언트)**
- OAuth2를 사용하여 자원을 요청하는 애플리케이션
- 웹/모바일 앱, 서버 등
- Resource Owner를 대신하여 자원 접근

**Authorization Server (권한 부여 서버)**
- 인증을 처리하고 토큰을 발급하는 서버
- 사용자 인증 및 동의 처리
- Access Token, Refresh Token 관리

**Resource Server (자원 서버)**
- 보호된 자원을 호스팅하는 서버
- API 엔드포인트 제공
- 토큰 기반으로 접근 제어

### 4.2 OAuth2 Grant Types

#### 4.2.1 Authorization Code Grant

가장 일반적이고 안전한 방식으로, 서버 사이드 애플리케이션에 적합합니다.

**흐름도**
1. 클라이언트가 권한 서버로 사용자 리다이렉트
2. 사용자 인증 및 권한 동의
3. 권한 서버가 클라이언트로 인가 코드 전달
4. 클라이언트가 인가 코드로 토큰 요청
5. 권한 서버가 액세스 토큰 발급

```java
@Configuration
public class OAuth2ClientConfig {
    @Bean
    public OAuth2AuthorizedClientManager authorizedClientManager(
            ClientRegistrationRepository clientRegistrationRepository,
            OAuth2AuthorizedClientRepository authorizedClientRepository) {
        
        OAuth2AuthorizedClientProvider authorizedClientProvider =
            OAuth2AuthorizedClientProviderBuilder.builder()
                .authorizationCode()
                .refreshToken()
                .build();
                
        DefaultOAuth2AuthorizedClientManager authorizedClientManager =
            new DefaultOAuth2AuthorizedClientManager(
                clientRegistrationRepository, authorizedClientRepository);
                
        authorizedClientManager.setAuthorizedClientProvider(authorizedClientProvider);
        
        return authorizedClientManager;
    }
}
```

#### 4.2.2 Client Credentials Grant

서버 간 통신에 사용되는 방식으로, 사용자 컨텍스트가 불필요한 경우에 적합합니다.

```java
@Service
public class ClientCredentialsTokenService {
    private final WebClient webClient;
    
    public Mono<TokenResponse> getToken() {
        return webClient
            .post()
            .uri("/oauth/token")
            .body(BodyInserters.fromFormData("grant_type", "client_credentials")
                .with("client_id", clientId)
                .with("client_secret", clientSecret))
            .retrieve()
            .bodyToMono(TokenResponse.class);
    }
}
```

### 4.3 OpenID Connect

#### 4.3.1 OIDC 개요

OpenID Connect는 OAuth2 위에 구축된 인증 계층으로, 사용자 신원 정보를 안전하게 전달합니다.

**주요 특징**
- ID Token(JWT 형식) 제공
- 표준화된 사용자 정보 클레임
- OAuth2와 완벽한 호환성

#### 4.3.2 ID Token 구조
```json
{
  "iss": "https://auth.example.com",
  "sub": "user123",
  "aud": "client_id",
  "exp": 1516239022,
  "iat": 1516235422,
  "auth_time": 1516235422,
  "nonce": "abc123",
  "name": "John Doe",
  "email": "john@example.com"
}
```

#### 4.3.3 실제 구현 예시
```java
@Service
public class OidcUserService extends DefaultOIDCUserService {
    
    @Override
    public OidcUser loadUser(OidcUserRequest userRequest) throws OAuth2AuthenticationException {
        OidcUser user = super.loadUser(userRequest);
        
        // ID Token 검증
        OidcIdToken idToken = userRequest.getIdToken();
        validateIdToken(idToken);
        
        // 추가 사용자 정보 매핑
        Map<String, Object> claims = user.getClaims();
        String email = (String) claims.get("email");
        
        // 사용자 정보 저장 또는 업데이트
        updateUserInfo(email, claims);
        
        return user;
    }
    
    private void validateIdToken(OidcIdToken idToken) {
        // 토큰 발급자 확인
        if (!idToken.getIssuer().equals(expectedIssuer)) {
            throw new OAuth2AuthenticationException("Invalid issuer");
        }
        
        // 청중(audience) 확인
        if (!idToken.getAudience().contains(clientId)) {
            throw new OAuth2AuthenticationException("Invalid audience");
        }
        
        // 만료 시간 확인
        if (idToken.getExpiresAt().before(new Date())) {
            throw new OAuth2AuthenticationException("Token expired");
        }
    }
}
```

### 4.4 소셜 로그인 구현

#### 4.4.1 Spring Security 설정
```java
@Configuration
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {
    
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http
            .oauth2Login()
                .authorizationEndpoint()
                    .baseUri("/oauth2/authorize")
                    .authorizationRequestRepository(cookieAuthorizationRequestRepository())
                .and()
                .redirectionEndpoint()
                    .baseUri("/oauth2/callback/*")
                .and()
                .userInfoEndpoint()
                    .userService(customOAuth2UserService)
                    .oidcUserService(customOidcUserService)
                .and()
                .successHandler(oAuth2AuthenticationSuccessHandler)
                .failureHandler(oAuth2AuthenticationFailureHandler);
    }
    
    @Bean
    public HttpCookieOAuth2AuthorizationRequestRepository cookieAuthorizationRequestRepository() {
        return new HttpCookieOAuth2AuthorizationRequestRepository();
    }
}
```

---

## 5. 인가(Authorization) 설계

### 5.1 RBAC vs ABAC

#### 5.1.1 RBAC (Role-Based Access Control)

역할 기반 접근 제어는 사용자의 역할에 기반하여 권한을 부여하는 모델입니다.

**기본 구성요소**
- 사용자(Users)
- 역할(Roles)
- 권한(Permissions)
- 세션(Sessions)

```java
@Entity
public class User {
    @ManyToMany
    private Set<Role> roles;
}

@Entity
public class Role {
    @ManyToMany
    private Set<Permission> permissions;
}

@Entity
public class Permission {
    private String name;        // "READ_USER", "WRITE_POST" 등
    private String resource;    // "USER", "POST" 등
}
```

#### 5.1.2 ABAC(Attribute-Based Access Control)

속성 기반 접근 제어는 다양한 속성을 기반으로 더 유연한 권한 제어를 제공합니다.

**주요 속성 유형**
- 사용자 속성(직책, 부서, 지역 등)
- 리소스 속성(문서 유형, 보안 레벨 등)
- 환경 속성(시간, IP 주소, 디바이스 등)

```java
@Service
public class AbacPolicyService {
    public boolean evaluatePolicy(
            Authentication authentication,
            Object resource,
            String action) {
        
        User user = (User) authentication.getPrincipal();
        
        // 사용자 속성 검사
        if (!checkUserAttributes(user)) return false;
        
        // 리소스 속성 검사
        if (!checkResourceAttributes(resource)) return false;
        
        // 환경 속성 검사
        if (!checkEnvironmentAttributes()) return false;
        
        return true;
    }
    
    private boolean checkEnvironmentAttributes() {
        LocalTime now = LocalTime.now();
        return now.isAfter(LocalTime.of(9, 0)) && 
               now.isBefore(LocalTime.of(18, 0));
    }
}
```

### 5.2 API Gateway vs 백엔드 레벨 인가

#### 5.2.1 API Gateway 레벨 인가

**장점**
- 중앙 집중식 권한 관리
- 일관된 보안 정책 적용
- 마이크로서비스 보호

```java
@Component
public class GatewayAuthorizationFilter extends AbstractGatewayFilterFactory<GatewayAuthorizationFilter.Config> {
    
    @Override
    public GatewayFilter apply(Config config) {
        return (exchange, chain) -> {
            ServerHttpRequest request = exchange.getRequest();
            
            // 토큰 검증
            String token = extractToken(request);
            if (!tokenService.validateToken(token)) {
                return handleUnauthorized(exchange);
            }
            
            // 권한 검사
            Claims claims = tokenService.getClaims(token);
            if (!hasRequiredPermissions(claims, request.getPath().value())) {
                return handleForbidden(exchange);
            }
            
            return chain.filter(exchange);
        };
    }
}
```

#### 5.2.2 백엔드 레벨 인가

**장점**
- 세밀한 권한 제어
- 도메인 특화 보안 로직
- 컨텍스트 기반 판탄

```java
@Service
public class PostService {
    
    @PreAuthorize("hasRole('ADMIN') or @postSecurity.isAuthor(#postId)")
    public Post updatePost(Long postId, PostUpdateDto dto) {
        Post post = postRepository.findById(postId)
            .orElseThrow(() -> new PostNotFoundException(postId));
            
        // 업데이트 로직
        return postRepository.save(post);
    }
}

@Component("postSecurity")
public class PostSecurityEvaluator {
    
    public boolean isAuthor(Long postId) {
        String currentUsername = SecurityContextHolder.getContext()
            .getAuthentication()
            .getName();
            
        return postRepository.findById(postId)
            .map(post -> post.getAuthor().getUsername().equals(currentUsername))
            .orElse(false);
    }
}
```

### 5.3 정책(Policy) 설계

#### 5.3.1 선언적 보안 정책

Spring Security의 어노테이션을 활용한 방식:

```java
@RestController
@RequestMapping("/api/users")
public class UserController {
    
    @GetMapping
    @PreAuthorize("hasRole('ADMIN')")
    public List<UserDto> getAllUsers() {
        return userService.findAll();
    }
    
    @GetMapping("/{id}")
    @PreAuthorize("hasRole('ADMIN') or #id == authentication.principal.id")
    public UserDto getUser(@PathVariable Long id) {
        return userService.findById(id);
    }
    
    @PutMapping("/{id}")
    @PreAuthorize("@userSecurity.canUpdate(#id)")
    @PostAuthorize("returnObject.username == authentication.principal.username")
    public UserDto updateUser(@PathVariable Long id, @RequestBody UserDto user) {
        return userService.update(id, user);
    }
}
```

#### 5.3.2 프로그래매틱 보안 정책

코드 기반의 유연한 권한 처리:

```java
@Service
@Transactional
public class DocumentService {
    
    private final SecurityPolicyEvaluator policyEvaluator;
    
    public Document shareDocument(Long documentId, String targetUsername) {
        Document document = documentRepository.findById(documentId)
            .orElseThrow(() -> new DocumentNotFoundException(documentId));
            
        // 현재 사용자 권한 확인
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
        if (!policyEvaluator.canShareDocument(document, auth)) {
            throw new AccessDeniedException("Cannot share document: " + documentId);
        }
        
        // 공유 대상 사용자 확인
        User targetUser = userRepository.findByUsername(targetUsername)
            .orElseThrow(() -> new UserNotFoundException(targetUsername));
            
        // 문서 공유 정책 확인
        if (!policyEvaluator.isValidShareTarget(document, targetUser)) {
            throw new PolicyViolationException("Invalid share target");
        }
        
        // 공유 처리
        document.addSharedUser(targetUser);
        return documentRepository.save(document);
    }
}
```

--- 

## 6. 보안 이슈와 공격 기법

### 6.1 토큰 탈취 / 재사용 공격

#### 6.1.1 주요 위협

**토큰 탈취 시나리오**
- XSS를 통한 토큰 탈취
- 중간자 공격(MITM)
- 안전하지 않은 저장소 접근
- 네트워크 스니핑

#### 6.1.2 방어 전략

**1. 안전한 토큰 저장**
```javascript
// ✅ 프론트엔드에서의 토큰 저장
class TokenStorage {
    // HttpOnly 쿠키에 저장 (추천)
    static storeAccessToken(token) {
        // 서버에서 HttpOnly 쿠키 설정
        // 프론트엔드에서는 별도 저장하지 않음
    }
    
    // 메모리에 저장 (대안)
    static storeTokenInMemory(token) {
        this.memoryToken = token;
    }
    
    // ❌ LocalStorage 사용 금지
    // localStorage.setItem('token', token); // 취약!
}
```

**2. 토큰 바인딩**
```java
@Service
public class TokenBindingService {
    
    public String generateBoundToken(String username, String fingerprint) {
        return Jwts.builder()
            .setSubject(username)
            .claim("fingerprint", hashFingerprint(fingerprint))
            .setIssuedAt(new Date())
            .setExpiration(new Date(System.currentTimeMillis() + 3600000))
            .signWith(SignatureAlgorithm.HS256, secretKey)
            .compact();
    }
    
    public boolean validateTokenBinding(String token, String fingerprint) {
        Claims claims = Jwts.parser()
            .setSigningKey(secretKey)
            .parseClaimsJws(token)
            .getBody();
            
        String expectedHash = claims.get("fingerprint", String.class);
        String actualHash = hashFingerprint(fingerprint);
        
        return expectedHash.equals(actualHash);
    }
}
```

### 6.2 Replay Attack & Token Revocation

#### 6.2.1 Replay Attack 방지

**1. Nonce 사용**
```java
@Service
public class NonceTokenService {
    private final RedisTemplate<String, String> redisTemplate;
    
    public String generateToken(Authentication auth) {
        String nonce = generateNonce();
        
        return Jwts.builder()
            .setSubject(auth.getName())
            .claim("nonce", nonce)
            .compact();
    }
    
    public boolean validateNonce(String token) {
        Claims claims = Jwts.parser()
            .setSigningKey(secretKey)
            .parseClaimsJws(token)
            .getBody();
            
        String nonce = claims.get("nonce", String.class);
        
        // Redis에서 nonce 사용 여부 확인
        String key = "nonce:" + nonce;
        if (Boolean.TRUE.equals(redisTemplate.hasKey(key))) {
            return false;  // 이미 사용된 nonce
        }
        
        // nonce 사용 처리
        redisTemplate.opsForValue().set(key, "used", 24, TimeUnit.HOURS);
        return true;
    }
}
```

**2. Token Revocation 구현**
```java
@Service
public class TokenRevocationService {
    private final RedisTemplate<String, String> redisTemplate;
    
    public void revokeToken(String token) {
        Claims claims = Jwts.parser()
            .setSigningKey(secretKey)
            .parseClaimsJws(token)
            .getBody();
            
        String username = claims.getSubject();
        Date expiration = claims.getExpiration();
        
        // 토큰 ID를 블랙리스트에 추가
        String tokenId = claims.getId();
        long ttl = expiration.getTime() - System.currentTimeMillis();
        
        redisTemplate.opsForValue()
            .set("blacklist:" + tokenId, username, ttl, TimeUnit.MILLISECONDS);
    }
    
    public boolean isTokenRevoked(String token) {
        Claims claims = Jwts.parser()
            .setSigningKey(secretKey)
            .parseClaimsJws(token)
            .getBody();
            
        String tokenId = claims.getId();
        return Boolean.TRUE.equals(
            redisTemplate.hasKey("blacklist:" + tokenId));
    }
}
```

### 6.3 무차별 대입 공격(Brute Force)

#### 6.3.1 공격 유형
- 로그인 시도 반복
- 토큰 값 추측
- API 키 무작위 시도

#### 6.3.2 방어 구현
```java
@Service
@Slf4j
public class BruteForceProtectionService {
    private final LoadingCache<String, Integer> attemptsCache;
    private final NotificationService notificationService;
    
    public BruteForceProtectionService() {
        attemptsCache = CacheBuilder.newBuilder()
            .expireAfterWrite(1, TimeUnit.DAYS)
            .build(new CacheLoader<>() {
                @Override
                public Integer load(String key) {
                    return 0;
                }
            });
    }
    
    public void recordFailedAttempt(String username, String ip) {
        String key = username + ":" + ip;
        int attempts = attemptsCache.getUnchecked(key) + 1;
        attemptsCache.put(key, attempts);
        
        if (attempts == 3) {
            log.warn("Multiple failed attempts detected for user: {}", username);
            notificationService.sendAlert(
                "Security Alert",
                String.format("Multiple failed login attempts for user %s from IP %s",
                    username, ip)
            );
        }
        
        if (attempts >= 5) {
            lockAccount(username);
            notificationService.sendAdminAlert(
                "Account Locked",
                String.format("Account %s locked due to multiple failed attempts",
                    username)
            );
        }
    }
    
    public boolean isBlocked(String username, String ip) {
        String key = username + ":" + ip;
        return attemptsCache.getUnchecked(key) >= 5;
    }
    
    private void lockAccount(String username) {
        // 계정 잠금 로직
    }
}
```

#### 6.3.3 Rate Limiting 구현
```java
@Component
public class RateLimitingFilter extends OncePerRequestFilter {
    private final RateLimiter rateLimiter;
    
    @Override
    protected void doFilterInternal(
            HttpServletRequest request,
            HttpServletResponse response,
            FilterChain filterChain) throws ServletException, IOException {
        
        String clientId = getClientIdentifier(request);
        
        if (!rateLimiter.tryAcquire(clientId)) {
            response.setStatus(HttpStatus.TOO_MANY_REQUESTS.value());
            response.getWriter().write("Too many requests");
            return;
        }
        
        filterChain.doFilter(request, response);
    }
    
    private String getClientIdentifier(HttpServletRequest request) {
        String apiKey = request.getHeader("X-API-Key");
        if (apiKey != null) return apiKey;
        
        return request.getRemoteAddr();
    }
}
```

--- 

## 7. 실무 예시 & 베스트 프랙티스

### 7.1 프레임워크별 구현 예시

#### 7.1.1 Spring Security 구현

```java
@Configuration
@EnableWebSecurity
public class SecurityConfig {
    
    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        return http
            .csrf(csrf -> csrf.disable())  // REST API이므로 CSRF 비활성화
            .authorizeRequests(auth -> auth
                .antMatchers("/api/public/**").permitAll()
                .antMatchers("/api/admin/**").hasRole("ADMIN")
                .anyRequest().authenticated()
            )
            .sessionManagement(session -> session
                .sessionCreationPolicy(SessionCreationPolicy.STATELESS)
            )
            .oauth2ResourceServer(oauth2 -> oauth2
                .jwt(jwt -> jwt
                    .decoder(jwtDecoder())
                    .jwtAuthenticationConverter(jwtAuthenticationConverter())
                )
            )
            .exceptionHandling(exceptions -> exceptions
                .authenticationEntryPoint(new BearerTokenAuthenticationEntryPoint())
                .accessDeniedHandler(new BearerTokenAccessDeniedHandler())
            )
            .build();
    }
    
    @Bean
    public JwtDecoder jwtDecoder() {
        return NimbusJwtDecoder.withPublicKey(publicKey).build();
    }
    
    @Bean
    public JwtAuthenticationConverter jwtAuthenticationConverter() {
        JwtGrantedAuthoritiesConverter authoritiesConverter = 
            new JwtGrantedAuthoritiesConverter();
        authoritiesConverter.setAuthoritiesClaimName("roles");
        
        JwtAuthenticationConverter converter = new JwtAuthenticationConverter();
        converter.setJwtGrantedAuthoritiesConverter(authoritiesConverter);
        return converter;
    }
}
```

#### 7.1.2 Express.js 구현
```javascript
// JWT 미들웨어
const jwt = require('jsonwebtoken');

const authMiddleware = (req, res, next) => {
    try {
        const token = req.headers.authorization?.split(' ')[1];
        if (!token) {
            return res.status(401).json({ message: 'No token provided' });
        }
        
        const decoded = jwt.verify(token, process.env.JWT_SECRET);
        req.user = decoded;
        
        next();
    } catch (error) {
        if (error instanceof jwt.TokenExpiredError) {
            return res.status(401).json({ message: 'Token expired' });
        }
        return res.status(401).json({ message: 'Invalid token' });
    }
};

// 역할 기반 접근 제어 미들웨어
const roleCheck = (requiredRole) => {
    return (req, res, next) => {
        if (!req.user.roles.includes(requiredRole)) {
            return res.status(403).json({ message: 'Insufficient permissions' });
        }
        next();
    };
};

// 라우터 적용
app.get('/api/users', authMiddleware, roleCheck('ADMIN'), async (req, res) => {
    try {
        const users = await User.find({});
        res.json(users);
    } catch (error) {
        res.status(500).json({ message: 'Server error' });
    }
});
```

### 7.2 Secure Cookie vs Local Storage

#### 7.2.1 Secure Cookie 구현
```java
@Service
public class SecureCookieService {
    
    public ResponseCookie createSecureCookie(String name, String value) {
        return ResponseCookie.from(name, value)
            .httpOnly(true)          // JavaScript 접근 방지
            .secure(true)            // HTTPS 전송만 허용
            .sameSite("Strict")      // CSRF 방지
            .path("/")
            .maxAge(Duration.ofHours(1))
            .build();
    }
    
    public void addTokenToCookie(HttpServletResponse response, String token) {
        ResponseCookie cookie = createSecureCookie("access_token", token);
        response.addHeader(HttpHeaders.SET_COOKIE, cookie.toString());
    }
}
```

#### 7.2.2 CSRF 보호
```java
@Configuration
public class CsrfConfig {
    
    @Bean
    public CsrfTokenRepository csrfTokenRepository() {
        CookieCsrfTokenRepository repository = CookieCsrfTokenRepository.withHttpOnlyFalse();
        repository.setCookieName("XSRF-TOKEN");
        repository.setHeaderName("X-XSRF-TOKEN");
        return repository;
    }
}
```

### 7.3 보안 모니터링과 감사

#### 7.3.1 보안 이벤트 로깅
```java
@Aspect
@Component
@Slf4j
public class SecurityAuditAspect {
    
    private final AuditEventRepository auditRepository;
    
    @Around("@annotation(Audited)")
    public Object auditMethod(ProceedingJoinPoint joinPoint) throws Throwable {
        String methodName = joinPoint.getSignature().getName();
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
        String username = auth != null ? auth.getName() : "anonymous";
        
        try {
            Object result = joinPoint.proceed();
            
            auditRepository.save(new AuditEvent(
                username,
                "SUCCESS",
                String.format("Method %s executed successfully", methodName)
            ));
            
            return result;
        } catch (Exception e) {
            auditRepository.save(new AuditEvent(
                username,
                "FAILURE",
                String.format("Method %s failed: %s", methodName, e.getMessage())
            ));
            
            throw e;
        }
    }
}
```

#### 7.3.2 실시간 알림 구현
```java
@Service
@Slf4j
public class SecurityAlertService {
    
    private final NotificationService notificationService;
    private final SecurityMetricsService metricsService;
    
    public void monitorSecurityEvents() {
        // 로그인 실패 모니터링
        if (metricsService.getLoginFailureRate() > 0.1) {  // 10% 이상 실패
            notifySecurityTeam("High login failure rate detected");
        }
        
        // 비정상 토큰 사용 모니터링
        if (metricsService.getInvalidTokenRate() > 0.05) {  // 5% 이상 실패
            notifySecurityTeam("Unusual invalid token usage detected");
        }
        
        // IP 기반 모니터링
        List<String> suspiciousIPs = metricsService.getSuspiciousIPs();
        if (!suspiciousIPs.isEmpty()) {
            notifySecurityTeam("Suspicious IP activity detected: " + 
                String.join(", ", suspiciousIPs));
        }
    }
    
    private void notifySecurityTeam(String message) {
        log.warn(message);
        notificationService.sendUrgentNotification(
            "Security Alert",
            message,
            NotificationPriority.HIGH
        );
    }
}
```

## 8. 요약 (Summary)

### 8.1 핵심 개념 정리

1. **인증과 인가의 기본**
   - 인증(Authentication): 신원 확인
   - 인가(Authorization): 권한 검증
   - 세션 vs 토큰 기반 인증의 장단점

2. **토큰 기반 인증**
   - JWT 구조와 활용
   - Access Token과 Refresh Token 전략
   - 토큰 관리와 보안

3. **OAuth2/OpenID Connect**
   - 다양한 Grant Type의 활용
   - 소셜 로그인 구현
   - ID Token과 사용자 정보 처리

4. **접근 제어 전략**
   - RBAC vs ABAC 선택과 구현
   - API Gateway vs 백엔드 레벨 인가
   - 정책 기반 접근 제어

### 8.2 보안 체크리스트

#### 8.2.1 인증 구현
- [ ] 강력한 패스워드 정책 적용
- [ ] 안전한 토큰 저장소 사용
- [ ] Refresh Token 순환 정책
- [ ] 멀티 팩터 인증(MFA) 고려

#### 8.2.2 인가 구현
- [ ] 최소 권한 원칙 적용
- [ ] 역할과 권한의 명확한 정의
- [ ] 동적 권한 검사 구현
- [ ] API 엔드포인트 보호

#### 8.2.3 보안 모니터링
- [ ] 보안 이벤트 로깅
- [ ] 실시간 알림 체계
- [ ] 감사(Audit) 추적
- [ ] 이상 징후 탐지

### 8.3 모범 사례

#### 8.3.1 토큰 관리
```java
// 토큰 관리 모범 사례
public class TokenBestPractices {
    // 1. 짧은 만료 시간 설정
    private static final long ACCESS_TOKEN_VALIDITY = 3600L; // 1시간
    
    // 2. 토큰 갱신 시 이전 토큰 무효화
    private static final boolean ROTATE_REFRESH_TOKENS = true;
    
    // 3. 토큰 Claims 최소화
    private Claims createMinimalClaims(User user) {
        return Jwts.claims()
            .setSubject(user.getId().toString())
            .setIssuedAt(new Date())
            .setExpiration(new Date(System.currentTimeMillis() + ACCESS_TOKEN_VALIDITY * 1000));
    }
}
```

#### 8.3.2 에러 처리
```java
// 표준화된 에러 응답
@ControllerAdvice
public class SecurityExceptionHandler {
    
    @ExceptionHandler(AccessDeniedException.class)
    public ResponseEntity<ErrorResponse> handleAccessDenied(AccessDeniedException ex) {
        ErrorResponse error = new ErrorResponse(
            "ACCESS_DENIED",
            "You don't have permission to access this resource",
            HttpStatus.FORBIDDEN.value()
        );
        return new ResponseEntity<>(error, HttpStatus.FORBIDDEN);
    }
    
    @ExceptionHandler(InvalidTokenException.class)
    public ResponseEntity<ErrorResponse> handleInvalidToken(InvalidTokenException ex) {
        ErrorResponse error = new ErrorResponse(
            "INVALID_TOKEN",
            "The provided token is invalid or expired",
            HttpStatus.UNAUTHORIZED.value()
        );
        return new ResponseEntity<>(error, HttpStatus.UNAUTHORIZED);
    }
}
```

### 8.4 향후 고려사항

1. **신기술 대응**
  - Zero Trust Architecture 도입
  - 서버리스 환경의 인증/인가
  - IoT 디바이스 인증

2. **규제 준수**
  - GDPR 데이터 보호 요구사항
  - 금융 보안 규제(PSD2, PCI DSS 등)
  - 산업별 컴플라이언스

3. **확장성 고려**
  - 마이크로서비스 환경의 인증
  - 글로벌 서비스의 지역별 규제
  - 대규모 트래픽 처리

--- 

## 9. 참고 자료 (References)

### 9.1 공식 문서 및 표준

#### 9.1.1 인증/인가 표준
- [JWT (RFC 7519)](https://tools.ietf.org/html/rfc7519)
- [OAuth 2.0 (RFC 6749)](https://tools.ietf.org/html/rfc6749)
- [OpenID Connect Core 1.0](https://openid.net/specs/openid-connect-core-1_0.html)
- [OAuth 2.0 Security Best Current Practice](https://tools.ietf.org/html/draft-ietf-oauth-security-topics)

#### 9.1.2 프레임워크 문서
- [Spring Security Reference](https://docs.spring.io/spring-security/reference/)
- [Express.js Security Best Practices](https://expressjs.com/en/advanced/best-practice-security.html)
- [Django Authentication](https://docs.djangoproject.com/en/stable/topics/auth/)
- [ASP.NET Core Security](https://docs.microsoft.com/aspnet/core/security/)

### 9.2 보안 가이드라인

#### 9.2.1 OWASP 가이드
- [OWASP Authentication Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/Authentication_Cheat_Sheet.html)
- [OWASP Authorization Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/Authorization_Cheat_Sheet.html)
- [OWASP REST Security Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/REST_Security_Cheat_Sheet.html)
- [OWASP API Security Top 10](https://owasp.org/www-project-api-security/)

#### 9.2.2 클라우드 보안 가이드
- [AWS Security Best Practices](https://aws.amazon.com/architecture/security-identity-compliance/)
- [Google Cloud Security Blueprint](https://cloud.google.com/architecture/security-foundations)
- [Azure Security Best Practices](https://docs.microsoft.com/azure/security/fundamentals/best-practices-concepts)

### 9.3 도구 및 라이브러리

#### 9.3.1 인증/인가 라이브러리
- [Spring Security OAuth](https://spring.io/projects/spring-security-oauth)
- [Passport.js](http://www.passportjs.org/)
- [JSON Web Token Libraries](https://jwt.io/libraries)
- [Keycloak](https://www.keycloak.org/)

#### 9.3.2 보안 테스트 도구
- [OWASP ZAP](https://www.zaproxy.org/)
- [Burp Suite](https://portswigger.net/burp)
- [JUnit Security Testing](https://junit.org/)
- [Spring Security Test](https://docs.spring.io/spring-security/reference/servlet/test/index.html)

### 9.4 추천 도서

#### 9.4.1 API 보안
- "API Security in Action" by Neil Madden
- "Securing Microservice APIs" by Matt McLarty
- "OAuth 2 in Action" by Justin Richer and Antonio Sanso

#### 9.4.2 인증/인가 설계
- "Identity and Data Security for Web Development" by Jonathan LeBlanc
- "Cloud Native Security" by Liz Rice
- "Microservices Security in Action" by Prabath Siriwardena

### 9.5 온라인 학습 자료

#### 9.5.1 온라인 강좌
- [Pluralsight - Web Security and the OWASP Top 10](https://www.pluralsight.com/)
- [Coursera - Security and Authentication Fundamentals](https://www.coursera.org/)
- [Udemy - API Security Best Practices](https://www.udemy.com/)

#### 9.5.2 보안 블로그 및 뉴스레터
- [Auth0 Blog](https://auth0.com/blog/)
- [Okta Developer Blog](https://developer.okta.com/blog/)
- [Security Weekly Newsletter](https://securityweekly.com/)
- [Troy Hunt's Blog](https://www.troyhunt.com/)

### 9.6 커뮤니티 및 포럼
- [Stack Overflow - security tag](https://stackoverflow.com/questions/tagged/security)
- [Information Security Stack Exchange](https://security.stackexchange.com/)
- [Reddit - r/netsec](https://www.reddit.com/r/netsec/)
- [OWASP Community](https://owasp.org/community/)