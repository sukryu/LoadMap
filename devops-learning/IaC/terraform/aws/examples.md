# AWS Terraform 인프라 코드 예제

> **목표:**  
> - 실무에서 자주 사용되는 AWS 인프라 구성 예제를 제공한다.
> - 각 예제의 목적과 동작 방식을 상세히 설명한다.
> - 실제 프로젝트에 적용할 수 있는 모범 사례를 소개한다.
> - 초보자도 이해하고 활용할 수 있는 기본 예제부터 시작한다.

---

## 1. 기본 VPC 네트워크 구성

### VPC와 서브넷 생성
기본적인 네트워크 인프라를 구성하는 예제입니다.

```hcl
# VPC 생성
resource "aws_vpc" "main" {
  cidr_block           = "10.0.0.0/16"
  enable_dns_hostnames = true
  enable_dns_support   = true

  tags = {
    Name = "main-vpc"
    Environment = "Production"
  }
}

# 퍼블릭 서브넷 생성
resource "aws_subnet" "public" {
  vpc_id                  = aws_vpc.main.id
  cidr_block              = "10.0.1.0/24"
  availability_zone       = "ap-northeast-2a"
  map_public_ip_on_launch = true

  tags = {
    Name = "public-subnet"
    Environment = "Production"
  }
}

# 프라이빗 서브넷 생성
resource "aws_subnet" "private" {
  vpc_id                  = aws_vpc.main.id
  cidr_block              = "10.0.2.0/24"
  availability_zone       = "ap-northeast-2b"

  tags = {
    Name = "private-subnet"
    Environment = "Production"
  }
}
```

### 인터넷 게이트웨이 및 라우팅 설정

```hcl
# 인터넷 게이트웨이 생성
resource "aws_internet_gateway" "main" {
  vpc_id = aws_vpc.main.id

  tags = {
    Name = "main-igw"
  }
}

# 퍼블릭 라우팅 테이블
resource "aws_route_table" "public" {
  vpc_id = aws_vpc.main.id

  route {
    cidr_block = "0.0.0.0/0"
    gateway_id = aws_internet_gateway.main.id
  }

  tags = {
    Name = "public-rt"
  }
}

# 퍼블릭 서브넷에 라우팅 테이블 연결
resource "aws_route_table_association" "public" {
  subnet_id      = aws_subnet.public.id
  route_table_id = aws_route_table.public.id
}
```

---

## 2. EC2 인스턴스 배포

### 기본 EC2 인스턴스 생성

```hcl
# 보안 그룹 생성
resource "aws_security_group" "web" {
  name        = "web-sg"
  description = "Security group for web servers"
  vpc_id      = aws_vpc.main.id

  ingress {
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  ingress {
    from_port   = 443
    to_port     = 443
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Name = "web-sg"
  }
}

# EC2 인스턴스 생성
resource "aws_instance" "web" {
  ami           = "ami-0c9c942bd7bf113a2"  # Amazon Linux 2 AMI ID
  instance_type = "t2.micro"
  subnet_id     = aws_subnet.public.id
  
  vpc_security_group_ids = [aws_security_group.web.id]
  
  user_data = <<-EOF
              #!/bin/bash
              yum update -y
              yum install -y httpd
              systemctl start httpd
              systemctl enable httpd
              echo "<h1>Hello from Terraform</h1>" > /var/www/html/index.html
              EOF

  tags = {
    Name = "web-server"
  }
}
```

---

## 3. RDS 데이터베이스 구성

### RDS 인스턴스 생성

```hcl
# RDS 보안 그룹
resource "aws_security_group" "db" {
  name        = "db-sg"
  description = "Security group for RDS"
  vpc_id      = aws_vpc.main.id

  ingress {
    from_port       = 3306
    to_port         = 3306
    protocol        = "tcp"
    security_groups = [aws_security_group.web.id]
  }

  tags = {
    Name = "db-sg"
  }
}

# RDS 서브넷 그룹
resource "aws_db_subnet_group" "default" {
  name       = "main"
  subnet_ids = [aws_subnet.private.id]

  tags = {
    Name = "DB subnet group"
  }
}

# RDS 인스턴스
resource "aws_db_instance" "default" {
  identifier           = "main-db"
  allocated_storage    = 20
  storage_type        = "gp2"
  engine              = "mysql"
  engine_version      = "8.0"
  instance_class      = "db.t3.micro"
  name                = "myappdb"
  username            = "admin"
  password            = "your_password_here"
  skip_final_snapshot = true

  vpc_security_group_ids = [aws_security_group.db.id]
  db_subnet_group_name   = aws_db_subnet_group.default.name

  tags = {
    Name = "main-db"
  }
}
```

---

## 4. S3 버킷 및 IAM 설정

### S3 버킷 생성 및 정책 설정

```hcl
# S3 버킷 생성
resource "aws_s3_bucket" "app_storage" {
  bucket = "my-app-storage-${random_string.suffix.result}"
}

resource "random_string" "suffix" {
  length  = 8
  special = false
  upper   = false
}

# 버킷 암호화 설정
resource "aws_s3_bucket_server_side_encryption_configuration" "app_storage" {
  bucket = aws_s3_bucket.app_storage.id

  rule {
    apply_server_side_encryption_by_default {
      sse_algorithm = "AES256"
    }
  }
}

# 버킷 정책
resource "aws_s3_bucket_policy" "app_storage" {
  bucket = aws_s3_bucket.app_storage.id

  policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Sid       = "PublicReadGetObject"
        Effect    = "Allow"
        Principal = "*"
        Action    = "s3:GetObject"
        Resource  = "${aws_s3_bucket.app_storage.arn}/*"
      },
    ]
  })
}
```

---

## 5. Auto Scaling 구성

### Auto Scaling 그룹 설정

```hcl
# 시작 템플릿 생성
resource "aws_launch_template" "web" {
  name_prefix   = "web-template"
  image_id      = "ami-0c9c942bd7bf113a2"
  instance_type = "t2.micro"

  network_interfaces {
    associate_public_ip_address = true
    security_groups            = [aws_security_group.web.id]
  }

  user_data = base64encode(<<-EOF
              #!/bin/bash
              yum update -y
              yum install -y httpd
              systemctl start httpd
              systemctl enable httpd
              EOF
  )

  tags = {
    Name = "web-template"
  }
}

# Auto Scaling 그룹 생성
resource "aws_autoscaling_group" "web" {
  desired_capacity    = 2
  max_size           = 4
  min_size           = 1
  target_group_arns  = [aws_lb_target_group.web.arn]
  vpc_zone_identifier = [aws_subnet.public.id]

  launch_template {
    id      = aws_launch_template.web.id
    version = "$Latest"
  }

  tag {
    key                 = "Name"
    value               = "web-asg"
    propagate_at_launch = true
  }
}
```

---

## 6. 응용 예제: 3-tier 아키텍처

### 전체 아키텍처 구성
3-tier 아키텍처(웹, 애플리케이션, 데이터베이스)를 구성하는 완성된 예제입니다.

```hcl
# VPC 및 서브넷 설정
# (앞서 작성한 VPC 코드 사용)

# 웹 티어
# (앞서 작성한 EC2 및 Auto Scaling 코드 사용)

# 애플리케이션 티어
resource "aws_instance" "app" {
  ami           = "ami-0c9c942bd7bf113a2"
  instance_type = "t2.small"
  subnet_id     = aws_subnet.private.id
  
  vpc_security_group_ids = [aws_security_group.app.id]

  tags = {
    Name = "app-server"
  }
}

# 데이터베이스 티어
# (앞서 작성한 RDS 코드 사용)
```

---

## 7. 모듈화 및 재사용

### 모듈 구조 예시

```
modules/
├── vpc/
│   ├── main.tf
│   ├── variables.tf
│   └── outputs.tf
├── ec2/
│   ├── main.tf
│   ├── variables.tf
│   └── outputs.tf
└── rds/
    ├── main.tf
    ├── variables.tf
    └── outputs.tf
```

### 모듈 사용 예시

```hcl
module "vpc" {
  source = "./modules/vpc"
  
  vpc_cidr     = "10.0.0.0/16"
  environment  = "production"
}

module "web_server" {
  source = "./modules/ec2"
  
  vpc_id     = module.vpc.vpc_id
  subnet_id  = module.vpc.public_subnet_id
  environment = "production"
}
```

---

## 참고 사항

1. 모든 예제는 실제 환경에 맞게 수정이 필요합니다.
2. 보안 그룹 규칙은 최소 권한 원칙에 따라 조정해야 합니다.
3. 비용이 발생할 수 있는 리소스는 사용 후 반드시 삭제해야 합니다.
4. 프로덕션 환경에서는 추가적인 보안 설정이 필요합니다.

---

## 마무리

이 문서에서 제공하는 예제들은 기본적인 AWS 인프라 구성을 위한 시작점입니다. 실제 프로젝트에서는 보안, 가용성, 확장성 등을 고려한 추가적인 설정이 필요할 수 있습니다. 각 예제를 기반으로 필요에 맞게 수정하고 확장하여 사용하시기 바랍니다.