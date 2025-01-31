# Python 파일 처리의 기초 📁

## 파일 처리 개요

파일 처리는 프로그램에서 데이터를 영구적으로 저장하고 불러오는 핵심적인 기능입니다. Python에서는 다양한 형식의 파일을 쉽고 효율적으로 다룰 수 있는 도구들을 제공합니다.

## 기본 파일 작업 💻

### 파일 열기와 닫기

Python에서는 `open()` 함수를 사용하여 파일을 열 수 있습니다. 파일을 열 때는 다음과 같은 모드를 지정할 수 있습니다:

```python
# 파일 열기 모드
# 'r': 읽기 모드 (기본값)
# 'w': 쓰기 모드 (파일이 존재하면 내용을 지움)
# 'a': 추가 모드 (파일 끝에 내용을 추가)
# 'x': 배타적 생성 (파일이 존재하면 실패)
# 'b': 이진 모드
# 't': 텍스트 모드 (기본값)

# 파일 열기 예시
file = open('example.txt', 'r', encoding='utf-8')
content = file.read()
file.close()
```

### with 문을 사용한 안전한 파일 처리

`with` 문을 사용하면 파일을 자동으로 닫을 수 있어 더 안전합니다:

```python
with open('example.txt', 'r', encoding='utf-8') as file:
    content = file.read()
    # 파일 작업 수행
# 파일이 자동으로 닫힘
```

### 파일 읽기 방법

```python
# 전체 내용 읽기
with open('example.txt', 'r', encoding='utf-8') as file:
    content = file.read()

# 한 줄씩 읽기
with open('example.txt', 'r', encoding='utf-8') as file:
    line = file.readline()

# 모든 줄을 리스트로 읽기
with open('example.txt', 'r', encoding='utf-8') as file:
    lines = file.readlines()

# for 문으로 효율적으로 읽기
with open('example.txt', 'r', encoding='utf-8') as file:
    for line in file:
        print(line.strip())
```

### 파일 쓰기 작업

```python
# 새로운 내용 쓰기
with open('output.txt', 'w', encoding='utf-8') as file:
    file.write('안녕하세요!\n')
    file.write('파일 쓰기 예제입니다.')

# 리스트의 내용을 파일에 쓰기
lines = ['첫 번째 줄', '두 번째 줄', '세 번째 줄']
with open('output.txt', 'w', encoding='utf-8') as file:
    file.writelines(f'{line}\n' for line in lines)
```

## 실용적인 파일 처리 예제 🔍

### 1. 로그 파일 분석기

```python
def analyze_log_file(filename):
    error_count = 0
    warning_count = 0
    
    with open(filename, 'r', encoding='utf-8') as file:
        for line in file:
            if 'ERROR' in line:
                error_count += 1
            elif 'WARNING' in line:
                warning_count += 1
    
    return {
        'errors': error_count,
        'warnings': warning_count,
        'total_issues': error_count + warning_count
    }

# 사용 예시
log_stats = analyze_log_file('application.log')
print(f"발견된 오류: {log_stats['errors']}")
print(f"발견된 경고: {log_stats['warnings']}")
```

### 2. 데이터 백업 시스템

```python
import shutil
from datetime import datetime

def backup_file(filename):
    # 백업 파일 이름 생성 (원본이름_날짜.확장자)
    timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
    backup_name = f"{filename}_{timestamp}"
    
    try:
        shutil.copy2(filename, backup_name)
        print(f"백업 완료: {backup_name}")
        return True
    except Exception as e:
        print(f"백업 실패: {str(e)}")
        return False
```

## 파일 처리 시 주의사항 ⚠️

1. **인코딩 처리**
   - 텍스트 파일을 다룰 때는 항상 적절한 인코딩을 지정하세요.
   - 한글을 다룰 때는 'utf-8' 사용을 권장합니다.

2. **예외 처리**
   ```python
   try:
       with open('file.txt', 'r', encoding='utf-8') as file:
           content = file.read()
   except FileNotFoundError:
       print("파일을 찾을 수 없습니다.")
   except PermissionError:
       print("파일에 접근할 권한이 없습니다.")
   except Exception as e:
       print(f"예상치 못한 오류 발생: {str(e)}")
   ```

3. **리소스 관리**
   - 가능한 한 `with` 문을 사용하여 파일을 자동으로 닫히도록 합니다.
   - 대용량 파일을 다룰 때는 메모리 사용량에 주의하세요.

## 파일 시스템 작업 🗂️

Python의 `os` 모듈을 사용한 파일 시스템 작업:

```python
import os

# 현재 작업 디렉토리 확인
current_dir = os.getcwd()

# 디렉토리 생성
os.makedirs('new_folder', exist_ok=True)

# 파일 존재 여부 확인
if os.path.exists('file.txt'):
    print("파일이 존재합니다.")

# 파일 삭제
if os.path.exists('old_file.txt'):
    os.remove('old_file.txt')

# 디렉토리 내용 나열
files = os.listdir('.')
```

## 실습 과제 📝

아래 요구사항을 만족하는 간단한 메모장 프로그램을 작성해보세요:

1. 새로운 메모를 작성하고 파일로 저장할 수 있어야 합니다.
2. 기존 메모를 불러와서 읽을 수 있어야 합니다.
3. 메모에 날짜와 시간이 자동으로 기록되어야 합니다.
4. 여러 메모를 한 번에 관리할 수 있어야 합니다.

```python
import os
from datetime import datetime

class NotePad:
    def __init__(self):
        self.notes_dir = 'notes'
        os.makedirs(self.notes_dir, exist_ok=True)
    
    def create_note(self, title, content):
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        filename = f"{self.notes_dir}/{title}.txt"
        
        with open(filename, 'w', encoding='utf-8') as file:
            file.write(f"작성일시: {timestamp}\n")
            file.write("-" * 50 + "\n")
            file.write(content)
        
        return filename
    
    def read_note(self, title):
        filename = f"{self.notes_dir}/{title}.txt"
        try:
            with open(filename, 'r', encoding='utf-8') as file:
                return file.read()
        except FileNotFoundError:
            return "메모를 찾을 수 없습니다."
    
    def list_notes(self):
        return [f.replace('.txt', '') for f in os.listdir(self.notes_dir)
                if f.endswith('.txt')]
```