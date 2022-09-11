#include <iostream>
#include "test.hpp"

using std::cout;
using std::cin;
using std::endl;

int Test::Count = 0;
Test::Test(){
    Count++;
    cout << "Create object. Count = " << Count << endl;
}
Test::Test(const Test& t){
    Count++;
    cout << "Copy object. Count = " << Count << endl;
}

Child::Child(){
    cout << "Create Child object" << endl;
}

Agregate::Agregate(){
    cout << "Create Agregate object" << endl;
}