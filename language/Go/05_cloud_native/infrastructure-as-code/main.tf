// main.tf
// ------------------------------------------------------------
// AWS Provider 설정
// Terraform이 AWS API와 상호작용할 수 있도록 리전을 지정합니다.
provider "aws" {
  region = var.aws_region  // variables.tf에서 정의된 aws_region 변수를 사용합니다.
}

// ------------------------------------------------------------
// VPC 생성
// 애플리케이션을 위한 기본 가상 네트워크를 생성합니다.
resource "aws_vpc" "main_vpc" {
  cidr_block           = var.vpc_cidr         // VPC의 CIDR 블록 (예: "10.0.0.0/16")
  enable_dns_support   = true                 // DNS 지원 활성화
  enable_dns_hostnames = true                 // DNS 호스트네임 활성화
  tags = {
    Name = "${var.project_name}-vpc"          // 태그에 프로젝트 이름 포함
  }
}

// ------------------------------------------------------------
// 퍼블릭 서브넷 생성
// 가용 영역 별로 여러 퍼블릭 서브넷을 생성합니다.
resource "aws_subnet" "public_subnet" {
  count                   = length(var.public_subnet_cidrs)  // 배열에 정의된 퍼블릭 서브넷 CIDR 수 만큼 생성
  vpc_id                  = aws_vpc.main_vpc.id              // 생성된 VPC에 연결
  cidr_block              = var.public_subnet_cidrs[count.index] // 각 서브넷에 대한 CIDR 블록 지정
  availability_zone       = element(var.availability_zones, count.index)  // 지정된 가용 영역 사용
  map_public_ip_on_launch = true                             // 인스턴스 생성 시 퍼블릭 IP 자동 할당
  tags = {
    Name = "${var.project_name}-public-subnet-${count.index + 1}"
  }
}

// ------------------------------------------------------------
// 인터넷 게이트웨이 생성
// VPC와 인터넷 간 연결을 위한 리소스 생성
resource "aws_internet_gateway" "igw" {
  vpc_id = aws_vpc.main_vpc.id
  tags = {
    Name = "${var.project_name}-igw"
  }
}

// ------------------------------------------------------------
// 퍼블릭 라우트 테이블 생성
// 퍼블릭 서브넷의 인터넷 트래픽을 라우팅할 라우트 테이블을 생성합니다.
resource "aws_route_table" "public_rt" {
  vpc_id = aws_vpc.main_vpc.id
  route {
    cidr_block = "0.0.0.0/0"                    // 모든 트래픽을 인터넷으로 라우팅
    gateway_id = aws_internet_gateway.igw.id      // 인터넷 게이트웨이로 연결
  }
  tags = {
    Name = "${var.project_name}-public-rt"
  }
}

// ------------------------------------------------------------
// 라우트 테이블과 서브넷 연결
// 각 퍼블릭 서브넷에 라우트 테이블을 연결하여 인터넷 접근을 가능하게 합니다.
resource "aws_route_table_association" "public_association" {
  count          = length(var.public_subnet_cidrs)
  subnet_id      = aws_subnet.public_subnet[count.index].id
  route_table_id = aws_route_table.public_rt.id
}

// ------------------------------------------------------------
// 보안 그룹 생성
// Go 백엔드 애플리케이션을 위한 보안 그룹을 생성합니다.
// 이 보안 그룹은 인바운드 및 아웃바운드 트래픽 규칙을 설정합니다.
resource "aws_security_group" "backend_sg" {
  name        = "${var.project_name}-backend-sg"
  description = "Security group for Go backend application"
  vpc_id      = aws_vpc.main_vpc.id

  // 인바운드 규칙: HTTP(80), HTTPS(443), SSH(22) 트래픽 허용
  ingress {
    description = "Allow HTTP traffic"
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = var.allowed_ingress_cidrs
  }
  ingress {
    description = "Allow HTTPS traffic"
    from_port   = 443
    to_port     = 443
    protocol    = "tcp"
    cidr_blocks = var.allowed_ingress_cidrs
  }
  ingress {
    description = "Allow SSH traffic for management"
    from_port   = 22
    to_port     = 22
    protocol    = "tcp"
    cidr_blocks = var.allowed_ingress_cidrs_ssh
  }

  // 아웃바운드 규칙: 모든 트래픽 허용
  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Name = "${var.project_name}-backend-sg"
  }
}

// ------------------------------------------------------------
// (선택 사항) EC2 인스턴스 생성
// Go 애플리케이션 배포를 위한 예시 인스턴스 생성. 실제 프로덕션에서는 Auto Scaling Group, EKS, ECS 등으로 관리할 수 있습니다.
resource "aws_instance" "backend_instance" {
  ami                    = var.instance_ami           // 사용할 AMI ID (variables.tf에서 정의)
  instance_type          = var.instance_type          // 인스턴스 유형 (예: t3.micro)
  subnet_id              = aws_subnet.public_subnet[0].id  // 첫 번째 퍼블릭 서브넷에 배포
  vpc_security_group_ids = [aws_security_group.backend_sg.id]
  key_name               = var.key_pair               // SSH 접근을 위한 키 페어

  tags = {
    Name = "${var.project_name}-backend-instance"
  }
}
