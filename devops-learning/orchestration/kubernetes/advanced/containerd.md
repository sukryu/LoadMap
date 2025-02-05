# Kubernetes 컨테이너 런타임: containerd 심층 이해

> **목표:**  
> - Kubernetes 컨테이너 런타임의 아키텍처와 작동 원리를 이해한다.
> - containerd의 구성 요소와 기능을 파악한다.
> - 컨테이너 런타임 관리 및 문제 해결 방법을 습득한다.
> - 실제 운영 환경에서의 컨테이너 런타임 최적화 방법을 익힌다.

---

## 1. 컨테이너 런타임 개요

Kubernetes의 컨테이너 런타임은 실제로 컨테이너를 실행하고 관리하는 소프트웨어 계층입니다. 현재 Kubernetes는 CRI(Container Runtime Interface)를 통해 다양한 컨테이너 런타임을 지원하며, 그 중 containerd가 표준으로 자리잡고 있습니다.

### 1.1 컨테이너 런타임 계층 구조

컨테이너 런타임은 다음과 같은 계층 구조로 구성됩니다:

1. 고수준 런타임 (CRI 구현체)
   - containerd
   - CRI-O

2. 저수준 런타임 (OCI 구현체)
   - runc
   - crun
   - kata-runtime

### 1.2 CRI (Container Runtime Interface)

CRI는 Kubernetes와 컨테이너 런타임 간의 표준 인터페이스를 제공합니다:

```protobuf
service RuntimeService {
    rpc CreateContainer(CreateContainerRequest) returns (CreateContainerResponse) {}
    rpc StartContainer(StartContainerRequest) returns (StartContainerResponse) {}
    rpc StopContainer(StopContainerRequest) returns (StopContainerResponse) {}
    rpc RemoveContainer(RemoveContainerRequest) returns (RemoveContainerResponse) {}
    // ... 기타 메서드들
}
```

---

## 2. containerd 아키텍처 및 구성

containerd는 산업 표준 컨테이너 런타임으로, 컨테이너의 전체 라이프사이클을 관리합니다.

### 2.1 기본 구성 요소

containerd의 주요 구성 요소는 다음과 같습니다:

```plaintext
containerd/
├── containerd daemon
│   ├── CRI plugin
│   ├── Storage plugin
│   └── Network plugin
├── containerd-shim
└── runc
```

### 2.2 containerd 설정

기본 설정 파일 (/etc/containerd/config.toml):

```toml
version = 2
root = "/var/lib/containerd"
state = "/run/containerd"

[plugins."io.containerd.grpc.v1.cri"]
  sandbox_image = "k8s.gcr.io/pause:3.6"
  
[plugins."io.containerd.grpc.v1.cri".containerd]
  default_runtime_name = "runc"
  
[plugins."io.containerd.grpc.v1.cri".containerd.runtimes.runc]
  runtime_type = "io.containerd.runc.v2"
  
[plugins."io.containerd.grpc.v1.cri".registry]
  config_path = "/etc/containerd/certs.d"
```

---

## 3. 컨테이너 라이프사이클 관리

containerd는 컨테이너의 전체 라이프사이클을 관리합니다.

### 3.1 컨테이너 생성 및 실행

```bash
# containerd CLI (ctr) 사용 예시
ctr images pull docker.io/library/nginx:latest
ctr run docker.io/library/nginx:latest nginx
```

### 3.2 컨테이너 모니터링

```bash
# 실행 중인 컨테이너 목록 확인
ctr containers list

# 컨테이너 상세 정보 확인
ctr containers info <container-id>

# 태스크 상태 확인
ctr tasks list
```

---

## 4. 이미지 관리

containerd는 효율적인 이미지 관리 기능을 제공합니다.

### 4.1 이미지 레이어 관리

```bash
# 이미지 풀링
ctr images pull docker.io/library/nginx:latest

# 이미지 목록 확인
ctr images list

# 이미지 상세 정보 확인
ctr images info docker.io/library/nginx:latest
```

### 4.2 이미지 캐시 관리

```toml
[plugins."io.containerd.grpc.v1.cri".registry.mirrors."docker.io"]
  endpoint = ["https://registry-1.docker.io"]
  
[plugins."io.containerd.grpc.v1.cri".registry.configs."registry-1.docker.io".tls]
  insecure_skip_verify = false
```

---

## 5. 네트워킹 및 스토리지

### 5.1 네트워크 설정

CNI 플러그인 설정 예시:

```json
{
    "cniVersion": "0.4.0",
    "name": "containerd-net",
    "plugins": [
        {
            "type": "bridge",
            "bridge": "cni0",
            "ipMasq": true,
            "ipam": {
                "type": "host-local",
                "ranges": [
                    [{
                        "subnet": "10.88.0.0/16"
                    }]
                ],
                "routes": [
                    { "dst": "0.0.0.0/0" }
                ]
            }
        }
    ]
}
```

### 5.2 스토리지 드라이버 설정

```toml
[plugins."io.containerd.grpc.v1.cri".containerd]
  snapshotter = "overlayfs"
  
[plugins."io.containerd.grpc.v1.cri".containerd.runtimes.runc.options]
  SystemdCgroup = true
```

---

## 6. 성능 최적화 및 문제 해결

### 6.1 성능 튜닝

containerd 성능 최적화를 위한 주요 설정:

```toml
[plugins."io.containerd.grpc.v1.cri"]
  max_container_log_line_size = 16384
  max_concurrent_downloads = 3
  disable_tcp_service = true
  
[debug]
  level = "info"
  
[metrics]
  address = "127.0.0.1:1338"
  grpc_histogram = false
```

### 6.2 문제 해결 도구

```bash
# 로그 확인
journalctl -u containerd

# 메트릭 수집
curl -s http://localhost:1338/metrics

# 디버그 정보 수집
containerd --log-level debug
```

---

## 7. 보안 설정

### 7.1 권한 및 보안 정책

seccomp 프로필 설정 예시:

```json
{
    "defaultAction": "SCMP_ACT_ERRNO",
    "architectures": ["SCMP_ARCH_X86_64"],
    "syscalls": [
        {
            "names": [
                "accept",
                "bind",
                "listen"
            ],
            "action": "SCMP_ACT_ALLOW"
        }
    ]
}
```

### 7.2 이미지 보안

```toml
[plugins."io.containerd.grpc.v1.cri".registry.configs."registry-1.docker.io".auth]
  username = "username"
  password = "password"
  
[plugins."io.containerd.grpc.v1.cri".registry.configs."registry-1.docker.io".tls]
  ca_file = "/etc/containerd/certs.d/registry-1.docker.io/ca.crt"
```

---

## 마무리

Kubernetes의 컨테이너 런타임은 전체 시스템의 안정성과 성능에 직접적인 영향을 미치는 핵심 구성 요소입니다. containerd를 효과적으로 구성하고 관리하는 것은 Kubernetes 클러스터의 성공적인 운영을 위해 매우 중요합니다.

특히 운영 환경에서는 성능 최적화, 보안 설정, 모니터링 체계 구축에 중점을 두어야 합니다. 또한 문제 발생 시 신속한 대응을 위해 로깅과 모니터링 시스템을 적절히 구성하고 관리하는 것이 필요합니다.

containerd의 구성과 관리 방법을 잘 이해하고 있다면, 안정적이고 효율적인 Kubernetes 환경을 구축하고 운영할 수 있을 것입니다.