//
// Created by Carlos Galo on 2/29/20.
//

#ifndef HUFF_HUFF_H
#define HUFF_HUFF_H

#include "MinHeap.h"    //Call the MinHeap header file

#define maxSize 256
class HUFF {
private:

    unsigned int frequencies[maxSize] = {0};
    int fileSize;


    bool buildFreqTable(std::string &inputFile); //Opens and reads file char by char and inserts it into freqTable
    std::string getFinalConfig(std::string &inputFile, std::string* codeBook);
    void writeEncodeFile(std::string &outputFile, std::string *codeBook, std::string& finalConfig);
    void writeTreeBuilderFile(std::string &outputFile, std::string* codeBook, std::string& finalConfig);

    unsigned int getFileSize(std::ifstream &file);

    std::string ByteToString(unsigned char readingByte);    //Convert given byte to string
    unsigned char StringToByte(std::string str);            //Convert byte to string
public:
    HUFF();     //Constructor
    ~HUFF();    //Destructor, for garbage-collection

    //Five different modes available
    void EncodeFile(std::string inputFile, std::string outputFile); //Creates an encoded file
    void DecodeFile(std::string inputFile, std::string outputFile); //Decodes an encoded file
    void MakeTreeBuilder(std::string inputFile, std::string outputFile);    //Creates a 510-byte file with frequency table in it
    void EncodeFileWithTree(std::string inputFile, std::string TreeFile, std::string outputFile);
    void DisplayHelp();     //Outputs cmd options with description



};

#endif //HUFF_HUFF_H
