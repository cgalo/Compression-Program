#include "sortedLL.h"
//
// Created by Carlos Galo on 2/26/20.
//

#include "sortedLL.h"

sortedLL::sortedLL()    //Constructor
{
    head = NULL;
    length =  0;
}   //End of constructor

sortedLL::~sortedLL()
{
    if (head != NULL)   //If the tree is not empty
    {
        Node* currentNode = head;
        while (currentNode != NULL)
        {
            Node* nextNode = currentNode->next;    //Save the pointer to the next node
            delete currentNode;                    //Garbage collection on the current node
            currentNode = nextNode;                //Move to the next node
        }   //End of while-loop
        head = NULL;                                //Set the head pointer back to NULL
    }   //End of if the tree is not empty
}   //End of destructor

int sortedLL::getLength(){ return length;}

bool sortedLL::isEmpty() { return (head == NULL) ? true : false; }

sortedLL::Node* sortedLL::search(char c)
{
    Node* currentNode = head;   //Start from the head of the LL

    while (currentNode != NULL) //Traverse through the LL to find Node w/ given char
    {
        if (currentNode->data == c) //If the current node has the char
            return currentNode;     //Return the node
        else                        //Else the current node doesn't have the char
            currentNode = currentNode->next;    //Move to the next node in the LL
    }   //End of while-loop
    //We are here if we never found a node with the char
    return NULL;    //Return NULL
}   //End of sorted method

void sortedLL::insert(char c)
{
    if (isEmpty())  //If the LL is empty
    {
        head = new Node(c); //Insert a new node in the head
        length++;           //Increase the length of the LL
    }   //End of if the LL is empty
    else            //Else the tree is not empty
    {
        Node* searchNode = search(c);   //Search for node with given char
        if (searchNode != NULL)         //If the search found a node w/ the char
        {
            searchNode->count++;        //Increase the count/frequency of the node

            sortLL();                   //Call the sort method
        }   //End of if the search found a node
        else                            //Else there was  no node w/ the char
        {
            Node* newHead = new Node(c);//Create a new node to insert as new head
            newHead->next = head;       //Connect the newHead to the current head of the LL
            head = newHead;             //Change the head pointer to the newHead node
            length++;                   //Increase the length of the LL
        }   //End of else, if there was no node
    }   //End of else, the tree is not empty
}   //End of insert method

void sortedLL::sortLL()
{
    ////This method is called after updating the count of a node in the LL
    /*Objective: Move the updated node into the right position in the LL
     */
    Node* currentNode = head;   //Start from the head of the LL

    Node* prevNode = NULL;      //Keep track of the last node as we traverse the LL
    while (currentNode->next != NULL)    //Traverse until the end of the LL
    {
        Node* nextNode = currentNode->next;
        //If our current node has a greater count than the next node, then we swap them
        if (currentNode->count > nextNode->count)
        {
            //Check value of prevNode to check if current node is the head
            if (currentNode == head)
                head = nextNode;
            else
                prevNode->next = nextNode;

            Node* newNext = currentNode;
            Node* oldNext = nextNode;
            newNext->next = oldNext->next;
            oldNext->next = newNext;
            prevNode = oldNext;
        }   //End of if current node count is greater than the next node
        //Else the current node count is >= to the next node's count
        else
        {
            prevNode = currentNode;         //Update the prevNode before moving
            currentNode = currentNode->next;//Move to the next node
        }   //End of else, if the currentNode count is less than or equal to the next node
    }   //End of the while-loop, finished traversing the tree
}   //End of sortLL method

void sortedLL::printLL()
{
    if (isEmpty())                  //If the LL is empty
        std::cout << std::endl;     //Output empty line
    else                            //Else the LL is not empty
    {
        Node* currentNode = head;   //Get the head pointer to traverse the LL
        while (currentNode != NULL) //Traverse until we reach the end of the LL
        {
            std::cout << currentNode->data << ": " << currentNode->count << std::endl;  //Output node info
            currentNode = currentNode->next;    //Move to the next node in the LL
        }   //End of while-loop, finished traversing the LL
    }   //End of else, the tree is not empty
}   //End of printLL method

sortedLL::Node* sortedLL::min()
{
    return head;
}

sortedLL::Node * sortedLL::returnMin()
{
    return min();
}

void sortedLL::deleteMin()
{
    Node* min = head;   //Get the first node in the LL
    if (min != NULL)
        head = min->next;
    length--;           //Subtract one unit from the total length of the LL
    delete min;
}
