# 인터페이스 분리 원칙 (Interface Segregation Principle, ISP)

인터페이스 분리 원칙은 **클라이언트가 자신이 사용하지 않는 메서드에 의존하지 않도록, 인터페이스를 작고 구체적으로 분리해야 한다**는 원칙입니다.  
즉, 하나의 거대한 인터페이스보다는 역할별로 세분화된 인터페이스를 제공함으로써, 불필요한 의존성을 제거하고 각 클라이언트가 필요한 기능만 사용하도록 유도합니다.

---

## 1. ISP의 개념 이해

- **클라이언트 중심 설계:**  
  인터페이스는 인터페이스를 사용하는 클라이언트가 실제로 필요한 기능만 노출해야 합니다.
  
- **불필요한 구현 부담 제거:**  
  한 인터페이스에 여러 기능이 포함되어 있다면, 어떤 클라이언트는 필요 없는 기능까지 구현해야 하는 문제가 발생할 수 있습니다.
  
- **유연한 확장:**  
  기능별로 분리된 인터페이스를 사용하면, 새로운 기능 추가 시 다른 기능에 영향을 주지 않고 확장할 수 있습니다.

---

## 2. 문제 상황과 해결 방안

### 2.1. 문제 상황: 하나의 거대한 인터페이스

초보자들이 흔히 겪는 문제는, 여러 기능을 하나의 인터페이스에 묶어놓은 후 특정 클라이언트가 불필요한 메서드를 구현해야 하는 상황입니다.

#### 예시: 모든 기능을 포함한 인터페이스 (ISP 미적용)
```python
from abc import ABC, abstractmethod

# 모든 기능을 한 인터페이스에 포함
class MultiFunctionDevice(ABC):
    @abstractmethod
    def print_document(self, document):
        pass

    @abstractmethod
    def scan_document(self, document):
        pass

    @abstractmethod
    def fax_document(self, document):
        pass

# 단순 프린터: 인쇄 기능만 필요하지만, 불필요한 스캔/팩스 메서드를 구현해야 함
class SimplePrinter(MultiFunctionDevice):
    def print_document(self, document):
        print("Printing document:", document)

    def scan_document(self, document):
        # 이 프린터는 스캔 기능이 없으므로 불필요한 구현
        raise NotImplementedError("이 프린터는 스캔 기능을 지원하지 않습니다.")

    def fax_document(self, document):
        # 이 프린터는 팩스 기능이 없으므로 불필요한 구현
        raise NotImplementedError("이 프린터는 팩스 기능을 지원하지 않습니다.")
```

**문제점:**  
- `SimplePrinter` 클래스는 실제 필요 없는 스캔과 팩스 메서드를 구현해야 하므로, 코드가 불필요하게 복잡해집니다.
- 클라이언트 입장에서는 사용하지 않는 기능에 의존하는 불편함이 발생합니다.

---

### 2.2. 해결 방안: 인터페이스 분리

기능별로 인터페이스를 분리하면, 각 클라이언트가 필요한 기능만 구현하면 되므로 ISP를 준수할 수 있습니다.

#### 개선 예시: 역할별 인터페이스 분리
```python
from abc import ABC, abstractmethod

# 인쇄 기능만 제공하는 인터페이스
class Printer(ABC):
    @abstractmethod
    def print_document(self, document):
        pass

# 스캔 기능만 제공하는 인터페이스
class Scanner(ABC):
    @abstractmethod
    def scan_document(self, document):
        pass

# 팩스 기능만 제공하는 인터페이스
class Fax(ABC):
    @abstractmethod
    def fax_document(self, document):
        pass

# 단순 프린터는 인쇄 기능만 구현하면 됨
class SimplePrinter(Printer):
    def print_document(self, document):
        print("Printing document:", document)

# 다기능 프린터는 필요한 인터페이스를 여러 개 구현
class MultiFunctionPrinter(Printer, Scanner, Fax):
    def print_document(self, document):
        print("Printing document:", document)

    def scan_document(self, document):
        print("Scanning document:", document)

    def fax_document(self, document):
        print("Faxing document:", document)
```

**장점:**  
- **명확한 역할 분리:** 각 인터페이스가 구체적인 기능만 담당하므로, 클라이언트는 필요한 기능만 의존합니다.
- **유지보수 용이성:** 인터페이스가 작고 구체적이므로, 변경이나 확장이 필요한 경우 해당 기능에만 집중할 수 있습니다.
- **테스트 편의성:** 각 기능별로 독립적인 단위 테스트를 작성할 수 있습니다.

**단점:**  
- 인터페이스가 여러 개로 분리되면서 클래스 설계 시 어느 인터페이스를 구현해야 하는지 결정하는 데 추가적인 고려가 필요할 수 있습니다.

---

## 3. 구체적 구현 방법 및 베스트 프랙티스

### 3.1. 구현 시 고려 사항
- **인터페이스 설계:**  
  기능 단위로 인터페이스를 분리하고, 클라이언트가 실제로 사용하는 메서드만 포함되도록 설계합니다.
  
- **클래스 다중 상속:**  
  파이썬과 같이 다중 상속이 가능한 언어에서는, 여러 작은 인터페이스를 필요한 만큼 조합하여 구현할 수 있습니다.
  
- **문서화:**  
  각 인터페이스의 역할과 사용법을 명확하게 문서화하여, 개발자들이 올바르게 사용할 수 있도록 합니다.

### 3.2. 테스트 및 엣지 케이스 고려
- **단위 테스트:**  
  각 인터페이스 별로 독립적인 테스트 케이스를 작성하여, 변경이 다른 기능에 미치는 영향을 최소화합니다.
  
- **예외 처리:**  
  클라이언트가 사용하지 않는 기능에 접근하려 할 때, 적절한 예외 처리를 통해 문제를 명확하게 알릴 수 있도록 합니다.

---

## 4. 추가 고려 사항

- **코드 리뷰와 협업:**  
  작고 구체적인 인터페이스는 코드 리뷰 시에 각 기능의 역할이 명확하게 드러나, 팀원 간 협업에 큰 도움이 됩니다.
  
- **확장성:**  
  새로운 기능이 필요할 때, 기존 인터페이스를 수정하지 않고 새로운 인터페이스를 추가하여 확장이 용이합니다.
  
- **실제 사례:**  
  프린터, 스캐너, 팩스와 같이 다기능 기기의 예시를 통해, ISP의 필요성과 장점을 실무에 쉽게 적용할 수 있습니다.

---

## 5. 결론

인터페이스 분리 원칙(ISP)은 **클라이언트가 불필요한 의존성을 갖지 않도록 인터페이스를 작고 구체적으로 분리**하는 데 중점을 둡니다.  
- **불필요한 메서드 구현 제거:** 클라이언트가 사용하지 않는 기능을 구현하지 않아도 되므로, 코드가 깔끔하고 유지보수가 용이합니다.
- **유연한 설계:** 필요에 따라 여러 개의 작은 인터페이스를 조합하여 다양한 기능을 구현할 수 있습니다.

ISP를 준수하면, 소프트웨어가 더 견고해지고 변화하는 요구사항에도 유연하게 대응할 수 있으므로, 초보자부터 숙련된 개발자까지 모두가 고려해야 할 중요한 설계 원칙입니다.