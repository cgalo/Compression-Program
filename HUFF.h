//
// Created by Carlos Galo on 2/29/20.
//

#ifndef HUFF_HUFF_H
#define HUFF_HUFF_H

#include "sortedLL.h"   //Call the self-sorted Linked-List header file
#include "MinHeap.h"    //Call the MinHeap header file
#include <string>
#define maxSize 256
class HUFF {
private:

    sortedLL* freqTable;
    unsigned int frequencies[maxSize] = {0};
    int fileSize;

    void buildFreqTable(std::string &inputFile); //Opens and reads file char by char and inserts it into freqTable
    //MinHeap* buildHuffTree();
public:
    HUFF();     //Constructor
    ~HUFF();    //Destructor, for garbage-collecion


    //Five different modes, these are called from the main.cpp
    void EncodeFile(std::string &inputFile, std::string &outputFile);
    void DecodeFile(std::string &inputFile, std::string &outputFile);
    void MakeTreeBuilder(std::string &inputFile, std::string &outputFile);
    void EncodeFileWithTree(std::string &inputFile, std::string &TreeFile, std::string &outputFile);
    void DisplayHelp();     //Outputs cmd options with description



};/*
//Get the file size
file.seekg(0, std::ios::beg);
int start = file.tellg();
file.seekg(0, std::ios::end);
int stop  = file.tellg();
file.seekg(0, std::ios::beg);
fileSize = stop - start;
//Finish calculating file size
std::cout << "File Size: " << std::endl;*/

#endif //HUFF_HUFF_H
