#include <iostream>

enum class Color { RED = 1, BLACK = 0 };

class Node {
private:
    int _key;
    Color _color;
    Node* _left;
    Node* _right;
    Node* _parent;

public:
    // 기본 생성자
    Node() : _key(0), _color(Color::RED), _left(nullptr), _right(nullptr), _parent(nullptr) {}
    
    // 매개변수가 있는 생성자
    Node(int key) : _key(key), _color(Color::RED), _left(nullptr), _right(nullptr), _parent(nullptr) {}
    
    // NIL 노드용 생성자
    Node(Color color) : _key(0), _color(color), _left(nullptr), _right(nullptr), _parent(nullptr) {}

    // getter/setter 메서드들
    int getKey() const { return _key; }
    Color getColor() const { return _color; }
    Node* getLeft() const { return _left; }
    Node* getRight() const { return _right; }
    Node* getParent() const { return _parent; }

    void setKey(int key) { _key = key; }
    void setColor(Color color) { _color = color; }
    void setLeft(Node* left) { _left = left; }
    void setRight(Node* right) { _right = right; }
    void setParent(Node* parent) { _parent = parent; }

    // RedBlackTree 클래스를 friend로 선언
    friend class RedBlackTree;
};

class RedBlackTree {
private:
    Node* _root;      // 트리의 루트 노드
    Node* _nil;       // NIL 노드 (리프 노드로 사용)

    // 내부 유틸리티 함수들
    void leftRotate(Node* x) {
        if (x == nullptr || x == _nil || x->getRight() == _nil) {
            return; // 회전이 불가능한 경우
        }

        Node* y = x->getRight(); // y를 x의 오른쪽 자식으로 설정

        // y의 왼쪽 서브 트리를 x의 오른쪽 서브트리로 이동
        x->setRight(y->getLeft());
        if (y->getLeft() != _nil) {
            y->getLeft()->setParent(x);
        }

        // x의 부모를 y의 부모로 변경
        y->setParent(x->getParent());

        // x의 부모와 y를 연결
        if (x->getParent() == _nil) { // x가 루트였던 경우
            _root = y;
        }
        else if (x = x->getParent()->getLeft()) { // x가 왼쪽 자식이었던 경우
            x->getParent()->setLeft(y);
        }
        else { // x가 오른쪽 자식이었던 경우
            x->getParent()->setRight(y);
        }

        // y의 왼쪽 자식을 x로 설정
        y->setLeft(x);
        x->setParent(y);
    };
    void rightRotate(Node* y) {
        if (y == nullptr || y == _nil || y->getLeft() == _nil) {
            return;  // 회전이 불가능한 경우
        }

        Node* x = y->getLeft();  // x를 y의 왼쪽 자식으로 설정

        // x의 오른쪽 서브트리를 y의 왼쪽 서브트리로 이동
        y->setLeft(x->getRight());
        if (x->getRight() != _nil) {
            x->getRight()->setParent(y);
        }

        // y의 부모를 x의 부모로 변경
        x->setParent(y->getParent());

        // y의 부모와 x를 연결
        if (y->getParent() == _nil) {  // y가 루트였던 경우
            _root = x;
        }
        else if (y == y->getParent()->getRight()) {  // y가 오른쪽 자식이었던 경우
            y->getParent()->setRight(x);
        }
        else {  // y가 왼쪽 자식이었던 경우
            y->getParent()->setLeft(x);
        }

        // x의 오른쪽 자식을 y로 설정
        x->setRight(y);
        y->setParent(x);
    }
    void transplant(Node* u, Node* v) {
        if (u->getParent() == _nil) {
            _root = v;
        }
        else if (u == u->getParent()->getLeft()) {
            u->getParent()->setLeft(v);
        }
        else {
            u->getParent()->setRight(v);
        }
        v->setParent(u->getParent());
    };
    void fixInsert(Node* z);
    void fixDelete(Node* x) {
        while (x != _root && x->getColor() == Color::BLACK) {
            if (x == x->getParent()->getLeft()) {
                Node* w = x->getParent()->getRight(); // x의 형제 노드

                if (w->getColor() == Color::RED) {
                    // Case 1: x의 형제 w가 RED인 경우
                    w->setColor(Color::BLACK);
                    x->getParent()->setColor(Color::RED);
                    leftRotate(x->getParent());
                    w = x->getParent()->getRight();
                }

                if (w->getLeft()->getColor() == Color::BLACK &&
                    w->getRight()->getColor() == Color::BLACK) {
                    // Case 2. w의 두 자식이 모두 BLACK인 경우
                    w->setColor(Color::RED);
                    x = x->getParent(); 
                }
                else {
                    if (w->getParent()->getColor() == Color::BLACK) {
                        // Case 3. w의 오른쪽 자식이 BLACK인 경우
                        w->getLeft()->setColor(Color::BLACK);
                        w->setColor(Color::RED);
                        rightRotate(w);
                        w = x->getParent()->getRight();
                    }

                    // Case 4. w의 오른쪽 자식이 RED인 경우
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(Color::BLACK);
                    w->getRight()->setColor(Color::BLACK);
                    leftRotate(x->getParent());
                    x = _root;
                }
            }
            else {
                // 위의 경우와 좌우가 대칭인 경우
                Node* w = x->getParent()->getLeft();

                if (w->getColor() == Color::RED) {
                    w->setColor(Color::BLACK);
                    x->getParent()->setColor(Color::RED);
                    rightRotate(x->getParent());
                    w = x->getParent()->getLeft();
                }

                if (w->getRight()->getColor() == Color::BLACK &&
                    w->getLeft()->getColor() == Color::BLACK) {
                    w->setColor(Color::RED);
                    x = x->getParent();
                }
                else {
                    if (w->getLeft()->getColor() == Color::BLACK) {
                        w->getRight()->setColor(Color::BLACK);
                        w->setColor(Color::RED);
                        leftRotate(w);
                        w = x->getParent()->getLeft();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(Color::BLACK);
                    w->getLeft()->setColor(Color::BLACK);
                    rightRotate(x->getParent());
                    x = _root;
                }
            }
        }
        x->setColor(Color::BLACK);
    };
    Node* minimum(Node* x) {
        while (x->getLeft() != _nil) {
            x = x->getLeft();
        }
        return x;
    };
    Node* maximum(Node* x) {
        while (x->getRight() != _nil) {
            x = x->getRight();
        }
        return x;
    };
    void destroyTree(Node* node);

public:
    // 생성자와 소멸자
    RedBlackTree();
    ~RedBlackTree();

    bool isNil(Node* node) const {
        return node == _nil;
    }

    // 탐색 연산
    Node* search(int key) {
        Node* current = _root;

        while (current != _nil && key != current->getKey()) {
            if (key < current->getKey()) {
                current = current->getLeft();
            } else {
                current = current->getRight();
            }
        }

        return current;
    };
    Node* successor(Node* x);
    Node* predecessor(Node* x);

    // 삽입과 삭제
    void insert(int key);
    void deleteNode(int key) {
        Node* z = search(key); // 삭제할 노드 찾기
        if (z == _nil) {
            return; // 삭제할 노드가 없는 경우
        }

        Node* y = z; // 실제로 삭제될 노드
        Node* x; // y의 자리를 대체할 노드
        Color y_original_color = y->getColor();

        if (z->getLeft() == _nil) {
            x = z->getRight();
            transplant(z, z->getRight());
        }
        else if (z->getRight() == _nil) {
            x = z->getLeft();
            transplant(z, z->getLeft());
        }
        else {
            y = minimum(z->getRight()); // z의 후계자 찾기
            y_original_color = y->getColor();
            x = y->getRight();

            if (y->getParent() == z) {
                x->setParent(y);
            }
            else {
                transplant(y, y->getRight());
                y->setRight(z->getRight());
                y->getRight()->setParent(y);
            }

            transplant(z, y);
            y->setLeft(z->getLeft());
            y->getLeft()->setParent(y);
            y->setColor(z->getColor());
        }

        delete z; // 메모리 해제

        if (y_original_color == Color::BLACK) {
            fixDelete(x); // Black 노드가 삭제된 경우 속성 복구
        }
    };

    // 트리 순회
    void inorderTraversal() {
        std::cout << "중위 순회 결과: ";
        inorderTraversalHelper(_root);
        std::cout << std::endl;
    };
    void printTree() { // 트리 구조를 시각적으로 출력 (디버깅용)
        if (_root == _nil) {
            std::cout << "트리가 비어있습니다." << std::endl;
            return;
        }
        printTreeHelper(_root, "", true);
    };

private:
    // 내부 순회 함수들
    void inorderTraversalHelper(Node* node) {
        if (node != _nil) {
            inorderTraversalHelper(node->getLeft());
            std::cout << node->getKey() << "("
                    << (node->getColor() == Color::RED ? "RED" : "BLACK")
                    << ") ";
            inorderTraversalHelper(node->getRight());
        }
    };
    void printTreeHelper(Node* root, std::string indent, bool last) {
        if (root != _nil) {
            std::cout << indent;
            if (last) {
            std::cout << "└── ";
            indent += "    ";
            } else {
                std::cout << "├── ";
                indent += "│   ";
            }

            std::string color = root->getColor() == Color::RED ? "RED" : "BLACK";
            std::cout << root->getKey() << "(" << color << ")" << std::endl;

            printTreeHelper(root->getLeft(), indent, false);
            printTreeHelper(root->getRight(), indent, true);
        }
    };
};

// 생성자 구현
RedBlackTree::RedBlackTree() {
    _nil = new Node(Color::BLACK);  // NIL 노드 생성
    _root = _nil;                   // 초기 루트는 NIL
}

// 소멸자 구현
RedBlackTree::~RedBlackTree() {
    destroyTree(_root);  // 트리의 모든 노드 삭제
    delete _nil;         // NIL 노드 삭제
}

int main() {
    RedBlackTree tree;
    std::string command;
    int key;

    std::cout << "Red-Black Tree 명령어 안내:" << std::endl;
    std::cout << "삽입: I key" << std::endl;
    std::cout << "삭제: D key" << std::endl;
    std::cout << "검색: S key" << std::endl;
    std::cout << "중위순회 출력: P" << std::endl;
    std::cout << "트리 구조 출력: T" << std::endl;
    std::cout << "종료: Q" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    while (true) {
        std::cout << "\n명령어 입력: ";
        std::cin >> command;

        if (command == "Q" || command == "q") {
            std::cout << "프로그램을 종료합니다." << std::endl;
            break;
        }

        try {
            switch (command[0]) {
                case 'I':
                case 'i':
                    std::cin >> key;
                    tree.insert(key);
                    std::cout << key << "를 삽입했습니다." << std::endl;
                    break;

                case 'D':
                case 'd':
                    std::cin >> key;
                    Node* searchResult = tree.search(key);
                    if (tree.isNil(searchResult)) {
                        std::cout << "키 " << key << "가 트리에 존재하지 않습니다." << std::endl;
                    } else {
                        tree.deleteNode(key);
                        std::cout << key << "를 삭제했습니다." << std::endl;
                    }
                    break;

                case 'S':
                case 's':
                    std::cin >> key;
                    Node* result = tree.search(key);
                    if (tree.isNil(result)) {
                        std::cout << "키 " << key << "를 찾을 수 없습니다." << std::endl;
                    } else {
                        std::cout << "키 " << key << "를 찾았습니다. 색상: " 
                                << (result->getColor() == Color::RED ? "RED" : "BLACK") 
                                << std::endl;
                    }
                    break;

                case 'P':
                case 'p':
                    tree.inorderTraversal();
                    break;

                case 'T':
                case 't':
                    tree.printTree();
                    break;

                default:
                    std::cout << "잘못된 명령어입니다. 다시 입력해주세요." << std::endl;
            }
        }
        catch (std::exception& e) {
            std::cout << "오류 발생: " << e.what() << std::endl;
        }
    }

    return 0;
}