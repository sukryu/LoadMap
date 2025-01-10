# DevOps & CI/CD 실무

1. CI/CD 파이프라인
    - Jenkins, Github Actions, GitLab CI, CircleCI 등 툴 사용법
    - 빌드, 테스트(단위/통합/E2E), 보안 스캔, 컨테이너 빌드, 배포(Helm 등) 자동화
    - Canary/Blue-Green/Rolling Update 등 배포 전략

2. IaC(Infrastructure as Code)
    - Terraform, Pulumi, AWS CloudFormation, Ansible, Chef, SaltStack 등 중 택 1 ~ 2
    - 코드로 인프라를 정의하고 버전 관리, 프로비저닝(생성/변경/삭제)

3. GitOps
    - Argo CD, Flux CD 등으로 선언적(declarative) 방식 배포
    - "Git이 곧 싱글 소스 오브 투르스" -> 리포지토리 상태를 자동으로 K8s 클러스터에 반영