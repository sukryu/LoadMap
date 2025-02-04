# Jenkins 사용자 정의 플러그인 개발

> **목표:**  
> - Jenkins 플러그인의 구조와 개발 환경을 이해한다.
> - 기본적인 플러그인 개발 방법과 API 사용법을 학습한다.
> - 플러그인의 테스트, 배포, 유지보수 방법을 익힌다.
> - 실제 플러그인 개발 사례를 통해 실무 적용 능력을 향상시킨다.

---

## 1. 플러그인 개발 개요

- **정의:**  
  Jenkins 플러그인은 Jenkins의 기능을 확장하는 소프트웨어 모듈입니다.
  Java 또는 Kotlin으로 개발되며, Jenkins의 코어 기능을 확장하거나 새로운 기능을 추가할 수 있습니다.

- **플러그인 개발의 필요성:**  
  Jenkins의 기본 기능만으로는 특정 프로젝트나 조직의 요구사항을 충족하기 어려운 경우가 있습니다.
  사용자 정의 플러그인을 통해 조직의 특수한 요구사항을 충족하고, 개발 프로세스를 더욱 효율적으로 만들 수 있습니다.

---

## 2. 개발 환경 설정

### 2.1 필수 도구

개발을 시작하기 전에 다음 도구들이 필요합니다:
- JDK 11 이상
- Maven 3.8.x 이상
- Git
- IDE (IntelliJ IDEA 권장)

### 2.2 개발 환경 구성

```bash
# Jenkins 플러그인 아키타입을 사용하여 프로젝트 생성
mvn archetype:generate -Dfilter=io.jenkins.archetypes:plugin
```

기본 프로젝트 구조:
```plaintext
my-plugin/
├── pom.xml                 # Maven 설정 파일
├── src/
│   ├── main/
│   │   ├── java/          # 소스 코드
│   │   └── resources/     # 리소스 파일
│   └── test/
│       ├── java/          # 테스트 코드
│       └── resources/     # 테스트 리소스
└── README.md
```

---

## 3. 플러그인 개발 기초

### 3.1 기본 구성 요소

프로젝트의 pom.xml 핵심 설정:
```xml
<project>
    <parent>
        <groupId>org.jenkins-ci.plugins</groupId>
        <artifactId>plugin</artifactId>
        <version>4.40</version>
    </parent>
    
    <properties>
        <jenkins.version>2.346.1</jenkins.version>
        <java.level>11</java.level>
    </properties>
    
    <dependencies>
        <dependency>
            <groupId>org.jenkins-ci.plugins</groupId>
            <artifactId>structs</artifactId>
            <version>318.v4fcc2b_7f4d67</version>
        </dependency>
    </dependencies>
</project>
```

### 3.2 기본 플러그인 구현

간단한 빌더 플러그인 예제:
```java
public class CustomBuilder extends Builder implements SimpleBuildStep {
    private final String name;
    
    @DataBoundConstructor
    public CustomBuilder(String name) {
        this.name = name;
    }
    
    @Override
    public void perform(Run<?,?> run, FilePath workspace, Launcher launcher,
                       TaskListener listener) throws InterruptedException, IOException {
        listener.getLogger().println("Hello, " + name + "!");
    }
    
    @Symbol("customBuild")
    @Extension
    public static final class DescriptorImpl extends BuildStepDescriptor<Builder> {
        @Override
        public boolean isApplicable(Class<? extends AbstractProject> aClass) {
            return true;
        }
        
        @Override
        public String getDisplayName() {
            return "Custom Build Step";
        }
    }
}
```

---

## 4. 주요 확장 포인트

### 4.1 빌드 단계 확장
빌드 프로세스에 새로운 단계를 추가할 수 있습니다:
```java
public class CustomBuildStep extends Builder implements SimpleBuildStep {
    @Override
    public void perform(Run<?,?> run, FilePath workspace, 
                       Launcher launcher, TaskListener listener) {
        // 빌드 단계 구현
    }
}
```

### 4.2 SCM 확장
새로운 버전 관리 시스템을 지원할 수 있습니다:
```java
public class CustomSCM extends SCM {
    @Override
    public ChangeLogParser createChangeLogParser() {
        return new CustomChangeLogParser();
    }
}
```

### 4.3 보안 영역 확장
인증 및 권한 관리 기능을 확장할 수 있습니다:
```java
public class CustomSecurityRealm extends SecurityRealm {
    @Override
    public SecurityComponents createSecurityComponents() {
        return new SecurityComponents(
            new AuthenticationManager() {
                // 인증 로직 구현
            }
        );
    }
}
```

---

## 5. 플러그인 설정 페이지 구현

### 5.1 전역 설정 페이지

```java
@Extension
public class GlobalConfigExample extends GlobalConfiguration {
    private String serverUrl;
    
    public GlobalConfigExample() {
        load();  // 저장된 설정 로드
    }
    
    public String getServerUrl() {
        return serverUrl;
    }
    
    @DataBoundSetter
    public void setServerUrl(String serverUrl) {
        this.serverUrl = serverUrl;
        save();  // 설정 저장
    }
}
```

### 5.2 Job 설정 페이지

설정 페이지용 Jelly 스크립트:
```xml
<?jelly escape-by-default='true'?>
<j:jelly xmlns:j="jelly:core" xmlns:f="/lib/form">
    <f:entry title="Server URL" field="serverUrl">
        <f:textbox />
    </f:entry>
    <f:entry title="Credentials" field="credentialsId">
        <c:select />
    </f:entry>
</j:jelly>
```

---

## 6. 테스트 및 디버깅

### 6.1 단위 테스트 작성

JUnit을 사용한 테스트 예제:
```java
public class CustomBuilderTest {
    @Rule
    public JenkinsRule jenkins = new JenkinsRule();
    
    @Test
    public void testBuildStep() throws Exception {
        FreeStyleProject project = jenkins.createFreeStyleProject();
        CustomBuilder builder = new CustomBuilder("test");
        project.getBuildersList().add(builder);
        
        FreeStyleBuild build = jenkins.buildAndAssertSuccess(project);
        jenkins.assertLogContains("Hello, test!", build);
    }
}
```

### 6.2 통합 테스트

실제 Jenkins 환경에서의 테스트:
```bash
mvn hpi:run  # 개발용 Jenkins 실행
```

### 6.3 디버깅

로그 출력을 통한 디버깅:
```java
private static final Logger LOGGER = Logger.getLogger(CustomBuilder.class.getName());

public void perform(...) {
    LOGGER.log(Level.FINE, "Starting custom build step");
    // ...
    LOGGER.log(Level.INFO, "Build step completed");
}
```

---

## 7. 배포 및 유지보수

### 7.1 플러그인 패키징

```bash
mvn package  # hpi 파일 생성
```

### 7.2 플러그인 배포

Jenkins 업데이트 센터에 배포:
1. GitHub 저장소 생성
2. Jenkins CI 인프라에 호스팅 요청
3. 릴리스 프로세스 진행

### 7.3 버전 관리

의미 있는 버전 번호 체계 사용:
- MAJOR.MINOR.PATCH
- Jenkins 버전 호환성 고려
- 변경 로그 관리

---

## 8. 모범 사례와 주의사항

### 모범 사례
- 명확한 문서화
- 철저한 테스트
- 버전 호환성 유지
- 성능 최적화
- 보안 고려사항 준수

### 주의사항
- 과도한 의존성 추가 지양
- 리소스 누수 방지
- 예외 처리 철저
- 보안 취약점 예방

---

## 9. 참고 자료

- [Jenkins 플러그인 개발 가이드](https://www.jenkins.io/doc/developer/)
- [Jenkins 플러그인 튜토리얼](https://www.jenkins.io/doc/developer/tutorial/)
- [Jenkins API 문서](https://javadoc.jenkins.io/)
- [Jenkins 플러그인 모범 사례](https://www.jenkins.io/doc/developer/publishing/style-guides/)

---

## 마무리

Jenkins 플러그인 개발은 Jenkins의 기능을 확장하고 커스터마이즈하는 강력한 방법입니다.
기본적인 개발 환경 설정부터 배포까지의 전체 프로세스를 이해하고,
실제 개발에서 마주치는 다양한 상황에 대처할 수 있는 능력을 키우는 것이 중요합니다.
지속적인 학습과 커뮤니티 참여를 통해 더 나은 플러그인을 개발할 수 있습니다.