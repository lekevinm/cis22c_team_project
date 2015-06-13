/*
 TO DO
  include more than one graph (storing each graph in a separate file), with 7 to 25 vertices in one graph
    - write out these graphs in a file beforehand
    - include code that can write changes to these graphs
 
  your team project MUST:
 o include a loop to allow solving the problem more than once in
 one run
 
 o display a menu to the user for the following options:
  read the graph from a text file where the file name is input from the user (use the openInputFile function)
  add an edge to the graph
  remove an edge from the graph
  undo the previous removal(s) (you MUST use an ArrayStack or LinkedStack from HW#1)
  display the graph on the screen (give the choices of Depth- First traversal or Breadth-First traversal)
  solve the problem for the graph, which would automatically display the results on the screen (NOTE: THERE MAY NOT BE A SOLUTION FOR A GIVEN GRAPH), and ask the user if the results should be saved to a text file (where the file name is input from the user)
  write the graph to a text file using the Breadth-First traversal, where the file name is input from the user
 
 1. Map coloring: represent adjacent geographic areas using a graph, and determine if you could color a map using a particular number of colors, OR find the minimum number of colors needed
 
 **remember to write function in LinkedGraph to save to file
 
 United States regions (west coast and east coast), two maps
 */

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