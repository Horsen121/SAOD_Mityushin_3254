#include <iostream>
#include "RefStr.h" 

int main(){
    RefStr s;
    RefStr r = "Hello, World!";
    s = r;
    RefStr w(s);
    
    std::cout<<s<<" "<< s.GetCount()<<std::endl;
    std::cout<<r<<" "<< r.GetCount()<<std::endl;
    std::cout<<w<<" "<< w.GetCount()<<std::endl;
}