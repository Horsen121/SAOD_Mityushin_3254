#include <iostream>
#include "test.hpp"

Test global_o;
void foo(Test copy){
    std::cout << "foo is running" << std::endl;
}

int main(){
    using std::cout;
    using std::cin;
    using std::endl;

    cout << "Before create t1" << endl;
    Test t1;
    cout << "After create t1" << endl;
    Test *p = new Test;
    delete p;
    Test *pm = new Test[3];
    delete[] pm;
    foo(t1);
    Child ch1;
    Agregate agr1;
    AgregateT<Test> agr2;
    AgregateT<Child> agr3;

    cout << "Before delete t1" << endl;
    return 0;
}