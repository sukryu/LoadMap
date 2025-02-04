# 📂 Ansible 학습 개요

> **목표:**  
> - **Ansible을 활용하여 인프라 및 애플리케이션을 자동화하는 방법을 학습**한다.  
> - **Infrastructure as Code(IaC) 개념을 익히고, Ansible을 사용하여 서버 및 클라우드 환경을 관리한다.**  
> - **기본 개념과 명령어를 학습한 후, 고급 기능 및 실무 활용 전략을 학습한다.**  
> - **이론 → 도구 실습 → 프로젝트 적용 → 최적화의 단계적 학습 방식**을 따른다.  

---

## 📂 **학습 디렉토리 구조**  
> **Ansible을 활용한 자동화 학습을 기초(Basic)와 고급(Advanced)으로 나누어 진행합니다.**  

```
ansible/
├── introduction.md  # Ansible 개요 및 기본 개념
├── setup.md         # Ansible 설치 및 환경 설정
├── playbooks.md     # Ansible Playbook 작성 및 실행
├── roles.md         # Ansible Roles 활용 및 모듈화
└── README.md
```

---

## 📖 **1. 기본 개념 개요**
> **Ansible은 에이전트리스(Agentless) 방식의 오픈소스 자동화 도구로, 서버 설정 및 애플리케이션 배포를 자동화할 수 있습니다.**

- ✅ **Playbook:** YAML 형식으로 작성된 자동화 스크립트  
- ✅ **Inventory:** 관리 대상 호스트 및 그룹 정의  
- ✅ **Modules:** 사전 정의된 작업 단위(패키지 설치, 서비스 관리 등)  
- ✅ **Roles:** 코드 재사용 및 모듈화를 위한 구조화된 디렉토리  
- ✅ **Idempotency:** 동일한 작업을 여러 번 실행해도 결과가 동일하도록 유지  

---

## 🏗 **2. 학습 내용**
### 📌 Ansible Setup (환경 설정)
- **Ansible 설치 및 기본 설정**
- **Inventory 파일 작성 및 관리 노드 정의**
- **SSH 키 기반의 원격 서버 접근 설정**

### 📌 Ansible Playbook 작성
- **YAML 기반 Playbook 문법 이해**
- **Tasks, Handlers, Variables 및 Templates 활용**
- **Multi-node 환경에서의 Ansible 실행**

### 📌 Ansible Roles 및 고급 기능
- **Roles을 활용한 코드 모듈화 및 재사용성 증가**
- **Ansible Vault를 활용한 보안 설정 관리**
- **Ansible Galaxy를 활용한 커뮤니티 Playbook 사용**

---

## 🚀 **3. 실전 예제**
> **Ansible을 활용하여 웹 서버(Nginx)를 배포하는 예제**

```yaml
- name: Install and configure Nginx
  hosts: web_servers
  become: yes
  tasks:
    - name: Install Nginx
      apt:
        name: nginx
        state: latest

    - name: Start and enable Nginx
      service:
        name: nginx
        state: started
        enabled: yes
```

```sh
# Ansible 실행 절차
ansible-playbook -i inventory.ini playbook.yml
```

---

## 🎯 **4. 학습 방법**
1. **이론 학습** → Ansible의 기본 개념과 원리 이해  
2. **도구 실습** → 기본 및 고급 Ansible Playbook 작성 및 실행  
3. **프로젝트 적용** → 실제 프로젝트에서 Ansible을 활용한 자동화 구성  
4. **최적화 연구** → 성능, 보안, 유지보수 최적화 전략 연구  

---

## 📚 **5. 추천 리소스**
- **Ansible 공식 문서:**  
  - [Ansible Docs](https://docs.ansible.com/)  
  - [Ansible Galaxy](https://galaxy.ansible.com/)  

- **Ansible 예제 및 템플릿:**  
  - [Awesome Ansible](https://github.com/ansible/awesome-ansible)  
  - [Ansible Examples](https://github.com/ansible/ansible-examples)  

---

## ✅ **마무리**
이 문서는 **Ansible의 기본 개념부터 실무 활용까지 학습하기 위한 로드맵**입니다.  
각 개념을 **이론 → 도구 실습 → 프로젝트 적용 → 최적화**의 단계로 학습하며, **실무에서 Ansible을 효과적으로 활용하는 방법**을 다룹니다. 🚀

