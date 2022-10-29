#include <iostream>
#include "utils.hpp"

int main(){
    using std::cout;
    using std::cin;
    using std::endl;

    int v[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    Array arr(4, 4, v);
    cout << arr << endl;
    cout << "Ref arr: " << arr.Ref() << endl;

    Array arr2 = arr.Clone();
    cout << "Array clone" << endl << arr2 << endl;
    cout << "Ref arr: " << arr.Ref() << endl << endl;

    cout << "Change first el in arr2 to 121" << endl;
    arr2.Item(0,0) = 121;
    cout << "Arr" << endl<< arr << endl;
    cout << "Arr2" << endl << arr2 << endl << endl;

    cout << "Copy arr to arr3" << endl;
    Array arr3(arr);
    cout << "Arr3" << endl;
    cout << arr3 << endl;
    cout << "Ref arr: " << arr.Ref() << endl << endl;


    return 0;
}