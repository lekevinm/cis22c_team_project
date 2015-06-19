#ifndef __team_project__ColorGraph__
#define __team_project__ColorGraph__
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "LinkedGraph.h"
#include "Vertex.h"
#include "Edge.h"
#include "LinkedStack.h"

template <class LabelType>
class ColorGraph : public LinkedGraph<LabelType>
{
private:
    LinkedStack<LabelType> removal_stack; // the linked stack that keeps track of removals (for undoing)
    int color_count = 4; // the number of colors to try to solve the color map problem (can be changed in future versions)
    bool isSafe(Vertex<LabelType>* currVertex, int c); // helper function for backtracking
    bool colorCheck(Vertex<LabelType>* currVertex, int i); // recursive helper function for backtracking
public:
    ColorGraph(){}
    ~ColorGraph(){}
    bool graphColoring(); // backtracking algorithm
    bool remove(LabelType start, LabelType end);
    bool undoRemove();
};

// Function to determine if the color assignment c is safe
template <class LabelType>
bool ColorGraph<LabelType>::isSafe(Vertex<LabelType>* currVertex, int c)
{
    currVertex->resetNeighbor();
    Vertex<LabelType>* loop;
    for (int i = 0; i < currVertex->getNumberOfNeighbors(); i++){ // check if any adjacent vertex has the same color
        loop = this->findOrCreateVertex(currVertex->getNextNeighbor());
        if (loop->getColor() == c)
            return false;
    }
    return true;
}

//Recursive function to solve the map coloring problem
template <class LabelType>
bool ColorGraph<LabelType>::colorCheck(Vertex<LabelType>* currVertex, int i)
{
    if (i > this->getNumVertices()) // base case: if all vertices have colors, return true
    {
        return true;
    }
    for (int c = 1; c <= color_count; c++)
    {
        if (isSafe(currVertex, c)) // check if color c can be assigned to this vertex
        {
            currVertex->setColor(c);
            if ((this->pvertexIterator)->hasNext()==true)
            {
                colorCheck((this->pvertexIterator)->next(), (i + 1)); // recur to assign colors to the rest of the vertices
                return true;
            }
            else
            {
                return true;
            }
        }
        currVertex->setColor(0); // If assigning color c isn't safe, then remove it
    }
    return false; // If a color can't be assigned to this vertex, return false
}


/* This function solved the map coloring problem through backtracking. It returns false if the number of colors cannot be assigned, 
 and otherwise returns trues and assigns colors to all vertices, or states. */
template <class LabelType>
bool ColorGraph<LabelType>::graphColoring()
{
    this->unvisitVertices();
    this->pvertexIterator = this->vertices.iterator();
    while (this->pvertexIterator->hasNext())
    {
        Vertex<LabelType>* loopVertex = this->pvertexIterator->next();
        
        loopVertex->setColor(0);
    }  // end while
    this->pvertexIterator = this->vertices.iterator();
    this->pstartvertex = this->pvertexIterator;
    if (colorCheck((this->pvertexIterator)->next(), 1) == false)
    {
       // cout << "Problem cannot be solved.\n";
        return false;
    }
    return true;
}

template<class LabelType>
bool ColorGraph<LabelType>::remove(LabelType start, LabelType end)
{
    bool successful = false;
    Vertex<LabelType>* startVertex = this->vertices.getItem(start);
    Vertex<LabelType>* endVertex = this->vertices.getItem(end);
    
    
    successful = startVertex->disconnect(end);
    if (successful)
    {
        successful = endVertex->disconnect(start);
        if (successful)
        {
            this->numberOfEdges--;
            removal_stack.push(start);
            removal_stack.push(end);
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
bool ColorGraph<LabelType>::undoRemove()
{
    if (!removal_stack.isEmpty()){
        LabelType start = removal_stack.peek();
        removal_stack.pop();
        LabelType end = removal_stack.peek();
        removal_stack.pop();
        this->add(start, end);
        return true;
    }
    else
        return false;
}

#endif
