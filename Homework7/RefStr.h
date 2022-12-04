#include <memory>
#include <cstring>
class RefStr {
    std::shared_ptr<char[]> m_pStr;
    public:
    RefStr() 
        :m_pStr(new char[1]{ 0 }) 
    {}

    RefStr (const char * p) 
        :m_pStr(new char[strlen(p)+1])	
    {
    	strcpy(m_pStr.get(),p);
    }

    int GetCount() const{
        return m_pStr.use_count();
    }

    int len() const {
        return strlen(m_pStr.get());
    }

    RefStr Clone(){
        return RefStr(this->m_pStr.get());
    }

    operator const char *()const { return m_pStr.get(); }
};