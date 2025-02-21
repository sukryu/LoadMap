{{/*
    _helpers.tpl - Go 백엔드 애플리케이션 Helm 차트를 위한 헬퍼 템플릿 정의
    
    이 파일은 Helm 차트 템플릿 전체에서 재사용할 수 있는 명명 헬퍼 함수와 레이블 정의를 제공합니다.
    각 함수는 특정 목적을 가지고 있으며, 차트의 여러 템플릿 파일에서 일관된 이름과 레이블을 생성하는 데 사용됩니다.
    */}}
    
    {{/*
    go-api.name - 차트 이름 생성
    차트 이름을 생성하기 위한 헬퍼 템플릿입니다.
    기본적으로 .Chart.Name을 사용하고, nameOverride가 지정된 경우 이를 사용합니다.
    이 함수는 일반적으로 레이블 및 리소스 이름의 일부로 사용됩니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      차트 이름 (영숫자와 '-'만 포함)
    
    사용 예:
      name: {{ include "go-api.name" . }}
    */}}
    {{- define "go-api.name" -}}
    {{- default .Chart.Name .Values.nameOverride | trunc 63 | trimSuffix "-" }}
    {{- end }}
    
    {{/*
    go-api.fullname - 전체 애플리케이션 이름 생성
    애플리케이션의 완전한 이름을 생성하기 위한 헬퍼 템플릿입니다.
    이는 일반적으로 "release-name-chart-name" 형식을 따릅니다.
    fullnameOverride가 지정된 경우 이를 사용합니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      릴리스 이름을 포함한 전체 애플리케이션 이름 (63자로 제한)
    
    사용 예:
      name: {{ include "go-api.fullname" . }}
    */}}
    {{- define "go-api.fullname" -}}
    {{- if .Values.fullnameOverride }}
    {{- .Values.fullnameOverride | trunc 63 | trimSuffix "-" }}
    {{- else }}
    {{- $name := default .Chart.Name .Values.nameOverride }}
    {{- if contains $name .Release.Name }}
    {{- .Release.Name | trunc 63 | trimSuffix "-" }}
    {{- else }}
    {{- printf "%s-%s" .Release.Name $name | trunc 63 | trimSuffix "-" }}
    {{- end }}
    {{- end }}
    {{- end }}
    
    {{/*
    go-api.chart - 차트 이름과 버전 생성
    차트 이름과 버전 정보를 "chart-name-chart-version" 형식으로 생성하는 헬퍼 템플릿입니다.
    이는 주로 차트 레이블에 사용됩니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      차트 이름과 버전으로 구성된 문자열
    
    사용 예:
      helm.sh/chart: {{ include "go-api.chart" . }}
    */}}
    {{- define "go-api.chart" -}}
    {{- printf "%s-%s" .Chart.Name .Chart.Version | replace "+" "_" | trunc 63 | trimSuffix "-" }}
    {{- end }}
    
    {{/*
    go-api.labels - 공통 레이블 생성
    모든 리소스에 적용할 공통 레이블을 생성하는 헬퍼 템플릿입니다.
    이 레이블들은 Kubernetes 리소스를 관리하고 분류하는 데 사용됩니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      여러 줄의 YAML 형식 레이블
    
    사용 예:
      labels:
        {{- include "go-api.labels" . | nindent 4 }}
    */}}
    {{- define "go-api.labels" -}}
    helm.sh/chart: {{ include "go-api.chart" . }}
    {{ include "go-api.selectorLabels" . }}
    {{- if .Chart.AppVersion }}
    app.kubernetes.io/version: {{ .Chart.AppVersion | quote }}
    {{- end }}
    app.kubernetes.io/managed-by: {{ .Release.Service }}
    {{- if .Values.global.environment }}
    environment: {{ .Values.global.environment }}
    {{- end }}
    {{- if .Values.additionalLabels }}
    {{- toYaml .Values.additionalLabels }}
    {{- end }}
    {{- end }}
    
    {{/*
    go-api.selectorLabels - 셀렉터 레이블 생성
    리소스 선택에 사용되는 레이블을 생성하는 헬퍼 템플릿입니다.
    이는 Service와 Deployment가 올바른 Pod를 선택하는 데 필수적입니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      여러 줄의 YAML 형식 셀렉터 레이블
    
    사용 예:
      selector:
        matchLabels:
          {{- include "go-api.selectorLabels" . | nindent 6 }}
    */}}
    {{- define "go-api.selectorLabels" -}}
    app.kubernetes.io/name: {{ include "go-api.name" . }}
    app.kubernetes.io/instance: {{ .Release.Name }}
    {{- if .Values.additionalSelectorLabels }}
    {{- toYaml .Values.additionalSelectorLabels }}
    {{- end }}
    {{- end }}
    
    {{/*
    go-api.serviceAccountName - 서비스 어카운트 이름 생성
    사용할 서비스 어카운트 이름을 결정하는 헬퍼 템플릿입니다.
    serviceAccount.create이 true인 경우 go-api.fullname을 사용하고,
    그렇지 않은 경우 serviceAccount.name 값을 사용합니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      사용할 서비스 어카운트 이름
    
    사용 예:
      serviceAccountName: {{ include "go-api.serviceAccountName" . }}
    */}}
    {{- define "go-api.serviceAccountName" -}}
    {{- if .Values.serviceAccount.create }}
    {{- default (include "go-api.fullname" .) .Values.serviceAccount.name }}
    {{- else }}
    {{- default "default" .Values.serviceAccount.name }}
    {{- end }}
    {{- end }}
    
    {{/*
    go-api.podAnnotations - Pod 어노테이션 생성
    Pod에 적용할 어노테이션을 생성하는 헬퍼 템플릿입니다.
    기본 어노테이션과 values.yaml에서 정의된 사용자 정의 어노테이션을 결합합니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      여러 줄의 YAML 형식 어노테이션
    
    사용 예:
      annotations:
        {{- include "go-api.podAnnotations" . | nindent 8 }}
    */}}
    {{- define "go-api.podAnnotations" -}}
    {{- if .Values.podAnnotations }}
    {{- toYaml .Values.podAnnotations }}
    {{- end }}
    checksum/config: {{ include (print $.Template.BasePath "/configmap.yaml") . | sha256sum }}
    checksum/secret: {{ include (print $.Template.BasePath "/secret.yaml") . | sha256sum }}
    {{- end }}
    
    {{/*
    go-api.containerPorts - 컨테이너 포트 정의 생성
    컨테이너 포트 정의를 생성하는 헬퍼 템플릿입니다.
    기본 HTTP 포트와 values.yaml에서 정의된 추가 포트를 포함합니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      여러 줄의 YAML 형식 포트 정의
    
    사용 예:
      ports:
        {{- include "go-api.containerPorts" . | nindent 8 }}
    */}}
    {{- define "go-api.containerPorts" -}}
    - name: http
      containerPort: {{ .Values.config.appPort | default 8080 }}
      protocol: TCP
    {{- if .Values.config.enableMetrics }}
    - name: metrics
      containerPort: {{ .Values.config.metricsPort | default 9090 }}
      protocol: TCP
    {{- end }}
    {{- if .Values.additionalPorts }}
    {{- toYaml .Values.additionalPorts }}
    {{- end }}
    {{- end }}
    
    {{/*
    go-api.deploymentPodSecurityContext - Pod 보안 컨텍스트 생성
    Pod 수준의 보안 컨텍스트 설정을 생성하는 헬퍼 템플릿입니다.
    values.yaml에서 정의된 설정이 있으면 사용하고, 그렇지 않으면 기본값을 제공합니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      YAML 형식의 Pod 보안 컨텍스트 설정
    
    사용 예:
      securityContext:
        {{- include "go-api.deploymentPodSecurityContext" . | nindent 8 }}
    */}}
    {{- define "go-api.deploymentPodSecurityContext" -}}
    {{- if .Values.podSecurityContext }}
    {{- toYaml .Values.podSecurityContext }}
    {{- else }}
    fsGroup: 1000
    runAsUser: 1000
    runAsGroup: 1000
    runAsNonRoot: true
    {{- end }}
    {{- end }}
    
    {{/*
    go-api.deploymentContainerSecurityContext - 컨테이너 보안 컨텍스트 생성
    컨테이너 수준의 보안 컨텍스트 설정을 생성하는 헬퍼 템플릿입니다.
    values.yaml에서 정의된 설정이 있으면 사용하고, 그렇지 않으면 기본값을 제공합니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      YAML 형식의 컨테이너 보안 컨텍스트 설정
    
    사용 예:
      securityContext:
        {{- include "go-api.deploymentContainerSecurityContext" . | nindent 12 }}
    */}}
    {{- define "go-api.deploymentContainerSecurityContext" -}}
    {{- if .Values.securityContext }}
    {{- toYaml .Values.securityContext }}
    {{- else }}
    capabilities:
      drop:
      - ALL
    readOnlyRootFilesystem: true
    allowPrivilegeEscalation: false
    runAsNonRoot: true
    runAsUser: 1000
    runAsGroup: 1000
    {{- end }}
    {{- end }}
    
    {{/*
    go-api.environment - 환경 변수 생성
    컨테이너에 설정할 환경 변수를 생성하는 헬퍼 템플릿입니다.
    환경 변수, ConfigMap 참조, Secret 참조 등 다양한 형태를 지원합니다.
    
    인자:
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      YAML 형식의 환경 변수 리스트
    
    사용 예:
      env:
        {{- include "go-api.environment" . | nindent 12 }}
    */}}
    {{- define "go-api.environment" -}}
    - name: POD_NAME
      valueFrom:
        fieldRef:
          fieldPath: metadata.name
    - name: POD_NAMESPACE
      valueFrom:
        fieldRef:
          fieldPath: metadata.namespace
    - name: APP_ENV
      value: {{ .Values.global.environment | default "development" | quote }}
    - name: LOG_LEVEL
      value: {{ .Values.config.logLevel | default "info" | quote }}
    - name: APP_PORT
      value: {{ .Values.config.appPort | default 8080 | quote }}
    {{- if .Values.config.extraEnv }}
    {{- toYaml .Values.config.extraEnv }}
    {{- end }}
    {{- end }}
    
    {{/*
    go-api.getValueByVersion - Kubernetes 버전에 따른 값 선택
    Kubernetes 버전에 따라 다른 값을 반환하는 헬퍼 템플릿입니다.
    API 버전이나 필드 이름이 Kubernetes 버전에 따라 달라질 때 유용합니다.
    
    인자:
      1. Kubernetes 버전 비교 문자열
      2. 버전이 일치할 때 반환할 값
      3. 버전이 일치하지 않을 때 반환할 값
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      선택된 값(문자열)
    
    사용 예:
      apiVersion: {{ include "go-api.getValueByVersion" (list ">= 1.19" "networking.k8s.io/v1" "networking.k8s.io/v1beta1" .) }}
    */}}
    {{- define "go-api.getValueByVersion" -}}
    {{- $compareVersion := index . 0 -}}
    {{- $ifValue := index . 1 -}}
    {{- $elseValue := index . 2 -}}
    {{- $root := index . 3 -}}
    {{- if semverCompare $compareVersion $root.Capabilities.KubeVersion.GitVersion -}}
    {{- $ifValue -}}
    {{- else -}}
    {{- $elseValue -}}
    {{- end -}}
    {{- end -}}
    
    {{/*
    go-api.getApiVersionByK8sVersion - Kubernetes 버전에 따른 API 버전 결정
    Kubernetes 버전에 따라 올바른 API 버전을 반환하는 헬퍼 템플릿입니다.
    이는 다양한 Kubernetes 클러스터 버전과의 호환성을 유지하는 데 도움이 됩니다.
    
    인자:
      1. API 그룹 이름 (예: "networking.k8s.io")
      2. 리소스 종류 (예: "Ingress")
      . - 차트의 전체 컨텍스트(루트 컨텍스트) 필요
    
    반환:
      완전한 API 버전 문자열
    
    사용 예:
      apiVersion: {{ include "go-api.getApiVersionByK8sVersion" (list "networking.k8s.io" "Ingress" .) }}
    */}}
    {{- define "go-api.getApiVersionByK8sVersion" -}}
    {{- $apiGroup := index . 0 -}}
    {{- $kind := index . 1 -}}
    {{- $root := index . 2 -}}
    
    {{- if eq $apiGroup "networking.k8s.io" -}}
      {{- if eq $kind "Ingress" -}}
        {{- include "go-api.getValueByVersion" (list ">= 1.19" "networking.k8s.io/v1" "networking.k8s.io/v1beta1" $root) -}}
      {{- end -}}
    {{- else if eq $apiGroup "autoscaling" -}}
      {{- if eq $kind "HorizontalPodAutoscaler" -}}
        {{- include "go-api.getValueByVersion" (list ">= 1.23" "autoscaling/v2" "autoscaling/v2beta2" $root) -}}
      {{- end -}}
    {{- end -}}
    {{- end -}}