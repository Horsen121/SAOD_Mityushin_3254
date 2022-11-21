#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>
#include <fstream>
#include <tuple>
#include <algorithm>
#include "prefix.hpp"

void umap(const std::string &text, std::string word)
{
 using namespace std;
 unordered_map<std::string, size_t> dict;
 string str = "";
 for(const auto & ch : text)
 {
  if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '\'')
   str += ch;
  else if(str.size() > 0)
  {
   ++dict[str];
   str = "";
   }
 }
 cout << "\ndict size: " << dict.size() << endl;
 cout << word << ": " << dict[word] << endl;
}

int main(int agrc, char* argv[]) {
    using std::cout;
    using std::endl;

    std::string text;
    std::ifstream fin(argv[1], std::ios::binary);
    if(!fin.is_open()) {
        cout << "not open!" << endl;
        return 0;
    }

    text.append((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>()); 
    std::string word = "wiki";

    cout << "umap" << endl;
    auto time_one = std::chrono::steady_clock::now();
    umap(text, word);
    auto time_two = std::chrono::steady_clock::now();
    cout << "time: " << std::chrono::duration_cast<std::chrono::seconds>(time_two - time_one).count() << " sec" << endl << endl;

    cout << "prefix" << endl;
    time_one = std::chrono::steady_clock::now();
    Prefix(text, word);
    time_two = std::chrono::steady_clock::now();
    cout << "time: " << std::chrono::duration_cast<std::chrono::seconds>(time_two - time_one).count() << " sec" << endl;

    return 0;
}
