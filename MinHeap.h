//
// Created by Carlos Galo on 2/26/20.
//

#ifndef HUFF_MINHEAP_H
#define HUFF_MINHEAP_H

#include "sortedLL.h"
#include "iostream"
#include <cstring>
#define maxSize 256     //Max size for the array/heap of unique characters


class MinHeap {
private:
    //std::string codeBook[maxSize];
    //unsigned char book [maxSize][8]; //Create a 2D array for each char, with maximum length of 8
    struct Node
    {
        std::string code[8];
        unsigned char data;
        int weight;
        Node *LCH, *RCH;
        Node(unsigned char data, int weight)
        {
            this->data = data;
            this->weight = weight;
            LCH = RCH = nullptr;
        }
        Node (int weight)
        {
            this->weight =  weight;
            data = '\0';
            LCH = RCH = nullptr;
        }
    };  //End of struct Node
    Node** array;       //Array of nodes for the heap
    int size;  //Keep track of the size of the heap
    Node* HUFFRoot;     //The top of the huffman tree

    void insert(Node* insertNode);          //Insert node into the heap array
    void swap(Node** left, Node **right);   //Swap the left node with the right node in the heap
    void heapify(int index);                //Helper function to maintain the order in the heap/array
    Node* popMin();                         //Get the first node in the array
    void printArr(int arr[], int length);    //Print the given array data
    void printCodes(Node* node, int codes[], int length);

public:
    MinHeap();          //Constructor
    ~MinHeap();         //Destructor, for garbage collection

    void push(unsigned char data, int weight);
    void buildHuff (unsigned int table[]);
    void getCodes();

};


#endif //HUFF_MINHEAP_H
