#include <iostream>
#include <string>
#include "node.h"

template <typename Type>
class MyList {
private:
    Node<Type>* pFirst;
public:
    MyList();
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
    pFirst = nullptr;
}

template <typename Type>
void MyList<Type>::PushBack(Type value) {
    Node<Type>* newNode = new Node<Type>(value);
    if(pFirst == nullptr) {
        pFirst = newNode;
        newNode->next = pFirst;
        return;
    }
    Node<Type>* nodeCurrent = pFirst;
    while(nodeCurrent->next != pFirst) {
        nodeCurrent = nodeCurrent->next;
    }
    nodeCurrent->next = newNode;
    newNode->next = pFirst;
}

template <typename Type>
void MyList<Type>::PushFront(Type value) {
    Node<Type>* newNode = new Node<Type>(value);
    if(pFirst == nullptr) {
        pFirst = newNode;
        pFirst->next = pFirst;
        return;
    }
    newNode->next = pFirst;
    
    Node<Type>* nodeCurrent = pFirst;
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
    Node<Type>* newNode = new Node<Type>(value);
    if (i == 0) {
        this->PushFront(value);
        return;
    }
    if (i == this->Size() - 1) {
        Node<Type>* nodeCurrent = pFirst;
        while (nodeCurrent->next != pFirst) {
            nodeCurrent = nodeCurrent->next;
        }
        nodeCurrent->next->next = pFirst;
        nodeCurrent->next = newNode;
        return;
    }
    int j = 0;
    Node<Type>* nodeCurrent = pFirst;
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
        delete pFirst;
        pFirst = nullptr;
        return;
    }    
    Node<Type>* nodeCurrent = pFirst;    
    int i = 0;
    while (i != size - 2) {
        nodeCurrent = nodeCurrent->next;
        i++;
    }
    delete nodeCurrent->next;
    nodeCurrent->next = pFirst;
}

template <typename Type>
void MyList<Type>::PopFront() {
    if(pFirst == nullptr) 
        return;
    size_t size = this->Size();
    if(size == 1) {
        delete pFirst;
        pFirst = nullptr;
        return;
    }

    Node<Type>* nodeCurrent = pFirst;
    while(nodeCurrent->next != pFirst) {
        nodeCurrent = nodeCurrent->next;
    }
    nodeCurrent->next = pFirst->next;
    Node<Type>* tmp = pFirst;
    pFirst = pFirst->next;
    delete tmp;
}

template <typename Type>
void MyList<Type>::RemoveAt(size_t i){
    size_t size = this->Size();
    if (i > size - 1 || i < 0) {
        throw std::out_of_range("Index out of range");
        return;
    }
    if (i == 0) {
        Node<Type>* tmp = pFirst;
        pFirst = tmp->next;
        delete tmp;
        return;
    }
    if (i == size - 1) {
        int j = 0;
        Node<Type>* nodeCurrent = pFirst;
        while (j != size - 2) {
            nodeCurrent = nodeCurrent->next;
            j++;
        }
        delete nodeCurrent->next;
        nodeCurrent->next = pFirst;
        return;
    }
    int j = 0;
    Node<Type>* nodeCurrent = pFirst;
    while (j != i - 1) {
        nodeCurrent = nodeCurrent->next;
        j++;
    }
    Node<Type>* tmp = nodeCurrent->next;
    nodeCurrent->next = nodeCurrent->next->next;
    delete tmp;
}

template <typename Type>
Type& MyList<Type>::operator[](const size_t index){
    if (index < 0 || index > this->Size() - 1) {
        throw std::out_of_range("Index out of range");
    }
    Node<Type>* nodeCurrent = pFirst;
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
    Node<Type>* nodeCurrent = pFirst;
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
    Node<Type>* nodeCurrent = pFirst;
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
    Node<Type>* nodeCurrent = pFirst;
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
    Node<Type>* nodeCurrent = pFirst;
    while(nodeCurrent != pFirst) {
        Node<Type>* tmp = nodeCurrent;
        nodeCurrent = nodeCurrent->next;
        delete tmp;
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
    Node<Type>* nodeCurrent = pFirst;
    while (i != size - 1) {
        nodeCurrent = nodeCurrent->next;
        i++;
    }
    return nodeCurrent->elem;
}