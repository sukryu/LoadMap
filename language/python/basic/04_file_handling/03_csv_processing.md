# Python CSV 처리: 데이터 분석과 처리

## CSV 파일의 이해

CSV(Comma-Separated Values) 파일은 비즈니스 환경에서 가장 널리 사용되는 데이터 교환 형식 중 하나입니다. 스프레드시트 데이터를 저장하고 교환하는 데 적합하며, Python에서는 `csv` 모듈과 `pandas` 라이브러리를 통해 효과적으로 처리할 수 있습니다.

## 기본 CSV 처리

Python의 내장 `csv` 모듈을 사용한 기본적인 CSV 파일 처리 방법을 살펴보겠습니다.

```python
import csv
from datetime import datetime

# CSV 파일 읽기
def read_csv_file(filename):
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            reader = csv.DictReader(file)
            return list(reader)
    except FileNotFoundError:
        print(f"파일을 찾을 수 없습니다: {filename}")
        return []
    except Exception as e:
        print(f"CSV 읽기 중 오류 발생: {str(e)}")
        return []

# CSV 파일 쓰기
def write_csv_file(filename, data, fieldnames):
    try:
        with open(filename, 'w', encoding='utf-8', newline='') as file:
            writer = csv.DictWriter(file, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(data)
        print(f"데이터가 {filename}에 성공적으로 저장되었습니다.")
    except Exception as e:
        print(f"CSV 쓰기 중 오류 발생: {str(e)}")
```

## 판다스를 활용한 고급 CSV 처리

판다스(pandas)는 데이터 분석을 위한 강력한 도구를 제공합니다.

```python
import pandas as pd
import numpy as np

def analyze_sales_data(filename):
    try:
        # CSV 파일 읽기
        df = pd.read_csv(filename)
        
        # 기본 통계 분석
        analysis = {
            'total_sales': df['amount'].sum(),
            'average_sales': df['amount'].mean(),
            'highest_sale': df['amount'].max(),
            'lowest_sale': df['amount'].min(),
            'sales_std': df['amount'].std(),
            
            # 월별 매출 집계
            'monthly_sales': df.groupby('month')['amount'].sum().to_dict(),
            
            # 제품별 매출 분석
            'product_analysis': df.groupby('product')['amount'].agg({
                'total_sales': 'sum',
                'average_sale': 'mean',
                'sales_count': 'count'
            }).to_dict('index')
        }
        
        return analysis
        
    except Exception as e:
        print(f"데이터 분석 중 오류 발생: {str(e)}")
        return None
```

## 데이터 검증과 전처리

CSV 데이터 처리 시 중요한 검증과 전처리 과정을 구현합니다.

```python
def validate_and_clean_data(df):
    """데이터 검증 및 정제 함수"""
    
    # 결측치 처리
    missing_count = df.isnull().sum()
    if missing_count.any():
        print("결측치 발견:")
        print(missing_count[missing_count > 0])
        
        # 수치형 컬럼의 결측치는 평균값으로 대체
        numeric_columns = df.select_dtypes(include=[np.number]).columns
        for col in numeric_columns:
            df[col].fillna(df[col].mean(), inplace=True)
        
        # 문자열 컬럼의 결측치는 'Unknown'으로 대체
        string_columns = df.select_dtypes(include=['object']).columns
        for col in string_columns:
            df[col].fillna('Unknown', inplace=True)
    
    # 이상치 탐지 (IQR 방식)
    numeric_columns = df.select_dtypes(include=[np.number]).columns
    for column in numeric_columns:
        Q1 = df[column].quantile(0.25)
        Q3 = df[column].quantile(0.75)
        IQR = Q3 - Q1
        lower_bound = Q1 - 1.5 * IQR
        upper_bound = Q3 + 1.5 * IQR
        
        outliers = df[(df[column] < lower_bound) | (df[column] > upper_bound)][column]
        if len(outliers) > 0:
            print(f"\n{column} 컬럼의 이상치 발견:")
            print(outliers)
    
    return df
```

## 실전 활용: 매출 데이터 분석 시스템

비즈니스 환경에서 자주 사용되는 매출 데이터 분석 시스템을 구현해보겠습니다.

```python
class SalesAnalyzer:
    def __init__(self, filename):
        self.filename = filename
        self.df = None
        self.load_data()
    
    def load_data(self):
        """CSV 파일에서 데이터 로드"""
        try:
            self.df = pd.read_csv(self.filename)
            self.df['date'] = pd.to_datetime(self.df['date'])
            print("데이터 로드 완료")
        except Exception as e:
            print(f"데이터 로드 중 오류 발생: {str(e)}")
    
    def generate_monthly_report(self):
        """월별 매출 보고서 생성"""
        if self.df is None:
            return None
            
        monthly_stats = self.df.groupby(self.df['date'].dt.strftime('%Y-%m')
                                      ).agg({
                                          'amount': ['sum', 'mean', 'count'],
                                          'product': 'count'
                                      })
        
        return monthly_stats
    
    def analyze_product_performance(self):
        """제품별 성과 분석"""
        if self.df is None:
            return None
            
        return self.df.groupby('product').agg({
            'amount': ['sum', 'mean', 'count'],
            'customer_id': 'nunique'
        }).round(2)
    
    def export_analysis(self, analysis_data, output_filename):
        """분석 결과를 CSV 파일로 내보내기"""
        try:
            analysis_data.to_csv(output_filename)
            print(f"분석 결과가 {output_filename}에 저장되었습니다.")
        except Exception as e:
            print(f"결과 저장 중 오류 발생: {str(e)}")
```

## CSV 처리 시 고려사항

1. **인코딩 처리**: CSV 파일은 다양한 인코딩을 사용할 수 있으므로, 적절한 인코딩 설정이 중요합니다.

2. **데이터 타입 관리**: 숫자, 날짜 등의 데이터 타입이 올바르게 처리되도록 주의해야 합니다.

3. **대용량 데이터 처리**: 큰 CSV 파일을 처리할 때는 메모리 사용량을 고려하여 청크 단위로 처리합니다.

4. **데이터 정합성**: CSV 파일의 구조가 일관되지 않을 수 있으므로, 데이터 검증이 필요합니다.

## 연습 과제

다음 요구사항을 만족하는 고객 데이터 분석 시스템을 구현해보세요:

1. 고객 데이터 CSV 파일을 읽고 기본적인 통계를 생성합니다.
2. 연령대별, 성별, 지역별 구매 패턴을 분석합니다.
3. 분석 결과를 새로운 CSV 파일로 저장합니다.
4. 데이터 품질 검사를 수행하고 문제가 있는 레코드를 보고합니다.