//
// Created by Carlos Galo on 2/26/20.
//

#include "MinHeap.h"

MinHeap::MinHeap()
{
    capacity = maxLength;
    currentSize = 0;
    array = new int[capacity];
}   //End of constructor

void MinHeap::insertHeap(int data)
{
    currentSize++;  //Increase the size of the heap
    int i = currentSize - 1;
    array[i] = data;
    while (i != 0 && array[parent(i)] > array[i])
}