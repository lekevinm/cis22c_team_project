// FINAL VERSION: no changes from presentation version

#include <iostream>
#include <string>
#include <fstream>
#include "LinkedGraph.h"
#include "ColorGraph.h"
#include "Vertex.h"

using namespace std;

bool openInputFile(ifstream &ifs);
bool openOutputFile(ofstream &ofs);
bool add(ColorGraph<string>* cg_object);
bool remove(ColorGraph<string>* cg_object);
bool undo(ColorGraph<string>* cg_object);
void display(ColorGraph<string>* cg_object, string root);
void displayVertex(string &vertex);
bool solve(ColorGraph<string>* cg_object, string root);
bool save(ColorGraph<string>* cg_object, string root);

int main()
{
    ColorGraph<string>* cg_object = new ColorGraph<string>;
    ifstream ifs; // input file stream for this program to read from
    string start, end, root;
    bool found_root = false;
    if (openInputFile(ifs)) {
        while (ifs >> start >> end){
            if (!found_root){
                root = start; // for this project, starting root will either be California or Florida
                found_root = true;
            }
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
        << "4. Display graph on screen\n"
        << "5. Solve the map coloring problem (with 4 colors)\n"
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
                save(cg_object, root); // write the graph to a text file using the Breadth-First traversal, where the file name is input from the user
                break;
            case QUIT_CHOICE:
                cout << "Quitting program.";
                return 0;
            default:
                cout << "The valid choices are 1 though 7.\n";
                break;
        }
    } while (choice != QUIT_CHOICE);
    delete cg_object; // delete dynamic memory
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
    if (isspace(filename[filename.length() - 1]))
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
    if (isspace(filename[filename.length() - 1]))
        filename.pop_back();
    ofs.open(filename.c_str());
    return ofs.is_open();
}

// A function to add an edge to the graph
bool add(ColorGraph<string>* cg_object)
{
    string start, end;
    cout << "What state do you wish to start at?\n";
    cin >> start;
    cout << "What state do you wish to connect to?\n";
    cin >> end;
    if (cg_object->add(start, end, 0)){
        cout << "Edge successfully added.\n";
        return true;
    }
    else{
        cout << "Edge wasn't successfully added.\n";
        return false;
    }
}

// A function to remove an edge from the graph
bool remove(ColorGraph<string>* cg_object)
{
    string start, end;
    cout << "What state do you wish to start at?\n";
    cin >> start;
    cout << "What state do you wish to remove it from?\n";
    cin >> end;
    if (cg_object->remove(start, end)){
        cout << "Edge successfully removed.\n";
        return true;
    }
    else{
        cout << "Edge wasn't successfully removed.\n";
        return false;
    }
}

// A function to undo the previous removal from the graph
bool undo(ColorGraph<string>* cg_object){
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
void display(ColorGraph<string>* cg_object, string root){
    int display_option;
    cout << "Would you like to do depth-first or breadth-first traversal? (1 for depth, 2 for breadth) \n";
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
void displayVertex(string &vertex)
{
    cout << left << "State: " << vertex << endl;
}

// A function to solve the map coloring problem for the current graph
bool solve(ColorGraph<string>* cg_object, string root){
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
                cg_object->clearQueue(); // we clear queue in both options here because the user may want to save at a later time
                save(cg_object, root);
                return true;
            }
            else if (save_option == 2){
                cg_object->clearQueue();
                return true;
            }
            else{
                cout << "The available options are 1 or 2. \n";
            }
        } while (save_option != 1 && save_option != 2);
    }
    else
        cout << "Problem could not be solved.\n";
    return false;
}

// A function to save the graph to a text file of user choice
bool save(ColorGraph<string>* cg_object, string root){
    ofstream ofs;
    if (openOutputFile(ofs)){
        cout << "This is the completed graph that will be saved:\n";
        cg_object->breadthFirstTraversal(root, displayVertex); // we populate the queue again here to be safe
        cg_object->saveToFile(ofs);
        ofs.close();
        cout << "File successfully saved.\n";
        return true;
    }
    else{
        cout << "File could not be successfully opened or created.\n";
        return false;
    }
}
