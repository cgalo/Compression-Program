//
// Created by Carlos Galo on 2/29/20.
//

#include "HUFF.h"
#include <fstream> //To read and write files
HUFF::HUFF()
{
    fileSize = 0;
    freqTable = new sortedLL;
};

HUFF::~HUFF()
{
    /*Destructor for HUFF class, as C++ does not have a garbage collection*/
    delete freqTable;
}
void HUFF::buildFreqTable(std::string &inputFile)
{
    /* Objective: Open and read the input file and save it into sortedLL object as a frequency table
     * Cases:
     *  1. File does not open then output error message
     *  2. File opens and we read unsigned char by unsigned char and insert it into the freqTable
     *  */
    std::ifstream file (inputFile, std::ios::in | std::ios::binary);    //Read the file as binary
    if (!file)      //If file is not found or unable to open
        std::cout << "Error! File not found" << std::endl;  //Throw error
    else            //Else we could find and open the file
    {
        unsigned char tempChar;   //Create variable to read unsigned char by unsigned char of the file

        while (file >> std::noskipws >> tempChar)    //Loop through each unsigned character in the file
        {
            frequencies[tempChar]++;
            freqTable->insert(tempChar);             //Save the current unsigned char in the freqTable
        }

        file.close();   //Close the file
    }   //End of else, if we could find and open the file
}   //End of buildFreqTable method

void HUFF::EncodeFile(std::string &inputFile, std::string &outputFile)
{
    std::cout << "In here" << std::endl;
    std::cout << "InputFile: " << inputFile << std::endl;
    buildFreqTable(inputFile);  //Build the frequency table from the file
    if (!freqTable->isEmpty())  //If there were no issues reading the file
    {
        MinHeap* huffTree = new MinHeap;
        huffTree->buildHuff(frequencies);
        huffTree->getCodes();
    }   //End of if the freqTable was build
    else                        //Else there was an error opening/reading the file
        return;                 //Exit the method
}   //End of EncodeFile method

void HUFF::DecodeFile(std::string &inputFile, std::string &outputFile)
{
    /* Objective: Decode Huffman-encoded file1 into file2.
     * */
}

void HUFF::MakeTreeBuilder(std::string &inputFile, std::string &outputFile)
{

}

void HUFF::EncodeFileWithTree(std::string &inputFile, std::string &TreeFile, std::string &outputFile)
{

}

void HUFF::DisplayHelp()
{
    /* Objective: Display list of commands and information of the HUFF class to be called in main
     * */
    std::cout << "\nList of commands:" << std::endl;

    //List cmd options inside the program
    //Help information
    std::cout << "-h, -?, -help"	<< "\t\t\tShow this help message" << std::endl;
    //Encode information
    std::cout << "-e file1 [file2]" << "\t\tEncode file1 placing the output into file2" << std::endl;
    //Decode information
    std::cout << "-d file1 file2"	<< "\t\t\tDecode Huffman-encoded file1 into file2" << std::endl;
    //Tree build creation information
    std::cout << "-t file1 [file2]" << "\t\tRead file1 and use the information in it to" << std::endl;
    std::cout << "\t\t\t\t\t\tproduce a 510-byte tree-builder file named file2" << std::endl;
    //Specific Tree Builder information
    std::cout << "-et file1 file2 [file3]" << "\tRead input from file1, and, rather than building a tree from the "
                                              "contents of file1," << std::endl;
    std::cout << "\t\t\t\t\t\tencode  it  usinga  tree  built  fromthe  510-byte  tree-builder  information  in "
                 "file2," << std::endl;
    std::cout<< "\t\t\t\t\t\tproducing file3" << std::endl;
    //Exit cmd
    std::cout << "-exit, -end" << "\t\t\t\tTerminate program" << std::endl; //Exit

    std::cout << std::endl; //Give a line of difference for the user to enter their cmd
}   //End of DisplayHelp method