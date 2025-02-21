output "vpc_id" {
  description = "생성된 VPC의 ID"
  value       = aws_vpc.main_vpc.id
}

output "public_subnet_ids" {
  description = "생성된 퍼블릭 서브넷의 ID 목록"
  value       = aws_subnet.public_subnet[*].id
}

output "instance_public_ip" {
  description = "생성된 EC2 인스턴스의 퍼블릭 IP (존재하는 경우)"
  value       = aws_instance.backend_instance.public_ip
}
