#ifndef __HW4__BinarySearchTree__
#define __HW4__BinarySearchTree__

#include "BinaryNode.h"
#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    // a PRIVATE pointer to function member variable (returns an int, has 2 const ItemType& parameters)
    int (*compare)(const ItemType&, const ItemType&);
    
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
    
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
    
    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
    
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
    
    // search for target node
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
    
public:
    BinarySearchTree(int compareFunction(const ItemType&, const ItemType&));
    BinarySearchTree(const BinarySearchTree<ItemType> &tree);
    // insert a node at the correct location
    bool insert(const ItemType & newEntry);
    // remove a node if found
    bool remove(const ItemType & anEntry);
    // find a target node
    bool getEntry(const ItemType & target, ItemType & returnedItem) const;
    // NOT IN THE Tree Code Files on Catalyst, use for HW#4:
    BinarySearchTree & operator=(const BinarySearchTree & sourceTree);
};


///////////////////////// public function definitions ///////////////////////////
//constructor that has a compare function parameter and assigns it to the function member variable
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(int compareFunction(const ItemType&, const ItemType&))
{
    compare = compareFunction;
}

//copy constructor that assigns the parameter's pointer to the function member variable then calls copyTree
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType> &tree)
{
    compare = tree.compare;
    this->count = 0;
    this->rootPtr = this->copyTree(tree.rootPtr);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}

// function that returns true if the parameter was found in the tree
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType>* temp_node = findNode(this->rootPtr, anEntry);
    
    if (temp_node){
        returnedItem = temp_node->getItem();
        return true;
    }
    else{
        return false;
    }
}

//NOT IN THE Tree Code Files on Catalyst, use for HW#4:
template<class ItemType>
BinarySearchTree<ItemType> & BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType> & sourceTree)
{
    compare = sourceTree.compare;
    this->BinaryTree<ItemType>::operator=(sourceTree);
    return *this;
}


//////////////////////////// private functions //////////////////////////////////

// Done as class exercise:
template<class ItemType> BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,BinaryNode<ItemType>* newNodePtr)
{
    if( nodePtr==0 )
        return newNodePtr;
    if (compare(newNodePtr->getItem(), nodePtr->getItem()) < 0)
        nodePtr->setLeftPtr(_insert( nodePtr->getLeftPtr(), newNodePtr ));
        else
            nodePtr->setRightPtr(_insert( nodePtr->getRightPtr(), newNodePtr ));
            return nodePtr; // must return
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target, bool & success)
{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    if (compare(nodePtr->getItem(), target) > 0)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (compare(nodePtr->getItem(), target) < 0)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else	// found the node
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType newNodeValue;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}


// finds the parameter in the BST and returns it
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const
{
    if (nodePtr == 0){
        return 0;
    }
    else if (compare(nodePtr->getItem(), target) > 0)
    {
        return findNode(nodePtr->getLeftPtr(), target);
    }
    else if (compare(nodePtr->getItem(), target) < 0)
    {
        return findNode(nodePtr->getRightPtr(), target);
    }
    return nodePtr;
}

#endif

