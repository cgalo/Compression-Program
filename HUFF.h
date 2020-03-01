//
// Created by Carlos Galo on 2/29/20.
//

#ifndef HUFF_HUFF_H
#define HUFF_HUFF_H

#include "sortedLL.h"   //Call the self-sorted Linked-List header file
#include <string>

const int maxSize = 256;    //ASCII max characters

class HUFF {
private:
    struct Node
    {
        unsigned char data;
        int weight;
        Node *LCH, *RCH, *parent;
        Node (): data('\0'), weight(0), LCH(NULL), RCH(NULL), parent(NULL){}
        Node(unsigned char data)
        {
            this->data = data;
            weight = 1;
            LCH = RCH = parent = NULL;
        }
        Node (int weight)
        {
            data = '\0';
            this->weight = weight;
            LCH = RCH = parent = NULL;
        }
    };  //End of struct Node
    //Node** array;
    Node* root;                                 //The top of the tree
    sortedLL* freqTable;
    int fileSize;

    void buildFreqTable(std::string inputFile); //Opens and reads file char by char and inserts it into freqTable
    void buildHuffTree();
public:
    HUFF();
    ~HUFF();

    void EncodeFile(std::string inputFile, std::string outputFile);
    void DecodeFile(std::string inputFile, std::string outputFile);
    void MakeTreeBuilder(std::string inputFile, std::string ouputFile);
    void DisplayHelp();


};


#endif //HUFF_HUFF_H
