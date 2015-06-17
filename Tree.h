// File Tree.h
// Template definitions for Trees, which are general trees
#ifndef Tree_H
#define Tree_H
#include <string>

// advanced prototype for the TreeNode to use to declare a friend
template <class Object>
class Tree;

// ---------------------- TreeNode Prototype --------------------------
template <class Object>
class TreeNode
{
   friend class Tree<Object>;

protected:
   TreeNode *firstChild, *sib, *prev;
   Object data;
   TreeNode *myRoot;  // needed to test for certain error

public:
   TreeNode( const Object & d = Object(),
      TreeNode *sb = NULL, TreeNode *chld = NULL, TreeNode *prv = NULL )
      : firstChild(chld), sib(sb), prev(prv), data(d), myRoot(NULL)
   { }
   Object GetData() const { return data; }

protected:
   // for use only by Tree
   TreeNode( const Object & d,
      TreeNode *sb, TreeNode *chld, TreeNode *prv,
      TreeNode *root )
      : firstChild(chld), sib(sb), prev(prv), data(d), myRoot(root)
   { }
};
// ---------------------- Tree Prototype --------------------------
template <class Object>
class Tree
{
protected:
   int mSize;
   TreeNode<Object> *mRoot;

public:
   Tree() { mSize = 0; mRoot = NULL; }
   Tree(const Tree &rhs) { mRoot = NULL; mSize = 0; *this = rhs; }
   virtual ~Tree() { clear(); }
   bool empty() const { return (mSize == 0); }
   int size() const { return mSize; }
   void clear() { removeNode(mRoot); }
   const Tree & operator=(const Tree &rhs);

   TreeNode<Object> *addChild( TreeNode<Object> *treeNode, const Object &x );

   TreeNode<Object> *find(const Object &x) { return find(mRoot, x); }
   TreeNode<Object> *find(TreeNode<Object> *root,
      const Object &x, int level = 0);

   bool remove(const Object &x) { return remove(mRoot, x); }
   bool remove(TreeNode<Object> *root, const Object &x);
   void removeNode(TreeNode<Object> *nodeToDelete);

   void display(TreeNode<Object> *treeNode = NULL, int level = 0) const;

   template <class Processor>
   void traverse(Processor func, TreeNode<Object> *treeNode = NULL) const;

protected:
   TreeNode<Object> *clone( TreeNode<Object> *root) const;
   void setMyRoots(TreeNode<Object> *treeNode);
};

// public interface methods of Tree ------------------------
template <class Object>
TreeNode<Object>* Tree<Object>::find(TreeNode<Object> *root,
   const Object &x, int level)
{
   TreeNode<Object> *retval;

   if (mSize == 0 || root == NULL)
      return NULL;

   if (root->data == x)
      return root;

   // otherwise, recurse.  don't process sibs if this was the original call
   if ( level > 0 && (retval = find(root->sib, x, level)))
      return retval;
   return find(root->firstChild, x, ++level);
}

template <class Object>
bool Tree<Object>::remove(TreeNode<Object> *root, const Object &x)
{
   TreeNode<Object> *tn = NULL;

   if (mSize == 0 || root == NULL)
      return false;

   if ( (tn = find(root, x)) != NULL )
   {
      removeNode(tn);
      return true;
   }
   return false;
}

template <class Object>
const Tree<Object> &Tree<Object>::operator=
   (const Tree &rhs)
{
   if (&rhs != this)
   {
      clear();
      mRoot = clone(rhs.mRoot);
      mSize = rhs.mSize;
      setMyRoots(mRoot);
   }
   return *this;
}

template <class Object>
void Tree<Object>::removeNode(TreeNode<Object> *nodeToDelete)
{
   if (nodeToDelete == NULL || mRoot == NULL)
      return;
   if (nodeToDelete->myRoot != mRoot)
      return;  // silent error, node does not belong to this tree

   // remove all the children of this node
   while (nodeToDelete->firstChild)
      removeNode(nodeToDelete->firstChild);

   if (nodeToDelete->prev == NULL)
      mRoot = NULL;  // last node in tree
   else if (nodeToDelete->prev->sib == nodeToDelete)
      nodeToDelete->prev->sib = nodeToDelete->sib; // adjust left sibling
   else
      nodeToDelete->prev->firstChild = nodeToDelete->sib;  // adjust parent

   // adjust the successor sib's prev pointer
   if (nodeToDelete->sib != NULL)
      nodeToDelete->sib->prev = nodeToDelete->prev;

   delete nodeToDelete;
  --mSize;
}

template <class Object>
TreeNode<Object> *Tree<Object>::addChild(
   TreeNode<Object> *treeNode, const Object &x )
{
   // empty tree? - create a root node if user passes in NULL
   if (mSize == 0)
   {
      if (treeNode != NULL)
         return NULL; // silent error something's fishy.  treeNode can't right
      mRoot = new TreeNode<Object>(x, NULL, NULL, NULL);
      mRoot->myRoot = mRoot;
      mSize = 1;
      return mRoot;
   }
   if (treeNode == NULL)
      return NULL; // silent error inserting into a non_null tree with a null parent
   if (treeNode->myRoot != mRoot)
      return NULL;  // silent error, node does not belong to this tree

   // push this node into the head of the sibling list; adjust prev pointers
   TreeNode<Object> *newNode = new TreeNode<Object>(x,
      treeNode->firstChild, NULL, treeNode, mRoot);  // sib, child, prev, root
   treeNode->firstChild = newNode;
   if (newNode->sib != NULL)
      newNode->sib->prev = newNode;
   ++mSize;
   return newNode;
}

template <class Object>
void Tree<Object>::display(TreeNode<Object> *treeNode, int level) const
{
   TreeNode<Object> *child;

   // this will be static and so will be shared by all calls
   static string blankString = "                                    ";
   string indent;

   // stop runaway indentation/recursion
   if  (level > (int)blankString.length() - 1)
   {
      cout << blankString << " ... " << endl;
      return;
   }

   indent = blankString.substr(0, level);

   if (mRoot == NULL)
      return;
   if (treeNode == NULL)
   {
      display(mRoot);
      return;
   }

   cout << indent << treeNode->data  << endl;
   for (child = treeNode->firstChild; child != NULL; child = child->sib)
      display(child, level+1);
}

template <class Object>
template <class Processor>
void Tree<Object>::traverse(Processor func, TreeNode<Object> *treeNode) const
{
   TreeNode<Object> *child;

   if (mRoot == NULL)
      return;
   if (treeNode == NULL)
   {
      traverse(func, mRoot);
      return;
   }

   func(treeNode->data);

   for (child = treeNode->firstChild; child != NULL; child = child->sib)
      traverse(func, child);
}

// FHsearchTree protected method definitions -----------------------------
template <class Object>
TreeNode<Object> *Tree<Object>::clone(
   TreeNode<Object> *root) const
{
   TreeNode<Object> *newNode;
   if (root == NULL)
      return NULL;

   // does not set myRoot which must be done by caller
   newNode = new TreeNode<Object>(
      root->data,
      clone(root->sib), clone(root->firstChild));
   if (newNode->sib)
      newNode->sib->prev = newNode;
   if (newNode->firstChild)
      newNode->firstChild->prev = newNode;
   return newNode;
}

template <class Object>
void Tree<Object>::setMyRoots(TreeNode<Object> *treeNode)
{
   TreeNode<Object> *child;

   if (mRoot == NULL)
      return;

   treeNode->myRoot = mRoot;
   for (child = treeNode->firstChild; child != NULL; child = child->sib)
      setMyRoots(child);
}

#endif
