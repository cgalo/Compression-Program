/*
 * Author: Carlos Galo
 * File: MinHeap.cpp
 * Created: 03/10/2020
 * Notes:
 *  -This is the source file for the MinHeap class
 *  -Gets called only from the HUFF class
 * */

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
    /* Swap private method, parameter(s): struct Node, struct Node
     * Objective: Swap node left with node right without moving their data in the array
     * */

    Node* oldLeft = *left;  //Remember the left node before any swap
    *left = *right;         //Insert the right node where left is
    *right = oldLeft;       //Insert the oldLeft into the right node
}   //End of swap method

void MinHeap::insert(MinHeap::Node *insertNode)
{
    /* Insert private method, parameter(s): struct Node
     * Objective: Insert the given node into the heap while not breaking the heap rules
     * */

    size++;                 //Update the current size of the heap
    int index = size - 1;   //Get the index of the last node in the array before updating count
    while (index && insertNode->weight < array[(index - 1) / 2]->weight)
    {
        array[index] = array[(index - 1) / 2];
        index = (index - 1) / 2;
    }   //End of while-loop
    array[index] = insertNode;  //Insert the node into the array
}   //End of insert method

void MinHeap::heapify(int index)
{
    /* Heapify private method, parameter(s): int index
     * Objective: Rearrange the heap to maintain the heap property, keeping it from min to max depending on the
     *  weight of the nodes. This is done through recursion.
     * */

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
    /* popMin private Node method, parameter(s): None
     * Objective: Get & remove first node in the heap, make sure that the heap remains balance, and return the first node
     * Cases:
     *  1. The size is less then 0 then we return a nullptr
     *  2. Get the first min in the heap, call the heapify method, and return the min node
     * */

    if (size < 0)       //If the size of the heap is 0
        return nullptr; //Then return null
    else                //Else the size is not 0
    {
        Node* minNode = array[0];   //Get the first node in the heap
        array[0] = array[size - 1]; //Move a node in the array to the the top of the heap
        size--;                     //Update the count of the heap
        heapify(0);             //Call heapify method to check the heap property
        return minNode;             //Return the node
    }   //End of else
}   //End of popMin method

void MinHeap::createCodes(MinHeap::Node *node, std::string &code, std::string *codeBook)
{
    /* createCode private recursive method, parameter(s): Node, string code, string array codeBook
     * Objective: Traverse through the tree to fill out the huffman code per character and add it to the codeBook
     * Cases:
     *  1. If the node has a left-child then we add 0 to the code string and move to the LCH node
     *  2. If the node has a right-child then we add 1 to the code string and move to the RCH node
     *  3. Reached a leaf node, we add the current string code to the codeBook, using the current node data as index
     * */

    if (node->LCH)      //If the node has a left child
    {
        code += "0";    //Add 0 to the current code
        createCodes(node->LCH, code, codeBook);  //Recurse starting from the left child of the node
        code.erase(code.end()-1);
    }   //End of if the node has a LCH

    if (node->RCH)      //If the node has a right child
    {
        code += "1";    //Add 1 to the current code
        createCodes(node->RCH, code, codeBook);  //Recurse starting from the right child of the node
        code.erase(code.end()-1);
    }   //End of if the node has a RCH

    if (!node->LCH && !node->RCH)       //If we reached a leaf
        codeBook[node->data] = code;    //Add the current code to the codeBook array
}   //End of printCodes

void MinHeap::buildHuff(unsigned int *table)
{
    /* buildHuff public method, parameter(s): unsigned int array
     * Objective: build a huffman tree with the given frequency table
     * */

    for (int i = 0; i < maxSize; i++)   //Loop through the table to insert populated values
    {
        if (table[i])                   //If there is a value in this index
        {
            frequencies[i] = table[i];  //Copy the values of the given table to the frequency table in the minHeap
            array[size] = new Node((unsigned char) i, table[i]);   //Insert new node into the heap array
            size++;                     //Update the size of the heap
        }   //End of if there is a value in the current
    }   //End of for-loop, finished pushing all the data into the heap

    //BuildMinHeap
    int n = size - 1;   //Get the last node index in the heap
    for (int index = (n - 1) / 2; index >= 0; index--)
        heapify(index);

    //We get here if we inserted everything from the table into the heap
    //Now we need to create the HuffTree
    while (size > 1)                    //Iterate the heap until there is only one node in it
    {
        Node* leftChild     = popMin();         //Get the current top of the heap & save it as left child node
        Node* rightChild    = popMin();         //Get the current top of the heap & save it as right child node

        //Create a parent node that has no data, but the added weight of left and right children
        Node* parent = new Node(leftChild->weight + rightChild->weight);
        parent->LCH = leftChild;    //Set the left node as the parent's LCH
        parent->RCH = rightChild;   //Set the right node as the parent's RCH

        insert(parent);             //Insert the parent node into the heap
    }   //End of while-loop
    HUFFRoot = popMin();        //Get the last node of the heap and set it as root of the HUFF Tree
}   //End of constructHeap method

std::string * MinHeap::getCodes()
{
    /* getCodes public method, parameter(s): None
     * Objective: Build the huffman codes using the huffman tree, return array of strings containing the codes
     * */

    std::string codeBook[maxSize], currentCode;         //Create an array of strings and an empty string
    createCodes(HUFFRoot, currentCode, codeBook);   //Build the code book with the huffman tree
    return codeBook;                                    //Return the filled code book
}   //End of getCodes method
