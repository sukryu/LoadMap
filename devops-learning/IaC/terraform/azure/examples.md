# Azure Terraform 인프라 코드 예제

> **목표:**  
> - 실무에서 자주 사용되는 Azure 인프라 구성 예제를 제공한다.
> - 각 예제의 목적과 동작 방식을 상세히 설명한다.
> - 실제 프로젝트에 적용할 수 있는 모범 사례를 소개한다.
> - 초보자도 이해하고 활용할 수 있는 기본 예제부터 시작한다.

---

## 1. 기본 네트워크 인프라 구성

### 가상 네트워크 및 서브넷 생성
기업 환경에서 필요한 기본적인 네트워크 인프라를 구성하는 예제입니다.

```hcl
# 리소스 그룹 생성
resource "azurerm_resource_group" "main" {
  name     = "example-network-rg"
  location = "Korea Central"

  tags = {
    Environment = "Production"
    Department  = "Infrastructure"
  }
}

# 가상 네트워크 생성
resource "azurerm_virtual_network" "main" {
  name                = "main-network"
  resource_group_name = azurerm_resource_group.main.name
  location            = azurerm_resource_group.main.location
  address_space       = ["10.0.0.0/16"]

  tags = {
    Environment = "Production"
  }
}

# 서브넷 생성
resource "azurerm_subnet" "frontend" {
  name                 = "frontend-subnet"
  resource_group_name  = azurerm_resource_group.main.name
  virtual_network_name = azurerm_virtual_network.main.name
  address_prefixes     = ["10.0.1.0/24"]

  service_endpoints = ["Microsoft.Web"]
}

resource "azurerm_subnet" "backend" {
  name                 = "backend-subnet"
  resource_group_name  = azurerm_resource_group.main.name
  virtual_network_name = azurerm_virtual_network.main.name
  address_prefixes     = ["10.0.2.0/24"]

  service_endpoints = ["Microsoft.Sql"]
}

# 네트워크 보안 그룹 생성
resource "azurerm_network_security_group" "frontend" {
  name                = "frontend-nsg"
  location            = azurerm_resource_group.main.location
  resource_group_name = azurerm_resource_group.main.name

  security_rule {
    name                       = "allow-http"
    priority                   = 100
    direction                  = "Inbound"
    access                     = "Allow"
    protocol                   = "Tcp"
    source_port_range         = "*"
    destination_port_range    = "80"
    source_address_prefix     = "*"
    destination_address_prefix = "*"
  }
}
```

---

## 2. 가상 머신 배포

### Windows 서버 배포 예제
일반적인 Windows 서버 배포 구성입니다.

```hcl
# 공용 IP 주소 생성
resource "azurerm_public_ip" "example" {
  name                = "example-pip"
  resource_group_name = azurerm_resource_group.main.name
  location            = azurerm_resource_group.main.location
  allocation_method   = "Static"
}

# 네트워크 인터페이스 생성
resource "azurerm_network_interface" "example" {
  name                = "example-nic"
  location            = azurerm_resource_group.main.location
  resource_group_name = azurerm_resource_group.main.name

  ip_configuration {
    name                          = "internal"
    subnet_id                     = azurerm_subnet.frontend.id
    private_ip_address_allocation = "Dynamic"
    public_ip_address_id          = azurerm_public_ip.example.id
  }
}

# Windows 가상 머신 생성
resource "azurerm_windows_virtual_machine" "example" {
  name                = "example-vm"
  resource_group_name = azurerm_resource_group.main.name
  location            = azurerm_resource_group.main.location
  size                = "Standard_D2s_v3"
  admin_username      = "adminuser"
  admin_password      = "P@ssw0rd1234!"  # 실제 환경에서는 변수나 Key Vault 사용 권장

  network_interface_ids = [
    azurerm_network_interface.example.id,
  ]

  os_disk {
    caching              = "ReadWrite"
    storage_account_type = "Premium_LRS"
  }

  source_image_reference {
    publisher = "MicrosoftWindowsServer"
    offer     = "WindowsServer"
    sku       = "2019-Datacenter"
    version   = "latest"
  }
}
```

---

## 3. 데이터베이스 서비스 구성

### Azure SQL Database 설정
보안이 강화된 데이터베이스 환경 구성 예제입니다.

```hcl
# Azure SQL Server 생성
resource "azurerm_mssql_server" "example" {
  name                         = "example-sqlserver"
  resource_group_name          = azurerm_resource_group.main.name
  location                     = azurerm_resource_group.main.location
  version                      = "12.0"
  administrator_login          = "sqladmin"
  administrator_login_password = "P@ssw0rd1234!"  # 실제 환경에서는 변수나 Key Vault 사용 권장

  public_network_access_enabled = false

  azuread_administrator {
    login_username = "AzureAD Admin"
    object_id      = "00000000-0000-0000-0000-000000000000"  # Azure AD 관리자 Object ID
  }
}

# Azure SQL Database 생성
resource "azurerm_mssql_database" "example" {
  name           = "example-db"
  server_id      = azurerm_mssql_server.example.id
  collation      = "SQL_Latin1_General_CP1_CI_AS"
  license_type   = "LicenseIncluded"
  max_size_gb    = 2
  sku_name       = "Basic"
  zone_redundant = false

  tags = {
    Environment = "Production"
  }
}

# 프라이빗 엔드포인트 구성
resource "azurerm_private_endpoint" "example" {
  name                = "example-endpoint"
  location            = azurerm_resource_group.main.location
  resource_group_name = azurerm_resource_group.main.name
  subnet_id           = azurerm_subnet.backend.id

  private_service_connection {
    name                           = "example-privateserviceconnection"
    private_connection_resource_id = azurerm_mssql_server.example.id
    subresource_names             = ["sqlServer"]
    is_manual_connection          = false
  }
}
```

---

## 4. 웹 애플리케이션 배포

### App Service 환경 구성
웹 애플리케이션 호스팅을 위한 환경 설정입니다.

```hcl
# App Service Plan 생성
resource "azurerm_service_plan" "example" {
  name                = "example-asp"
  resource_group_name = azurerm_resource_group.main.name
  location            = azurerm_resource_group.main.location
  os_type             = "Windows"
  sku_name            = "P1v2"
}

# Web App 생성
resource "azurerm_windows_web_app" "example" {
  name                = "example-webapp"
  resource_group_name = azurerm_resource_group.main.name
  location            = azurerm_service_plan.example.location
  service_plan_id     = azurerm_service_plan.example.id

  site_config {
    application_stack {
      current_stack  = "dotnet"
      dotnet_version = "v6.0"
    }
    always_on = true
  }

  app_settings = {
    "WEBSITE_TIME_ZONE" = "Korea Standard Time"
  }

  identity {
    type = "SystemAssigned"
  }
}
```

---

## 5. 저장소 계정 설정

### Blob Storage 구성
안전한 데이터 저장소 구성 예제입니다.

```hcl
# Storage Account 생성
resource "azurerm_storage_account" "example" {
  name                     = "examplestorageacc"
  resource_group_name      = azurerm_resource_group.main.name
  location                 = azurerm_resource_group.main.location
  account_tier             = "Standard"
  account_replication_type = "GRS"

  enable_https_traffic_only = true
  min_tls_version           = "TLS1_2"

  network_rules {
    default_action             = "Deny"
    ip_rules                   = ["100.0.0.1"]
    virtual_network_subnet_ids = [azurerm_subnet.frontend.id]
  }

  tags = {
    environment = "Production"
  }
}

# Container 생성
resource "azurerm_storage_container" "example" {
  name                  = "content"
  storage_account_name  = azurerm_storage_account.example.name
  container_access_type = "private"
}
```

---

## 6. 보안 및 모니터링 설정

### Key Vault 및 모니터링 구성
보안 강화와 모니터링을 위한 설정입니다.

```hcl
# Key Vault 생성
resource "azurerm_key_vault" "example" {
  name                        = "example-kv"
  location                    = azurerm_resource_group.main.location
  resource_group_name         = azurerm_resource_group.main.name
  enabled_for_disk_encryption = true
  tenant_id                   = data.azurerm_client_config.current.tenant_id
  soft_delete_retention_days  = 7
  purge_protection_enabled    = false

  sku_name = "standard"

  access_policy {
    tenant_id = data.azurerm_client_config.current.tenant_id
    object_id = data.azurerm_client_config.current.object_id

    key_permissions = [
      "Get", "List", "Create", "Delete",
    ]

    secret_permissions = [
      "Get", "List", "Set", "Delete",
    ]
  }
}

# Application Insights 설정
resource "azurerm_application_insights" "example" {
  name                = "example-appinsights"
  location            = azurerm_resource_group.main.location
  resource_group_name = azurerm_resource_group.main.name
  application_type    = "web"
}
```

---

## 7. 완전한 3-Tier 아키텍처 예제

### 전체 인프라 구성
웹, 애플리케이션, 데이터베이스 계층을 포함한 완전한 아키텍처 예제입니다.

```hcl
# 이전에 정의된 네트워크 리소스들 사용

# Application Gateway 생성
resource "azurerm_application_gateway" "example" {
  name                = "example-appgateway"
  resource_group_name = azurerm_resource_group.main.name
  location            = azurerm_resource_group.main.location

  sku {
    name     = "Standard_v2"
    tier     = "Standard_v2"
    capacity = 2
  }

  gateway_ip_configuration {
    name      = "gateway-ip-config"
    subnet_id = azurerm_subnet.frontend.id
  }

  frontend_port {
    name = "http-port"
    port = 80
  }

  frontend_ip_configuration {
    name                 = "frontend-ip-config"
    public_ip_address_id = azurerm_public_ip.example.id
  }

  backend_address_pool {
    name = "backend-pool"
  }

  backend_http_settings {
    name                  = "http-setting"
    cookie_based_affinity = "Disabled"
    port                 = 80
    protocol             = "Http"
    request_timeout      = 60
  }

  http_listener {
    name                           = "http-listener"
    frontend_ip_configuration_name = "frontend-ip-config"
    frontend_port_name             = "http-port"
    protocol                       = "Http"
  }

  request_routing_rule {
    name                       = "routing-rule"
    rule_type                 = "Basic"
    http_listener_name        = "http-listener"
    backend_address_pool_name = "backend-pool"
    backend_http_settings_name = "http-setting"
    priority                  = 1
  }
}
```

---

## 참고 사항

1. 모든 예제는 실제 환경에 맞게 수정이 필요합니다.
2. 보안 관련 설정(비밀번호, 키 등)은 반드시 Key Vault나 환경 변수를 통해 관리해야 합니다.
3. 네트워크 보안 그룹 규칙은 최소 권한 원칙에 따라 구성해야 합니다.
4. 태그를 적절히 사용하여 리소스 관리와 비용 추적을 용이하게 해야 합니다.
5. 프로덕션 환경에서는 가용성과 재해 복구를 고려한 추가 설정이 필요합니다.

---

## 마무리

이 문서에서 제공하는 예제들은 Azure 인프라 구성을 위한 기본적인 템플릿입니다. 실제 프로젝트에서는 보안, 확장성, 가용성 등을 고려한 추가적인 설정이 필요할 수 있습니다. 각 예제를 기반으로 필요에 따라 수정해서 사용하시면 됩니다.