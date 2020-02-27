#include <iostream>
#include <fstream>  //To read & write files
#include "sortedLL.h"
#include "HuffTree.h"
using namespace std;


const char filePath [] = "/Users/cgalo/CLionProjects/HUFF/Hamlet.txt";

void readFile();

int main() {
    HuffTree* tree = new HuffTree;

    readFile();
    /*sortedLL * LL = new sortedLL;
    LL->insert('c');
    LL->insert('a');
    LL->printLL();
    cout << endl;
    LL->insert('b');
    LL->printLL();
    cout << endl;
    LL->insert('b');
    LL->insert('b');
    LL->printLL();
    LL->insert('c');
    LL->insert('c');
    LL->insert('c');
    cout << endl;
    LL->printLL();
    cout << LL->getLength() << endl;
    LL->deleteMin();
    cout << LL->getLength() << endl;
    LL->printLL();
    LL->deleteMin();
    LL->deleteMin();
    LL->printLL();
    cout <<LL->getLength() << endl;*/
    /*LL->insert('c');
    LL->insert('a');
    LL->insert('a');
    LL->printLL();
    std::cout << std::endl;
    LL->insert('c');
    LL->insert('c');
    LL->printLL();*/


    return 0;
}



void interface()
{

}

void readFile(HuffTree* tree)
{
    ifstream file (filePath, ios::in | ios::binary);    //Read the file as binary
    if (!file)      //If file is not found or unable to open
        std::cout << "Error! File not found" << std::endl;  //Throw error
    else            //Else we could find and open the file
    {
        char tempChar;   //Create variable to read char by char of the file

        while (file >> noskipws >> tempChar)    //Loop through each character in the file
        {
            tree->frequencyTable->insert(tempChar);
        }   //End of while-loop
        LL->printLL();
        std::cout << "Length: " << LL->getLength() << std::endl;
    }   //End of else, if we could find and open the file
}