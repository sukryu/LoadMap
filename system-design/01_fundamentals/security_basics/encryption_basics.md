# 암호화 기초 (Encryption Basics)

---

## 1. 개념 개요

암호화는 데이터를 보호하기 위해 원본 데이터를 읽을 수 없는 형태로 변환하는 기술입니다. 암호화 기법은 크게 **대칭키 암호화**, **비대칭키 암호화**, 그리고 **해싱** 세 가지로 분류됩니다.

### 1.1. 대칭키 암호화

- **정의:**  
  - 암호화와 복호화에 동일한 키를 사용하는 암호화 방식입니다.
  
- **특징:**  
  - **빠른 성능:** 대칭키 알고리즘(예: AES, DES)은 상대적으로 연산 속도가 빠르며 대량의 데이터를 암호화하는 데 효율적입니다.
  - **키 관리:** 동일한 키를 사용하는 관계로, 키가 유출되면 암호화된 모든 데이터가 위험에 노출됩니다.
  
- **예시:**  
  - AES (Advanced Encryption Standard)는 현재 가장 널리 사용되는 대칭키 암호화 알고리즘입니다.

### 1.2. 비대칭키 암호화

- **정의:**  
  - 암호화와 복호화에 서로 다른 키를 사용하는 암호화 방식입니다. 일반적으로 공개키(Public Key)와 개인키(Private Key) 한 쌍으로 구성됩니다.
  
- **특징:**  
  - **보안성:** 공개키와 개인키가 서로 다르므로, 공개키는 자유롭게 배포하고 개인키만 안전하게 보관하면 됩니다.
  - **연산 비용:** 대칭키에 비해 연산 비용이 크며, 대량의 데이터 암호화에는 적합하지 않습니다.
  
- **예시:**  
  - RSA, ECC (Elliptic Curve Cryptography) 등이 대표적인 비대칭키 암호화 알고리즘입니다.

### 1.3. 해싱 (Hashing)

- **정의:**  
  - 임의의 길이를 가진 데이터를 고정된 길이의 해시 값으로 변환하는 단방향 함수입니다.
  
- **특징:**  
  - **단방향성:** 해시 함수는 원본 데이터를 복원할 수 없으므로, 비밀번호 저장 및 데이터 무결성 검증에 적합합니다.
  - **충돌 가능성:** 서로 다른 입력 값이 동일한 해시 값을 가질 수 있는 충돌 가능성이 존재하며, 이를 최소화하기 위해 강력한 해시 알고리즘이 필요합니다.
  
- **예시:**  
  - SHA-256, bcrypt, Argon2 등은 해싱 알고리즘의 대표적인 예입니다.

---

## 2. 문제 상황 및 해결 방안

### 2.1. 문제 상황

- **대칭키 암호화:**  
  - 키 분배 문제: 암호화와 복호화에 동일한 키를 사용하므로, 안전하게 키를 공유하고 관리하는 것이 어려울 수 있습니다.
  
- **비대칭키 암호화:**  
  - 연산 부하: 대칭키에 비해 연산이 복잡하고 느리기 때문에, 대량의 데이터 암호화에는 부적합할 수 있습니다.
  
- **해싱:**  
  - 충돌 위험: 입력 데이터가 다르더라도 동일한 해시 값이 발생할 수 있는 가능성이 있으며, 이를 방지하기 위해 강력한 해시 알고리즘 선택이 필요합니다.

### 2.2. 해결 방안

- **대칭키 암호화:**  
  - 안전한 키 관리 시스템(KMS)을 도입하여, 키를 중앙 집중식으로 관리하고, 키 교환 프로토콜(예: Diffie-Hellman)을 통해 안전하게 분배합니다.
  
- **비대칭키 암호화:**  
  - 대칭키 암호화와 결합한 하이브리드 암호화 방식을 사용하여, 초기 키 교환은 비대칭키로 처리하고, 이후 데이터 암호화는 대칭키 알고리즘으로 수행합니다.
  
- **해싱:**  
  - 강력한 해시 함수(예: SHA-256, bcrypt, Argon2 등)를 선택하고, 필요에 따라 솔트(Salt)를 추가하여 충돌 및 사전 공격을 방지합니다.

---

## 3. 구체적 구현 방법 및 베스트 프랙티스

### 3.1. 대칭키 암호화 예시 (Node.js, AES)

```javascript
const crypto = require('crypto');

const algorithm = 'aes-256-cbc';
const key = crypto.randomBytes(32);  // 256비트 키 생성
const iv = crypto.randomBytes(16);   // 초기화 벡터 생성

/**
 * 데이터를 암호화하는 함수
 * @param {string} text - 평문 데이터
 * @returns {string} 암호문
 */
function encrypt(text) {
  const cipher = crypto.createCipheriv(algorithm, key, iv);
  let encrypted = cipher.update(text, 'utf8', 'hex');
  encrypted += cipher.final('hex');
  return encrypted;
}

/**
 * 암호문을 복호화하는 함수
 * @param {string} encryptedText - 암호문
 * @returns {string} 복호화된 평문
 */
function decrypt(encryptedText) {
  const decipher = crypto.createDecipheriv(algorithm, key, iv);
  let decrypted = decipher.update(encryptedText, 'hex', 'utf8');
  decrypted += decipher.final('utf8');
  return decrypted;
}

// 사용 예시
const message = "Hello, Encryption!";
const encryptedMessage = encrypt(message);
const decryptedMessage = decrypt(encryptedMessage);

console.log("암호문:", encryptedMessage);
console.log("복호문:", decryptedMessage);
```

### 3.2. 비대칭키 암호화 예시 (Node.js, RSA)

```javascript
const { generateKeyPairSync, publicEncrypt, privateDecrypt } = require('crypto');

// RSA 키 쌍 생성
const { publicKey, privateKey } = generateKeyPairSync('rsa', {
  modulusLength: 2048,
});

// 공개키로 암호화
function encryptWithPublicKey(data) {
  return publicEncrypt(publicKey, Buffer.from(data)).toString('base64');
}

// 개인키로 복호화
function decryptWithPrivateKey(encryptedData) {
  return privateDecrypt(privateKey, Buffer.from(encryptedData, 'base64')).toString('utf8');
}

// 사용 예시
const secretMessage = "Hello, RSA Encryption!";
const encryptedData = encryptWithPublicKey(secretMessage);
const decryptedData = decryptWithPrivateKey(encryptedData);

console.log("암호문:", encryptedData);
console.log("복호문:", decryptedData);
```

### 3.3. 해싱 예시 (Node.js, SHA-256 & bcrypt)

```javascript
const crypto = require('crypto');
const bcrypt = require('bcrypt');

// SHA-256 해시 함수 사용 예시
function sha256Hash(data) {
  return crypto.createHash('sha256').update(data).digest('hex');
}

const dataToHash = "Hello, Hashing!";
const hashValue = sha256Hash(dataToHash);
console.log("SHA-256 해시:", hashValue);

// bcrypt를 사용한 비밀번호 해싱 예시
async function hashPassword(password) {
  const saltRounds = 10;
  return await bcrypt.hash(password, saltRounds);
}

async function verifyPassword(password, hash) {
  return await bcrypt.compare(password, hash);
}

// 사용 예시
(async () => {
  const password = "securePassword123";
  const hashedPassword = await hashPassword(password);
  console.log("bcrypt 해시:", hashedPassword);
  
  const isMatch = await verifyPassword(password, hashedPassword);
  console.log("비밀번호 일치 여부:", isMatch);
})();
```

### 3.4. 베스트 프랙티스

- **대칭키 암호화:**  
  - 키 관리 시스템(KMS)을 도입하여, 키의 생성, 저장, 교환 및 폐기를 안전하게 처리합니다.
  - 초기화 벡터(IV)는 매 암호화마다 새로 생성하여, 동일한 평문이 동일한 암호문으로 변환되지 않도록 합니다.
  
- **비대칭키 암호화:**  
  - 하이브리드 암호화 방식을 활용하여, 대칭키 암호화의 성능과 비대칭키 암호화의 보안성을 결합합니다.
  - 공개키와 개인키를 안전하게 관리하고, 공개키 인프라(PKI)를 활용하여 인증서를 관리합니다.
  
- **해싱:**  
  - 민감 정보(예: 비밀번호)는 반드시 솔트(salt)를 추가하여 해싱하고, 필요 시 bcrypt, Argon2와 같은 느린 해시 함수를 사용합니다.
  - 데이터 무결성 검증에는 빠른 해시 함수(SHA-256 등)를 사용하되, 보안 요구 사항에 따라 적절한 알고리즘을 선택합니다.

---

## 4. 추가 고려 사항

- **성능 vs. 보안:**  
  - 암호화 및 해싱 연산은 시스템 성능에 영향을 줄 수 있으므로, 성능과 보안의 균형을 맞추는 것이 중요합니다.
  
- **키 관리:**  
  - 암호화 시스템의 보안은 키 관리에 크게 의존하므로, 키 분배, 저장, 폐기를 위한 강력한 정책과 도구를 도입해야 합니다.
  
- **규정 준수:**  
  - 산업별 보안 규정과 법적 요구 사항(GDPR, HIPAA 등)을 준수하는 암호화 기법과 정책을 수립합니다.
  
- **정기적인 감사:**  
  - 암호화 알고리즘과 키 관리 시스템에 대해 정기적인 보안 감사를 실시하여, 최신 보안 위협에 대응할 수 있도록 합니다.

---

## 5. 결론

**암호화 기초**는 대칭키, 비대칭키, 해싱과 같은 다양한 암호화 기술을 통해 데이터의 기밀성, 무결성 및 보안을 보장하는 핵심적인 기술입니다.

- **대칭키 암호화:**  
  - 빠른 성능과 대량 데이터 암호화에 유리하지만, 키 관리가 핵심 과제로 작용합니다.
  
- **비대칭키 암호화:**  
  - 공개키와 개인키의 분리로 보안성이 뛰어나며, 주로 키 교환 및 디지털 서명에 사용됩니다.
  
- **해싱:**  
  - 단방향 특성을 활용하여 데이터 무결성 검증 및 비밀번호 저장 등에 사용되며, 솔트와 함께 적용하여 보안을 강화합니다.

이러한 암호화 기법들을 적절히 활용하고, 강력한 키 관리와 보안 정책을 도입함으로써, 안전한 데이터 보호 및 통신 환경을 구축할 수 있습니다.