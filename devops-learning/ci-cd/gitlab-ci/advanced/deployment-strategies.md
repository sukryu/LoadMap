# 실무 CI/CD 배포 전략

> **목표:**  
> - CI/CD의 주요 배포 전략 이해
> - 각 배포 전략의 장단점 파악
> - GitLab CI/CD를 활용한 배포 전략 구현

---

## 1. Blue-Green 배포

### 1.1 개념
- 동일한 프로덕션 환경을 Blue/Green으로 구성
- 무중단 배포 가능
- 빠른 롤백 지원

### 1.2 구현 예제
```yaml
stages:
  - build
  - deploy
  - switch
  - cleanup

variables:
  BLUE_PORT: 8080
  GREEN_PORT: 8081

build:
  stage: build
  script:
    - docker build -t $CI_REGISTRY_IMAGE:$CI_COMMIT_SHA .

deploy_green:
  stage: deploy
  script:
    - docker stop green_app || true
    - docker rm green_app || true
    - docker run -d --name green_app -p $GREEN_PORT:8080 $CI_REGISTRY_IMAGE:$CI_COMMIT_SHA
    - ./health_check.sh http://localhost:$GREEN_PORT

switch_to_green:
  stage: switch
  script:
    - nginx -s reload  # Green으로 트래픽 전환
  when: manual

cleanup_blue:
  stage: cleanup
  script:
    - docker stop blue_app || true
    - docker rm blue_app || true
```

---

## 2. Canary 배포

### 2.1 개념
- 일부 사용자에게만 새 버전 배포
- 점진적인 트래픽 전환
- 위험 최소화

### 2.2 구현 예제
```yaml
.deploy_template: &deploy_definition
  image: kubectl:latest
  script:
    - kubectl apply -f k8s/deployment.yml

canary_deploy:
  stage: deploy
  <<: *deploy_definition
  variables:
    REPLICAS: 1
    CANARY: "true"
  environment:
    name: production
    url: https://myapp.example.com
  when: manual

promote_canary:
  stage: promote
  <<: *deploy_definition
  variables:
    REPLICAS: 10
    CANARY: "false"
  when: manual
```

### 2.3 Kubernetes Manifest
```yaml
# deployment.yml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: myapp-canary
spec:
  replicas: ${REPLICAS}
  selector:
    matchLabels:
      app: myapp
      track: canary
  template:
    metadata:
      labels:
        app: myapp
        track: canary
    spec:
      containers:
        - name: myapp
          image: ${CI_REGISTRY_IMAGE}:${CI_COMMIT_SHA}
```

---

## 3. Rolling 업데이트

### 3.1 개념
- 점진적으로 인스턴스 교체
- 무중단 배포
- 리소스 효율적 사용

### 3.2 구현 예제
```yaml
deploy_rolling:
  stage: deploy
  script:
    - kubectl set image deployment/myapp container=$CI_REGISTRY_IMAGE:$CI_COMMIT_SHA
    - kubectl rollout status deployment/myapp
  environment:
    name: production
    url: https://myapp.example.com

rollback:
  stage: rollback
  script:
    - kubectl rollout undo deployment/myapp
  when: manual
  only:
    - main
```

---

## 4. A/B 테스트 배포

### 4.1 개념
- 특정 기능/UI 테스트
- 사용자 피드백 수집
- 데이터 기반 의사결정

### 4.2 구현 예제
```yaml
deploy_ab_test:
  stage: deploy
  script:
    - helm upgrade myapp ./helm-chart
      --set version=$CI_COMMIT_SHA
      --set experiment.enabled=true
      --set experiment.variant=B
  environment:
    name: production
    url: https://myapp.example.com

analyze_results:
  stage: analyze
  script:
    - python analyze_ab_test.py
  artifacts:
    reports:
      metrics: metrics.txt
```

---

## 5. 배포 자동화 도구 연동

### 5.1 ArgoCD 연동
```yaml
deploy_argocd:
  stage: deploy
  script:
    - argocd app sync myapp
    - argocd app wait myapp
  environment:
    name: production
    url: https://myapp.example.com
```

### 5.2 Helm 사용
```yaml
deploy_helm:
  stage: deploy
  script:
    - helm upgrade --install myapp ./helm-chart
      --set image.tag=$CI_COMMIT_SHA
      --wait --timeout 5m
```

---

## 6. 모니터링 및 알림

### 6.1 배포 모니터링
```yaml
.monitor_deployment:
  script:
    - curl -f http://myapp.example.com/health
    - ./monitor_metrics.sh
    - ./check_logs.sh

deploy:
  stage: deploy
  script:
    - kubectl apply -f k8s/
  after_script:
    - !reference [.monitor_deployment, script]
```

### 6.2 알림 설정
```yaml
notify:
  stage: notify
  script:
    - |
      if [ "$CI_JOB_STATUS" = "success" ]; then
        curl -X POST $SLACK_WEBHOOK \
          -H 'Content-Type: application/json' \
          -d '{"text":"배포 성공: '"$CI_COMMIT_SHA"'"}'
      else
        curl -X POST $SLACK_WEBHOOK \
          -H 'Content-Type: application/json' \
          -d '{"text":"배포 실패: '"$CI_COMMIT_SHA"'"}'
      fi
```

---

## 7. 배포 전략 선택 기준

### 장애 영향도
- Blue-Green: 즉각적인 롤백 가능
- Canary: 점진적 위험 관리
- Rolling: 부분적 영향

### 리소스 요구사항
- Blue-Green: 2배의 리소스 필요
- Canary: 추가 리소스 최소화
- Rolling: 기존 리소스 활용

### 복잡도
- Blue-Green: 구성 단순
- Canary: 트래픽 제어 복잡
- Rolling: 중간 수준

---

## 참고 자료

- [GitLab 배포 전략](https://docs.gitlab.com/ee/ci/environments/)
- [Kubernetes Deployment 전략](https://kubernetes.io/docs/concepts/workloads/controllers/deployment/)
- [ArgoCD 공식 문서](https://argo-cd.readthedocs.io/)

---

## 마무리

효과적인 배포 전략은 안정적인 서비스 운영의 핵심입니다. 프로젝트의 특성과 요구사항에 맞는 최적의 배포 전략을 선택하고 구현하세요.