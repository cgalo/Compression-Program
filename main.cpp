#include <iostream>
#include "MinHeap.h"
#include "HUFF.h"

void interface      (std::string &cmd, std::string &input, HUFF* huff);    //Declaring the menu function
std::string getWord (std::string line, int wordIndex);      //Declaring getWord function
bool checkWord      (std::string &word);                     //Declaring checkWord function

const char filePath [] = "/Users/cgalo/CLionProjects/Compression-Program/DSC_0113.NEF.jpg";


int main()
{
    HUFF * huff = new HUFF; //Initiate the huff object
    while (true)
    {
        std::string input;  //Create string to accept the input of the user
        std::cout<< "";
        std::getline (std::cin, input); //Get the whole input of the user
        //Now we need to split the input to get the cmd and the word we want to store
        std::string strHuff = getWord(input, 1);    //Get the first word in the input and save as cmd
        if (strHuff == "HUFF")                                 //If the first word is "HUFF"
        {
            std::string cmd = getWord(input, 2);    //Get the cmd from the user

            if (cmd == "-exit" || cmd == "-end")                //If the command entered was 'EXIT'
            {
                delete huff;                                    //Perform garbage-collection to the HUFF object
                break;                                          //Exit the while-loop/ the program
            }   //End of if the cmd was exit/end
            else if (cmd == "error")                            //User did not provide a cmd
                std::cout << "Please enter a cmd" << std::endl;
            else                                                //Else the command was not 'EXIT'
            {
                //std::string word = getWord (input, 2);//Get the second word of the input
                //Now we can call the menu and check the input
                interface(cmd, input, huff);
            }   //End of else, if the cmd was not error or exit
        }   //End of if the first word is "HUFF"
        else                                                    //Else the first word in the line is not 'HUFF'
            std::cout << std::endl;                             //Output empty line
    }   //End of while-loop, only breaks out of it if user enters HUFF -end or HUFF -exit
    //We are here if the user used the exit cmd
    return 0;
}   //End of main function

void interface(std::string&cmd, std::string &input, HUFF* huff)
{

    std::string inputFile = getWord(input, 3);   //Get the word after the cmd, aka inputFile
    std::string outputFile =  getWord(input, 4); //Get the 3rd word after the cmd, outputFile
    bool checkInputFile = checkWord(inputFile); //True if user gave us a input file
    bool checkOutFile = checkWord(outputFile);  //True if the user gave us an output file

    if (cmd == "-e")                    //Encode
    {
        /* Objective: Encode input file, placing the output into output file
         * Required: input file
         * Optional: output file
         * */

        if (checkInputFile)             //If the user provided  an input file
        {
            //Here we encode the file from the user, but first we check if the user provided an output file
            if (checkOutFile)           //If the user provided an output file
                huff->EncodeFile(filePath, outputFile);
            else                        //Else the user did not provide an output file
                huff->EncodeFile(filePath, "");
        }   //End of if the user provided an input file
        else                        //Else user did not provide an input file
            std::cout << "Error! Please enter an input file with this cmd" << std::endl;    //Output error
    }   //End of Encode File, cmd -e

    else if (cmd == "-d")               //Decode
    {
        /* Objective: Decode input file into output file
         * Required: input file, output file
         * Optional: None
         * */

        if (checkInputFile)             //If the user provided an input file
        {
            //We are required to have two file paths
            if (checkInputFile && checkOutFile)                 //If the user provided an input and output file
                huff->DecodeFile(inputFile, outputFile);        //Call the decode method from the huff obj
            else                                                //Else the user did not provide one of the files
                std::cout << "Error! Please provide an output file" << std::endl;    //Output error
        }   //End of if the user did provide input file
        else                            //Else the user didn't provide an input file
            std::cout << "Error! Please provide input file with the cmd" <<  std::endl; //Output error
    }   //End of Decode File, cmd -d

    else if (cmd == "-t")               //Create a tree-building file
    {
        /* Objective: Read input file, produce a tree-builder file as output file
         * Required: input file
         * Optional: output file
         * */

        if (checkInputFile)             //If the user provided an input file
        {
            if (checkOutFile)           //If the user provided the optional output file
                huff->MakeTreeBuilder(inputFile, outputFile);
            else                        //Else the user did not provide the optional output file
                huff->MakeTreeBuilder(inputFile, nullptr);
        }   //End of if the user provided an input file
        else                            //Else the user didn't provide an input file
            std::cout << "Error! Please provide input file with the cmd" <<  std::endl; //Output error

    }   //End of create a tree-building file, cmd -t

    else if (cmd == "-et")              //Encode with a specific tree-builder
    {
        /* Objective: Read input file, encode with tree-building file, and produce output file
         * Required: input file, tree-building file
         * Optional: output file
         * */

        std::string treeFile = outputFile;
        bool checkTreeFile = checkOutFile;

        if (checkInputFile)             //Check that the user provided an input file
        {
            if (checkTreeFile)          //Check that the user provided a tree file
            {
                outputFile = getWord(inputFile, 5); //Get the optional output file from the input
                checkOutFile = checkWord(outputFile);       //Check if the user input the output file
                if (checkOutFile)                           //If the user did provide the optional output file
                    huff->EncodeFileWithTree(inputFile, treeFile, outputFile);
                else                                        //Else the user did not provide the output file
                    huff->EncodeFileWithTree(inputFile, treeFile, nullptr);
            }   //End of if the the user provided the tree file
            else
                std::cout << "Error! Please enter a tree-builder file" << std::endl;    //Output error
        }   //End of if the user provided an input file
        else                        //Else user did not provide an input file
            std::cout << "Error! Please enter an input file with this cmd" << std::endl;//Output error
    }   //End of Encoding w/ a tree-builder

    else if (cmd == "-?" || cmd == "-help" || cmd == "-h")  //Else call display help
        huff->DisplayHelp();                                //Display help

    else                                //Else not a valid cmd
        std::cout << "Invalid command, check commands with: HUFF -?" << std::endl;  //Output error
}   //End of interface function

std::string getWord (std::string line, int wordIndex)
{
    /*
     * getWord function, parameter(s): string, int
     * Objective: Get the word from the given string of the position given (int)
     * Cases:
     *  1. If the string has the position of the word then return the word
     *  2. The string doesn't have a word in the requested index, return string "wordIndex error"
     * */
    int countWord = 0;      //Will be used the keep tracks of the amount of words read in the string
    std::string returnWord; //To store the word and return it
    for (int i = 0 ; i < line.length(); i++)            //Iterate through the string char by char
    {
        if (line[i] == ' ' || i == line.length() - 1)   //If the char is a space or the last one in the string
        {
            if (line[i+1] != ' ' || i == line.length() - 1 )    //If the next char is not a space
            {                                                   //  Or the char is the last char in the string
                countWord++;                                    //We reach the end of the word, update countWord
                if (countWord == wordIndex)                     //If we reached the word number we wanted in the string
                {
                    if (i == line.length() - 1)
                    {
                        returnWord += line [i];                 //Append the current character to the returnWord string
                    }
                    return returnWord; // yes it was, so return it
                }   //End of if
                returnWord =""; // nope it wasn't .. so reset word and start over with the next one in 'line'
            }
        }
        else                                            //Else the char is not a space
            returnWord += line[i];                      //We append the char at the end of the returnWord string
    }   //End of if the char is a space or the last char in the string
    return "error";   //If the line does not have the # of word requested in the wordIndex
}   //End of getWord function

bool checkWord (std::string &word)
{
    /*
     * checkWord function is called every time a user enters a cmd
     * Objective: check if the user entered two strings in the input
     * Cases:
     *  -If string is "wordIndex error" then the user only entered one word
     *  -Else the user entered a string/word and a command
     * */

    return  (word == "error") ?  false : true;

}   //End of checkWord function

/*
    MinHeap* min = new MinHeap;
    min->insertKey(3);
    min->insertKey(2);
    min->insertKey(1);
    min->insertKey(15);
    min->insertKey(5);
    min->insertKey(4);
    min->insertKey(45);
    min->print();
    readFile();

    */