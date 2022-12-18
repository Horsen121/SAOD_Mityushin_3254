#include <iostream>
#include <vector>

template <typename Type>
class Heap {
    int size;

public:
    std::vector<Type> heap;

    Heap(std::vector<Type> arr) {
        size = arr.size();
        heap = arr;
        for(int i = size/2 - 1; i >= 0; i--) {
            long prev_i = i;
            i = InsertHeap(i, size);
            if (prev_i != i) i++;
        }
    }

    int InsertHeap(int i, int N) {
        int imax;
        Type buf;
        if((2*i + 2) < N) {
            if(heap[2*i + 1] < heap[2*i + 2]) imax = 2*i + 2;
            else imax = 2*i + 1;
        }
        else imax = 2*i + 1;
        if(imax >= N) return i;

        if(heap[i] < heap[imax]) {
            buf = heap[i];
            heap[i] = heap[imax];
            heap[imax] = buf;
            if(imax < N / 2) i = imax;
        }
        return i;
    }

    int HeapSort() {
        int count =1;
        for(int k = size - 1; k > 0; k--) {
            Type buf = heap[0];
            heap[0] = heap[k];
            heap[k] = buf;
            int i = 0, prev_i = -1;
            while(i != prev_i) {
                prev_i = i;
                i = InsertHeap(i, k);
                count++;
            }
        }

        return count;
    }
};