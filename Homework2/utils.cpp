#include <iostream>
#include "utils.hpp"

void Swap(int &a, int &b) {
   int temp = a;
   a = b;
   b = temp;
}
void Rotate (int *a, int n, bool clockwise=false) {
    if(clockwise){
        int last = *(a+n-1);
        int *finish = a+n-1;
        for (int *p = finish-1; finish!=a; p--,finish--){
		    *finish = *p;
        }
        *a = last;
    }
    else{
        int *start = a;
        int first = *a;
        for (int *p = a+1; a-start< n-1; a++,p++){
		    *a = *p;
        }
        *a = first;
    }
}
void String_copy(char *d, char *s){
    for(;*d!='\0';){
        *d++ = *s++;
    }
}
int Len(const char *s){
    int len = 0;
    for(;*s!='\0';s++)
        len++;
    return len;
}
int Compare(const char *s, const char *t){
    int sLen = 0, tLen = 0;
    for(;*s!='\0';s++,sLen++);
    for(;*t!='\0';t++,tLen++);
    if(sLen < tLen) {return -1;}
    else if(sLen == tLen) {return 0;}
    else {return 1;}
}