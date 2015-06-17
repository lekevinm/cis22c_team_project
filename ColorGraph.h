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
    LinkedStack<Vertex<LabelType>> removal_stack; // the linked stack that keeps track of removals (for undoing)
    int color_count = 1; // the number of colors to try to solve the color map problem (WILL BE UPDATED LATER)
    bool isSafe(/*vertex*/, int c);
    bool colorCheck(/*vertex*/);
public:
    ColorGraph(){} // not sure what is needed here during construction
 //   ~ColorGraph(){}
    bool graphColoring(); // backtracking algorithm answers problem better
  //  bool add(LabelType start, LabelType end, int edgeWeight = 0);
    bool remove(LabelType start, LabelType end);
    bool undoRemove();
  //  void printColorMap();
  //  void setNumColor(int c){color_count = c;}
  //  int getNumColor(){return color_count;}
};

/* A utility function to check if the current color assignment
 is safe for vertex v */
template <class LabelType>
bool ColorGraph<LabelType>::isSafe(/*vertex*/, int c)
{
    for (int i = 0; i < this->numberOfVertices; i++){
      //  if (/*vertex*/ && c == color[i]) // color[i] is not used in this program,
        // possibly change to check if the same color is used for any adjacent vertices
            return false;
    }
    return true;
}
                 
/* A recursive utility function to solve m coloring problem */
template <class LabelType>
bool ColorGraph<LabelType>::colorCheck(/*vertex*/)
{
        /* base case: If all vertices are assigned a color then
         return true */
       // if (/*vertex*/ == this->numberOfVertices) // not sure what this checks exactly, possibly change to check if no vertex has a color of 0
            return true;
        
        /* Consider this vertex v and try different colors */
        for (int c = 1; c <= color_count; c++)
        {
            /* Check if assignment of color c to v is fine*/
            if (isSafe(/*vertex*/, c))
            {
               // color[/*vertex*/] = c;
                /*vertex*/.setColor(c);
                
                /* recur to assign colors to rest of the vertices */
                if (colorCheck (/*next vertex*/) == true)
                    return true;
                
                /* If assigning color c doesn't lead to a solution
                 then remove it */
               // color[/*vertex*/] = 0;
                /*vertex*/.setColor(0);
            }
        }
        
        /* If no color can be assigned to this vertex then return false */
        return false;
}
                 
/* This function solves the m Coloring problem using Backtracking.
It mainly uses graphColoringUtil() to solve the problem. It returns
false if the m colors cannot be assigned, otherwise return true and
prints assignments of colors to all vertices. Please note that there
may be more than one solutions, this function prints one of the
feasible solutions.*/
template <class LabelType>
bool ColorGraph<LabelType>::graphColoring()
{
        // Initialize all color values as 0. This initialization is needed
        // correct functioning of isSafe()
      /*  int *color = new int[this->numberOfVertices];
        for (int i = 0; i < this->numberOfVertices; i++)
            color[i] = 0;*/
    
    // change this so that each vertex in the map gets a color of 0 initially
    
        // Call graphColoringUtil() for vertex 0
        if (colorCheck(/*first vertex*/) == false)
        {
            cout << "Problem cannot be solved.\n";
            return false;
        }
        return true;
}

template<class LabelType>
bool ColorGraph<LabelType>::remove(LabelType start, LabelType end)
{
    bool successful = false;
    Vertex<LabelType>* startVertex = this->vertices.getItem(start);
    Vertex<LabelType>* endVertex   = this->vertices.getItem(end);
    
    successful = startVertex->disconnect(end);
    if (successful)
    {
        successful = endVertex->disconnect(start);
        if (successful)
        {
            this->numberOfEdges--;
            
            removal_stack.push(*endVertex); // adds the vertices to the stack, but not sure if both are needed
            removal_stack.push(*startVertex);
            
            // If either vertex no longer has a neighbor, remove it
            if (startVertex->getNumberOfNeighbors() == 0)
            {
                this->vertices.remove(start);
                --this->numberOfVertices; // UPDATED 06/11/2015
                delete startVertex; // UPDATED 06/08/2015
            }
            
            if (endVertex->getNumberOfNeighbors() == 0)
            {
                this->vertices.remove(end);
                --this->numberOfVertices; // UPDATED 06/11/2015
                delete endVertex;  // UPDATED 06/08/2015
            }
        }
        else
            successful = false; // Failed disconnect from endVertex
    }
    else
        successful = false;    // Failed disconnect from startVertex
    
    return successful;
}  // end remove

template <class LabelType>
bool ColorGraph<LabelType>::undoRemove();
{
    if (!removal_stack.isEmpty()){
    Vertex<LabelType>* startVertex = removal_stack.pop();
    Vertex<LabelType>* endVertex = removal_stack.pop();
    
    this->add(startvertex, endVertex);
        return true;
    }
    else
        return false;
}

/*template <class LabelType>
void ColorGraph<LabelType>::printColorMap()
{
    /* use iterator here?
}*/

#endif
