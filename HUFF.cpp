//
// Created by Carlos Galo on 2/29/20.
//

#include "HUFF.h"
HUFF::HUFF()
{
    root = NULL;
    for (int i = 0; i < maxSize; i++)
        array[i] = NULL;

};

void HUFF::displayHelp()
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