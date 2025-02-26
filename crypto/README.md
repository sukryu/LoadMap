# 암호화(Cryptography) 디렉토리

이 디렉토리는 **백엔드**, **클라우드**, **실시간 시스템 엔지니어**가 반드시 숙지해야 할 **암호화 기법 및 보안** 주제들을 체계적으로 정리한 자료입니다.  
암호화는 데이터 보호, 인증, 무결성 검증 및 기밀성 보장을 위한 핵심 기술로, 현대 애플리케이션과 인프라의 보안을 강화하는 데 필수적인 요소입니다.

---

## 디렉토리 구성 (Files & Folders)

```plaintext
crypto/
├── README.md                       # 암호화 디렉토리 개요 및 학습 가이드
├── symmetric_encryption.md         # 대칭 암호화 알고리즘 (AES, DES, 3DES 등) 및 적용 사례
├── asymmetric_encryption.md        # 비대칭 암호화 (RSA, ECC 등)와 디지털 서명, 키 교환
├── hashing_and_mac.md              # 해시 함수, 메시지 인증 코드(MAC), HMAC 등의 기초 및 응용
├── tls_ssl.md                      # TLS/SSL 프로토콜, 인증서 관리 및 전송 중 암호화
├── key_management.md               # 키 생성, 저장, 순환 및 HSM/KMS 활용 방안
├── crypto_best_practices.md        # 암호화 모범 사례 및 보안 정책 가이드
└── examples/                       # 코드 예제, 실습 스크립트 및 데모 애플리케이션
    ├── aes_example.go                      # AES 암호화/복호화, 패딩 및 GCM 모드 사용 예제
    ├── des_3des_example.go                 # DES 및 3DES 알고리즘의 기본 동작, 단점 및 사용 사례 비교 예제
    ├── stream_cipher_example.go            # ChaCha20 등 스트림 암호화 알고리즘 예제
    ├── rsa_example.go                      # RSA 키 쌍 생성, 암호화/복호화, 디지털 서명 및 검증 예제
    ├── ecc_example.go                      # ECC (타원곡선 암호) 기반 키 생성 및 ECDSA 서명/검증 예제
    ├── hybrid_encryption.go                # 대칭키와 비대칭키를 혼합한 하이브리드 암호화 예제
    ├── sha256_example.go                   # SHA-256 해시 함수 적용 및 해시값 검증 예제
    ├── hmac_example.go                     # HMAC 생성, 검증 및 상수 시간 비교 예제
    ├── cmac_example.go                     # CMAC 구현 및 사용 사례 예제 (외부 라이브러리 활용)
    ├── tls_server_client.go                # TLS/SSL 서버와 클라이언트 구현 예제 (HTTPS 서버/클라이언트 코드)
    ├── certificate_management.go          # X.509 인증서 생성, 자체 서명 인증서 발급 및 저장 예제
    ├── tls_handshake_simulation.go         # TLS 핸드셰이크 과정의 단계별 시뮬레이션 예제
    ├── key_generation.go                   # 안전한 키 생성 (대칭, 비대칭) 예제
    ├── key_storage.go                      # 생성된 키를 암호화하여 안전하게 파일이나 KMS에 저장하는 예제
    ├── key_rotation.go                     # 키 순환 및 수명주기 관리 시뮬레이션 예제
    ├── key_revocation.go                   # 키 폐기 절차 및 폐기 로그 기록 예제
    ├── crypto_best_practices_example.go    # 안전한 암호화 구현, 접근 제어, 감사 로그 기록 등 모범 사례 예제
    ├── security_policy_template.md         # 보안 정책 문서 템플릿 및 체크리스트 샘플
    ├── hsm_kms_integration.go              # HSM 또는 클라우드 기반 KMS와 연동하여 키 관리 작업을 자동화하는 개념 증명 코드
    └── hybrid_encryption_pqc.go            # 기존 암호화 기법과 포스트 양자 암호화를 혼합한 하이브리드 암호화 예제 (개념적 스텁 코드)
```

---

## 학습 및 활용 팁

1. **기초부터 심화까지**  
   - **기초 개념**: 대칭/비대칭 암호화, 해시 함수, MAC 등 암호화의 기본 원리를 학습합니다.  
   - **전문 도구**: TLS/SSL 설정, 키 관리, HSM/KMS 활용 사례를 통해 실제 환경에 적용할 수 있는 기술을 익힙니다.  
   - **모범 사례**: 암호화 모범 사례 및 보안 정책을 참고하여, 코드와 인프라에 안전한 암호화 기술을 도입합니다.

2. **실습 및 데모**  
   - examples/ 디렉토리 내의 다양한 예제 파일들을 통해, 암호화 기술을 실제로 구현하고 테스트해 보세요.  
   - CI/CD 파이프라인에 암호화 검증 도구를 연계하여, 변경 사항에 따른 보안 검증 프로세스를 자동화할 수 있습니다.

3. **최신 동향 및 업데이트**  
   - 암호화 기술은 지속적으로 발전하고 있으므로, 최신 연구 결과와 표준 문서를 주기적으로 참고합니다.  
   - 커뮤니티 및 오픈소스 프로젝트를 통해 실시간 암호화 동향을 학습하고, 관련 도구를 테스트해 보세요.

---

## 대상 독자

- **백엔드 개발자**:  
  애플리케이션 내 민감 데이터 암호화, 사용자 인증 및 데이터 무결성 보장을 위해 필요한 암호화 기술을 이해합니다.
  
- **클라우드 엔지니어/DevOps**:  
  클라우드 인프라의 전송 및 저장 데이터 암호화, TLS 설정, 그리고 안전한 키 관리에 대해 심도 있게 학습합니다.
  
- **실시간 시스템 엔지니어**:  
  낮은 지연 시간과 높은 성능을 유지하면서, 안전하게 데이터를 암호화하고 보호하는 방법을 익힙니다.

---

## 학습 순서

1. **대칭 암호화 및 해시 함수**:  
   - `symmetric_encryption.md`와 `hashing_and_mac.md`를 통해 기본 암호화 기법과 해시 알고리즘의 원리를 학습합니다.
   
2. **비대칭 암호화 및 디지털 서명**:  
   - `asymmetric_encryption.md`에서 RSA, ECC 등 비대칭 암호화 기법과 디지털 서명의 개념, 키 교환 방식을 익힙니다.
   
3. **전송 중 암호화 및 인증서 관리**:  
   - `tls_ssl.md`를 통해 TLS/SSL 프로토콜의 동작 원리와 인증서 관리, 클라이언트/서버 상호 인증 방법을 다룹니다.
   
4. **키 관리 전략**:  
   - `key_management.md`에서 안전한 키 생성, 저장, 순환 및 HSM/KMS 활용 방안을 학습하여, 장기적인 암호화 보안을 강화합니다.
   
5. **모범 사례 및 실제 적용 사례**:  
   - `crypto_best_practices.md`에서 업계 모범 사례와 실제 적용 사례를 참고하여, 암호화 정책 및 보안 전략을 최적화합니다.

---

## 향후 발전 방향

- **암호화 기술 최신 동향**:  
  최신 암호화 알고리즘, 포스트-양자 암호화, 동적 키 관리 등 미래 기술 동향을 지속적으로 학습합니다.
- **자동화 및 DevSecOps**:  
  암호화 검증과 키 관리 자동화를 CI/CD 파이프라인에 통합하여, 지속적인 보안 개선과 정책 준수를 보장합니다.
- **통합 보안 아키텍처**:  
  암호화 기술을 애플리케이션, 인프라, 네트워크 보안과 통합하여, 전방위적인 보안 체계를 구축합니다.

---

이 디렉토리는 암호화 기술 전반에 대한 체계적인 이해와 실무 적용을 목표로 하며, 백엔드, 클라우드, 실시간 시스템 엔지니어들이 암호화 관련 기술을 효과적으로 도입할 수 있도록 돕습니다.

좋은 학습 되세요! 😊🔒🚀