// Linked list implementation of queue ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by CNguyen

#ifndef _LINKED_QUEUE
#define _LINKED_QUEUE

#include "QueueInterface.h"
#include "Node.h"

template<class ItemType>
class LinkedQueue : public QueueInterface<ItemType>
{
private:
   Node<ItemType>* backPtr;
   Node<ItemType>* frontPtr;
   int count;

public:
    LinkedQueue() { backPtr = 0; frontPtr = 0; } // default constructor (inline, initialize each member variable to 0)
	LinkedQueue (const LinkedQueue& aQueue);
	~LinkedQueue();
	int size() const {return count;}
	bool isEmpty() const {return (count == 0);}
	bool enqueue(const ItemType& newEntry);
	bool dequeue();
	ItemType peekFront() const {return frontPtr->getItem();}
};

// copy constructor, similar to LinkedStack but modified to use frontPtr and backPtr instead of topPtr
template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue& aQueue)
{
    Node<ItemType>* origChainPtr = aQueue.frontPtr;	// original chain is linked queue to be copied
    
    if (origChainPtr == 0) // if original queue is empty
    {
        frontPtr = 0;
        backPtr = 0;
    }
    else
    {
        frontPtr = new Node<ItemType>(); // Copy first node
        frontPtr->setItem(origChainPtr->getItem());
        
        Node<ItemType>* newChainPtr = frontPtr;		// new chain starts at top
        origChainPtr = origChainPtr->getNext(); // start with next item in original chain
        
        while (origChainPtr != 0) // copy rest of list
        {
            ItemType nextItem = origChainPtr->getItem();
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem); // create new node
            newChainPtr->setNext(newNodePtr); // add new node to queue
            newChainPtr = newChainPtr->getNext(); // walk to next item
            origChainPtr = origChainPtr->getNext();
        }
        
        newChainPtr->setNext(0); // set end of queue
        backPtr = newChainPtr;
    }
}

// destructor for LinkedQueue, dequeues everything in the queue
template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
    while (!isEmpty())
        dequeue();
}

//enqueue function which adds to the back of the queue, and checks if it was empty (if it was, also assign the frontPtr, but it not, link the new node to the old back node)
template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry)
{
    Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
    
    if (isEmpty())
        frontPtr = newNodePtr; // assign the frontPtr if empty
    else
        backPtr->setNext(newNodePtr); // link new node to the old back node
    
    backPtr = newNodePtr; // add to back of queue
	count++;
	return true;
}

//dequeue removes from the front of the queue, but if it becomes empty after removing it, the backPtr is updated
template<class ItemType>
bool LinkedQueue<ItemType>::dequeue()
{
	if (count == 0) // if queue is empty
		return false;
 
	// code to remove data
    Node<ItemType>* nodeToDeletePtr = frontPtr; // set to front of the queue
    frontPtr = frontPtr->getNext();
    nodeToDeletePtr->setNext(0); // set to null
    delete nodeToDeletePtr; // if front of the queue
    
	count--;
    
    if (count == 0){ // if the queue becomes empty after deletion, update backPtr to null
        backPtr = 0;
    }
    
	return true;
}

#endif

