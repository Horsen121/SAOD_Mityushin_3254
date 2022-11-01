#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>

size_t naive(const std::string& str, const std::string& sub)
{
 size_t n = str.size(), m = sub.size(), j = 0;
 for(size_t i = 0; i < n - m + 1; i++)
 {
  for(j = 0; j < m; j++)
  {
   if(str[i + j] != sub[j])
    break;
  }
  if(j == m)
   return i;
 }
 return std::string::npos;
}

size_t kmp(const std::string& str, const std::string& sub)
{
 // ваша быстрая реализация KMP
    int sublen = sub.size();
    int textlen = str.size();

    for(int i = 0; i < textlen; i++) {
        int j = 0;
        while(str[i] == sub[j]){
            j++;
            i++;
        }
        if(j == sublen){
            return i;
        }
    }
 return std::string::npos;
}

size_t bm(const std::string& str, const std::string& sub)
{
 // ваша быстрая реализация BM
    int sublen = sub.size();
    int textlen = str.size();
 
    int s = 0, i, j;
    int bpos[sublen+1], shift[sublen+1];
    for(int i=0;i<sublen+1;i++) 
        shift[i]=0;
  
    i = sublen, j = sublen+1;
    bpos[i]=j;
    while(i>0) {
        while(j<=sublen && sub[i-1] != sub[j-1]) {
            if (shift[j]==0)
                shift[j] = j-i;
            j = bpos[j];
        }
        i--;
        j--;
        bpos[i] = j; 
    }
    j = bpos[0];
    for(i=0; i<=sublen; i++) {
        if(shift[i]==0)
            shift[i] = j;
        if (i==j)
            j = bpos[j];
    }

    while(s <= textlen-sublen) {
        j = sublen-1;
        while(j >= 0 && sub[j] == str[s+j])
            j--;
        if (j<0)
            return s;
        else s += shift[j+1];
    }
  return std::string::npos;
}

int main()
{
 using namespace std;

 string str, sub = "was born in a small town called Sceptre";
 ifstream fin("../../../Another/engwiki_ascii.txt", ios::binary);
 if(!fin.is_open())
 {
  cout << "not open!" << endl;
  return 0;
 }
 str.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

 size_t n = 10;
 std::vector<size_t> times(n), indx(n);
 
 cout << "\nstd::find\n";
 for(size_t i = 0; i < n; i++)
 {
  auto time_one = chrono::high_resolution_clock::now();
  auto index = str.find(sub);
  if(index == std::string::npos)
   std::cout << "not found\n";
  else
   indx[i] = index;
  auto time_two = chrono::high_resolution_clock::now();
  times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
 }
 for(size_t i = 0; i < n; i++)
 {
  cout << indx[i] << '\t' << times[i] << endl;
 }
 
 cout << "\nnaive\n";
 for(size_t i = 0; i < n; i++)
 {
  auto time_one = chrono::high_resolution_clock::now();
  auto index = naive(str, sub);
  if(index == std::string::npos)
   std::cout << "not found\n";
  else
   indx[i] = index;
  auto time_two = chrono::high_resolution_clock::now();
  times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
 }
 for(size_t i = 0; i < n; i++)
 {
  cout << indx[i] << '\t' << times[i] << endl;
 }

 cout << "\nkmp\n";
 for(size_t i = 0; i < n; i++)
 {
  auto time_one = chrono::high_resolution_clock::now();
  auto index = kmp(str, sub);
  if(index == std::string::npos)
   std::cout << "not found\n";
  else
   indx[i] = index;
  auto time_two = chrono::high_resolution_clock::now();
  times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
 }
 for(size_t i = 0; i < n; i++)
 {
  cout << indx[i] << '\t' << times[i] << endl;
 }

 cout << "\nbm\n";
 for(size_t i = 0; i < n; i++)
 {
  auto time_one = chrono::high_resolution_clock::now();
  auto index = bm(str, sub);
  if(index == std::string::npos)
   std::cout << "not found\n";
  else
   indx[i] = index;
  auto time_two = chrono::high_resolution_clock::now();
  times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
 }
 for(size_t i = 0; i < n; i++)
 {
  cout << indx[i] << '\t' << times[i] << endl;
 }
}