// bst.cpp
#include <iostream>
#include "bst.h"

using namespace std;

/// Get predecessor
BSTNode* BSTNode::pred() const
{
  BSTNode* lc = const_cast<BSTNode*>(left());
  if (lc == NULL) {
    return NULL;
  }
  while (lc->right() != NULL) {
    lc = lc->right();
  }
  return lc;
}

/// Get successor
BSTNode* BSTNode::succ() const
{
  BSTNode* rc = const_cast<BSTNode*>(right());
  if (rc == NULL) {
    return NULL;
  }
  while (rc->left() != NULL) {
    rc = rc->left();
  }
  return rc;
}


/// Find min
BSTNode* BSTNode::getMin()
{
  if (left() == NULL) {
    return this;
  }
  return left()->getMin();
}

/// Find max
BSTNode* BSTNode::getMax()
{
  if (right() == NULL) {
    return this;
  }
  return right()->getMax();

}

/// Swap left
void BSTNode::swapLeft()
{
  BSTNode* c = left();
  BSTNode* p = parent();
  if (p->left() == this) {
    p->setLeft(c);
  } else {
    p->setRight(c);
  }
}

/// Swap right
void BSTNode::swapRight()
{
  BSTNode* c = right();
  BSTNode* p = parent();
  if (p->left() == this) {
    p->setLeft(c);
  } else {
    p->setRight(c);
  }
}


/// Detach from parent
void BSTNode::detachFromParent() 
{
  BSTNode* p = parent();
  if (p == NULL) {
    return;
  }
  if (p->left() == this) {
    p->setLeft(NULL);
  } else {
    p->setRight(NULL);
  }
}

void BSTNode::inorder() const
{
  if (left()) {
    left()->inorder();
  }
  cout << key() << endl;
  if (right()) {
    right()->inorder();
  }
}

void BSTNode::inorder(Array& a, int &aIndex) const
{
  if (left()) {
    left()->inorder(a, aIndex);
  }
  a[aIndex++] = key();
  if (right()) {
    right()->inorder(a, aIndex);
  }
}

void BSTNode::postorder() const
{
  if (left()) {
    left()->postorder();
  }
  if (right()) {
    right()->postorder();
  }
  cout << key() << endl;
}

void BSTNode::preorder() const
{
  cout << key() << endl;
  if (left()) {
    left()->preorder();
  }
  if (right()) {
    right()->preorder();
  }
}

/// Find a node in the BST containing the given key
BSTNode* BSTNode::find(int aKey) 
{
  if (key() == aKey) {
    // found
    return this;
  }
  if (aKey < key()) {
    if (left()) {
      return left()->find(aKey);
    } else {
      return this;
    }
  } else if (aKey > key()) {
    if (right()) {
      return right()->find(aKey);
    } else {
      return this;
    }
  }
  return NULL;
}

/// Print the tree starting from this node
void BSTNode::output(ostream& s) const
{
  static int count = 0;
  if (left() != NULL) {
    s << key() << " -> " << left()->key() << endl; // << " [label=\"L\"] " << endl;
    left()->output(s);
  } else {
    s << "NULL" << count << "[shape=point]" << endl;
    s << key() << " -> " << "NULL" << count++ << endl;
  }
  if (right() != NULL) {
    s << key() << " -> " << right()->key() << endl; // " [label=\"R\"] " << endl;
    right()->output(s);
  } else {
    s << "NULL" << count << "[shape=point]" << endl;
    s << key() << " -> " << "NULL" << count++ << endl;
  }
}

///////////////////////////////////////


/// Insert a new key in the BST
BSTNode* BST::insert(int aKey)
{
  BSTNode* place = find(aKey);
  BSTNode* newNode = NULL;
  if (place == NULL) {
    // First node to be inserted
    newNode = new BSTNode(aKey);
    mRoot = newNode;
  } else if (aKey < place->key()) {
    newNode = new BSTNode(aKey, NULL, NULL, place);
    // Node on the left of place
    place->setLeft(newNode);
  } else {
    newNode = new BSTNode(aKey, NULL, NULL, place);
    // Node on the right of place
    place->setRight(newNode);
  }
  return newNode;
}

// Cases 1, 2 and 3
BSTNode* BST::trivialRemove(BSTNode* n)
{
  BSTNode* parent = n->parent();    
  if (n->left() == NULL && 
      n->right() == NULL) {
    // Case 1: No children
    // Detach it from the parent
    n->detachFromParent();
    delete n;
    return parent;
  }
  if (n->left() == NULL &&
      n->right() != NULL) {
    // Case 2: n has only right child
    n->swapRight();
    delete n;
    return parent;
  }
  if (n->right() == NULL &&
      n->left() != NULL) {
    // Case 3: n has only left child
    n->swapLeft();
    delete n;
  }
  return parent;
}

/// delete a node corresponding to a given key in the BST
/// and return the pointer to the parent
/// of the node that actually got deleted
BSTNode* BST::remove(int aKey)
{
  BSTNode* n = find(aKey);
  if (n == NULL ||
      n->key() != aKey) {
    // No node containing aKey
    return NULL;
  }
  // Trivial remove
  trivialRemove(n);
  if (n->left() != NULL &&
      n->right() != NULL) {
    // Case 4: n has both left and right child
    BSTNode* s = n->succ();
    n->setKey(s->key());
    trivialRemove(s);
  } else {
    // Cases 1, 2 and 3
    trivialRemove(n);
  }
}

/// Print inorder
void BST::inorder() const
{
  if (mRoot) mRoot->inorder();
}

/// Store sorted data into the given array
void BST::inorder(Array& a, int& aIndex) const
{
  if (mRoot) mRoot->inorder(a, aIndex);
}

/// Print preorder
void BST::preorder() const
{
 if (mRoot) mRoot->preorder();
}

/// Print postorder
void BST::postorder() const
{
  if (mRoot) mRoot->postorder();
}

void BST::output(ostream& s) const
{
  s << "digraph{" << endl;
  if (mRoot) mRoot->output(s);
  s << "}" << endl;
}

std::ostream& operator<<(std::ostream& s, const BST& bst)
{
  bst.output(s);
  return s;
}
