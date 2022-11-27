#include <iostream>
#include "myList.hpp"

void printList(const MyList<char> &list) {
    for (int i = 0; i < list.Size() - 1; i++)
        std::cout << list[i] << " -> ";
    std::cout << list[list.Size() - 1];
    std::cout << "\n";
}

int main() {
    MyList<char> list;
    std::cout << std::boolalpha << list.isEmpty() << std::endl;

    for(int i = 0; i < 5; i++)
        list.PushBack(char('a' + i));
    printList(list);
    
    for(int i = 0; i < 5; i++)
        list.Insert(0, char('z' - i));
    printList(list);
    for(size_t i = 0; i != list.Size(); i++)
        list[i] = char('a' + i);
    printList(list);

    list.PopBack();
    list.PopFront();
    printList(list);

    list.RemoveAt(5);
    list.Insert(3, 'o');
    printList(list);
    
    list.Clear();
    
    list.PushBack('q');
    list.PushBack('w');
    std::cout << list.Size() << ' ' << std::boolalpha << list.isEmpty() << std::endl;
}