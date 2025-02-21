# Go 백엔드 애플리케이션 Helm 차트

이 Helm 차트는 Go로 작성된 백엔드 애플리케이션을 Kubernetes 클러스터에 배포하기 위한 패키지입니다. 이 차트는 개발, 스테이징, 프로덕션 환경 전반에 걸쳐 일관된 배포 프로세스를 제공하며, 다양한 구성 매개변수를 통해 각 환경에 맞게 조정할 수 있습니다.

## 특징

- Go 백엔드 애플리케이션의 완전한 배포 구성
- 수평적 Pod 자동 확장(HPA) 지원
- ConfigMap 및 Secret을 통한 구성 관리
- Ingress 리소스를 통한 외부 접근성
- 프로메테우스 모니터링 통합
- 여러 환경(개발, 스테이징, 프로덕션)에 대한 별도의 값 파일 제공

## 사전 요구 사항

- Kubernetes 1.19+
- Helm 3.0+
- 동적 스토리지 프로비저닝을 지원하는 PersistentVolume 프로비저너 (선택 사항)
- Ingress 컨트롤러 (외부 접근성이 필요한 경우)

## 설치 방법

### 1. Helm 저장소 추가 (내부 저장소를 사용하는 경우)

```bash
helm repo add mycompany-repo https://helm.mycompany.com/
helm repo update
```

### 2. 차트 설치

```bash
# 기본 설정으로 설치
helm install my-api mycompany-repo/go-api

# 또는, 로컬 차트 디렉토리에서 설치
helm install my-api ./helm

# 사용자 정의 values 파일로 설치
helm install my-api ./helm -f ./helm/values-production.yaml

# 특정 매개변수 오버라이드
helm install my-api ./helm --set replicaCount=3 --set image.tag=v1.2.3
```

### 3. 업그레이드

애플리케이션을 새 버전으로 업그레이드하려면:

```bash
# 차트 업그레이드
helm upgrade my-api mycompany-repo/go-api

# 또는, 로컬 차트로 업그레이드
helm upgrade my-api ./helm

# 특정 values 파일로 업그레이드
helm upgrade my-api ./helm -f ./helm/values-production.yaml
```

### 4. 삭제

애플리케이션 배포를 삭제하려면:

```bash
helm uninstall my-api
```

## 구성 매개변수

다음은 `values.yaml` 파일에서 구성할 수 있는 주요 매개변수의 목록입니다:

### 글로벌 설정

| 매개변수 | 설명 | 기본값 |
|---------|-------------|---------|
| `nameOverride` | 차트 이름 오버라이드 | `""` |
| `fullnameOverride` | 전체 이름 오버라이드 | `""` |
| `environment` | 배포 환경 (dev, staging, prod) | `"dev"` |

### 이미지 설정

| 매개변수 | 설명 | 기본값 |
|---------|-------------|---------|
| `image.repository` | 컨테이너 이미지 저장소 | `"registry.mycompany.com/backend/go-api"` |
| `image.tag` | 컨테이너 이미지 태그 (버전) | `"latest"` |
| `image.pullPolicy` | 이미지 풀 정책 | `"Always"` |
| `imagePullSecrets` | 이미지 풀 시크릿 | `[]` |

### 배포 설정

| 매개변수 | 설명 | 기본값 |
|---------|-------------|---------|
| `replicaCount` | 배포할 Pod 복제본 수 | `2` |
| `strategy` | 배포 전략 설정 | `{ type: RollingUpdate }` |
| `resources` | 컨테이너 리소스 요청 및 제한 | `{}` |
| `nodeSelector` | Pod 노드 선택 제약 조건 | `{}` |
| `tolerations` | Pod 톨러레이션 | `[]` |
| `affinity` | Pod 어피니티 설정 | `{}` |

### 서비스 설정

| 매개변수 | 설명 | 기본값 |
|---------|-------------|---------|
| `service.type` | 서비스 유형 | `"ClusterIP"` |
| `service.port` | 서비스 포트 | `80` |
| `service.targetPort` | 컨테이너 대상 포트 | `8080` |

### Ingress 설정

| 매개변수 | 설명 | 기본값 |
|---------|-------------|---------|
| `ingress.enabled` | Ingress 활성화 여부 | `false` |
| `ingress.className` | Ingress 클래스 이름 | `"nginx"` |
| `ingress.annotations` | Ingress 어노테이션 | `{}` |
| `ingress.hosts` | Ingress 호스트 설정 | `[{host: "api.local", paths: [{path: "/", pathType: "Prefix"}]}]` |
| `ingress.tls` | Ingress TLS 설정 | `[]` |

### 자동 확장 설정

| 매개변수 | 설명 | 기본값 |
|---------|-------------|---------|
| `autoscaling.enabled` | HPA 활성화 여부 | `false` |
| `autoscaling.minReplicas` | 최소 복제본 수 | `2` |
| `autoscaling.maxReplicas` | 최대 복제본 수 | `10` |
| `autoscaling.targetCPUUtilizationPercentage` | 목표 CPU 사용률 | `80` |
| `autoscaling.targetMemoryUtilizationPercentage` | 목표 메모리 사용률 | `80` |

### 애플리케이션 설정

| 매개변수 | 설명 | 기본값 |
|---------|-------------|---------|
| `config.logLevel` | 로그 레벨 | `"info"` |
| `config.appPort` | 애플리케이션 포트 | `8080` |
| `config.timeoutSeconds` | 요청 타임아웃 | `30` |
| `config.enableMetrics` | 메트릭 활성화 여부 | `true` |
| `config.extraEnv` | 추가 환경 변수 | `[]` |

### 데이터베이스 설정

| 매개변수 | 설명 | 기본값 |
|---------|-------------|---------|
| `database.enabled` | 데이터베이스 연결 활성화 | `true` |
| `database.type` | 데이터베이스 유형 (postgres, mysql) | `"postgres"` |
| `database.host` | 데이터베이스 호스트 | `"postgres.database"` |
| `database.port` | 데이터베이스 포트 | `5432` |
| `database.name` | 데이터베이스 이름 | `"myapp"` |
| `database.username` | 데이터베이스 사용자 이름 | `"postgres"` |
| `database.existingSecret` | 데이터베이스 인증 정보용 기존 시크릿 | `""` |

## 환경별 구성

이 차트는 다양한 환경에 대한 별도의 값 파일을 제공합니다:

- `values.yaml`: 기본값
- `values-dev.yaml`: 개발 환경 설정
- `values-staging.yaml`: 스테이징 환경 설정
- `values-production.yaml`: 프로덕션 환경 설정

각 환경에 맞는 값 파일을 사용하여 Helm 설치 또는 업그레이드를 수행하세요.

## 보안 고려사항

### 민감한 정보 관리

민감한 데이터(비밀번호, API 키 등)는 Kubernetes Secret으로 관리해야 합니다. 이 차트는 다음 방법으로 Secret을 처리할 수 있습니다:

1. 기존 Secret 사용:
   ```yaml
   database:
     existingSecret: "my-db-credentials"
   ```

2. 외부 시크릿 관리자 통합:
   - Hashicorp Vault
   - AWS Secrets Manager
   - GCP Secret Manager

### 권장 사항

- 프로덕션 환경에서는 항상 특정 이미지 태그를 사용하고, `latest` 태그 사용을 피하세요.
- Secret과 ConfigMap을 정기적으로 순환하세요.
- 최소 권한 원칙에 따라 ServiceAccount 권한을 구성하세요.
- 가능하면 Secret 암호화를 활성화하세요.

## 모니터링 및 로깅

### 프로메테우스 메트릭

이 차트는 프로메테우스 메트릭을 지원합니다. 활성화하려면:

```yaml
config:
  enableMetrics: true

serviceMonitor:
  enabled: true
  interval: "15s"
```

### 로깅

애플리케이션 로그는 표준 출력(stdout)과 표준 오류(stderr)로 전송됩니다. Fluentd, Elasticsearch, Kibana(EFK) 스택 또는 Loki를 사용하여 이러한 로그를 수집하고 검색할 수 있습니다.

## 문제 해결

### 공통 이슈

1. **Pod가 시작되지 않음**
   ```bash
   kubectl describe pod <pod-name>
   kubectl logs <pod-name>
   ```

2. **서비스 연결 불가**
   ```bash
   kubectl get endpoints <service-name>
   kubectl describe service <service-name>
   ```

3. **Ingress 문제**
   ```bash
   kubectl describe ingress <ingress-name>
   kubectl get events --field-selector involvedObject.name=<ingress-name>
   ```

## 차트 개발 및 테스트

### 로컬 개발

차트 개발 시 다음 명령어로 템플릿 렌더링을 확인할 수 있습니다:

```bash
# 템플릿 렌더링 확인
helm template ./helm

# 특정 값 파일로 템플릿 렌더링
helm template ./helm -f ./helm/values-dev.yaml

# 특정 매개변수 오버라이드하여 템플릿 렌더링
helm template ./helm --set replicaCount=1
```

### 린팅 및 테스트

배포 전 차트 검증:

```bash
# 차트 문법 검증
helm lint ./helm

# 설치 테스트 (실제 설치하지 않음)
helm install my-api ./helm --dry-run
```

## 참고 사항

- 이 차트는 Go 백엔드 애플리케이션을 위해 설계되었으며, 다른 유형의 애플리케이션에는 수정이 필요할 수 있습니다.
- Kubernetes 버전 호환성을 고려하여 적절한 Kubernetes API 버전을 사용하세요.
- 대규모 클러스터에서는 리소스 요청과 제한을 적절하게 설정하여 안정적인 성능을 보장하세요.

## 지원 및 기여

문제 보고 또는 기능 요청은 내부 JIRA/GitHub 이슈 트래커를 사용하세요. 이 차트에 기여하려면 내부 개발 가이드라인을 참조하세요.