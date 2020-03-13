#include "MinHeap.h"
//
// Created by Carlos Galo on 2/26/20.
//

#include "MinHeap.h"

MinHeap::MinHeap()
{
    /* Basic constructor for the MinHeap*/
    size = 0;                       //Set the current size to 0
    array = new Node* [maxSize];    //Create array of size
    HUFFRoot = nullptr;                //Set the root for the HUFF as NULL
}   //End of constructor

MinHeap::~MinHeap()
{
    /* Destructor for garbage collection, as C++ doesn't have its own*/
    delete array;
    delete HUFFRoot;
    size = 0;
}   //End of destructor

void MinHeap::swap(MinHeap::Node **left, MinHeap::Node **right)
{
    /*Objective: Swap node left with node right without moving their data in the array*/
    Node* oldLeft = *left;  //Remember the left node before any swap
    *left = *right;         //Insert the right node where left is
    *right = oldLeft;       //Insert the oldLeft into the right node
}   //End of swap method

void MinHeap::insert(MinHeap::Node *insertNode)
{
    size++;                 //Update the current size of the heap
    int index = size - 1;   //Get the index of the last node in the array before updating count
    while (index && insertNode->weight < array[(index - 1) / 2]->weight)
    {
        array[index] = array[(index - 1) / 2];
        index = (index - 1) / 2;
    }   //End of while-loop
    array[index] = insertNode;  //Insert the node into the array
}   //End of insert method

void MinHeap::push(unsigned char data, int weight)
{
    if (size >= maxSize)        //If the size of the array has reached or passed the max capable size of the heap
        std::cout << "Error! Overflow in the heap" << std::endl;    //Output error
    else                        //Else the size is below the max size so we can insert a new node into the heap
        insert(new Node (data, weight));    //Call the insertion method by passing the given parameters
}   //End of push method

void MinHeap::heapify(int index)
{
    /* Heapify private method, parameter(s): int index
     * Objective: Rearrange the heap to maintain the heap property, keeping it from min to max depending on the
     *  weight of the nodes. This is done through recursion.*/

    int newIndex = index;       //Remember the index before moving it
    int left = 2 * index+ 1;    //Get the left child of the index in the array
    int right = 2 * index + 2;  //Get the right child of the index in the array

    if (left < size && array[left]->weight < array[newIndex]->weight)
        newIndex = left;

    if (right < size && array[right]->weight < array[newIndex]->weight)
        newIndex = right;

    if (newIndex != index)
    {
        swap(&array[newIndex], &array[index]);
        heapify(newIndex);
    }
}   //End of heapify method

MinHeap::Node* MinHeap::popMin()
{
    if (size < 0)      //If the size of the heap is 0
        return nullptr;    //Then return null
    else                //Else the size is not 0
    {
        Node* minNode = array[0];   //Get the first node in the heap
        array[0] = array[size - 1]; //Move a node in the array to the the top of the heap
        size--;                     //Update the count of the heap
        heapify(0);             //Call heapify method to check the heap property
        return minNode;             //Return the node
    }   //End of else
}   //End of popMin method

void MinHeap::printArr(int *arr, int length)
{
    for (int i = 0; i <  length; i++)
        std::cout << arr[i];
}

void MinHeap::printCodes(MinHeap::Node *node, int *codes, int length)
{
    if (node->LCH)
    {
        codes[length] = 0;
        printCodes(node->LCH, codes, length + 1);
    }
    if (node->RCH)
    {
        codes[length] = 1;
        printCodes(node->RCH, codes, length + 1) ;
    }
    if (!node->LCH && !node->RCH)
    {
        std::cout << node->data << ": ";
        printArr(codes, length);
        std::cout << std::endl;
    }
}


void MinHeap::buildHuff(unsigned int *table)
{
    std::cout << "Size: " << size << std::endl;
    for (int i = 0; i < maxSize; i++)   //Loop through the table to insert populated values
    {
        if (table[i])                   //If there is a value in this index
        {

            array[size] = new Node((char) i, table[i]);   //Insert new node into the heap array
            size++;                     //Update the size of the heap
        }
    }   //End of for-loop, finished pushing all the data into the heap

    //BuildMinHeap
    int n = size - 1;   //Get the last node index in the heap
    for (int index  = (n - 1) / 2; index >= 0; index--)
        heapify(index);
    for (int i = 0; i < size; i++)
        std::cout << array[i]->data << ": " << array[i]->weight << std::endl;

    //We get here if we inserted everything from the table into the heap
    //Now we need to create the HuffTree
    while (size > 1)                    //Iterate the heap until there is only one node in it
    {
        Node* leftChild     = popMin();         //Get the current top of the heap & save it as left child node
        Node* rightChild    = popMin();         //Get the current top of the heap & save it as right child node

        //Create a parent node that has no data, but the added weight of left and right children
        Node* parent = new Node(leftChild->weight + rightChild->weight);
        parent->LCH = leftChild;     //Set the left node as the parent's LCH
        parent->RCH = rightChild;    //Set the right node as the parent's RCH

        insert(parent);         //Insert the parent node into the heap

        std::cout << "Left: " << leftChild->data << ", " << leftChild->weight<< std::endl;
        std::cout << "Right: " << rightChild->data << ", " << rightChild->weight << std::endl;
        std::cout << "Parent: " << parent->data << ", " << parent->weight << std::endl;
    }   //End of while-loop
    HUFFRoot = popMin();        //Get the last node of the heap and set it as root of the HUFF Tree
    std::cout << "Root: " << HUFFRoot->data << ", " << HUFFRoot->weight << std::endl;
}   //End of constructHeap method


void MinHeap::getCodes()
{
    int arr[maxSize], top = 0;
    printCodes(HUFFRoot, arr, top);
}
