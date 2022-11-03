#include <iostream>

template <typename Type>
struct Node {
public:
    Type elem;
    Node<Type>* next = nullptr;

    Node(Type data) {
        this->elem = data;
        // this->next = nullptr;
    }
};