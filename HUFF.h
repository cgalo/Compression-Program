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
        Node(char data)
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
    };
    Node** array;
    Node* root;
public:
    HUFF();
    ~HUFF();

    void EncodeFile(std::string inputFile, std::string outputFile);
    void DecodeFile(std::string inputFile, std::string outputFile);
    void MakeTreeBuilder(std::string inputFile, std::string ouputFile);
    void DisplayHelp();

};


#endif //HUFF_HUFF_H
