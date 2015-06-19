#ifndef __team_project__ColorGraph__
#define __team_project__ColorGraph__
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "LinkedGraph.h"
#include "BinarySearchTree.h"
#include "Vertex.h"
#include "Edge.h"
#include "LinkedStack.h"

template <class LabelType>
class ColorGraph : public LinkedGraph<LabelType>
{
private:
	LinkedStack<LabelType> removal_stack; // the linked stack that keeps track of removals (for undoing)
	vector<Edge<LabelType>> colorGraph;
	int color_count = 4; // the number of colors to try to solve the color map problem (WILL BE UPDATED LATER)
	bool isSafe(Vertex<LabelType>* currVertex, int c);
	bool colorCheck(Vertex<LabelType>* currVertex, int i);
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
bool ColorGraph<LabelType>::isSafe(Vertex<LabelType>* currVertex, int c)
{
	currVertex->resetNeighbor();
	Vertex<LabelType>* loop;
	for (int i = 0; i < currVertex->getNumberOfNeighbors(); i++){
		loop = findOrCreateVertex(currVertex->getNextNeighbor());
		if (loop->getColor() == c)
			return false;
	}
	return true;
}

/* A recursive utility function to solve m coloring problem */
template <class LabelType>
bool ColorGraph<LabelType>::colorCheck(Vertex<LabelType>* currVertex, int i)
{
	cout << i;
	cout << currVertex->getLabel();
	if (i > this->getNumVertices())
	{
		return true;
	}
	/* Consider this vertex v and try different colors */
	for (int c = 1; c <= color_count; c++)
	{
		/* Check if assignment of color c to v is fine*/
		if (isSafe(currVertex, c))
		{
			// color[/*vertex*/] = c;
			currVertex->setColor(c);

			/* recur to assign colors to rest of the vertices */
			if ((this->pvertexIterator)->hasNext()==true)
			{
				colorCheck((this->pvertexIterator)->next(), (i + 1));
				return true;
			}
			else
			{
				return true;
			}
			
		}

		/* If assigning color c doesn't lead to a solution
		then remove it */
		// color[/*vertex*/] = 0;
		currVertex->setColor(0);
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
	this->unvisitVertices();
	pvertexIterator = vertices.iterator();
	while (pvertexIterator->hasNext())
	{
		Vertex<LabelType>* loopVertex = pvertexIterator->next();

		loopVertex->setColor(0);
	}  // end while
	pvertexIterator = vertices.iterator();
	pstartvertex = pvertexIterator;
	if (colorCheck((this->pvertexIterator)->next(), 1) == false)
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

/*template <class LabelType>
void ColorGraph<LabelType>::printColorMap()
{
use iterator here?
}*/

#endif
