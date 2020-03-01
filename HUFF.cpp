//
// Created by Carlos Galo on 2/29/20.
//

#include "HUFF.h"
#include <fstream> //To read and write files
HUFF::HUFF()
{
    root = NULL;

    freqTable = new sortedLL;
};

HUFF::~HUFF()
{
    /*Destructor for HUFF class, as C++ does not have a garbage collection*/
    delete freqTable;
}
/*sortedLL* HUFF::buildFreqTable(std::string inputFile)
{
    std::ifstream file (inputFile, std::ios::in | std::ios::binary);    //Read the file as binary
    if (!file)      //If file is not found or unable to open
        std::cout << "Error! File not found" << std::endl;  //Throw error
    else            //Else we could find and open the file
    {
        sortedLL* LL = new sortedLL;
        char tempChar;   //Create variable to read char by char of the file

        while (file >> std::noskipws >> tempChar)    //Loop through each character in the file
        {
            LL->insert(tempChar);
        }   //End of while-loop
        //LL->printLL();
        std::cout << "Length: " << LL->getLength() << std::endl;
        return LL;
    }   //End of else, if we could find and open the file
}*/

void HUFF::buildFreqTable(std::string inputFile)
{
    /* Objective: Open and read the input file and save it into sortedLL object as a frequency table
     * Cases:
     *  1. File does not open then output error message
     *  2. File opens and we read char by char and insert it into the freqTable
     *  */
    std::ifstream file (inputFile, std::ios::in | std::ios::binary);    //Read the file as binary
    if (!file)      //If file is not found or unable to open
        std::cout << "Error! File not found" << std::endl;  //Throw error
    else            //Else we could find and open the file
    {
        char tempChar;   //Create variable to read char by char of the file
        while (file >> std::noskipws >> tempChar)    //Loop through each character in the file
        {
            freqTable->insert(tempChar);
        }   //End of while-loop
        freqTable->printLL();
        std::cout << "Length: " << freqTable->getLength() << std::endl;
    }   //End of else, if we could find and open the file
}   //End of buildFreqTable method

void HUFF::EncodeFile(std::string inputFile, std::string outputFile)
{
    std::cout << "InputFile: " << inputFile << std::endl;
    buildFreqTable(inputFile);  //Build the frequency table from the file
    if (!freqTable->isEmpty())  //If there were no issues reading the file
    {

    }   //End of if the freqTable was build
    else                        //Else there was an error opening/reading the file
        return;                 //Exit the method
}



void HUFF::DecodeFile(std::string inputFile, std::string outputFile)
{

}

void HUFF::MakeTreeBuilder(std::string inputFile, std::string ouputFile)
{

}

void HUFF::DisplayHelp()
{
    std::cout << "\nList of commands:" << std::endl;

    //List cmd options inside the program
    //Help information
    std::cout << "-h, -?, -help"	<< "\t\t\tShow this help message and exit" << std::endl;
    //Encode information
    std::cout << "-e file1 [file2]" << "\t\tEnconde file1 placing the output into file2" << std::endl;
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
}