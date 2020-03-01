#include <iostream>
#include <fstream>  //To read & write files
#include "sortedLL.h"
#include "MinHeap.h"
#include "HUFF.h"

void interface      (std::string cmd, std::string input, HUFF* huff);    //Declaring the menu function
void toUpper        (std::string* word);                    //Declaring the toUpper function
std::string getWord (std::string line, int wordIndex);      //Declaring getWord function
bool checkWord      (std::string word);                     //Declaring checkWord function
void showHelp       ();                                     //Declaring showHelp function
void readFile();

const char filePath [] = "/Users/cgalo/CLionProjects/HUFF/Hamlet.txt";




int main()
{
    HUFF* huff = new HUFF;
    while (true)
    {
        std::string input;  //Create string to accept the input of the user
        std::cout<< "";
        std::getline (std::cin, input); //Get the whole input of the user
        //Now we need to split the input to get the cmd and the word we want to store
        std::string cmd = getWord(input, 1);      //Get the first word in the input and save as cmd
        toUpper(&cmd);                                      //Convert the cmd into upper case

        if (cmd == "-EXIT" || cmd == "-END")                //If the command entered was 'EXIT'
            break;                                          //Exit the while-loop/ the program
        else                                                //Else the command was not 'EXIT'
        {
            //std::string word = getWord (input, 2);//Get the second word of the input
            //Now we can call the menu and check the input
            interface(cmd, input, huff);
        }
    }   //End of while-loop

    //delete tree;
    return 0;
}


void interface(std::string cmd, std::string input, HUFF* huff)
{

    std::string inputFile = getWord(input, 2);  //Get the word after the cmd, aka inputFile
    std::string outputFile =  getWord(input, 3);//Get the 2nd word after the cmd, outputFile
    bool checkInputFile = checkWord(inputFile); //True if user gave us a input file
    bool checkOutFile = checkWord(outputFile);  //True if the user gave us an output file


    if (cmd == "-e")                    //Encode
    {
        //The user is required the filename, and optional 2nd file

        if (checkInputFile)    //If there was no filename after the cmd
        {
            //Here we encode the file from the user, but first we check if the user provided an output file
            if (checkOutFile)           //If the user did not provide an output file
                huff->encode(inputFile, NULL);
            else                        //Else the user provided an output file
                huff->encode(inputFile, outputFile);
        }   //End of the if the user provided a filename
        else                            //Else the user did not provide an input file
            std::cout << "Error! No file provided" << std::endl;    //Output error, no file path provided
    }   //End of Encode cmd

    else if (cmd == "-d")               //Decode
    {
        //We are required to have two file paths
        if (checkInputFile && checkOutFile) //If the user provided an input and output file
        {

        }
    }
}

/*void interface2(std::string cmd, int ma)
{
    //Check if the user input a word with the cmd
    bool wordCheck = checkWord(word);
    //C++ does not support switch statement with a string/char array so I'll use if-else statements through out
    if (cmd == "INSERT")                        //If the cmd is insert
    {
        if (wordCheck == false)                 //If the user did not input a word to insert with the cmd
            std::cout << std::endl;             //Print empty line, do not insert
        else                                    //Else the user did provide a word to insert with the cmd
            tree->insert(word);                  //Insert the provided word to the BST
    }   //End of if the cmd == "INSERT"
    else if (cmd == "DELETE")                   //Else if the cmd is delete
    {
        if (wordCheck == false)                 //If the user did not input a second word
            std::cout << std::endl;             //Output empty line, as we need a word w/ the cmd
        else                                    //Else user input a cmd w/ a word
            tree->remove(word);                  //We call the tree's remove method and pass the word given
    }   //End of else-if cmd == "DELETE"
    else if (cmd == "SEARCH")                   //Else if the cmd is search
    {
        if (wordCheck == false)                 //If the user did not input a word
            std::cout << std::endl;
        else                                    //Else the user input a word
            tree->search(word);                  //Call the tree's search function
    }   //End of else-if cmd == "SEARCH"
    else if (cmd == "MIN")                      //Else if the cmd is min
    {
        tree->min();                             //Call the min method in the tree
    }   //End of else-if cmd == "MIN"
    else if (cmd == "MAX")                      //Else if the cmd is max
    {
        tree->max();                             //Call the max method of the tree, we do not need a word w/ the cmd
    }   //End of else-if cmd == "MAX"
    else if (cmd == "NEXT")
    {
        if (wordCheck == false)                 //If the user did not input a second word
            std::cout << std::endl;
        else
            tree->next(word);

    }   //End of else-if cmd == "NEXT"
    else if (cmd == "PREV")
    {
        if (wordCheck == false)
            std::cout << std::endl;
        else
            tree->previous(word);
    }   //End of else-if cmd == "PREV"
    else  if (cmd == "PARENT")
    {
        if(wordCheck == false)                //If the user did not provide a string with the cmd
            std::cout << std::endl;           //Output an empty line
        else
            tree->parent(word);                //Call the parent method of the tree
    }   //End of else-if cmd == "PARENT"
    else if (cmd == "CHILD")
    {
        if (wordCheck == false)               //If the user did not provide a word w/ the cmd
            std::cout << std::endl;           //Output empty line
        else                                  //Else the user did provide a word w/ the cmd
            tree->children(word);              //Call the children function from the tree
    }   //End of else-if cmd == "CHILD"
    else if (cmd == "LIST")
    {
        tree->printTree();       //Prints in-order traversal of the tree node's, outputs all the node's data and count
    }   //End of else-if cmd == "LIST
    else if (cmd == "HELP")
    {
        showHelp();
    }   //End of else-if cmd == "HELP"
    else
    {
        std::cout << std::endl; //Print empty line
    }   //End of else, the user input a wrong cmd

}*/

void readFile()
{
    std::ifstream file (filePath, std::ios::in | std::ios::binary);    //Read the file as binary
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
        LL->printLL();
        std::cout << "Length: " << LL->getLength() << std::endl;
    }   //End of else, if we could find and open the file
}


//Function takes pointer/reference of a string and converts it into uppercase
void toUpper (std::string* word)
{
    for (auto & c: *word) c = toupper(c);
}   //End of toUpper function

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

bool checkWord (std::string word)
{
    /*
     * checkWord function is called every time a user enters a cmd
     * Objective: check if the user entered two strings in the input
     * Cases:
     *  -If string is "wordIndex error" then the user only entered one word
     *  -Else the user entered a string/word and a command
     * */
    if (word == "error")  //If the user did not provide another word with the cmd
        return false;               //Return false
    else                            //Else the user did input a cmd with a word
        return true;                //Return true
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