#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Test{
    static int Count;
public:
    Test();
    Test(const Test&);
    ~Test(){
        Count--;
        cout << "Delete object. Count = " << Count << endl;
    }
};

class Child: public Test{
public:
    Child();
    ~Child(){
        cout << "Delete Child object" << endl;
    }
};

class Agregate{
public:
    Test t;
    Agregate();
    ~Agregate(){
        cout << "Delete Agregate object" << endl;
    }
};

template <typename T> class AgregateT{
    T test;
public:
    AgregateT(){
        cout << "Create AgregateT object" << endl;
    }
    ~AgregateT(){
        cout << "Delete AgregateT object" << endl;
    }
};