//
// Created by Carlos Galo on 2/26/20.
//

#ifndef HUFF_SORTEDLL_H
#define HUFF_SORTEDLL_H

#include <iostream>

class sortedLL {
private:
    struct Node
    {
        char data;
        int count;
        Node* next;
        Node (char data)    //Constructor
        {
            this->data = data;
            count = 1;
            next = NULL;
        }   //End of Node construct
    };  //End of struct node
    Node *head;
    int length;
    void sortLL();
    Node* search(char c);
    Node* min();
public:
    sortedLL();             //Constructor
    ~sortedLL();            //Destructor, garbage collection
    int getLength();        //Return the current length of the LL
    bool isEmpty();         //Return true if head is NULL, else return false
    void insert (char c);   //Insert a new node in the LL, or update count if node already exist with the give char
    void printLL();         //Print all nodes' data &  count in the LL
    Node* returnMin();
    void deleteMin();


};


#endif //HUFF_SORTEDLL_H
