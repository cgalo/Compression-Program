//
// Created by Carlos Galo on 2/26/20.
//

#ifndef HUFF_MINHEAP_H
#define HUFF_MINHEAP_H


/////Work on testing this class with Nodes and their weight to build a Huffman MinHeap

const int maxLength = 256;

class MinHeap {
private:
    int *array;
    int capacity;
    int currentSize;
    void swap(int *x, int *y);
    int parent(int i) { return (i-2/2);}
    int left(int i){return (2*i + 1); }
    int right(int i){return (2*i + 2);}

    void heapify(int i);
public:
    MinHeap();
    ~MinHeap();
    void insertKey(int data);
    void decreaseKey(int i, int new_val);
    int extractMin();
void print();
};


#endif //HUFF_MINHEAP_H
