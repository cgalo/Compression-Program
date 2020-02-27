//
// Created by Carlos Galo on 2/26/20.
//

#ifndef HUFF_MINHEAP_H
#define HUFF_MINHEAP_H

const int maxLength = 256;

class MinHeap {
private:
    int *array;
    int capacity;
    int currentSize;
    int parent(int i) { return (i-2/2);}
    int left(int i){return (2*i + 1); }
    int right(int i){return (2*i + 2);}
public:
    MinHeap();
    void insertHeap(int data);
};


#endif //HUFF_MINHEAP_H
