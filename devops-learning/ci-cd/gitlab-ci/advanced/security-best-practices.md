# 보안 및 권한 관리

> **목표:**  
> - GitLab CI/CD의 보안 설정과 권한 관리 방법 습득
> - 안전한 시크릿 관리와 접근 제어 구현
> - 보안 취약점 스캔 및 모니터링 구성

---

## 1. 기본 보안 설정

### 1.1 접근 제어
```yaml
# .gitlab-ci.yml
variables:
  DEPLOY_TOKEN: ${CI_DEPLOY_TOKEN}

deploy:
  script:
    - deploy.sh
  environment:
    name: production
  rules:
    - if: $CI_COMMIT_BRANCH == "main"
      when: manual
  needs: ["test"]
```

### 1.2 보안 변수 설정
```bash
# GitLab UI에서 설정
Settings > CI/CD > Variables

# 마스킹과 보호 옵션 활성화
- Masked Variable: 로그에서 값 숨김
- Protected Variable: 보호된 브랜치에서만 사용
```

---

## 2. 시크릿 관리

### 2.1 환경 변수 관리
```yaml
variables:
  # 프로젝트 변수
  DB_HOST: "db.example.com"
  
  # 민감한 정보는 UI에서 설정
  # DB_PASSWORD: ${DB_PASSWORD}
  # API_KEY: ${API_KEY}

job:
  script:
    - echo "데이터베이스 연결: $DB_HOST"
    - echo "API 키는 마스킹됨: $API_KEY"
```

### 2.2 파일 기반 시크릿
```yaml
create_secret:
  script:
    - echo -n $DB_PASSWORD > db_password.txt
    - kubectl create secret generic db-creds --from-file=db_password.txt
  rules:
    - if: $CI_COMMIT_BRANCH == "main"
```

---

## 3. 컨테이너 보안

### 3.1 이미지 스캔
```yaml
container_scanning:
  image: registry.gitlab.com/security-products/container-scanning
  variables:
    DOCKER_IMAGE: $CI_REGISTRY_IMAGE:$CI_COMMIT_SHA
    DOCKER_USER: $CI_REGISTRY_USER
    DOCKER_PASSWORD: $CI_REGISTRY_PASSWORD
  script:
    - scanner
  artifacts:
    reports:
      container_scanning: gl-container-scanning-report.json
```

### 3.2 권한 제한
```yaml
build:
  image: docker:20.10
  services:
    - docker:20.10-dind
  variables:
    DOCKER_TLS_CERTDIR: "/certs"
  script:
    - docker build --no-cache .
```

---

## 4. 코드 보안 스캔

### 4.1 SAST(정적 분석)
```yaml
sast:
  image: registry.gitlab.com/security-products/sast
  script:
    - /analyzer run
  artifacts:
    reports:
      sast: gl-sast-report.json
  rules:
    - when: always
```

### 4.2 의존성 스캔
```yaml
dependency_scanning:
  image: registry.gitlab.com/security-products/dependency-scanning
  script:
    - scan
  artifacts:
    reports:
      dependency_scanning: gl-dependency-scanning-report.json
```

---

## 5. 네트워크 보안

### 5.1 네트워크 정책
```yaml
.secure_job:
  tags:
    - secure
  variables:
    FF_NETWORK_PER_BUILD: "true"
  script:
    - curl https://api.internal.com

job:
  extends: .secure_job
```

### 5.2 VPN 구성
```yaml
vpn_job:
  before_script:
    - apt-get update && apt-get install -y openvpn
    - echo "$VPN_CONFIG" > config.ovpn
    - openvpn --config config.ovpn --daemon
  script:
    - curl https://internal-service.company.com
```

---

## 6. 감사 및 모니터링

### 6.1 로그 감사
```yaml
audit_job:
  script:
    - generate_audit_report.sh
  artifacts:
    paths:
      - audit-report/
    reports:
      junit: junit-report.xml
```

### 6.2 알림 설정
```yaml
.notify:
  after_script:
    - |
      if [ "$CI_JOB_STATUS" = "failed" ]; then
        curl -X POST -H 'Content-type: application/json' \
        --data "{\"text\":\"파이프라인 실패: $CI_PROJECT_URL/-/pipelines/$CI_PIPELINE_ID\"}" \
        $SLACK_WEBHOOK_URL
      fi
```

---

## 7. 보안 정책 구현

### 7.1 브랜치 보호
```yaml
# GitLab UI 설정
Settings > Repository > Protected Branches

# CI/CD 설정
merge_request:
  script:
    - run_security_checks.sh
  rules:
    - if: $CI_MERGE_REQUEST_TARGET_BRANCH_NAME == "main"
```

### 7.2 승인 워크플로우
```yaml
deploy:
  stage: deploy
  environment:
    name: production
  rules:
    - if: $CI_COMMIT_BRANCH == "main"
      when: manual
  needs:
    - security_scan
    - tests
```

---

## 8. 보안 체크리스트

### 8.1 필수 확인 사항
- 시크릿 관리 적절성
- 권한 설정 검증
- 네트워크 접근 제어
- 컨테이너 보안 설정
- 의존성 취약점 검사
- 감사 로그 설정

### 8.2 정기 점검 항목
- 권한 및 접근 로그 검토
- 보안 스캔 결과 분석
- 의존성 업데이트 확인
- 인증서 만료일 점검
- 보안 정책 준수 여부

---

## 참고 자료

- [GitLab 보안 설정 가이드](https://docs.gitlab.com/ee/security/)
- [CI/CD 보안 모범 사례](https://docs.gitlab.com/ee/ci/yaml/#secrets)
- [컨테이너 보안 가이드](https://docs.gitlab.com/ee/user/application_security/container_scanning/)

---

## 마무리

보안과 권한 관리는 CI/CD 파이프라인의 핵심 요소입니다. 적절한 보안 설정과 지속적인 모니터링을 통해 안전한 개발 환경을 유지하세요.