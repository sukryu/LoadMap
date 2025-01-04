# 내부 서비스 정의.

* 여기에서는 내부 모놀릭 서버에 들어갈 모듈들을 정의합니다.

## 1. 사용자 관리 서비스

### 1.1. 개요
* 사용자 관리 서비스는 사용자에 대한 전반적인 CRUD 기능을 담당합니다.
    - 예: 사용자 생성, 조회, 업데이트, 삭제 등.

* 테이블 구조 정의
    1. `users` 테이블
        - 해당 테이블은 인증 및 인가와 같은 매우 중요한 부분에서 주로 쓰이는 테이블이 됩니다.

        * 스키마 구조:
            - id: `UUID`
            - name: `VARCHAR(255)`
            - role: `number`(RoleID를 ManyToOne으로 참조)
            - status: `number`(StatusID를 OnyToOne으로 참조)
            - createdAt: `TIMESTAMP`
            - updatedAt: `TIMESTAMP`
            - deletedAt: `TIMESTAMP` | `NIL` (소프트 Delete를 위해서)

    2. `user_settings` 테이블
        - 해당 테이블은 사용자의 세팅에 대한 내용을 담습니다.
            - 예를 들어: EMAIL 또는 SMS 알림 활성화 여부, 정책 또는 감사 알림 활성화 여부
        * 스키마 구조:


    3. `user_infos` 테이블
        - 해당 테이블은 사용자의 결제 정보, 배송 정보 등의 내한 내용을 담습니다.
            - 예를 들어: 사용자의 신용카드 정보, 배송지 정보 등.

        * 스키마 구조: