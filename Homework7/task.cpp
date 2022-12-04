#include <iostream>
#include <list>
#include <set>
#include <chrono>

inline bool find(const std::set<int>& lst, int val) {
    for (auto& l : lst) {
        if (l == val) return true;
    }
    return false;
}

int main() {
    std::set<int> l;
    int N = 1000000;
    int M = 200;
    for (int i = 0; i < N; i++) {
        l.insert(2 * i);
    }
    int k = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = (2 * N - M) / 2; i < (2 * N + M) / 2; i++) {
        if(find(l, i)) k++;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count()/5 << std::endl;

    return 0;
}