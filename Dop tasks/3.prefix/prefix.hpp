#include <iostream>
#include <string>
#include <memory>
#include <cctype>
#include "node.hpp"

class Prefix{
    private:
        std::shared_ptr<Node> root;
        int count;

    public:
        Prefix(const std::string &text, std::string word){
            root = std::make_shared<Node>();
            count = 0;

            std::string str = "";
            for(const auto & ch : text)
            {
                if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '\'')
                    str += ch;
                else if(str.size() > 0)
                {
                    this->Insert(str);
                    str = "";
                }
            }
            std::cout << "\ntrie size: " << this->Size() << std::endl;
            std::cout << word << ": " << this->Find(word) << std::endl;
        }

        void Insert(std::string  &word){
            using namespace std;
            std::shared_ptr<Node> cur(root);
            for(int i = 0; i<word.size(); i++){
                int let;
                if(word[i]>= 'A' && word[i] <= 'Z') let = (word[i] - 'A')+26;
                else if(word[i]=='\'') let = 52;
                else let = word[i]- 'a';
                if(!cur->next[let]){
                    cur->next[let] = std::make_shared<Node>();
                }
                cur = cur->next[let];
            }  
            cur->wordCount++;                           
            if(!cur->end){
                count++;
                cur->end = true;
            }
        }

        int Find(std::string  &word){
            std::shared_ptr<Node> cur(root);
            for(int i = 0; i<word.size(); i++){
                int let;
                if(word[i]>= 'A' && word[i] <= 'Z') let = (word[i] - 'A')+26;
                else if(word[i]=='\'') let = 52;
                else let = word[i]- 'a';
                if(!cur->next[let]){
                    return 0;
                }
                cur = cur->next[let];
            }
            return cur->wordCount;
        }

        int Size(){
            return count;
        }
};