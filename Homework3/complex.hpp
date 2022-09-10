#include <iostream>
#include <cmath>
using std::ostream;

class Complex {

public:	
	double Re, Im;
	inline Complex(double re=0.0, double im=0.0){
        Re = re;
        Im = im;
    }

    inline Complex operator +(const Complex&c)const { 
        return Complex (Re + c.Re, Im + c.Im); 
    }
    inline Complex operator -(const Complex&c)const { 
        return Complex (Re - c.Re, Im - c.Im); 
    }
    inline Complex operator *(const Complex&c)const { 
        return Complex (Re*c.Re - Im*c.Im, Re*c.Im + Im*c.Re); 
    }
    inline Complex operator /(const Complex&c)const { 
        return Complex ((Re*c.Re + Im*c.Im)/(c.Re*c.Re + c.Im*c.Im), (Im*c.Re - Re*c.Im)/(c.Re*c.Re + c.Im*c.Im)); 
    }

    inline Complex Conjugate() { 
        return Complex (Re, -Im); 
    }
    inline double Mod(){
        return double(sqrt(Re*Re + Im*Im));
    }
    inline double Arg(){
        if(Mod()==0) return 0;
        if(Re > 0) return atan(Im/Re);
        else if(Re < 0){
            if(Im >= 0) return acos(-1) + atan(Im/Re);
            else return -acos(-1) - atan(Im/Re);
        }
        else if(Im > 0) return acos(0);
        else return -acos(0);
    }

    friend ostream& operator << (ostream &, const Complex &);
};

inline ostream& operator << (ostream &o, const Complex &c) { 
    return o << '(' << c.Re << ", " << c.Im << "i)"; 
    }