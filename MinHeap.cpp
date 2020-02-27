//
// Created by Carlos Galo on 2/26/20.
//

#include "MinHeap.h"

MinHeap::MinHeap()
{
    capacity = maxLength;
    currentSize = 0;
    array = new int[capacity];
}