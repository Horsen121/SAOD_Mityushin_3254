#include <iostream>
#include <cstring>
#include "utils.hpp"

int main(){
    using std::cout;
    using std::cin;
    using std::endl;

    // int x;
    // cout << "Enter x: ";
    // cin >> x;
    // int *p = &x; 
    // cout << "x: " << x << '  ' << "*p: " << *p << '  ' << "p: " << p << endl;

    // p++; 
    // cout << "p: " << p << endl;
    // cout << "p - &x = " << p - &x << endl;

    // typedef unsigned char byte;
	// byte *pb = (byte *)--p;
	// for (byte *pt = pb; pt - pb<sizeof(int); pt++)
	// 	cout << (int)*pt << ' ';
    // cout << endl;


    int x = 3, y = 5;
    cout << "Swap(" << x << ", " << y << ") = ";
    Swap(x, y);
    cout << "(" << x << ", " << y << ")" << endl;

    int a[5]{1,2,3,4,5};
    int b[5]{1,2,3,4,5};
    // for(int i = 0; i<5; i++)
    //    cout<<a[i] << ' ';
    // cout<<endl; 
    for (int *p = a; p-a<5; p++)
		cout << *p << ' ';
	cout << endl;
    Rotate(a, sizeof(a)/sizeof(*a), true);
    for (int *p = a; p-a<5; p++)
		cout << *p << ' ';
    cout << endl;
    Rotate(b, sizeof(b)/sizeof(*b), false);
    for (int *p = b; p-b<5; p++)
		cout << *p << ' ';
    cout << endl;


    char str[] = "Hello!";
	//cout << str << endl;
    //cout << strlen(str) << ' ' << sizeof(str) << endl;
    char t[32];
    char empt[32];
    char longstr[32] = "Long str";
    for (char *pd = t, *ps = str; *pd++ = *ps++;)
    String_copy(t, str);
    cout << "String_copy(t, str) = " << t << endl;
    cout << "Len(str) = " << Len(str) << endl;
    cout << "Compare('Hello!','Hello!') = " << Compare(str,str) << "  " << "Compare('Hello!', '') = " << Compare(str, empt) 
        << "  Compare('Hello!', 'Long str') = " << Compare(str, longstr) << endl;

    return 0;
}