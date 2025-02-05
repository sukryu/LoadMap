# Kubernetes 스토리지 관리: 퍼시스턴트 볼륨과 스토리지

> **목표:**  
> - Kubernetes의 스토리지 아키텍처와 개념을 이해한다.
> - 퍼시스턴트 볼륨과 퍼시스턴트 볼륨 클레임의 관계를 파악한다.
> - 스토리지 클래스를 통한 동적 프로비저닝 방법을 습득한다.
> - 실제 운영 환경에서의 스토리지 관리 베스트 프랙티스를 익힌다.

---

## 1. Kubernetes 스토리지 기본 개념

Kubernetes에서 스토리지는 컨테이너의 데이터를 영속적으로 저장하고 관리하는 중요한 리소스입니다. 컨테이너가 재시작되더라도 데이터는 유지되어야 하며, 여러 파드에서 동일한 데이터에 접근해야 할 수도 있습니다.

### 1.1 스토리지의 종류

Kubernetes는 다음과 같은 다양한 유형의 스토리지를 지원합니다:

1. 임시 스토리지 (emptyDir)
   - 파드의 생명주기와 함께하는 임시 저장소
   - 파드가 삭제되면 데이터도 함께 삭제됨

2. 호스트 경로 (hostPath)
   - 노드의 파일시스템을 직접 마운트
   - 노드 레벨의 영속성 제공

3. 퍼시스턴트 볼륨 (PV)
   - 클러스터 수준의 스토리지 리소스
   - 파드의 생명주기와 독립적으로 존재

---

## 2. 퍼시스턴트 볼륨 (PV) 구성

퍼시스턴트 볼륨은 관리자가 프로비저닝하거나 스토리지 클래스를 통해 동적으로 프로비저닝할 수 있는 클러스터의 스토리지입니다.

### 2.1 정적 프로비저닝

수동으로 PV를 생성하는 예시:

```yaml
apiVersion: v1
kind: PersistentVolume
metadata:
  name: pv-static
spec:
  capacity:
    storage: 10Gi
  accessModes:
    - ReadWriteOnce
  persistentVolumeReclaimPolicy: Retain
  storageClassName: standard
  nfs:
    path: /path/to/data
    server: nfs-server.example.com
```

### 2.2 동적 프로비저닝

스토리지 클래스를 통한 동적 PV 프로비저닝 설정:

```yaml
apiVersion: storage.k8s.io/v1
kind: StorageClass
metadata:
  name: fast
provisioner: kubernetes.io/aws-ebs
parameters:
  type: gp2
  fsType: ext4
reclaimPolicy: Delete
allowVolumeExpansion: true
```

---

## 3. 퍼시스턴트 볼륨 클레임 (PVC)

PVC는 사용자가 PV를 요청하는 방법입니다. PVC를 통해 스토리지의 크기와 접근 모드를 지정할 수 있습니다.

### 3.1 PVC 생성

```yaml
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: mysql-pvc
spec:
  accessModes:
    - ReadWriteOnce
  resources:
    requests:
      storage: 8Gi
  storageClassName: fast
```

### 3.2 파드에서 PVC 사용

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: mysql-pod
spec:
  containers:
    - name: mysql
      image: mysql:5.7
      volumeMounts:
        - name: mysql-storage
          mountPath: /var/lib/mysql
      env:
        - name: MYSQL_ROOT_PASSWORD
          value: "password"
  volumes:
    - name: mysql-storage
      persistentVolumeClaim:
        claimName: mysql-pvc
```

---

## 4. 스토리지 클래스(StorageClass) 관리

스토리지 클래스는 스토리지의 "등급"을 정의하며, 동적 프로비저닝을 가능하게 합니다.

### 4.1 클라우드 프로바이더별 설정

AWS EBS 스토리지 클래스 예시:

```yaml
apiVersion: storage.k8s.io/v1
kind: StorageClass
metadata:
  name: aws-standard
provisioner: kubernetes.io/aws-ebs
parameters:
  type: gp2
  encrypted: "true"
  kmsKeyId: "arn:aws:kms:us-east-1:123456789012:key/abcd1234-a123-456a-a12b-a123b4cd56ef"
```

Azure Disk 스토리지 클래스 예시:

```yaml
apiVersion: storage.k8s.io/v1
kind: StorageClass
metadata:
  name: azure-standard
provisioner: kubernetes.io/azure-disk
parameters:
  storageaccounttype: Standard_LRS
  kind: Managed
```

---

## 5. 볼륨 스냅샷 관리

볼륨 스냅샷을 통해 데이터 백업과 복원이 가능합니다.

### 5.1 볼륨 스냅샷 클래스 정의

```yaml
apiVersion: snapshot.storage.k8s.io/v1
kind: VolumeSnapshotClass
metadata:
  name: csi-hostpath-snapclass
driver: hostpath.csi.k8s.io
deletionPolicy: Delete
```

### 5.2 볼륨 스냅샷 생성

```yaml
apiVersion: snapshot.storage.k8s.io/v1
kind: VolumeSnapshot
metadata:
  name: mysql-snapshot
spec:
  volumeSnapshotClassName: csi-hostpath-snapclass
  source:
    persistentVolumeClaimName: mysql-pvc
```

---

## 6. 스토리지 모니터링 및 관리

### 6.1 스토리지 사용량 모니터링

```bash
# PV 상태 확인
kubectl get pv

# PVC 상태 확인
kubectl get pvc

# 스토리지 클래스 확인
kubectl get storageclass

# 특정 PV의 상세 정보 확인
kubectl describe pv <pv-name>
```

### 6.2 볼륨 확장

```yaml
apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: mysql-pvc
spec:
  accessModes:
    - ReadWriteOnce
  resources:
    requests:
      storage: 16Gi  # 크기 증가
```

---

## 7. 스토리지 운영 베스트 프랙티스

1. 데이터 보호
   - 중요 데이터는 항상 백업 정책을 설정
   - 정기적인 스냅샷 생성
   - 암호화 사용

2. 성능 최적화
   - 워크로드에 적합한 스토리지 유형 선택
   - 적절한 스토리지 클래스 설정
   - IOPS 요구사항 고려

3. 비용 최적화
   - 필요한 만큼만 스토리지 할당
   - 미사용 PV 정리
   - 적절한 ReclaimPolicy 설정

4. 장애 대비
   - 고가용성 구성 고려
   - 장애 복구 절차 마련
   - 정기적인 복구 테스트

---

## 8. 문제 해결 가이드

### 8.1 일반적인 문제 해결

```bash
# 볼륨 마운트 문제 확인
kubectl describe pod <pod-name>

# PV 바인딩 문제 확인
kubectl describe pv <pv-name>
kubectl describe pvc <pvc-name>

# 스토리지 클래스 프로비저너 확인
kubectl describe storageclass <storageclass-name>
```

### 8.2 로그 확인

```bash
# 스토리지 프로비저너 로그 확인
kubectl logs -n kube-system <provisioner-pod-name>

# 볼륨 컨트롤러 로그 확인
kubectl logs -n kube-system <volume-controller-pod-name>
```

---

## 마무리

Kubernetes의 스토리지 관리는 애플리케이션의 데이터 지속성과 가용성을 보장하는 핵심 요소입니다. 퍼시스턴트 볼륨, 퍼시스턴트 볼륨 클레임, 스토리지 클래스를 적절히 구성하고 관리함으로써, 안정적이고 확장 가능한 스토리지 인프라를 구축할 수 있습니다. 특히 운영 환경에서는 데이터 보호, 성능 최적화, 비용 관리를 균형있게 고려하여 스토리지 전략을 수립해야 합니다.