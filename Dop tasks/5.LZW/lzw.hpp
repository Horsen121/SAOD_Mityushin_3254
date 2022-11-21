#include <bits/stdc++.h>

using namespace std;

vector<int> encoding(string s1) {
    try{
        unordered_map<string, int> table;
        for(int i = 0; i <= 255; i++) {
            string ch = "";
            ch += char(i);
            table[ch] = i;
        }
    
        string p = "", c = "";
        p += s1[0];
        int code = 256;
        vector<int> output_code;

        for(int i = 0; i < s1.length(); i++) {
            if(i != s1.length() - 1)
                c += s1[i + 1];
            if(table.find(p + c) != table.end()) {
                p = p + c;
            }
            else {
                // // lzw+
                // if(c == p){
                //     table[p+c] = code;
                //     code++;
                //     p += c;
                // }
                // else{
                    output_code.push_back(table[p]);
                    table[p + c] = code;
                    code++;
                    p = c;
                // }
            }
            c = "";
        }
        output_code.push_back(table[p]);
        
        return output_code;
    }
    catch(...){
        std::cout << "Fatal error!" << endl;
    }
}
 
string decoding(vector<int> op) {
    try{
        unordered_map<int, string> table;
        for (int i = 0; i <= 255; i++) {
            string ch = "";
            ch += char(i);
            table[i] = ch;
        }

        int old = op[0], n;
        string s = table[old];
        string c = "";
        c += s[0];
        string res = s;
        int count = 256;

        for(int i = 0; i < op.size() - 1; i++) {
            n = op[i + 1];
            if(table.find(n) == table.end()) {
                // if(n == old){
                //     table[count] = table[old] + table[old];
                //     s = table[old];
                // }
                // else{
                    s = table[old];
                    s += c;
                // }
            }
            else {
                s = table[n];
            }
            res += s;
            c = "";
            c += s[0];
            table[count] = table[old] + c;
            count++;
            old = n;
        }

        return res;

    }
    catch(...){
        std::cout << "Fatal error!" << endl;
    }
}