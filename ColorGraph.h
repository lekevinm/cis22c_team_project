#ifndef __team_project__ColorGraph__
#define __team_project__ColorGraph__
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "LinkedGraph.h"
#include "BinarySearchTree.h"
#include "Vertex.h"
#include "Edge.h"
#include "LinkedStack.h"

template <class LabelType>
class ColorGraph: public LinkedGraph<LabelType>
{
private:
    LinkedStack<Edge> removal_stack; // the linked stack that keeps track of removals (for undoing)
    int color_count = 1; // the number of colors to try to solve the color map problem
public:
    ColorGraph(){}
    ~ColorGraph(){}
    bool greedyColor();
    bool undoRemove();
    void printColorMap();
    void setNumColor(int numColor);
};

template <class LabelType>
bool ColorGraph<LabelType>::greedyColor();
{

}

/* Greedy Coloring Algorithm --> port over to our code
 // Assigns colors (starting from 0) to all vertices and prints
 // the assignment of colors
 void Graph::greedyColoring()
 {
 int result[V];
 
 // Assign the first color to first vertex
 result[0]  = 0;
 
 // Initialize remaining V-1 vertices as unassigned
 for (int u = 1; u < V; u++)
 result[u] = -1;  // no color is assigned to u
 
 // A temporary array to store the available colors. True
 // value of available[cr] would mean that the color cr is
 // assigned to one of its adjacent vertices
 bool available[V];
 for (int cr = 0; cr < V; cr++)
 available[cr] = false;
 
 // Assign colors to remaining V-1 vertices
 for (int u = 1; u < V; u++)
 {
 // Process all adjacent vertices and flag their colors
 // as unavailable
 list<int>::iterator i;
 for (i = adj[u].begin(); i != adj[u].end(); ++i)
 if (result[*i] != -1)
 available[result[*i]] = true;
 
 // Find the first available color
 int cr;
 for (cr = 0; cr < V; cr++)
 if (available[cr] == false)
 break;
 
 result[u] = cr; // Assign the found color
 
 // Reset the values back to false for the next iteration
 for (i = adj[u].begin(); i != adj[u].end(); ++i)
 if (result[*i] != -1)
 available[result[*i]] = false;
 }
 
 // print the result
 for (int u = 0; u < V; u++)
 cout << "Vertex " << u << " --->  Color "
 << result[u] << endl;
 }
 */
 

template <class LabelType>
bool ColorGraph<LabelType>::undoRemove();
{

}

template <class LabelType>
void ColorGraph<LabelType>::printColorMap()
{

}

template <class LabelType>
void ColorGraph<LabelType>::setNumColor(int numColor)
{
    color_count = numColor;
}
#endif
