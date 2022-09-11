#include <iostream>

class Str {
    char* m_pszText;

public:
	inline Str() {
        m_pszText = new char[1]{0};
    }
    inline Str(const char * p) {
        if(p) {
            m_pszText = new char [strlen(p) + 1];
            strcpy(m_pszText, p);
        }
        else
            m_pszText = new char[1]{0};
    }
    inline Str(const Str &s) {
        m_pszText = new char[strlen(s.m_pszText) + 1];
        strcpy(m_pszText, s.m_pszText);
    }
	inline ~Str() { 
        delete []m_pszText;
    }

    inline operator const char *()const {
        return m_pszText;
    }
    inline const Str& operator =(const Str &s){
        if(&s == this) return *this;
        delete [] m_pszText;
        m_pszText = new char[strlen(s.m_pszText) + 1];
        strcpy(m_pszText, s.m_pszText);
        return *this;
    }
    inline Str& operator +=(const char *sz){
        if (sz) {
            Str tmp(*this);
            int len = strlen(sz) + strlen(m_pszText);
            m_pszText = new char[len + 1];
            strcpy(m_pszText, tmp.m_pszText);
            strcpy(m_pszText + strlen(tmp.m_pszText), sz);
        }
        return *this;
    }
    inline Str operator +(const char *sz) const{
        Str res(*this);
        res += sz;

        return res;
    }
};