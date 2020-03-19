//
// Created by Carlos Galo on 2/29/20.
//

#include "HUFF.h"
#include <fstream> //To read and write files

HUFF::HUFF()
{
    fileSize = 0;
}   //End of constructor

HUFF::~HUFF()
{
    /*Destructor for HUFF class, as C++ does not have a garbage collection*/
    fileSize = 0;
    memset(frequencies, 0, sizeof(frequencies));    //Reset the frequency table
}   //End of destructor

bool HUFF::buildFreqTable(std::string &inputFile)
{
    /* Objective: Open and read the input file and save the frequency of each symbol in frequency array
     * Cases:
     *  1. File does not open then output error message. return false
     *  2. File opens and we read unsigned char by unsigned char and  insert it into the freqTable, return true
     *  */

    std::ifstream file (inputFile, std::ios::in | std::ios::binary);    //Read the file as binary
    if (!file)     //If file is not found or unable to open
        return false;   //Return false as we were not able to open/locate the file in the directory
    else                //Else we could find and open the file
    {
        unsigned char tempChar;   //Create variable to read unsigned char by unsigned char of the file

        while (file >> std::noskipws >> tempChar)   //Loop through each unsigned character in the file
            frequencies[tempChar]++;                //Update the count in the frequency

        file.close();   //Close the file, as we finished reading every byte in it
        return true;    //Return true as we were able to open the file and save the frequency of the symbols
    }   //End of else, if we could find and open the file
}   //End of buildFreqTable method

unsigned int HUFF::getFileSize(std::ifstream &file)
{
    file.seekg(0,file.end); //Move to the end of file
    unsigned int fileSize = file.tellg();    //Get the size of the file
    file.seekg(0,file.beg); //Go back to the beginning of the file
    return fileSize;
}

std::string HUFF::getFinalConfig(std::string &inputFile, std::string* codeBook)
{
    /* getFinalConfig private method parameter(s): string inputFile name, string pointer to codeBook
     * Objective: Open the file, read char by char, get the corresponding code from the codebook and append
     *  to the local finalConfig string, return the string after reading the whole file
     *  Cases:
     *      1. Error opening the file, output error, and return empty string
     *      2. We were able to open & read the file, return the finalConfig
     * */

    std::string finalConfig;    //Start with an empty string before appending any characters as we read the file
    std::ifstream readFile (inputFile, std::ios::in | std::ios::binary);    //Read the file as binary
    if (!readFile)              //If there was an issue opening the file
        std::cout << "Error! Could not open/read file: " << inputFile << std::endl;
    else
    {
        unsigned char tempChar;     //Create empty char to save each byte in the file as we loop through it
        while (readFile >> std::noskipws >> tempChar)   //Loop through each unsigned character in the file
            finalConfig += codeBook[(int)tempChar];     //Append the corresponding code to the char in the string
        readFile.close();   //Close the file after reading through it
    }   //End of else, if we were able to open the file successfully
    return finalConfig;
}   //End of getFinalConfig method

std::string HUFF::ByteToString(unsigned char readingByte)
{
    std::string readingString;  //Initiate string to return the final
    for (int i = 0; i < 8; i++)
    {
        unsigned char mask = 1; //Right-most bit
        if (readingByte & (mask << i))
            readingString = '1' + readingString;    //Insert 1 in the beginning of the string
        else
            readingString = '0' + readingString;    //Insert 0 in the beginning of the string
    }   //End of for-loop
    return readingString;
}   //End of getReadingByteString

unsigned char HUFF::StringToByte(std::string str)
{
    /* Convert the bits of string into unsigned char (byte)
     * */

    int count = 0;
    unsigned char returnChar = 0;
    for (int i = 7; i > 0; i--)
    {
        unsigned char mask = 1;
        if (str[i] == '1')
            returnChar = mask << count;
        count++;
    }
    return returnChar;
}

void HUFF::writeEncodedFile(std::string &outputFile, std::string *codeBook, std::string &finalConfig)
{
    /* writeEncodedFile private method, parameter(s): string output file, string array codeBook, string finalConfig
     * Objective: Insert frequency table, and finalConfig into a new file (output file).
     * */

    std::ofstream outFile (outputFile, std::ios::out | std::ios::binary);  //Write to the file in binary

    if (!outFile)       //If there is an issue creating/opening the output file
        std::cout << "Error creating new Encoding file" << std::endl;   //Output error

    else                //Else there was no issue creating/opening the output file
    {
        int totInsert = 0;                  //Keep track of total inserted pairs into the file
        for (int i = 0; i < maxSize; i++)   //Insert all the values inside the frequency table
        {
            if (frequencies[i]) //If there is a value inside of the current index of the array
            {
                int freqVal = frequencies[i];       //Save the current frequency
                unsigned char freqChar;             //Initiate unsigned char to move the freqVal
                freqChar = (unsigned char) freqVal; //Save the current frequency as unsigned char

                outFile.put((unsigned char) i);     //Insert the symbol byte into the file
                outFile.put((unsigned char)freqChar);//Insert the frequency byte into the file
                totInsert += 2;                     //Update the count of total pairs inserted in the loop
            }   //End of if the frequency has a value
        }   //End of for-loop
        if (totInsert < maxSize)            //If we did not fill the 510 bytes of the frequency table
        {                                   //Then we need to insert empty pairs into the file
            for ( totInsert; totInsert < 510; totInsert++)   //For-loop the rest of the 510 bytes with bytes of 0
                outFile.put((unsigned int) 0);    //Inserts unsigned char 0 through out as padding
        }   //End of the if the file was not filled with the 510 bytes

        //We get here after inserting the frequency table into the file, occupying the first 510 bytes
        //Now append the finalConfig into the



    }   //End of else, if there was no issue creating the output file
    /*
    int numberOfBytes = finalConfig.length()/8; //Need to check for rounding
    if (numberOfBytes == 0) numberOfBytes = 1;
    std::cout << "NuM:" << numberOfBytes << std::endl;
    float sizeOfPadding = finalConfig.length()/8;

    unsigned char myChar[numberOfBytes + 1];
    int byteIndex = 0;
    for(int i=0; i < finalConfig.length(); i+=8){

        std::string toWriteString = "";
        if (i + 8 < finalConfig.length())
            toWriteString = finalConfig.substr(i, i + 8);
        else
            toWriteString = finalConfig.substr(i, finalConfig.length());

        //
        unsigned char toWriteByte = 0;
        toWriteByte |= 0xAA;
        myChar[byteIndex] = toWriteByte;
    }
    for (int i = 0 ; i < numberOfBytes; i++)
        outFile.put(myChar[i]);
*/
    outFile.close();    //Close the file
}   //End of writeEncodeFile method

void HUFF::EncodeFile(std::string inputFile, std::string outputFile)
{
    if (buildFreqTable(inputFile))  //If there were no issues reading the file and building the array of frequencies
    {
        MinHeap* huffTree = new MinHeap;    //Initiate MinHeap object
        huffTree->buildHuff(frequencies);   //Build the huffman tree with the frequency of the symbols in the array
        std::string *codeBook = huffTree->getCodes();   //Get the codes from the tree

        //Check if the user provided an output file, if not then we use the input file name and add huff at the end
        if (outputFile.empty())             //If the user did not provide an output file name
            outputFile = inputFile.substr(0, inputFile.find('.')) + ".huf";

        std::string finalConfig = getFinalConfig(inputFile, codeBook);  //Get the string of codes for the file

        if (finalConfig.empty())    //If the string is empty then we had an issue opening the file
            return;                 //We have already output error message so we just exit the method
        else                        //Else the string is not empty, we have the finalConfig to write it to new file
            writeEncodedFile(outputFile, codeBook, finalConfig); //Write to the file

        //We are done with this cmd/method now just perform GC on our objects
        delete huffTree;    //Garbage collection on the MinHeap object
        memset(frequencies, 0, sizeof(frequencies));    //Reset the frequency table
    }   //End of if the freqTable was build
    else                        //Else there was an error opening/reading the file
        std::cout << "Error! Could not open file: " << inputFile << std::endl;  //Output error message
}   //End of EncodeFile method

void HUFF::DecodeFile(std::string inputFile, std::string outputFile)
{
    /* DecodeFile public method, parameter(s): string inputFile, string outputFile
     * Objective: Decode Huffman-encoded file1 into file2.
     * */

    std::ifstream file (inputFile, std::ios::in | std::ios::binary);
    if (!file)
        std::cout << "Error opening/reading file in decode file method" << std::endl;
    else
    {
        unsigned int fileSize = getFileSize(file);

        std::cout << "File Size: " << fileSize << std::endl;
        unsigned char fileBytes[fileSize];
        //First we need to get the first 510 bytes, which are pair values of characters and their frequency
        //std::string str;
        unsigned char tempVal;
        int totalBytes = 0;
        //Insert all the bytes from the file to the array
        while (file >> std::noskipws >> tempVal)    //Loop through each unsigned character in the file
        {
            fileBytes[totalBytes] = tempVal;        //Insert  the tempVal
            totalBytes++;
            //str = getReadingByteString(tempChar);
            //std::cout << "String value: " << str << std::endl;
        }
        std::cout << "Total Bytes: "  << totalBytes << std::endl;

        for (int i = 0; i < 510; i += 2)    //Get the frequency table from the file
        {
            unsigned char symbol = fileBytes[i];
            unsigned char syFreq = fileBytes[i+1];
            frequencies[symbol] = (unsigned int)syFreq;
        }   //End of for-loop
        //Print the frequency table
        for (int i = 0; i < maxSize; i++)
        {
            if (frequencies[i])
                std::cout << (char)i << ": " << frequencies[i] << std::endl;
        }
    }
}   //End of DecodeFile method

void HUFF::MakeTreeBuilder(std::string inputFile, std::string outputFile)
{
    /* MakeTreeBuilder public method, parameter(s): string inputFile, string outputFile
     * Objective: Read input file and use the information in it to produce a 510 byte tree-builder file as outputFile
     * Cases:
     *  1. No issue opening the input file, the frequency table was build successfully
     *      A. Build the huffman tree with the frequency table
     *      B. Get the huffman code from the huffman tree and save it into a string array
     *      C. Iterate through the file, replacing char-by-char with its corresponding huff code and append to string
     *          finalConfig
     *          -If there was an issue opening the file then getFinalConfig will output an error and return false
     *          -Else we call the writeTreeBuilder method to create the new TreeBuilder file
     *  2. There was an issue opening the input file, output error and exit the method
     * */


    MinHeap* huffTree = new MinHeap();  //Initiate huffman tree
    if (outputFile.empty()) //If the user did not provide an output
        outputFile = inputFile.substr(0, inputFile.find('.')) + ".htree";   //Use input file with new extension

    //Now we need to try to open the inputFile to read through it and create a frequency table
    if (buildFreqTable(inputFile))   //If there was no issue opening/reading the file
    {
        //Here we have the frequency table populated, we use it to build the huff tree
        huffTree->buildHuff(frequencies);   //Create the huff tree with the frequency table
        std::string* codeBook =huffTree->getCodes();    //Get the huffman codes and save it in a string array


        ////Switch finalConfig from string to char array as its breaking here with bigger files
        std::string finalConfig = getFinalConfig(inputFile, codeBook);  //Get the string equivalent of the file using the code book

        if (finalConfig.empty())    //If the string is empty then we had an issue opening the file
            return;                 //We have already output error message so we just exit the method
        else                        //Else the string is not empty, we have the finalConfig to write it to new file
            writeTreeBuilderFile(outputFile, codeBook, finalConfig);    //Create the Tree-Builder file
    }   //End of if we were able to open and build the frequency table successfully

    else                                //Else there was an error opening/reading the file
        std::cout << "Error! Could not open file: " << inputFile << std::endl;  //Output error message

    //We are done with this cmd/method now just perform GC on our objects
    delete huffTree;                    //Perform GC on the MinHeap object
    memset(frequencies, 0, sizeof(frequencies));    //Reset the frequency table
}   //End of MakeTreeBuilder method

void HUFF::writeTreeBuilderFile(std::string &outputFile, std::string *codeBook, std::string &finalConfig)
{
    /* WriteTreeBuilderFile private method, parameter(s): string outputFile, string array codeBook, string finalConfig
     * Objective: Create a new file, of size 510 bytes, containing the frequency table
     * */

    //First try to create the new output file
    std::ofstream outFile (outputFile, std::ios::out | std::ios::binary);  //Write to the file in binary

    if (outFile) //If there is no issue opening/creating the file
    {
        int totInsert = 0;                  //Keep track of total inserted pairs into the file
        for (int i = 0; i < maxSize; i++)   //Insert all the values inside the frequency table
        {
            if (frequencies[i]) //If there is a value inside of the current index of the array
            {
                int freqVal = frequencies[i];       //Save the current frequency
                unsigned char freqChar;             //Initiate unsigned char to move the freqVal
                freqChar = (unsigned char) freqVal; //Save the current frequency as unsigned char

                outFile.put((unsigned char) i);     //Insert the symbol byte into the file
                outFile.put((unsigned char)freqChar);//Insert the frequency byte into the file
                totInsert += 2;                     //Update the count of total pairs inserted in the loop
            }   //End of if the frequency has a value
        }   //End of for-loop

        if (totInsert < maxSize)            //If we did not fill the 510 bytes of the frequency table
        {                                   //Then we need to insert empty pairs into the file
            for ( totInsert; totInsert < 510; totInsert++)   //For-loop the rest of the 510 bytes with bytes of 0
                outFile.put((unsigned int) 0);    //Insert empty bytes for padding
        }   //End of the if the file was not filled with the 510 bytes
    }   //End of if no issues creating/opening the new file
    else                //Else there was an issue opening/creating the file
        std::cout << "Error! There was an issue creating file: " << outputFile << std::endl;    //Output error

}   //End of writeTreeBuilderFile method

void HUFF::EncodeFileWithTree(std::string inputFile, std::string TreeFile, std::string outputFile)
{

}

void HUFF::DisplayHelp()
{
    //Objective: Display list of commands and information of the commands

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