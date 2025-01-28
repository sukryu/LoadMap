# 08_design_patterns: Design Patterns in C++

디자인 패턴은 소프트웨어 설계에서 반복적으로 나타나는 문제들에 대한 일반적인 해결책을 제공합니다. 이 문서에서는 C++로 구현할 수 있는 주요 디자인 패턴을 다룹니다.

---

## 1. 싱글톤 패턴 (Singleton Pattern)
싱글톤 패턴은 클래스의 인스턴스를 하나로 제한하는 디자인 패턴입니다.

### 1.1 구현
```cpp
#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mtx;

    // 생성자를 private으로 선언
    Singleton() {}

public:
    // 복사와 대입 금지
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!instance) {
            instance = new Singleton();
        }
        return instance;
    }

    void showMessage() {
        std::cout << "Singleton instance" << std::endl;
    }
};

Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;

int main() {
    Singleton* s = Singleton::getInstance();
    s->showMessage();
    return 0;
}
```

---

## 2. 팩토리 패턴 (Factory Pattern)
팩토리 패턴은 객체 생성 로직을 캡슐화하여 클라이언트 코드가 객체 생성 방식을 알 필요 없도록 하는 패턴입니다.

### 2.1 구현
```cpp
#include <iostream>
#include <string>
#include <memory>

class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Circle" << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Square" << std::endl;
    }
};

class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(const std::string& type) {
        if (type == "Circle") {
            return std::make_unique<Circle>();
        } else if (type == "Square") {
            return std::make_unique<Square>();
        } else {
            return nullptr;
        }
    }
};

int main() {
    auto circle = ShapeFactory::createShape("Circle");
    auto square = ShapeFactory::createShape("Square");

    if (circle) circle->draw();
    if (square) square->draw();

    return 0;
}
```

---

## 3. 옵저버 패턴 (Observer Pattern)
옵저버 패턴은 객체 상태 변경 시 연결된 객체들에게 자동으로 알림을 보내는 패턴입니다.

### 3.1 구현
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update(int value) = 0;
    virtual ~Observer() {}
};

class Subject {
private:
    std::vector<Observer*> observers;
    int value;

public:
    void attach(Observer* obs) {
        observers.push_back(obs);
    }

    void detach(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notify() {
        for (auto obs : observers) {
            obs->update(value);
        }
    }

    void setValue(int val) {
        value = val;
        notify();
    }
};

class ConcreteObserver : public Observer {
private:
    std::string name;

public:
    ConcreteObserver(const std::string& name) : name(name) {}

    void update(int value) override {
        std::cout << "Observer " << name << " received value: " << value << std::endl;
    }
};

int main() {
    Subject subject;

    ConcreteObserver obs1("A"), obs2("B");
    subject.attach(&obs1);
    subject.attach(&obs2);

    subject.setValue(42);
    subject.setValue(100);

    return 0;
}
```

---

## 4. 전략 패턴 (Strategy Pattern)
전략 패턴은 실행 중에 알고리즘을 선택할 수 있도록 설계된 패턴입니다.

### 4.1 구현
```cpp
#include <iostream>
#include <memory>

class Strategy {
public:
    virtual void execute() const = 0;
    virtual ~Strategy() {}
};

class ConcreteStrategyA : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy A" << std::endl;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy B" << std::endl;
    }
};

class Context {
private:
    std::unique_ptr<Strategy> strategy;

public:
    void setStrategy(std::unique_ptr<Strategy> strat) {
        strategy = std::move(strat);
    }

    void executeStrategy() const {
        if (strategy) {
            strategy->execute();
        }
    }
};

int main() {
    Context context;

    context.setStrategy(std::make_unique<ConcreteStrategyA>());
    context.executeStrategy();

    context.setStrategy(std::make_unique<ConcreteStrategyB>());
    context.executeStrategy();

    return 0;
}
```

---

## 5. 데코레이터 패턴 (Decorator Pattern)
데코레이터 패턴은 객체의 동작을 동적으로 추가하거나 변경할 수 있는 패턴입니다.

### 5.1 구현
```cpp
#include <iostream>
#include <memory>

class Component {
public:
    virtual void operation() const = 0;
    virtual ~Component() {}
};

class ConcreteComponent : public Component {
public:
    void operation() const override {
        std::cout << "ConcreteComponent operation" << std::endl;
    }
};

class Decorator : public Component {
protected:
    std::unique_ptr<Component> component;

public:
    Decorator(std::unique_ptr<Component> comp) : component(std::move(comp)) {}
};

class ConcreteDecorator : public Decorator {
public:
    ConcreteDecorator(std::unique_ptr<Component> comp) : Decorator(std::move(comp)) {}

    void operation() const override {
        component->operation();
        std::cout << " + added behavior by ConcreteDecorator" << std::endl;
    }
};

int main() {
    auto component = std::make_unique<ConcreteComponent>();
    auto decorator = std::make_unique<ConcreteDecorator>(std::move(component));

    decorator->operation();
    return 0;
}
```

---

디자인 패턴은 코드 재사용성과 유지보수성을 높이는 데 중요한 역할을 합니다. 위의 예제들을 통해 C++에서 자주 사용되는 디자인 패턴을 이해하고 활용할 수 있습니다.

