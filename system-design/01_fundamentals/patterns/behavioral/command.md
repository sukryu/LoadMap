# 커맨드 패턴

> **목표:**  
> - 요청(request)을 객체(Command)로 캡슐화하여, 요청의 발신자(Invoker)와 실제 작업을 수행하는 수신자(Receiver) 간의 결합도를 낮춘다.  
> - 요청의 실행, 취소, 재실행 등의 기능을 유연하게 구현할 수 있도록 한다.  
> - 클라이언트 코드가 구체적인 작업 수행 방법에 의존하지 않고, 명령을 전달하는 방식으로 요청을 처리하도록 한다.

---

## 1. 개념 개요

- **정의:**  
  커맨드 패턴은 요청을 하나의 객체로 캡슐화하여, 요청에 필요한 모든 정보를 포함시키고, 이를 Invoker(요청 발신자)에게 전달하여 실행하게 하는 패턴입니다.  
  이렇게 하면 요청을 매개 변수화하고, 실행 취소나 재실행 등의 기능을 지원할 수 있으며, 요청을 큐에 저장하거나 로그를 남기는 등의 추가 작업도 용이해집니다.

- **왜 중요한가?**  
  - **결합도 감소:** 요청을 실행하는 객체(Receiver)와 요청을 보내는 객체(Invoker)를 분리하여, 서로 독립적으로 변경할 수 있습니다.  
  - **확장성:** 새로운 명령을 추가할 때 기존 코드를 변경하지 않고 새로운 Command 클래스를 도입하여 기능을 확장할 수 있습니다.  
  - **유연한 요청 관리:** 요청을 객체로 캡슐화함으로써, 요청의 취소(undo), 재실행, 큐잉, 로그 기록 등 다양한 부가 기능을 쉽게 구현할 수 있습니다.

- **해결하는 문제:**  
  - 직접적인 메서드 호출로 인한 강한 결합 문제를 해결합니다.  
  - 복잡한 요청 처리 로직을 단순화하고, 요청에 대한 실행, 취소 등의 제어를 중앙집중적으로 관리할 수 있게 합니다.

---

## 2. 실무 적용 사례

- **UI 이벤트 처리:**  
  - 버튼 클릭, 메뉴 선택 등 UI 이벤트를 커맨드 객체로 캡슐화하여, 여러 이벤트 핸들러에서 일관된 방식으로 처리할 수 있습니다.
  
- **트랜잭션 관리:**  
  - 데이터베이스 작업이나 파일 처리 등에서 실행, 취소, 재실행 기능을 제공하기 위해 커맨드 패턴을 활용할 수 있습니다.
  
- **매크로 기록:**  
  - 사용자의 작업을 일련의 커맨드 객체로 기록하여, 나중에 동일 작업을 자동으로 재실행하는 매크로 기능에 적용됩니다.

---

## 3. 구현 방법

아래 예제는 TypeScript를 사용하여 커맨드 패턴을 구현하는 방법을 보여줍니다.  
예제에서는 간단한 텍스트 편집기의 동작(예: 텍스트 추가)을 커맨드 객체로 캡슐화하는 예제를 구현합니다.

### 3.1 기본 구성 요소

1. **Command 인터페이스:**  
   모든 커맨드 객체가 구현해야 할 메서드를 정의합니다.

```typescript
// Command.ts
export interface Command {
  execute(): void;
  undo(): void;  // 실행 취소 기능이 필요한 경우
}
```

2. **Receiver 클래스:**  
   실제 작업을 수행하는 클래스입니다.

```typescript
// TextEditor.ts
export class TextEditor {
  private content: string = "";

  public addText(text: string): void {
    this.content += text;
    console.log(`현재 내용: ${this.content}`);
  }

  public removeText(text: string): void {
    // 단순 예시: 입력된 텍스트를 제거하는 로직 (실제 구현 시 복잡할 수 있음)
    this.content = this.content.replace(text, "");
    console.log(`현재 내용: ${this.content}`);
  }
}
```

3. **ConcreteCommand 클래스:**  
   Command 인터페이스를 구현하여, Receiver의 작업을 캡슐화합니다.

```typescript
// AddTextCommand.ts
import { Command } from './Command';
import { TextEditor } from './TextEditor';

export class AddTextCommand implements Command {
  private editor: TextEditor;
  private text: string;

  constructor(editor: TextEditor, text: string) {
    this.editor = editor;
    this.text = text;
  }

  public execute(): void {
    this.editor.addText(this.text);
  }

  public undo(): void {
    this.editor.removeText(this.text);
  }
}
```

4. **Invoker 클래스:**  
   커맨드를 실행시키고, 필요 시 실행 취소 등의 작업을 관리하는 역할을 합니다.

```typescript
// Invoker.ts
import { Command } from './Command';

export class Invoker {
  private history: Command[] = [];

  public executeCommand(command: Command): void {
    command.execute();
    this.history.push(command);
  }

  public undoLastCommand(): void {
    const command = this.history.pop();
    if (command) {
      command.undo();
    }
  }
}
```

### 3.2 클라이언트 코드 예시

```typescript
// client.ts
import { TextEditor } from './TextEditor';
import { AddTextCommand } from './AddTextCommand';
import { Invoker } from './Invoker';

const editor = new TextEditor();
const invoker = new Invoker();

// 텍스트 추가 명령 생성 및 실행
const command1 = new AddTextCommand(editor, "Hello, ");
invoker.executeCommand(command1);

const command2 = new AddTextCommand(editor, "World!");
invoker.executeCommand(command2);

// 실행 취소 (마지막 명령 취소)
invoker.undoLastCommand();

// 결과 출력 예시:
// 현재 내용: Hello, 
// 현재 내용: Hello, World!
// 현재 내용: Hello, 
```

- **구현 포인트:**  
  - **캡슐화:** Command 객체는 요청에 필요한 정보를 모두 캡슐화하고, 실행과 실행 취소(undo) 메서드를 통해 작업을 수행합니다.  
  - **Invoker의 역할:** Invoker는 커맨드 객체를 받아 실행하며, 실행 기록(history)을 저장하여 필요 시 실행 취소 기능을 제공합니다.
  - **독립성:** 클라이언트는 구체적인 작업 수행 로직(Receiver)과는 독립적으로 커맨드 객체를 생성하고, Invoker를 통해 실행함으로써 결합도를 낮춥니다.

---

## 4. 장단점 및 고려 사항

### 장점
- **결합도 감소:**  
  - 요청의 발신자(Invoker)와 수신자(Receiver)를 분리하여 서로 독립적으로 변경할 수 있습니다.
  
- **유연한 요청 관리:**  
  - 요청을 객체로 캡슐화함으로써, 실행 취소, 재실행, 요청 큐잉 및 로깅 등의 부가 기능을 쉽게 구현할 수 있습니다.
  
- **확장성:**  
  - 새로운 명령을 추가할 때, 기존 코드를 수정하지 않고 새로운 Command 클래스를 도입하여 기능을 확장할 수 있습니다.

### 단점
- **객체 수 증가:**  
  - 요청마다 별도의 Command 객체가 생성되므로, 시스템에 많은 수의 객체가 생길 수 있습니다.
  
- **구현 복잡성:**  
  - 간단한 요청에도 패턴을 적용하면 오히려 코드 구조가 복잡해질 수 있으므로, 적용 시 신중해야 합니다.

### 추가 고려 사항
- **메모리 관리:**  
  - 실행 기록(history)에 의해 커맨드 객체가 장기간 저장될 경우 메모리 사용에 주의해야 합니다.
  
- **동시성:**  
  - 멀티스레드 환경에서 Invoker의 실행 기록 관리와 Command의 실행/취소가 올바르게 동작하는지 동기화가 필요할 수 있습니다.
  
- **테스트 전략:**  
  - 각 Command의 execute 및 undo 메서드에 대한 단위 테스트와, Invoker를 통한 전체 흐름을 통합 테스트로 검증합니다.

---

## 5. 참고 자료

- [Refactoring Guru - Command Pattern](https://refactoring.guru/design-patterns/command)  
- _Design Patterns: Elements of Reusable Object-Oriented Software_ - Erich Gamma 외  
- _Head First Design Patterns_ - Eric Freeman

---

## 마무리

커맨드 패턴은 요청을 객체로 캡슐화하여 실행, 취소, 재실행 등의 기능을 지원하고, 발신자와 수신자 간의 결합도를 낮추는 강력한 설계 기법입니다.  
실제 프로젝트에서는 UI 이벤트 처리, 트랜잭션 관리, 매크로 기록 등 다양한 분야에서 커맨드 패턴을 활용하여 코드의 유연성과 유지보수성을 크게 향상시킬 수 있습니다.