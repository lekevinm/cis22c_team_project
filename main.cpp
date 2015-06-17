/*
 TO DO
  include more than one graph (storing each graph in a separate file), with 7 vertices in each graph
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
 
 STILL NEEDED 
 =======
 LinkedGraph function that saves graph to file
 completion of ColorGraph.h (learn how traversal works, how to step through each vertex, etc)
 testing of program
 bug fixes
 */

#include <iostream>
#include <string>
#include <fstream>
#include "LinkedGraph.h"
#include "ColorGraph.h"
#include "Vertex.h"

using namespace std;

bool openInputFile(ifstream &ifs);
bool openOutputFile(ofstream &ofs);
bool add(LinkedGraph<string>* cg_object);
bool remove(LinkedGraph<string>* cg_object);
bool undo(LinkedGraph<string>* cg_object);
void display(LinkedGraph<string>* cg_object, string root);
void displayVertex(Vertex<string> &vertex);
bool solve(LinkedGraph<string>* cg_object, string root);
bool save(LinkedGraph<string>* cg_object);

int main()
{
    // add ColorGraph object here (?)
    LinkedGraph<string>* cg_object = new ColorGraph<string>;
     ifstream ifs; // input file stream for this program to read from // NOTE WE MAY NEED ADDITIONAL FILE OBJECTS TO SAVE GRAPH(?) bc user can define different file name
    string start, end, root; // maybe these need to be dynamically allocated?
    bool found_root = false;
    if(openInputFile(ifs)) {
        while (ifs >> start >> end){
            if (!found_root){
            root = start;
                found_root = true;
            }
        // read the graph in from here // NOTE THIS IS ASSUMING EACH LINE CONTAINS THE START AND END POINTS (or each state is separated by a whitespace)
        cg_object->add(start, end, 0);
        }
    }
    else {
        cout << "The file could not be opened.\n";
        delete cg_object;
        return 0; // end program prematurely
    }
    
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
                add(cg_object); // add an edge to the graph
                break;
            case REMOVE_CHOICE:
                remove(cg_object); // remove an edge from the graph
                break;
            case UNDO_CHOICE:
                undo(cg_object); // undo the previous removal(s) (you MUST use an ArrayStack or LinkedStack from HW#1)
                break;
            case DISPLAY_CHOICE:
                display(cg_object, root); // display the graph on the screen (give the choices of Depth- First traversal or Breadth-First traversal)
                break;
            case SOLVE_CHOICE:
                solve(cg_object, root); // solve the problem for the graph, which would automatically display the results on the screen (NOTE: THERE MAY NOT BE A SOLUTION FOR A GIVEN GRAPH), and ask the user if the results should be saved to a text file (where the file name is input from the user)
                break;
            case SAVE_CHOICE:
                save(cg_object); // write the graph to a text file using the Breadth-First traversal, where the file name is input from the user
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
    delete cg_object; // *** possibly need to delete things inside the graph before ???
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

bool openOutputFile(ofstream &ofs)
{
    string filename; // file name for the file to be opened
    cout << "Enter the output filename (write the current graph to): ";
    getline(cin, filename);
    // IF USING A MAC, ADD CODE SHOWN BELOW***
    if( isspace(filename[filename.length()-1]) )
        filename.pop_back();
    ofs.open(filename.c_str());
    return ofs.is_open();
}

// A function to add an edge to the graph
bool add(LinkedGraph<string>* cg_object)
{
    string start, end;
    cout << "What state do you wish to start at?\n";
    cin >> start;
    cout << "What state do you wish to connect to?\n";
    cin >> end;
    if (cg_object->add(start, end, 0)){
        cout << "Edge successfully added.\n";
    }
    else{
        cout << "Edge wasn't successfully added.\n";
    }
}

// A function to remove an edge from the graph
bool remove(LinkedGraph<string>* cg_object)
{
    string start, end;
    cout << "What state do you wish to start at?\n";
    cin >> start;
    cout << "What state do you wish to connect to?\n";
    cin >> end;
    cg_object->remove(start, end);
}

// A function to undo the previous removal from the graph
bool undo(LinkedGraph<string>* cg_object){
    if (cg_object->undoRemove()){
        cout << "Previous removal successfully undone.\n";
        return true;
    }
    else {
        cout << "Previous removal was not undone.\n";
        return false;
    }
}

// A function to display the graph through BFS or DFS
void display(LinkedGraph<string>* cg_object, string root){
    int display_option;
    cout << "Would you like to do depth-first or breadth-first traversal?\n";
    do{
        cin >> display_option;
        cin.clear();
        cin.ignore();
        if (display_option == 1){
            cg_object->depthFirstTraversal(root, displayVertex);
            return;
        }
        else if (display_option == 2){
            cg_object->breadthFirstTraversal(root, displayVertex);
            return;
        }
        else{
            cout << "The available options are 1 or 2. \n";
        }
    } while (display_option != 1 && display_option != 2);
}

// Function that displays the state and color at each vertex.
void displayVertex(Vertex<string> &vertex)
{
   // cout << hex << left << setw(10) << ptrIp->getDottedDecimal() << right << setw(10) << " " << ptrIp->getIpValue() << endl;
    cout << left << setw(10) << vertex.getLabel() << right << setw(10) << " " << vertex.getColor() << endl; // not sure if we should change int to an actual color...
}

// A function to solve the map coloring problem for the current graph
bool solve(LinkedGraph<string>* cg_object, string root){
    if (cg_object->graphColoring()){
        cout << "Problem successfully solved, now displaying graph:\n";
        display(cg_object, root);
        int save_option;
        cout << "Would you like to save the results to a file? 1 for yes, 2 for no. \n";
        do{
            cin >> save_option;
            cin.clear();
            cin.ignore();
            if (save_option == 1){
                save(cg_object);
                return true;
            }
            else if (save_option == 2){
                return true;
            }
            else{
                cout << "The available options are 1 or 2. \n";
            }
        } while (save_option != 1 && save_option != 2);
    }
    else {
        cout << "Problem could not be solved.\n";
        return false;
    }
}

// A function to save the graph to a text file of user choice
bool save(LinkedGraph<string>* cg_object){
    ofstream ofs;
    if (openOutputFile(ofs)){
    cg_object->saveToFile(ofs); // need to write this function in LinkedGraph.
    }
    else{
        cout << "File could not be successfully opened or created.\n";
    }
}