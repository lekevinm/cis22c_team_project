#include <iostream>
#include <string>
#include <fstream>
#include "LinkedGraph.h"

using namespace std;

bool openInputFile(ifstream &ifs);

int main()
{
    return 0;
}


// A function called from main that opens a file FOR INPUT using a filename input from the user.
bool openInputFile(ifstream &ifs)
{
    string filename; // file name for the file to be opened
    cout << "Enter the input filename: ";
    getline(cin, filename);
    // IF USING A MAC, ADD CODE SHOWN BELOW***
    if( isspace(filename[filename.length()-1]) )
        filename.pop_back();
    ifs.open(filename.c_str());
    return ifs.is_open();
}