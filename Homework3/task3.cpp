#include <iostream>
#include <cmath>
#include "complex.hpp"

int main(){
    using std::cout;
    using std::cin;
    using std::endl;

    Complex c(1.0, 4.0);
    Complex d(2.0, 1.0);
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
    cout << "c+d = " << c+d << endl;
    cout << "c-c = " << c-c << endl;
    cout << "c*d = " << c*d << endl;
    cout << "c/c = " << c/c << endl;
    cout << "Conjugate" << c << " = " << c.Conjugate() << endl;
    cout << "Mod" << c << " = " << c.Mod() << endl;
    cout << "Arg" << c << " = " << c.Arg() << endl;

    Complex v[4]{ Complex (1,1), Complex (2,3), Complex (4,5), Complex (6,0) };
    for(int i = 0; i<5; i++)
        cout<<v[i] << ' ';
     cout<<endl;

    Complex *pc = &c;
    cout << "*pc = " << *pc << endl;
    cout << "Complex(1) = " << *(new Complex(1)) << "  Complex = " << *(new Complex) << "  Complex(1,2) = " << *(new Complex(1,2)) << endl;
    cout << "Re = " << pc->Re << "  Im = " << pc->Im << endl;

    return 0;
}