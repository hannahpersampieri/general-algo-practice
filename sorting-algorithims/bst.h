
#ifndef BST_H
#define BST_H

#include <iostream>
#include "Array.h"

using namespace std;

class BSTNode {
 public:

  /// Constructors
  explicit BSTNode(int aKey) 
    : mKey(aKey), mLeft(NULL), mRight(NULL), mParent(NULL)
  {}

  explicit BSTNode(int aKey, BSTNode* aLeft, BSTNode* aRight, BSTNode* aParent)
    : mKey(aKey), mLeft(aLeft), mRight(aRight), mParent(aParent)
  {}

  /// Getting and setting key
  int key() const { return mKey; }
  void setKey(int aData) { mKey = aData; }

  /// Getting and setting left child node
  BSTNode* left() { return mLeft; }
  const BSTNode* left() const { return mLeft; }
  void setLeft(BSTNode* aLeft) { mLeft = aLeft; }

  /// Getting and setting right child node
  BSTNode* right() { return mRight; }
  const BSTNode* right() const { return mRight; }
  void setRight(BSTNode* aRight) { mRight = aRight; }

  /// Getting and setting the parent node
  BSTNode* parent() { return mParent; }
  const BSTNode* parent() const { return mParent; }
  void setParent(BSTNode* aParent) { mParent = aParent; }

  /// Getting preds and succs
  BSTNode* pred() const;
  BSTNode* succ() const;

  /// Some utilities
  void swapLeft(); 
  void swapRight();
  void detachFromParent();
  void inorder() const;
  void inorder(Array& a, int &aIndex) const;
  void preorder() const;
  void postorder() const;

  /// Find a node in the BST containing the given key
  BSTNode* find(int aKey);
  /// Find min
  BSTNode* getMin();
  /// Find max
  BSTNode* getMax();
  /// Output
  void output(ostream& s) const;

 private:
  /// Key
  int mKey;
  /// Left child
  BSTNode* mLeft;
  /// Right child
  BSTNode* mRight;
  /// Parent
  BSTNode* mParent;
};

class BST {
 public:  
  BST() 
    : mRoot(NULL)
    {}
  
  /// Setting and getting root
  void setRoot(BSTNode* aNode) { mRoot = aNode; }
  BSTNode* root() { return mRoot; }
  const BSTNode* root() const { return mRoot; }

  /// Find a node in the BST containing the given key
  BSTNode* find(int aKey)
  { 
    if (mRoot) 
      return mRoot->find(aKey); 
    else
      return NULL;
  }

  /// Insert a new key in the BST
  BSTNode* insert(int aKey);
  
  /// Find min
  BSTNode* getMin()
  { 
    if (mRoot == NULL) {
      cout << "No node in the tree." << endl;
      exit(1);
    } 
    return mRoot->getMin(); 
  }

  /// Find max
  BSTNode* getMax()
  { 
    if (mRoot == NULL) {
      cout << "No node in the tree." << endl;
      exit(1);
    } 
    return mRoot->getMax(); 
  }

  /// delete a node corresponding to a given key in the BST
  /// and return the pointer to the parent
  /// of the node that actually got deleted
  BSTNode* remove(int aKey);

  /// Print inorder
  void inorder() const;

  /// Copy the sorted order into an Array
  void inorder(Array& a, int &aIndex) const;

  /// Print preorder
  void preorder() const;

  /// Print postorder
  void postorder() const;

  /// Trivially remove a node n
  BSTNode* trivialRemove(BSTNode* n);

  /// Output the tree
  void output(ostream& s) const;
    
 private:
  /// Root pointer
  BSTNode* mRoot;
};

ostream& operator<<(ostream& s, const BST& bst);

#endif
