#include <memory>

class Node{
    public:
        std::shared_ptr<Node> next[53];
        int wordCount;
        bool end;
        Node(){
            wordCount=0;
            for(int i = 0;i<53;i++) next[i]=nullptr;
            end = false;
        }
};