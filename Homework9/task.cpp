#include <iostream>
#include <vector>
#include "heap.hpp"

int main(){
    using std::cout;
    using std::endl;

    std::vector<int> arr;
    
    srand(time(NULL));

    for(int len = 16; len <= 1024; len*=2){
        for(int i = 0; i < len; i++)
            arr.push_back(rand()%100);
        
        Heap heap = Heap(arr);
        int count = heap.HeapSort();

        cout << "len: " << len << "  count: " << count << endl;
    }

    arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Heap heap1 = Heap(arr);
    int count = heap1.HeapSort();
    cout << "count: " << count << endl;

    arr = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    Heap heap2 = Heap(arr);
    count = heap2.HeapSort();
    cout << "count: " << count << endl;

    return 0;
}