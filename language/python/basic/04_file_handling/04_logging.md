# Python 로깅: 효과적인 애플리케이션 모니터링과 디버깅

## 로깅의 중요성

로깅은 애플리케이션의 실행 상태, 오류, 성능 지표를 기록하는 필수적인 기능입니다. 효과적인 로깅은 문제 해결, 성능 최적화, 보안 감사에 핵심적인 역할을 합니다. Python의 내장 logging 모듈은 유연하고 강력한 로깅 기능을 제공합니다.

## 로깅 기본 설정

```python
import logging
from datetime import datetime
import os

def setup_logger(log_directory='logs'):
    """기본 로거 설정"""
    
    # 로그 디렉토리 생성
    if not os.path.exists(log_directory):
        os.makedirs(log_directory)
    
    # 로그 파일명 설정 (날짜 포함)
    log_filename = f"{log_directory}/app_{datetime.now().strftime('%Y%m%d')}.log"
    
    # 로거 설정
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
        handlers=[
            logging.FileHandler(log_filename, encoding='utf-8'),
            logging.StreamHandler()  # 콘솔 출력을 위한 핸들러
        ]
    )
    
    return logging.getLogger(__name__)

# 로거 생성
logger = setup_logger()
```

## 로깅 레벨의 이해와 활용

Python의 로깅 시스템은 다섯 가지 주요 레벨을 제공합니다:

```python
def demonstrate_logging_levels():
    """로깅 레벨 데모"""
    logger.debug('디버그 정보: 상세한 디버깅 정보')
    logger.info('정보: 정상적인 프로그램 실행 정보')
    logger.warning('경고: 잠재적인 문제 상황')
    logger.error('오류: 프로그램 실행 중 발생한 오류')
    logger.critical('심각: 프로그램 실행이 불가능한 심각한 오류')
```

## 고급 로깅 설정

여러 컴포넌트를 가진 애플리케이션을 위한 고급 로깅 설정:

```python
import logging.handlers
import json

class ApplicationLogger:
    def __init__(self, app_name, log_directory='logs'):
        self.app_name = app_name
        self.log_directory = log_directory
        self.setup_logging()
    
    def setup_logging(self):
        """고급 로깅 설정"""
        
        # 로그 디렉토리 생성
        os.makedirs(self.log_directory, exist_ok=True)
        
        # 로거 생성
        logger = logging.getLogger(self.app_name)
        logger.setLevel(logging.DEBUG)
        
        # 파일 핸들러 설정 (일별 로테이션)
        file_handler = logging.handlers.TimedRotatingFileHandler(
            filename=f"{self.log_directory}/{self.app_name}.log",
            when='midnight',
            interval=1,
            backupCount=30,
            encoding='utf-8'
        )
        
        # JSON 형식의 로그 포매터
        class JsonFormatter(logging.Formatter):
            def format(self, record):
                log_entry = {
                    'timestamp': self.formatTime(record),
                    'level': record.levelname,
                    'message': record.getMessage(),
                    'module': record.module,
                    'function': record.funcName,
                    'line': record.lineno
                }
                if hasattr(record, 'extra_data'):
                    log_entry.update(record.extra_data)
                return json.dumps(log_entry, ensure_ascii=False)
        
        file_handler.setFormatter(JsonFormatter())
        logger.addHandler(file_handler)
        
        return logger
```

## 실전 로깅 활용: 웹 애플리케이션 예시

```python
class WebAppLogger:
    def __init__(self):
        self.logger = setup_logger('webapp_logs')
    
    def log_request(self, request_data):
        """웹 요청 로깅"""
        self.logger.info('웹 요청 수신', extra={
            'method': request_data.get('method'),
            'path': request_data.get('path'),
            'ip': request_data.get('ip'),
            'user_agent': request_data.get('user_agent')
        })
    
    def log_database_operation(self, operation_type, table, duration):
        """데이터베이스 작업 로깅"""
        self.logger.info('데이터베이스 작업', extra={
            'operation': operation_type,
            'table': table,
            'duration_ms': duration
        })
    
    def log_error(self, error, context=None):
        """오류 로깅"""
        error_data = {
            'error_type': type(error).__name__,
            'error_message': str(error)
        }
        if context:
            error_data['context'] = context
        
        self.logger.error('애플리케이션 오류', extra=error_data)
```

## 성능 모니터링을 위한 로깅

```python
import time
from functools import wraps

def log_performance(logger):
    """성능 측정을 위한 데코레이터"""
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            start_time = time.time()
            try:
                result = func(*args, **kwargs)
                duration = (time.time() - start_time) * 1000
                logger.info('함수 실행 완료', extra={
                    'function': func.__name__,
                    'duration_ms': round(duration, 2)
                })
                return result
            except Exception as e:
                duration = (time.time() - start_time) * 1000
                logger.error('함수 실행 오류', extra={
                    'function': func.__name__,
                    'duration_ms': round(duration, 2),
                    'error': str(e)
                })
                raise
        return wrapper
    return decorator
```

## 로그 분석과 모니터링

로그 분석을 위한 유틸리티 함수들:

```python
class LogAnalyzer:
    def __init__(self, log_file):
        self.log_file = log_file
    
    def analyze_errors(self):
        """오류 로그 분석"""
        error_counts = {}
        with open(self.log_file, 'r', encoding='utf-8') as f:
            for line in f:
                try:
                    log_entry = json.loads(line)
                    if log_entry['level'] in ['ERROR', 'CRITICAL']:
                        error_type = log_entry.get('error_type', 'Unknown')
                        error_counts[error_type] = error_counts.get(error_type, 0) + 1
                except json.JSONDecodeError:
                    continue
        
        return error_counts
    
    def analyze_performance(self):
        """성능 관련 로그 분석"""
        performance_data = []
        with open(self.log_file, 'r', encoding='utf-8') as f:
            for line in f:
                try:
                    log_entry = json.loads(line)
                    if 'duration_ms' in log_entry:
                        performance_data.append({
                            'timestamp': log_entry['timestamp'],
                            'function': log_entry.get('function', 'Unknown'),
                            'duration_ms': log_entry['duration_ms']
                        })
                except json.JSONDecodeError:
                    continue
        
        return performance_data
```

## 로깅 모범 사례

1. **구조화된 로깅**: JSON 형식을 사용하여 로그를 구조화하면 분석이 용이합니다.

2. **적절한 로그 레벨 사용**: 각 상황에 맞는 로그 레벨을 선택합니다.

3. **로그 로테이션**: 디스크 공간 관리를 위해 로그 파일 로테이션을 설정합니다.

4. **컨텍스트 정보 포함**: 문제 해결에 필요한 충분한 컨텍스트 정보를 포함합니다.

5. **민감 정보 제외**: 개인정보나 보안 관련 데이터는 로깅하지 않습니다.

## 보안과 규정 준수

```python
class SecureLogger:
    """보안을 고려한 로깅 클래스"""
    
    SENSITIVE_FIELDS = {'password', 'credit_card', 'ssn'}
    
    @staticmethod
    def mask_sensitive_data(data):
        """민감한 데이터 마스킹"""
        if isinstance(data, dict):
            return {
                k: '****' if k.lower() in SecureLogger.SENSITIVE_FIELDS 
                else SecureLogger.mask_sensitive_data(v)
                for k, v in data.items()
            }
        return data
    
    def log_security_event(self, event_type, data):
        """보안 이벤트 로깅"""
        safe_data = self.mask_sensitive_data(data)
        logger.info('보안 이벤트', extra={
            'event_type': event_type,
            'data': safe_data
        })
```