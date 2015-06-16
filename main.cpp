/*
 TO DO
  include more than one graph (storing each graph in a separate file), with 7 to 25 vertices in one graph
    - write out these graphs in two files beforehand , United States regions (west coast and east coast), two maps
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
 
  Map coloring: represent adjacent geographic areas using a graph and determine if you could color a map using a particular number of colors
 
  write function in LinkedGraph to save to file

 */

#include <iostream>
#include <string>
#include <fstream>
#include "ColorGraph.h"

using namespace std;

bool openInputFile(ifstream &ifs);

int main()
{
    // add ColorGraph object here (?)
     ifstream ifs; // input file stream for this program to read from // NOTE WE MAY NEED ADDITIONAL FILE OBJECTS TO SAVE GRAPH(?) bc user can define different file name
    if(openInputFile(ifs)) {
        // read the graph in from here
    }
    else {
        cout << "The file could not be opened.\n";
        return 0; // end program prematurely
    }
    /* TO DO : make a preliminary switch menu, and then work from there */
    int choice;
    const int ADD_CHOICE = 1,
    REMOVE_CHOICE = 2,
    UNDO_CHOICE = 3,
    DISPLAY_CHOICE = 4,
    SOLVE_CHOICE = 5,
    SAVE_CHOICE = 6,
    QUIT_CHOICE = 7;
    cout << "\t\tMap Coloring Program\n";
    do{
        cout << "Enter the desired option's number\n"
        << "1. Add an edge to the graph\n"
        << "2. Remove an edge from the graph\n"
        << "3. Undo removal of edge\n"
        << "4. Display graph on screen\n" // maybe have a bool here in case problem isn't solved yet // ALSO add DFS or BFS
        << "5. Solve the map coloring problem (with N colors)\n" // remember to replace N in final version
        << "6. Save graph to text file\n"
        << "7. Quit the program\n";
        cin >> choice;
        cin.clear();
        cin.ignore();
        switch (choice) {
            case ADD_CHOICE:
                // add an edge to the graph
                break;
            case REMOVE_CHOICE:
                // remove an edge from the graph
                break;
            case UNDO_CHOICE:
                // undo the previous removal(s) (you MUST use an ArrayStack or LinkedStack from HW#1)
                break;
            case DISPLAY_CHOICE:
                // display the graph on the screen (give the choices of Depth- First traversal or Breadth-First traversal)
                break;
            case SOLVE_CHOICE:
                // solve the problem for the graph, which would automatically display the results on the screen (NOTE: THERE MAY NOT BE A SOLUTION FOR A GIVEN GRAPH), and ask the user if the results should be saved to a text file (where the file name is input from the user)
                break;
            case SAVE_CHOICE:
                // write the graph to a text file using the Breadth-First traversal, where the file name is input from the user
                break;
            case QUIT_CHOICE:
                cout << "Quitting program.";
                return 0;
            default:
                cout << "The valid choices are 1 though 7.\n";
                break;
        }
    }
    while (choice != QUIT_CHOICE);
    // remember to close file + delete dynamic memory before quitting program!
     ifs.close();
    return 0;
}


// A function called from main that opens a file FOR INPUT using a filename input from the user.
bool openInputFile(ifstream &ifs)
{
    string filename; // file name for the file to be opened
    cout << "Enter the input filename (to read the starting graph from): ";
    getline(cin, filename);
    // IF USING A MAC, ADD CODE SHOWN BELOW***
    if( isspace(filename[filename.length()-1]) )
        filename.pop_back();
    ifs.open(filename.c_str());
    return ifs.is_open();
}