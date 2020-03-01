//
// Created by Carlos Galo on 2/26/20.
//


/////Work on testing this class with Nodes and their weight to build a Huffman MinHeap


#include "MinHeap.h"
#include <iostream>
MinHeap::MinHeap()
{
    capacity = maxLength;
    currentSize = 0;
    array = new int[capacity];
}   //End of constructor

void MinHeap::insertKey(int data)
{
    currentSize++;  //Increase the size of the heap
    int i = currentSize - 1;
    array[i] = data;
    while (i != 0 && array[parent(i)] > array[i])
    {
        swap(&array[i], &array[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::decreaseKey(int i, int new_val)
{
    array[i] = new_val;
    while (i != 0 && array[parent(i)] > array[i])
    {
        swap(&array[i], &array[parent(i)]);
        i = parent(i);
    }
}

int MinHeap::extractMin()
{
    if (currentSize <= 0)
        return 0;
    else if (currentSize == 1)
    {
        currentSize--;
        return array[0];
    }
    else
    {
        int root = array[0];
        array[0] = array[currentSize - 1];
        currentSize--;
        heapify(0);
    }

}

void MinHeap::heapify(int i)
{
    int l =  left(i);
    int r = right(i);
    int smallest = i;
    if (l < currentSize && array[l] <  array[i])
        smallest = 1;
    if (r < currentSize && array[r] < array[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&array[i], &array[smallest]);
        heapify(smallest);
    }
}

void MinHeap::swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void MinHeap::print()
{
    for (int i = 0; i < maxLength; i++)
        std::cout << array[i] << std::endl;
}