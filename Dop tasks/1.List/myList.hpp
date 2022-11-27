#include <iostream>
#include <memory>
#include <string>
#include "node.hpp"

template <typename Type>
class MyList {
private:
    std::shared_ptr<Node<Type>> pFirst;
public:
    MyList();
    ~MyList();
    void PushBack(Type value);
    void PushFront(Type value);
    void Insert(size_t idx, Type value);
    void PopBack();
    void PopFront();
    void RemoveAt(size_t index);
    Type& operator[](const size_t index);
    Type const& operator[](const size_t index) const;
    size_t Size() const;
    bool isEmpty() const;
    void Clear();
    Type Front() const;
    Type Back() const;

    std::string tostr();
    
    MyList<Type>& operator=(const MyList<Type>& other) = delete;
    MyList<Type>& operator=(MyList<Type>&& other) = delete;
};

template <typename Type>
MyList<Type>::MyList() {
    pFirst = std::make_shared<Node<Type>>();
}
template <typename Type>
MyList<Type>::~MyList() {
    this->Clear();
}

template <typename Type>
void MyList<Type>::PushBack(Type value) {
    std::shared_ptr<Node<Type>> newNode = std::make_shared<Node<Type>>();
    newNode->elem = value;
    if(pFirst == nullptr) {
        std::shared_ptr<Node<Type>> pFirst(newNode);
        newNode->next = pFirst;
        return;
    }
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    while(nodeCurrent->next != pFirst) {
        nodeCurrent = nodeCurrent->next;
    }
    nodeCurrent->next = newNode;
    newNode->next = pFirst;
}

template <typename Type>
void MyList<Type>::PushFront(Type value) {
    std::shared_ptr<Node<Type>> newNode = std::make_shared<Node<Type>>();
    newNode->elem = value;
    if(pFirst == nullptr) {
        std::shared_ptr<Node<Type>> pFirst(newNode);
        newNode->next = pFirst;
        return;
    }
    newNode->next = pFirst;
    
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    while(nodeCurrent->next != pFirst) {
        nodeCurrent = nodeCurrent->next;
    }
    nodeCurrent->next = newNode;

    pFirst = newNode;
}

template <typename Type>
void MyList<Type>::Insert(size_t i, Type value) {
    if (i > this->Size() - 1 || i < 0) {
        throw std::out_of_range("Index out of range");
        return;
    }
    std::shared_ptr<Node<Type>> newNode = std::make_shared<Node<Type>>();
    newNode->elem = value;
    if (i == 0) {
        this->PushFront(value);
        return;
    }
    if (i == this->Size() - 1) {
        std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
        while (nodeCurrent->next != pFirst) {
            nodeCurrent = nodeCurrent->next;
        }
        nodeCurrent->next->next = pFirst;
        nodeCurrent->next = newNode;
        return;
    }
    int j = 0;
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    while (j != i - 1) {
        nodeCurrent = nodeCurrent->next;
        j++;
    }
    newNode->next = nodeCurrent->next;
    nodeCurrent->next = newNode;
};

template <typename Type>
void MyList<Type>::PopBack() {
    size_t size = this->Size();
    if (size == 0) return;
    if (size == 1) {
        pFirst = nullptr;
        return;
    }    
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    int i = 0;
    while (i != size - 2) {
        nodeCurrent = nodeCurrent->next;
        i++;
    }
    nodeCurrent->next = pFirst;
}

template <typename Type>
void MyList<Type>::PopFront() {
    if(pFirst == nullptr) 
        return;
    size_t size = this->Size();
    if(size == 1) {
        pFirst = nullptr;
        return;
    }

    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    while(nodeCurrent->next != pFirst) {
        nodeCurrent = nodeCurrent->next;
    }
    nodeCurrent->next = pFirst->next;
    pFirst = pFirst->next;
}

template <typename Type>
void MyList<Type>::RemoveAt(size_t i){
    size_t size = this->Size();
    if (i > size - 1 || i < 0) {
        throw std::out_of_range("Index out of range");
        return;
    }
    if (i == 0) {
        pFirst = pFirst->next;
        return;
    }
    if (i == size - 1) {
        int j = 0;
        std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
        while (j != size - 2) {
            nodeCurrent = nodeCurrent->next;
            j++;
        }
        nodeCurrent->next = pFirst;
        return;
    }
    int j = 0;
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    while (j != i - 1) {
        nodeCurrent = nodeCurrent->next;
        j++;
    }
    nodeCurrent->next = nodeCurrent->next->next;
}

template <typename Type>
Type& MyList<Type>::operator[](const size_t index){
    if (index < 0 || index > this->Size() - 1) {
        throw std::out_of_range("Index out of range");
    }
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    size_t i = index;
    while (i--) {
        nodeCurrent = nodeCurrent->next;
    }
    return nodeCurrent->elem;
}

template <typename Type>
Type const& MyList<Type>::operator[](const size_t index)const{
    if (0 > index || index > this->Size() - 1) {
        throw std::out_of_range("Index out of range");
    }
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    size_t i = index;
    while (i--) {
        nodeCurrent = nodeCurrent->next;
    }
    return nodeCurrent->elem;
}

template <typename Type>
size_t MyList<Type>::Size()const {
    if(pFirst == nullptr) 
        return 0;
    size_t len = 1;
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    while(nodeCurrent->next != pFirst) {
        len++;
        nodeCurrent = nodeCurrent->next;
    }
    return len;
}

template <typename Type>
std::string MyList<Type>::tostr() {
    if (pFirst == nullptr) {
        return "List is empty";
    }
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    std::string res;
    while (nodeCurrent->next != nullptr) {
        res += std::to_string(nodeCurrent->elem) + "->";
        nodeCurrent = nodeCurrent->next;
    } 
    res += std::to_string(nodeCurrent->elem) + "\n";
    return res;
}

template <typename Type>
bool MyList<Type>::isEmpty()const {
    return pFirst == nullptr;
}

template <typename Type>
void MyList<Type>::Clear() { 
    if(pFirst == nullptr) 
        return;
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    while(nodeCurrent != pFirst) {
        nodeCurrent = nodeCurrent->next;
    }
    pFirst = nullptr;
}

template <typename Type>
Type MyList<Type>::Front()const {
    return pFirst->elem;
}

template <typename Type>
Type MyList<Type>::Back()const {
    size_t size = this->Size(), i = 0;
    std::shared_ptr<Node<Type>> nodeCurrent(pFirst);
    while (i != size - 1) {
        nodeCurrent = nodeCurrent->next;
        i++;
    }
    return nodeCurrent->elem;
}