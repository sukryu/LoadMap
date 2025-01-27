# Boost.Asio 라이브러리 사용 가이드

Boost.Asio는 C++ 네트워크와 비동기 I/O 프로그래밍을 위한 라이브러리로, TCP, UDP, 타이머, 직렬 포트 등의 네트워크 및 비동기 작업을 지원합니다. 이 가이드는 Boost.Asio의 주요 기능과 사용법을 다룹니다.

---

## 1. 주요 특징

1. **비동기 I/O**: 비동기 방식으로 효율적인 네트워크 통신과 파일 작업 지원.
2. **멀티프로토콜 지원**: TCP, UDP, ICMP 등 다양한 네트워크 프로토콜 지원.
3. **타이머 및 스케줄링**: 시간 기반 이벤트 처리 가능.
4. **멀티스레드 지원**: 멀티스레드 환경에서 안전하게 작동.
5. **C++ 표준 기반**: C++11 이상과 호환.

---

## 2. 설치

### 2.1 설치 방법

**Ubuntu/Linux:**
```bash
sudo apt-get update
sudo apt-get install libboost-all-dev
```

**macOS:**
```bash
brew install boost
```

**Windows:**
- Boost 공식 웹사이트(https://www.boost.org/)에서 다운로드 후 설치.

### 2.2 CMake 프로젝트 설정
```cmake
find_package(Boost REQUIRED COMPONENTS asio)

add_executable(my_project main.cpp)
target_link_libraries(my_project Boost::asio)
```

---

## 3. 주요 구성 요소

### 3.1 `boost::asio::io_context`
- **설명**: 모든 I/O 작업의 중심으로, 작업 실행을 관리.

### 3.2 `boost::asio::ip::tcp` / `boost::asio::ip::udp`
- **설명**: TCP와 UDP 네트워크 통신을 위한 클래스 제공.

### 3.3 `boost::asio::steady_timer`
- **설명**: 타이머 이벤트 처리를 위한 클래스.

---

## 4. 주요 사용법

### 4.1 비동기 타이머

**예제:** 5초 후 메시지 출력
```cpp
#include <boost/asio.hpp>
#include <iostream>

void timer_handler(const boost::system::error_code& /*e*/) {
    std::cout << "타이머 완료!" << std::endl;
}

int main() {
    boost::asio::io_context io;
    boost::asio::steady_timer timer(io, std::chrono::seconds(5));

    timer.async_wait(&timer_handler);
    io.run();

    return 0;
}
```

**출력:**
```
타이머 완료!
```

---

### 4.2 TCP 서버

**예제:** 간단한 TCP 에코 서버
```cpp
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>

using boost::asio::ip::tcp;

void handle_client(std::shared_ptr<tcp::socket> socket) {
    try {
        char data[1024];
        while (true) {
            size_t length = socket->read_some(boost::asio::buffer(data));
            boost::asio::write(*socket, boost::asio::buffer(data, length));
        }
    } catch (std::exception& e) {
        std::cerr << "클라이언트 처리 중 오류: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io;
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 12345));

        while (true) {
            auto socket = std::make_shared<tcp::socket>(io);
            acceptor.accept(*socket);
            std::thread(handle_client, socket).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "서버 오류: " << e.what() << std::endl;
    }

    return 0;
}
```

**설명:**
- TCP 포트 12345에서 연결을 대기합니다.
- 클라이언트로부터 데이터를 수신하면 그대로 반환합니다.

---

### 4.3 TCP 클라이언트

**예제:** TCP 서버에 메시지 전송
```cpp
#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io;
        tcp::socket socket(io);
        tcp::resolver resolver(io);

        boost::asio::connect(socket, resolver.resolve("127.0.0.1", "12345"));

        std::string message = "Hello, Server!";
        boost::asio::write(socket, boost::asio::buffer(message));

        char response[1024];
        size_t length = socket.read_some(boost::asio::buffer(response));
        std::cout << "서버 응답: " << std::string(response, length) << std::endl;

    } catch (std::exception& e) {
        std::cerr << "클라이언트 오류: " << e.what() << std::endl;
    }

    return 0;
}
```

**출력:**
```
서버 응답: Hello, Server!
```

---

### 4.4 UDP 클라이언트와 서버

**예제:** UDP 에코 클라이언트와 서버

#### UDP 서버
```cpp
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::udp;

int main() {
    boost::asio::io_context io;
    udp::socket socket(io, udp::endpoint(udp::v4(), 12345));

    char data[1024];
    udp::endpoint sender_endpoint;

    while (true) {
        size_t length = socket.receive_from(boost::asio::buffer(data), sender_endpoint);
        socket.send_to(boost::asio::buffer(data, length), sender_endpoint);
    }

    return 0;
}
```

#### UDP 클라이언트
```cpp
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::udp;

int main() {
    boost::asio::io_context io;
    udp::socket socket(io);
    socket.open(udp::v4());

    udp::endpoint endpoint(boost::asio::ip::make_address("127.0.0.1"), 12345);

    std::string message = "Hello, UDP Server!";
    socket.send_to(boost::asio::buffer(message), endpoint);

    char response[1024];
    udp::endpoint sender_endpoint;
    size_t length = socket.receive_from(boost::asio::buffer(response), sender_endpoint);

    std::cout << "서버 응답: " << std::string(response, length) << std::endl;

    return 0;
}
```

**출력:**
```
서버 응답: Hello, UDP Server!
```

---

## 5. 사용 시 주의사항

1. **에러 처리**: 모든 Boost.Asio 호출에 대해 예외 처리 또는 `boost::system::error_code`를 사용하여 오류를 처리하세요.
2. **멀티스레드 환경**: 멀티스레드로 사용할 경우 `io_context` 객체를 적절히 공유해야 합니다.
3. **자원 해제**: 소켓 및 핸들 객체는 사용 후 반드시 해제해야 합니다.

---

Boost.Asio는 고성능 네트워크 애플리케이션을 개발하는 데 강력한 도구를 제공합니다. 위의 예제와 기능을 활용하여 TCP/UDP 기반 네트워크 프로그램을 작성해보세요.