#include <iostream>
#include <memory>

template <typename Type>
struct Node {
public:
    Type elem;
    std::shared_ptr<Node<Type>> next;

    Node(Type data) {
        this->elem = data;
    }
};