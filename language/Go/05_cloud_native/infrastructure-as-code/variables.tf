variable "aws_region" {
  description = "AWS 리전을 지정합니다."
  type        = string
  default     = "us-west-2"
}

variable "vpc_cidr" {
  description = "VPC의 CIDR 블록입니다."
  type        = string
  default     = "10.0.0.0/16"
}

variable "project_name" {
  description = "프로젝트 이름, 리소스 태그 및 이름 생성에 사용됩니다."
  type        = string
  default     = "go-backend"
}

variable "public_subnet_cidrs" {
  description = "퍼블릭 서브넷의 CIDR 블록 목록입니다."
  type        = list(string)
  default     = ["10.0.1.0/24", "10.0.2.0/24"]
}

variable "availability_zones" {
  description = "AWS 가용 영역 목록입니다."
  type        = list(string)
  default     = ["us-west-2a", "us-west-2b"]
}

variable "allowed_ingress_cidrs" {
  description = "애플리케이션 접근을 허용할 CIDR 블록 목록입니다."
  type        = list(string)
  default     = ["0.0.0.0/0"]
}

variable "allowed_ingress_cidrs_ssh" {
  description = "SSH 접근을 허용할 CIDR 블록 목록입니다."
  type        = list(string)
  default     = ["0.0.0.0/0"]
}

variable "instance_ami" {
  description = "EC2 인스턴스에 사용할 AMI ID입니다."
  type        = string
  default     = "ami-0c55b159cbfafe1f0"  // 예시 AMI, 실제 값으로 교체 필요
}

variable "instance_type" {
  description = "EC2 인스턴스 유형입니다."
  type        = string
  default     = "t3.micro"
}

variable "key_pair" {
  description = "EC2 인스턴스에 접근하기 위한 키 페어 이름입니다."
  type        = string
  default     = "my-key-pair"
}
