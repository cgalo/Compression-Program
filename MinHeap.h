/*
 * Author: Carlos Galo
 * File: MinHeap.h
 * Created: 03/10/2020
 * Objective: This file was created in order to have a priority queue and create the HuffMan Tree with Huffman Codes
 * Notes:
 *  -This is the header file for the MinHeap class
 *  -Gets called only from the HUFF class
 * */

#ifndef HUFF_MINHEAP_H
#define HUFF_MINHEAP_H

#include <iostream>     //To utilize "cout" & "cin"
#include <string>       //to utilize strings

#define maxSize 256     //Max size for the array/heap of unique characters

class MinHeap {
private:
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

    unsigned int frequencies[maxSize] = {0};    //Create an array to keep track of the frequency of the symbols
    Node** array;       //Array of nodes for the heap
    int size;           //Keep track of the size of the heap
    Node* HUFFRoot;     //The top of the huffman tree

    void insert(Node* insertNode);          //Insert node into the heap array
    void swap(Node** left, Node **right);   //Swap the left node with the right node in the heap
    void heapify(int index);                //Helper function to maintain the order in the heap/array
    Node* popMin();                         //Get the first node in the array
    void createCodes(MinHeap::Node *node, std::string &code, std::string *codeBook); //Create an array of codes with the huff tree
public:
    MinHeap();          //Constructor
    ~MinHeap();         //Destructor, for garbage collection

    void buildHuff (unsigned int table[]);  //Build a huffman tree with the given frequency table
    std::string *getCodes();                //Method calls printCodes to collect the codes of the HuffTree
};


#endif //HUFF_MINHEAP_H
