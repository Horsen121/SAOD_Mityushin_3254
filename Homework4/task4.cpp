#include <iostream>
#include <string.h>
#include "strings.hpp"

int main(){
    using std::cout;
    using std::cin;
    using std::endl;

    Str s = "123";
    cout << "s = " << s << endl;
    cout << "strlen(s) = " << strlen(s) << endl;

    Str t;
	//t = s = t;
    //cout << "t = s = t: " << t << " = " << s << " = " << t << endl;
    t = "45";
    cout << "t = " << t << endl;
    cout << "s += t = " << (s+=t) << endl;
    cout << "s + t = " << (s+t) << endl;

    return 0;
}