# Python JSON 처리: 기초부터 실전 활용까지

## JSON의 이해

JSON(JavaScript Object Notation)은 데이터 교환을 위한 경량의 텍스트 기반 형식입니다. Python에서는 `json` 모듈을 통해 JSON 데이터를 쉽게 처리할 수 있습니다. JSON은 웹 API와의 통신, 설정 파일 관리, 데이터 저장 등 다양한 상황에서 활용됩니다.

## 기본 JSON 처리

Python의 `json` 모듈은 JSON 데이터와 Python 객체 간의 변환을 지원합니다. 주요 메서드는 다음과 같습니다:

```python
import json

# Python 객체를 JSON 문자열로 변환 (직렬화)
python_dict = {
    "name": "김철수",
    "age": 30,
    "city": "서울",
    "active": True,
    "skills": ["Python", "SQL", "AWS"]
}

json_string = json.dumps(python_dict, ensure_ascii=False, indent=4)
print("JSON 문자열로 변환된 결과:")
print(json_string)

# JSON 문자열을 Python 객체로 변환 (역직렬화)
decoded_dict = json.loads(json_string)
print("\n다시 Python 객체로 변환된 결과:")
print(decoded_dict["name"])  # 출력: 김철수
```

## 파일 기반 JSON 처리

실무에서는 JSON 데이터를 파일로 저장하고 읽어오는 작업이 빈번합니다:

```python
# JSON 파일 쓰기
def save_config(config_data, filename):
    try:
        with open(filename, 'w', encoding='utf-8') as f:
            json.dump(config_data, f, ensure_ascii=False, indent=4)
        print(f"설정이 {filename}에 저장되었습니다.")
    except Exception as e:
        print(f"설정 저장 중 오류 발생: {str(e)}")

# JSON 파일 읽기
def load_config(filename):
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"설정 파일을 찾을 수 없습니다: {filename}")
        return {}
    except json.JSONDecodeError:
        print("잘못된 JSON 형식입니다.")
        return {}
    except Exception as e:
        print(f"설정 로드 중 오류 발생: {str(e)}")
        return {}
```

## 실전 활용 사례: 사용자 관리 시스템

다음은 JSON을 활용한 간단한 사용자 관리 시스템의 예시입니다:

```python
class UserManager:
    def __init__(self, filename='users.json'):
        self.filename = filename
        self.users = self._load_users()

    def _load_users(self):
        try:
            with open(self.filename, 'r', encoding='utf-8') as f:
                return json.load(f)
        except FileNotFoundError:
            return {}

    def _save_users(self):
        with open(self.filename, 'w', encoding='utf-8') as f:
            json.dump(self.users, f, ensure_ascii=False, indent=4)

    def add_user(self, user_id, user_data):
        if user_id in self.users:
            raise ValueError("이미 존재하는 사용자 ID입니다.")
        
        self.users[user_id] = {
            "created_at": datetime.now().isoformat(),
            **user_data
        }
        self._save_users()

    def get_user(self, user_id):
        return self.users.get(user_id)

    def update_user(self, user_id, user_data):
        if user_id not in self.users:
            raise ValueError("존재하지 않는 사용자 ID입니다.")
        
        self.users[user_id].update(user_data)
        self._save_users()

    def delete_user(self, user_id):
        if user_id not in self.users:
            raise ValueError("존재하지 않는 사용자 ID입니다.")
        
        del self.users[user_id]
        self._save_users()
```

## JSON 스키마 검증

실무에서는 JSON 데이터의 유효성 검증이 매우 중요합니다:

```python
def validate_user_data(data):
    required_fields = {'name', 'email', 'age'}
    
    # 필수 필드 확인
    if not all(field in data for field in required_fields):
        missing_fields = required_fields - set(data.keys())
        raise ValueError(f"필수 필드가 누락되었습니다: {missing_fields}")
    
    # 데이터 타입 검증
    if not isinstance(data['name'], str):
        raise TypeError("이름은 문자열이어야 합니다.")
    
    if not isinstance(data['age'], int):
        raise TypeError("나이는 정수여야 합니다.")
    
    # 이메일 형식 검증
    import re
    email_pattern = re.compile(r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$')
    if not email_pattern.match(data['email']):
        raise ValueError("올바르지 않은 이메일 형식입니다.")
    
    return True
```

## 고급 JSON 처리 기법

### 1. 사용자 정의 객체의 JSON 직렬화

```python
from datetime import datetime

class DateTimeEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, datetime):
            return obj.isoformat()
        return super().default(obj)

# 사용 예시
data = {
    "name": "프로젝트 A",
    "created_at": datetime.now()
}

json_string = json.dumps(data, cls=DateTimeEncoder, ensure_ascii=False)
```

### 2. JSON 데이터 병합

```python
def merge_json_data(original, update):
    """두 JSON 객체를 재귀적으로 병합합니다."""
    for key, value in update.items():
        if key in original and isinstance(original[key], dict) and isinstance(value, dict):
            merge_json_data(original[key], value)
        else:
            original[key] = value
    return original
```

## JSON 처리 시 주의사항

1. 문자 인코딩 관리: 한글 등 유니코드 문자를 처리할 때는 `ensure_ascii=False`를 사용하여 가독성을 유지합니다.

2. 예외 처리: JSON 파싱 오류에 대한 적절한 예외 처리가 필요합니다.

3. 데이터 검증: 외부에서 받은 JSON 데이터는 반드시 검증 후 사용합니다.

4. 성능 고려: 대용량 JSON 처리 시 메모리 사용량에 주의합니다.

## 연습 과제

다음 요구사항을 만족하는 설정 관리 시스템을 구현해보세요:

1. 애플리케이션 설정을 JSON 파일로 저장하고 로드할 수 있어야 합니다.
2. 설정 변경 시 자동으로 파일에 저장되어야 합니다.
3. 잘못된 설정 값에 대한 유효성 검사가 이루어져야 합니다.
4. 설정 변경 이력을 관리할 수 있어야 합니다.