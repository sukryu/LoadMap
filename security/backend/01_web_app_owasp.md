# 웹 애플리케이션 보안: OWASP Top 10

현대 웹 애플리케이션에서 발생하는 **주요 보안 취약점**과 이에 대한 **방어 기법**을 정리한 문서입니다.  
[OWASP(Open Web Application Security Project) Top 10](https://owasp.org/www-project-top-ten/)을 기반으로, 백엔드 개발자가 반드시 알아야 할 보안 지식을 다룹니다.

> 최근 업데이트: 2024-01-16  
> OWASP Top 10 (2021년 버전 기준)

---

## 1. 들어가기 (Introduction)

### 1.1 OWASP란?

OWASP(Open Web Application Security Project)는 웹 애플리케이션 보안을 연구하고 이를 개선하기 위해 만들어진 오픈소스 프로젝트입니다. 특히 **OWASP Top 10**은 가장 위험하고 일반적인 웹 애플리케이션 보안 취약점을 정리한 표준 문서로, 전 세계 보안 전문가들이 참고하고 있습니다.

### 1.2 이 문서의 목적

- 백엔드 개발자가 알아야 할 **핵심 웹 취약점**의 이해
- 각 취약점의 **원리와 공격 시나리오** 파악
- 실무에서 바로 적용 가능한 **방어 기법과 모범 사례** 제시
- **DevSecOps** 관점에서의 지속적인 보안 강화 방안 소개

### 1.3 학습 목표

이 문서를 통해 다음을 배우실 수 있습니다:

1. OWASP Top 10에 해당하는 각각의 취약점이 무엇인지 이해
2. 실제 공격이 어떻게 이루어지는지 시나리오 기반 학습
3. 프로그래밍 언어/프레임워크별 구체적인 방어 코드 작성법
4. 보안 취약점을 사전에 방지하기 위한 설계/아키텍처 방법론

> 💡 **Note**  
> OWASP Top 10은 웹 보안의 시작점입니다. 이는 "최소한 이 정도는 알아야 한다"는 기준을 제시하며, 실제 보안 위협은 이보다 훨씬 다양하고 복잡할 수 있습니다.

## 2. OWASP Top 10 개요

### 2.1 OWASP Top 10 (2021) 목록

| 순위 | 카테고리 | 설명 |
|------|----------|------|
| A01 | Broken Access Control | 접근 제어 취약점 - 인증/권한 검증 미흡 |
| A02 | Cryptographic Failures | 암호화 실패 - 민감 데이터 노출 위험 |
| A03 | Injection | 입력값 검증 없이 명령/쿼리 실행 |
| A04 | Insecure Design | 안전하지 않은 설계 - 보안 설계 부재 |
| A05 | Security Misconfiguration | 보안 설정 오류 - 기본 설정 미변경 등 |
| A06 | Vulnerable Components | 알려진 취약점이 있는 컴포넌트 사용 |
| A07 | Auth/Identity Failures | 인증/식별 실패 - 세션 관리 취약 등 |
| A08 | Software/Data Integrity | 소프트웨어/데이터 무결성 검증 실패 |
| A09 | Security Logging Failures | 보안 로깅/모니터링 부재 |
| A10 | Server-Side Request Forgery | 서버측 요청 위조 취약점 |

### 2.2 주요 변경사항 (2017 → 2021)

2021년 버전에서 크게 달라진 점들:

- **Broken Access Control**이 1위로 상승 (2017년 5위)
- **Cryptographic Failures**가 새롭게 2위 등장 (기존 'Sensitive Data Exposure'가 확장)
- **Insecure Design**이 신규 진입 (보안 설계의 중요성 강조)
- **XML External Entities(XXE)**는 Top 10에서 제외
- **Server-Side Request Forgery(SSRF)**가 신규 진입

### 2.3 위험도 평가 기준

OWASP는 다음 요소들을 고려하여 취약점의 위험도를 평가합니다:

1. **공격 용이성** (Exploitability)
   - 취약점을 악용하기 얼마나 쉬운가?
   - 특별한 도구나 기술이 필요한가?

2. **발견 가능성** (Prevalence)
   - 해당 취약점이 얼마나 흔하게 발견되는가?
   - 자동화된 도구로 발견 가능한가?

3. **탐지 용이성** (Detectability)
   - 취약점 존재 여부를 얼마나 쉽게 파악할 수 있는가?
   - 공격 시도를 탐지할 수 있는가?

4. **기술적 영향** (Technical Impact)
   - 취약점이 악용되었을 때 어떤 피해가 발생하는가?
   - 데이터 유출? 서비스 중단? 권한 탈취?

### 2.4 앞으로의 전개 방식

다음 섹션부터는 각 취약점 항목별로 다음 내용을 다룹니다:

1. **개념과 원리**
   - 취약점의 정의와 발생 원인
   - 위험성과 영향도

2. **공격 시나리오**
   - 실제 공격 사례와 방법
   - 코드/시스템 레벨의 취약점 예시

3. **방어 기법**
   - 개발 단계별 대응 방안
   - 프레임워크/언어별 보안 코드 예시
   - 설정과 모니터링 방법

> 💡 **Tip**  
> 각 취약점은 독립적으로 존재하지 않습니다. 예를 들어, 'Broken Access Control'은 'Security Logging Failures'와 연계될 수 있으며, 이는 공격의 탐지와 대응을 어렵게 만듭니다.

## 3. 취약점별 상세

### 3.1 Broken Access Control (A01:2021)

접근 제어(Access Control)는 "누가 무엇을 할 수 있는가?"를 관리하는 보안의 핵심입니다. 이것이 깨졌다는 것은 권한이 없는 사용자가 허용되지 않은 행동을 할 수 있다는 의미입니다.

#### 3.1.1 취약점 개요

- **정의**: 인증된 사용자가 허용된 권한 범위를 넘어서는 행동을 할 수 있는 상태
- **위험도**: 🔴 높음 (공격 성공 시 치명적 피해 가능)
- **주요 취약점 유형**:
  - URL 직접 접근을 통한 인증 우회
  - 권한 상승 (일반 사용자 → 관리자)
  - 메타데이터 조작 (JWT 토큰 변조 등)
  - CORS 오설정
  - Force browsing (인증 없이 보호된 페이지 접근)

#### 3.1.2 공격 시나리오

**시나리오 #1: URL 변조를 통한 접근**
```javascript
// 취약한 API 엔드포인트
app.get('/api/users/:id/profile', (req, res) => {
  const userId = req.params.id;
  // ❌ 잘못된 구현: 권한 검증 없음
  db.getUserProfile(userId).then(profile => {
    res.json(profile);
  });
});
```

공격자는 단순히 URL의 `id`파라미터를 변경하여 다른 사용자의 프로필 정보에 접근할 수 있습니다.

**시나리오 #2: JWT 토큰 변조**
```json
{
  "sub": "1234567890",
  "role": "user",
  "iat": 1516239022
}
```

공격자가 JWT 토큰을 디코딩하여 `"role": "admin"`으로 변조할 수 있습니다.

#### 3.1.3 방어 기법

1. 접근 제어 정책 구현
```javascript
// ✅ 올바른 구현: 권한 검증 미들웨어 사용
const checkAccessPermission = (req, res, next) => {
  const userId = req.params.id;
  const currentUser = req.user;
  
  if (currentUser.id !== userId && !currentUser.isAdmin) {
    return res.status(403).json({ error: 'Access denied' });
  }
  next();
};

app.get('/api/users/:id/profile', checkAccessPermission, (req, res) => {
  // ... 프로필 조회 로직
});
```

2. RBAC(Role-Based Access Control) 구현
```javascript
const rolePermissions = {
  user: ['read_own_profile', 'edit_own_profile'],
  admin: ['read_all_profiles', 'edit_all_profiles']
};

const checkPermission = (requiredPermission) => {
  return (req, res, next) => {
    const userRole = req.user.role;
    if (!rolePermissions[userRole].includes(requiredPermission)) {
      return res.status(403).json({ error: 'Permission denied' });
    }
    next();
  };
};
```

3. 안전한 JWT 처리
  - 토큰 서명 검증 필수
  - 민감한 정보는 토큰에 포함하지 않음
  - 적절한 마료 시간 설정

#### 3.1.4 예방을 위한 체크리스트
- [ ] 모든 API엔드포인트에 접근 제어 적용
- [ ] 인증된 사용자의 권한 범위 명확히 정의
- [ ] 중요 리소스는 기본적으로 접근 거부(Deny by default)
- [ ] JWT 토큰의 무결성 검증
- [ ] CORS 설정 검토 및 제한
- [ ] API 요청 및 접근 실패 로그 기록

#### 3.1.5 실무 보안 설정 예시

**Spring Security 설정**
```java
@Configuration
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {
    
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http
            .authorizeRequests()
                .antMatchers("/public/**").permitAll()
                .antMatchers("/api/admin/**").hasRole("ADMIN")
                .antMatchers("/api/users/**").hasRole("USER")
                .anyRequest().authenticated()
            .and()
                .csrf().csrfTokenRepository(CookieCsrfTokenRepository.withHttpOnlyFalse());
    }
}
```

**Express.js에서 helmet사용**
```javascript
const helmet = require('helmet');
app.use(helmet());

// CORS 설정
app.use(cors({
  origin: ['https://trusted-domain.com'],
  methods: ['GET', 'POST'],
  credentials: true
}));
```

> 💡 **Best Practice**  
> 접근 제어는 서버 측에서 반드시 수행되어야 합니다.
> UI에서 버튼/메뉴를 숨기는 것은 보안 통제가 아닙니다.
> 세션 ID나 토큰은 URL에 노출되지 않도록 합니다.

### 3.2 Cryptographic Failures (A02:2021)

암호화 실패는 민감한 데이터가 proper한 보호를 받지 못하는 상황을 의미합니다. 이는 데이터가 전송 중이든(in transit) 저장 중이든(at rest) 발생할 수 있는 취약점입니다.

#### 3.2.1 취약점 개요

- **정의**: 민감 데이터가 적절히 암호화되지 않거나, 취약한 암호화 방식을 사용하는 경우
- **위험도**: 🔴 높음 (개인정보 유출 위험)
- **주요 취약 패턴**:
  - 평문으로 민감 정보 전송
  - 취약한 암호화 알고리즘 사용
  - 하드코딩된 암호화 키
  - 부적절한 키 관리
  - 취약한 패스워드 해싱

#### 3.2.2 공격 시나리오

**시나리오 #1: 안전하지 않은 데이터 저장**
```java
// ❌ 잘못된 구현: 평문 저장
public class UserService {
    public void saveUser(User user) {
        String query = "INSERT INTO users (username, password) VALUES (?, ?)";
        // 패스워드를 평문으로 저장
        jdbcTemplate.update(query, user.getUsername(), user.getPassword());
    }
}
```

**시나리오 #2: 취약한 해시 알고리즘**
```java
// ❌ 취약한 구현: MD5 사용
String hashedPassword = DigestUtils.md5Hex(password);
```

#### 3.2.3 방어 기법

**1. 안전한 패스워드 해싱**
```java
// ✅ 올바른 구현: bcrypt 사용
@Service
public class PasswordService {
    private BCryptPasswordEncoder encoder = new BCryptPasswordEncoder();
    
    public String hashPassword(String password) {
        return encoder.encode(password);
    }
    
    public boolean verifyPassword(String raw, String hashed) {
        return encoder.matches(raw, hashed);
    }
}
```

**2. 데이터 암호화 예시**
```java
// ✅ AES 암호화 구현
public class EncryptionService {
    private final String SECRET_KEY = getKeyFromVault(); // 키는 외부 관리
    
    public String encrypt(String data) {
        SecretKey key = new SecretKeySpec(SECRET_KEY.getBytes(), "AES");
        Cipher cipher = Cipher.getInstance("AES/GCM/NoPadding");
        cipher.init(Cipher.ENCRYPT_MODE, key);
        byte[] encrypted = cipher.doFinal(data.getBytes());
        return Base64.getEncoder().encodeToString(encrypted);
    }
    
    private String getKeyFromVault() {
        // AWS KMS, HashiCorp Vault 등에서 키 조회
    }
}
```

**3. HTTPS 설정**
```java
// Spring Boot SSL 설정
server.ssl.key-store=classpath:keystore.p12
server.ssl.key-store-password=${SSL_KEY_STORE_PASSWORD}
server.ssl.key-store-type=PKCS12
server.ssl.enabled=true
```

#### 3.2.4 예방을 위한 체크리스트

- [ ] 모든 민감 데이터 식별 및 분류
- [ ] 불필요한 민감 데이터는 저장하지 않음
- [ ] 최신 암호화 알고리즘 사용 (AES-256, RSA-2048 이상)
- [ ] 강력한 패스워드 해싱(bcrypt, Argon2, PBKDF2)
- [ ] HTTPS/TLS 1.2 이상 사용
- [ ] 암호화 키는 안전하게 관리 (AWS KMS, Vault 등)

#### 3.2.5 실무 보안 설정 예시

**application.yml에서 민감정보 처리**
```yaml
spring:
  datasource:
    # ❌ 잘못된 방식
    password: mySecretPassword123
    
    # ✅ 올바른 방식
    password: ${DB_PASSWORD}  # 환경 변수에서 로드
```

**Node.js에서 암호화 예시**
```javascript
const crypto = require('crypto');

const encrypt = (text, secretKey) => {
  const iv = crypto.randomBytes(16);
  const cipher = crypto.createCipheriv('aes-256-gcm', secretKey, iv);
  
  const encrypted = Buffer.concat([
    cipher.update(text, 'utf8'),
    cipher.final()
  ]);
  
  const tag = cipher.getAuthTag();
  
  return {
    iv: iv.toString('hex'),
    content: encrypted.toString('hex'),
    tag: tag.toString('hex')
  };
};
```

> 💡 **Best Practice**  
> 암호화 키는 절대 소스코드에 하드코딩하지 않습니다.
> 가능한 표준 라이브러리나 검증된 암호화 라이브러리를 사용합니다.
> 패스워드는 반드시 단방향 해시로 저장합니다.
> 모든 민감 통신은 TLS를 사용합니다.

#### 3.2.6 추가 보안 고려사항

1. 키 순환(Key Rotation)
  - 주기적인 암호화 키 변경
  - 키 유출 시 영향 최소화

2. 암호화 키 백업
  - 키 분실 시 복구 계획
  - 안전한 키 백업 저장소 운영

3. 감사 및 모니터링
  - 암호화 작업 로깅
  - 키 사용 추적
  - 비정상 접근 탐지

### 3.3 Injection (A03:2021)

Injection 취약점은 신뢰할 수 없는 데이터가 명령어나 쿼리의 일부로 처리될 때 발생합니다. 공격자의 악의적인 데이터가 예상치 못한 명령을 실행하게 만들 수 있습니다.

#### 3.3.1 취약점 개요

- **정의**: 사용자 입력값이 적절한 검증/이스케이프 없이 명령어로 실행되는 경우
- **위험도**: 🔴 높음 (데이터베이스 파괴, 시스템 장악 가능)
- **주요 유형**:
  - SQL Injection
  - NoSQL Injection
  - OS Command Injection
  - LDAP Injection
  - XPath Injection

#### 3.3.2 공격 시나리오

**시나리오 #1: SQL Injection**
```java
// ❌ 취약한 코드
String query = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "'";
// 공격 입력값: username = "admin' --"
// 실제 쿼리: SELECT * FROM users WHERE username = 'admin' --' AND password = ''
```

**시나리오 #2: OS Command Injection**
```javascript
// ❌ 취약한 코드
app.get('/ping', (req, res) => {
    const ip = req.query.ip;
    exec('ping -c 4 ' + ip, (error, stdout, stderr) => {
        res.send(stdout);
    });
});
// 공격 입력값: "8.8.8.8; rm -rf /"
```

#### 3.3.3 방어 기법

**1. SQL Injection 방지**
```java
// ✅ PreparedStatement 사용
public User findUser(String username, String password) {
    String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
    PreparedStatement pstmt = connection.prepareStatement(sql);
    pstmt.setString(1, username);
    pstmt.setString(2, password);
    ResultSet rs = pstmt.executeQuery();
    // 결과 처리
}
```

**2. ORM 사용**
```typescript
// ✅ TypeORM 예시
async function getUser(username: string) {
    const userRepository = getRepository(User);
    const user = await userRepository.findOne({
        where: { username }
    });
    return user;
}
```

**3. Command Injectiona 방지**
```javascript
// ✅ 입력값 검증과 이스케이프
const { exec } = require('child_process');
const validator = require('validator');

app.get('/ping', (req, res) => {
    const ip = req.query.ip;
    if (!validator.isIP(ip)) {
        return res.status(400).send('Invalid IP address');
    }
    
    exec(`ping -c 4 ${ip.replace(/[;|&]/g, '')}`, {
        shell: '/bin/bash',
        timeout: 5000
    }, (error, stdout, stderr) => {
        if (error) return res.status(500).send('Error executing command');
        res.send(stdout);
    });
});
```

#### 3.3.4 예방을 위한 체크리스트
- [ ] 모든 사용자 입력을 신뢰하지 않음
- [ ] PreparedStatement 또는 ORM 사용
- [ ] 입력값 검증(화이트리스트 방식)
- [ ] 특수문자 이스케이프 처리
- [ ] 최소 권한 원칙 적용 (DB 계정 등)
- [ ] WAF(Web Application Firewall) 설정

#### 3.3.5 프레임워크별 방어 예시

**Spring Data JPA**
```java
@Repository
public interface UserRepository extends JpaRepository<User, Long> {
    // ✅ 안전한 쿼리 메소드
    @Query("SELECT u FROM User u WHERE u.username = :username")
    Optional<User> findByUsername(@Param("username") String username);
}
```

**Mongoose(MongoDB)**
```javascript
// ✅ 안전한 쿼리 빌더 사용
const user = await User.findOne({
    username: req.body.username
}).select('-password');
```

**MyBatis**
```xml
<!-- ✅ PreparedStatement 사용 -->
<select id="findUser" parameterType="String" resultType="User">
    SELECT * FROM users
    WHERE username = #{username}
    AND active = true
</select>
```

#### 3.3.6 모니터링과 로깅

**1. SQL 쿼리 모니터링**
```java
// ✅ SQL 로깅 설정 (application.properties)
spring.jpa.show-sql=true
spring.jpa.properties.hibernate.format_sql=true
logging.level.org.hibernate.SQL=DEBUG
logging.level.org.hibernate.type.descriptor.sql.BasicBinder=TRACE
```

**2. 비정상 패턴 탐지**
```java
// ✅ SQL 인젝션 의심 패턴 로깅
public class SQLInjectionDetector extends OncePerRequestFilter {
    @Override
    protected void doFilterInternal(HttpServletRequest request,
                                  HttpServletResponse response,
                                  FilterChain filterChain) {
        String[] suspiciousPatterns = {"--", ";", "UNION", "DROP", "DELETE FROM"};
        String queryString = request.getQueryString();
        
        if (containsSuspiciousPattern(queryString, suspiciousPatterns)) {
            log.warn("Possible SQL Injection attempt: {}", queryString);
            response.setStatus(HttpServletResponse.SC_FORBIDDEN);
            return;
        }
        filterChain.doFilter(request, response);
    }
}
```

> 💡 **Best Practice**
> 동적 쿼리 생성을 피하고 PreparedStatement 사용
> ORM과 쿼리 빌더의 안전한 메소드 활용
> 에러 메시지에 상세 정보 노출 금지
> 정기적인 보안 감사와 로그 분석 수행

### 3.4 Insecure Design (A04:2021)

Insecure Design은 "보안이 설계 단계에서부터 고려되지 않은 상태"를 의미합니다. 이는 단순한 구현상의 버그나 설정 오류가 아닌, 아키텍처 수준의 보안 결함을 다룹니다.

#### 3.4.1 취약점 개요

- **정의**: 보안 요구사항이 설계 단계에서 누락되거나 부적절하게 처리된 경우
- **위험도**: 🔴 높음 (시스템 전반의 보안 취약성 발생)
- **주요 문제점**:
  - 비즈니스 로직 결함
  - 부적절한 접근 통제 설계
  - 보안 통제의 부재
  - 에러 처리 미흡
  - 데이터 흐름 보안 설계 부재

#### 3.4.2 취약한 설계 사례

**사례 #1: 비즈니스 로직 결함**
```java
// ❌ 취약한 설계: 계좌 이체 로직
public class TransferService {
    public void transfer(Account from, Account to, BigDecimal amount) {
        // 잔액 검증 없이 이체 진행
        to.credit(amount);
        from.debit(amount);
        // 트랜잭션 처리 없음
    }
}
```

**사례 #2: 부적절한 인증 설계**
```javascript
// ❌ 취약한 설계: 비밀번호 재설정
app.post('/reset-password', (req, res) => {
    const { email } = req.body;
    const tempPassword = generateTempPassword();
    // 이메일 확인 없이 임시 비밀번호 발급
    sendPasswordResetEmail(email, tempPassword);
    res.json({ success: true });
});
```

#### 3.4.3 안전한 설계 패턴

**1. 계층화된 보안 설계**
```java
// ✅ 다중 방어 계층 구현
@Service
public class SecureTransferService {
    @Transactional
    public void transfer(
            @NotNull Account from,
            @NotNull Account to,
            @NotNull @Positive BigDecimal amount) {
        
        // 1. 입력값 검증
        validateTransfer(from, to, amount);
        
        // 2. 비즈니스 규칙 검사
        if (!from.canWithdraw(amount)) {
            throw new InsufficientBalanceException();
        }
        
        // 3. 이상 거래 탐지
        fraudDetectionService.checkTransaction(from, to, amount);
        
        // 4. 트랜잭션 처리
        to.credit(amount);
        from.debit(amount);
        
        // 5. 감사 로그 기록
        auditService.logTransfer(from, to, amount);
    }
}
```

**2. 안전한 비밀번호 재설정 흐름**
```java
// ✅ 토큰 기반 비밀번호 재설정
@Service
public class PasswordResetService {
    public void initiateReset(String email) {
        User user = userRepository.findByEmail(email)
            .orElseThrow(() -> new UserNotFoundException());
        
        String token = tokenService.generateSecureToken();
        DateTime expiry = DateTime.now().plusHours(1);
        
        passwordResetRepository.save(new PasswordReset(user, token, expiry));
        emailService.sendResetLink(email, token);
    }
    
    public void confirmReset(String token, String newPassword) {
        PasswordReset reset = passwordResetRepository.findValidToken(token)
            .orElseThrow(() -> new InvalidTokenException());
        
        if (reset.isExpired()) {
            throw new TokenExpiredException();
        }
        
        userService.updatePassword(reset.getUser(), newPassword);
        passwordResetRepository.invalidateToken(token);
    }
}
```

#### 3.4.4 보안 설계 원칙

**1. 최소 권한 원칙**
```java
// ✅ 명시적 권한 설계
@PreAuthorize("hasRole('ADMIN') or @userSecurity.isAccountOwner(#accountId)")
public AccountDetails getAccountDetails(Long accountId) {
    return accountRepository.findById(accountId)
        .orElseThrow(() -> new AccountNotFoundException());
}
```

**2. Fail-safe 기본값**
```java
// ✅ 안전한 기본 설정
@Configuration
public class SecurityConfig {
    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        return http
            .authorizeRequests()
                .antMatchers("/public/**").permitAll()
                .anyRequest().authenticated() // 기본적으로 모든 요청 인증 필요
            .and()
            .csrf()
                .csrfTokenRepository(CookieCsrfTokenRepository.withHttpOnlyFalse())
            .and()
            .headers()
                .contentSecurityPolicy("default-src 'self'")
            .and()
            .build();
    }
}
```

#### 3.4.5 설계 검토 체크리스트
- [ ] 모든 비즈니스 로직에 대한 보안 위협 모델링 수행
- [ ] 인증/인가 요구사항 명확화
- [ ] 데이터 흐름의 보안 통제 지점 식별
- [ ] 에러 처리와 예외 상황 대응 계획
- [ ] 감사(Audit) 및 로깅 요구사항 정의
- [ ] 확장성을 고려한 보안 아키텍처 설계

> 💡 **Best Practice**
> 설계 단계에서 보안 요구사항을 명확히 정의
> 위협 모델링을 통한 잠재적 위험 식별
> 보안 통제의 계층화 구현
> 모든 가정(Assumption)을 문서화하고 검증

### 3.5 Security Misconfiguration (A05:2021)

보안 설정 오류는 가장 흔하게 발견되는 취약점 중 하나입니다. 기본 설정, 불완전한 설정, 임시 설정의 운영 환경 적용 등으로 인해 발생하며, 모든 레벨(네트워크, 플랫폼, 서버, 애플리케이션)에서 발생할 수 있습니다.

#### 3.5.1 취약점 개요

- **정의**: 보안 설정이 불완전하거나 위험한 상태로 남아있는 경우
- **위험도**: 🟠 중간 (시스템 노출로 인한 2차 공격 가능)
- **주요 문제점**:
  - 기본 계정/비밀번호 미변경
  - 불필요한 기능/포트 활성화
  - 디버그 모드 활성화
  - 보안 헤더 미설정
  - 에러 메시지의 과도한 정보 노출

#### 3.5.2 취약한 설정 사례

**사례 #1: 에러 핸들링**
```java
// ❌ 취약한 설정: 상세 에러 노출
@ControllerAdvice
public class GlobalExceptionHandler {
    @ExceptionHandler(Exception.class)
    public ResponseEntity<String> handleException(Exception e) {
        // 스택 트레이스 노출
        return ResponseEntity.status(500)
            .body(ExceptionUtils.getStackTrace(e));
    }
}
```

**사례 #2: 서버 설정**
```properties
# ❌ 취약한 설정: application.properties
# 운영 환경에서 디버그 모드 활성화
debug=true
spring.jpa.show-sql=true

# 모든 Origin 허용
spring.mvc.cors.allowed-origins=*
```

#### 3.5.3 안전한 설계 방법

**1. 에러 핸들링 보안**
```java
// ✅ 안전한 에러 핸들링
@ControllerAdvice
public class SecureExceptionHandler {
    @ExceptionHandler(Exception.class)
    public ResponseEntity<ErrorResponse> handleException(Exception e) {
        // 로그에는 상세 정보 기록
        log.error("Error occurred", e);
        
        // 클라이언트에는 제한된 정보만 전송
        return ResponseEntity.status(500)
            .body(new ErrorResponse("An internal error occurred"));
    }
    
    @ExceptionHandler(ValidationException.class)
    public ResponseEntity<ErrorResponse> handleValidation(ValidationException e) {
        return ResponseEntity.status(400)
            .body(new ErrorResponse("Invalid input provided"));
    }
}
```

**2. 보안 헤더 설정**
```java
// ✅ 보안 헤더 구성
@Configuration
public class WebSecurityConfig {
    @Bean
    public WebSecurityCustomizer webSecurityCustomizer() {
        return (web) -> web.ignoring().antMatchers("/public/**");
    }
    
    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        return http
            .headers()
                .contentSecurityPolicy("default-src 'self'")
                .frameOptions().deny()
                .xssProtection().block(true)
                .and()
            .httpStrictTransportSecurity()
                .includeSubDomains(true)
                .maxAgeInSeconds(31536000)
            .and()
            .build();
    }
}
```

**3. 환경별 설정 분리**
```yaml
# ✅ application-prod.yml
spring:
  # 운영 환경 설정
  jpa:
    show-sql: false
  security:
    debug: false
  server:
    error:
      include-stacktrace: never
      
# 로깅 설정
logging:
  level:
    root: ERROR
    com.myapp: INFO
```

#### 3.5.4 설정 검토 체크리스트
- [ ] 모든 기본 계정/비밀번호 변경
- [ ] 불필요한 포트/서비스/페이지 비활성화
- [ ] 디버그 모드/개발자 기능 비활성화
- [ ] 보안 헤더 적용(HSTS, CSP, X-Frame-Options 등)
- [ ] 에러 처리 설정 검토
- [ ] 암호화 설정 컴토(TLS 버전, 암호화 스위트)
- [ ] 파일 업로드/다운로드 제한 설정
- [ ] 세션 설정 검토

#### 3.5.5 환경별 보안 설정 예시

**1. 개발 환경**
```yaml
# application-dev.yml
spring:
  h2:
    console:
      enabled: true
      path: /h2-console
  jpa:
    show-sql: true
    
logging:
  level:
    root: INFO
    com.myapp: DEBUG
```

**2. 운영 환경**
```yaml
# application-prod.yml
spring:
  h2:
    console:
      enabled: false
  jpa:
    show-sql: false
    
security:
  require-ssl: true
  headers:
    hsts: true
    
server:
  tomcat:
    max-threads: 200
    accept-count: 100
```

#### 3.5.6 모니터링과 감사
```java
// ✅ 설정 변경 감사 로깅
@Component
@Aspect
public class ConfigurationAuditAspect {
    @Around("@annotation(ConfigurationChange)")
    public Object logConfigChange(ProceedingJoinPoint joinPoint) throws Throwable {
        String user = SecurityContextHolder.getContext().getAuthentication().getName();
        String method = joinPoint.getSignature().getName();
        
        log.info("Configuration change by {} - method: {}", user, method);
        
        Object result = joinPoint.proceed();
        
        auditService.recordConfigChange(user, method, new Date());
        return result;
    }
}
```

> 💡 **Best Practice**
> 환경별(개발/스테이징/운영) 설정 분리
> 설정 변경 시 필수 승인 프로세스 적용
> 정기적인 보안 설정 검토 수행
> 자동화된 설정 검증 도구 활용
> 중요 설정 변경은 감사 로그 기록

### 3.6 Vulnerable and Outdated Components (A06:2021)

취약하거나 오래된 컴포넌트 사용은 알려진 보안 취약점을 시스템에 노출시킬 수 있습니다. 이는 직접 사용하는 라이브러리뿐만 아니라, 이들의 종속성(dependencies)까지 포함합니다.

#### 3.6.1 취약점 개요

- **정의**: 알려진 취약점이 있는 라이브러리, 프레임워크, 모듈 사용
- **위험도**: 🟠 중간 (알려진 취약점 악용 가능)
- **주요 위험**:
  - 알려진 CVE 취약점 노출
  - 보안 패치되지 않은 버전 사용
  - 종속성의 취약점 전파
  - 호환성 문제로 인한 업데이트 지연

#### 3.6.2 취약점 사례

**사례 #1: 취약한 종속성**
```xml
<!-- ❌ 취약한 버전 사용 -->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
    <version>2.3.1.RELEASE</version>  <!-- 오래된 버전 -->
</dependency>

<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.9.8</version>  <!-- 알려진 취약점 존재 -->
</dependency>
```

**사례 #2: Node.js 취약한 패키지**
```json
{
  "dependencies": {
    "lodash": "4.17.15",     // ❌ 취약한 버전
    "express": "4.16.1",     // ❌ 오래된 버전
    "moment": "2.24.0"       // ❌ 보안 업데이트 필요
  }
}
```

#### 3.6.3 보안 강화 기법

**1. 종속성 관리 자동화**
```xml
<!-- ✅ Spring Boot 의존성 관리 -->
<parent>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-parent</artifactId>
    <version>2.7.0</version>
</parent>

<!-- 버전 속성 중앙 관리 -->
<properties>
    <jackson.version>2.13.3</jackson.version>
    <lombok.version>1.18.24</lombok.version>
</properties>
```

**2. 취약점 스캐닝 설정**
```xml
<!-- ✅ Maven 취약점 체크 플러그인 -->
<plugin>
    <groupId>org.owasp</groupId>
    <artifactId>dependency-check-maven</artifactId>
    <version>7.1.1</version>
    <executions>
        <execution>
            <goals>
                <goal>check</goal>
            </goals>
        </execution>
    </executions>
</plugin>
```

**3. 자동 업데이트 파이프라인**
```yaml
# ✅ GitHub Actions 취약점 스캔
name: Dependency Review
on: [pull_request]

jobs:
  dependency-review:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v3
      
      - name: Dependency Review
        uses: actions/dependency-review-action@v2
```

#### 3.6.4 모니터링 및 관리 도구

**1. NPM 보안 검사**
```bash
# 취약점 검사
npm audit

# 자동 수정 시도
npm audit fix

# 상세 리포트
npm audit --json
```

**2. Maven 의존성 체크**
```bash
# 의존성 트리 확인
mvn dependency:tree

# OWASP 취약점 체크
mvn org.owasp:dependency-check-maven:check
```

**3. Gradle 의존성 관리**
```groovy
// ✅ 의존성 버전 관리
dependencyManagement {
    imports {
        mavenBom "org.springframework.boot:spring-boot-dependencies:2.7.0"
    }
}

// 취약점 체크 설정
dependencies {
    dependencyCheck 'org.owasp:dependency-check-gradle:7.1.1'
}
```

#### 3.6.5 관리 체크리스트
- [ ] 정기적인 의존성 취약점 스캔 수행
- [ ] CI/CD 파이프라인에 취약점 검사 포함
- [ ] 사용하지 않는 의존성 제거
- [ ] 버전 업데이트 정책 수립
- [ ] 패치 관리 프로세스 구축
- [ ] 취약점 알림 설정
- [ ] 호환성 테스트 자동화

#### 3.6.6 보안 업데이트 프로세스

**1. 정기 점검**
```java
// ✅ 의존성 상태 체크 스케줄러
@Component
public class DependencyHealthChecker {
    @Scheduled(cron = "0 0 0 * * MON") // 매주 월요일
    public void checkDependencies() {
        // 1. 의존성 목록 조회
        List<Dependency> dependencies = dependencyService.getAllDependencies();
        
        // 2. 버전 체크
        List<Dependency> outdatedDeps = dependencies.stream()
            .filter(this::isOutdated)
            .collect(Collectors.toList());
            
        // 3. 알림 발송
        if (!outdatedDeps.isEmpty()) {
            notificationService.sendAlert(
                "Outdated Dependencies Found",
                createReport(outdatedDeps)
            );
        }
    }
}
```

> 💡 **Best Practice**
- 의존성 버전을 중앙에서 관리
> 보안 업데이트는 최우선 순위로 처리
> 주기적인 취약점 스캔 자동화
> 업데이트 전 호환성 테스트 필수
> 패치 적용 후 시스템 모니터링 강화