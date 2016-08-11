
#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>
#include "Array.h"
#include "bst.h"
#include <cassert>

using namespace std;

template<typename KeyT, typename ValueT>
class SplayTree : public BST<KeyT,ValueT> {
  public:  
enum Orientation {
    NONE,
    RIGHT,
    LEFT
  };
    /// Find a node in the BST containing the given key
    BSTNode<KeyT,ValueT>* find(KeyT aKey)
    {
        BSTNode<KeyT,ValueT>* node = BST<KeyT,ValueT>::find(aKey);
        if (node != nullptr) {
            // Splay the node that is found or the node where the search ended
            splay(node);
        }
        return node;
    }

    /// Find a node in the BST containing the given key.
    /// If exact match not found, return nullptr but also set the approxMatchNode
    BSTNode<KeyT,ValueT>* findApprox(KeyT aKey, 
                                     BSTNode<KeyT,ValueT>*& approxMatchNode_lb,
                                     BSTNode<KeyT,ValueT>*& approxMatchNode_ub)
    {
        BSTNode<KeyT,ValueT>* node = BST<KeyT,ValueT>::findApprox(aKey, 
                                                                  approxMatchNode_lb,
                                                                  approxMatchNode_ub);
        if (node != nullptr) {
            // Splay the node that is found or the node where the search ended
            splay(node);
        } else {
	  if (approxMatchNode_lb)
            splay(approxMatchNode_lb);
	  if (approxMatchNode_ub)
	    splay(approxMatchNode_ub);
        }
        return node;
    }
  
    /// Find min
    BSTNode<KeyT,ValueT>* getMin() 
    { 
        BSTNode<KeyT,ValueT>* minBSTNode = BST<KeyT,ValueT>::getMin(); 
        if (minBSTNode != nullptr) {
            // Splay the min node
            splay(minBSTNode);
        }
        return minBSTNode;
    }

    /// Find max
    BSTNode<KeyT,ValueT>* getMax() 
    { 
        BSTNode<KeyT,ValueT>* maxBSTNode = BST<KeyT,ValueT>::getMax(); 
        if (maxBSTNode != nullptr) {
            // Splay the max node
            splay(maxBSTNode);
        }
        return maxBSTNode;
    }

    /// Remvoe
    void remove(KeyT aKey) 
    { 
        BSTNode<KeyT,ValueT>* parentNode = BST<KeyT,ValueT>::remove(aKey); 
	if (parentNode != nullptr) {
            // Splay the parent node of the removed node
            splay(parentNode);
        }
    }

    /// Zig rotation -- left to right
  /// Scenario: aNode is a left child of root
  void zigLR(BSTNode<KeyT,ValueT>* aNode, BSTNode<KeyT,ValueT>* aParent)
  {
    BSTNode<KeyT,ValueT>* rightChild = aNode->right();
    aNode->setRight(aParent);
    aParent->setParent(aNode);
    aParent->setLeft(rightChild);
    if (rightChild != NULL) {
      rightChild->setParent(aParent);
    }
    // Set the new root
    if (BST<KeyT,ValueT>::root()== aParent) {
      this->setRoot(aNode);
      aNode->setParent(NULL);
    }
  }
  //Zag rotation
  void zagRL(BSTNode<KeyT,ValueT>*& aNode, BSTNode<KeyT,ValueT>*& aParent){
    BSTNode<KeyT,ValueT>* leftChild = aNode->left();
    aNode->setLeft(aParent);
    aParent->setParent(aNode);
    aParent->setRight(leftChild);
    if(leftChild != NULL){
        leftChild->setParent(aParent);
    }
    //setting root, if necessary
    if(BST<KeyT,ValueT>::root() == aParent){
        this->setRoot(aNode);
        aNode->setParent(NULL);
    }
  }

  /// Zigzag rotation --
  /// around parent from left to right
  /// around grandparent from right to left
  /// Scenario: aNode is a left child of a right child
  void zigLRzagRL(BSTNode<KeyT,ValueT>*& aNode, BSTNode<KeyT,ValueT>*& aParent, BSTNode<KeyT,ValueT>*& aGrandParent)
  {
    BSTNode<KeyT,ValueT>* ggParent = aGrandParent->parent();
    SplayTree::Orientation orient = SplayTree<KeyT,ValueT>::NONE;
    if (ggParent != NULL) {
      if (ggParent->left() == aGrandParent) {
        orient = SplayTree<KeyT,ValueT>::LEFT;
      } else {
        orient = SplayTree<KeyT,ValueT>::RIGHT;
      }
    }
    // Rotate around the parent from left to right
    zigLR(aNode, aParent);
    // Rotate around the grandparent from right to left
    zagRL(aNode, aGrandParent);
    if (orient == SplayTree<KeyT,ValueT>::LEFT) {
      ggParent->setLeft(aNode);
      aNode->setParent(ggParent);
    } else if (orient == SplayTree<KeyT,ValueT>::RIGHT) {
      ggParent->setRight(aNode);
      aNode->setParent(ggParent);
    }
  }
  //Zigzag -- around parent from right to left
  // around grandparent from left to right
  // aNode is a right child of a left child
  void zigRLzagLR(BSTNode<KeyT,ValueT>* aNode, BSTNode<KeyT, ValueT>* aParent, BSTNode<KeyT, ValueT>* aGrandParent)
  {
    BSTNode<KeyT,ValueT>* ggParent = aGrandParent->parent();
    SplayTree::Orientation orient = SplayTree<KeyT,ValueT>::NONE;
    if (ggParent != NULL) {
      if (ggParent->left() == aGrandParent) {
        orient = SplayTree<KeyT,ValueT>::LEFT;
      } else {
        orient = SplayTree<KeyT,ValueT>::RIGHT;
      }
    }
    // Rotate around the parent from left to right
    zagRL(aNode, aParent);
    // Rotate around the grandparent from right to left
    zigLR(aNode, aGrandParent);
    if (orient == SplayTree<KeyT,ValueT>::LEFT) {
      ggParent->setLeft(aNode);
      aNode->setParent(ggParent);
    } else if (orient == SplayTree<KeyT,ValueT>::RIGHT) {
      ggParent->setRight(aNode);
      aNode->setParent(ggParent);
    }
  }
  
  //zigzig operations
  //aNode is a right child of a right child
  void zigRLzigRL(BSTNode<KeyT,ValueT>* aNode,BSTNode<KeyT,ValueT>* aParent, BSTNode<KeyT,ValueT>* aGrandParent){
        BSTNode<KeyT,ValueT>* ggParent = aGrandParent->parent();
    SplayTree::Orientation orient = SplayTree<KeyT,ValueT>::NONE;
    if (ggParent != NULL) {
      if (ggParent->left() == aGrandParent) {
        orient = SplayTree<KeyT,ValueT>::LEFT;
      } else {
        orient = SplayTree<KeyT,ValueT>::RIGHT;
      }
    }
        //rotate RL about grandparent first
        zagRL(aParent, aGrandParent);
        //rotate RL about parent second
        zagRL(aNode, aParent);
         if (orient == SplayTree<KeyT,ValueT>::LEFT) {
      ggParent->setLeft(aNode);
      aNode->setParent(ggParent);
    } else if (orient == SplayTree<KeyT,ValueT>::RIGHT) {
      ggParent->setRight(aNode);
      aNode->setParent(ggParent);
    }
  }

  //aNode is a left child of a left child
  void zigLRzigLR(BSTNode<KeyT,ValueT>* aNode,BSTNode<KeyT,ValueT>* aParent, BSTNode<KeyT,ValueT>* aGrandParent){
    BSTNode<KeyT,ValueT>* ggParent = aGrandParent->parent();
    SplayTree::Orientation orient = SplayTree<KeyT,ValueT>::NONE;
    if (ggParent != NULL) {
      if (ggParent->left() == aGrandParent) {
        orient = SplayTree<KeyT,ValueT>::LEFT;
      } else {
        orient = SplayTree<KeyT,ValueT>::RIGHT;
      }
    }
    zigLR(aParent, aGrandParent);
    zigLR(aNode, aParent);
     if (orient == SplayTree<KeyT,ValueT>::LEFT) {
      ggParent->setLeft(aNode);
      aNode->setParent(ggParent);
    } else if (orient == SplayTree<KeyT,ValueT>::RIGHT) {
      ggParent->setRight(aNode);
      aNode->setParent(ggParent);
    }
  }
     /// Splay operation
void splay(BSTNode<KeyT,ValueT>* aNode){
        BSTNode<KeyT,ValueT>* parent = aNode->parent();
        if (parent == NULL) {
            return;
        }
        BSTNode<KeyT,ValueT>* grandParent = parent->parent();
        while (parent != NULL && grandParent != NULL){
        // All zigzag and zigzig operations go here      
            if(aNode == parent->left() and parent == grandParent->right()){ //left child of a right child
                zigLRzagRL(aNode, parent, grandParent);
            }
            else if(aNode == parent->right() and parent == grandParent ->left()){
                zigRLzagLR(aNode, parent, grandParent);
            }
            else if(aNode == parent->left() and parent == grandParent ->left()){
                zigLRzigLR(aNode, parent, grandParent);
            }
            else{ 
                zigRLzigRL(aNode, parent, grandParent);
            }
        // Evaluate new parent and grandparent after rotations
        parent = aNode->parent();
        if (parent == NULL) {
            break;
        }
        grandParent = parent->parent();
        if (grandParent == NULL) {
            break;
        }
    }
    // Zig operation is done only as a last pass
    // after Zigzig and/or Zigzag operations
    if (grandParent == NULL) {
      // Parent is the root -- Zig operation
      if (parent->left() == aNode) {
        // aNode is a left child of root
        // Zig operation
        zigLR(aNode, parent);
      } else {
        // aNode is a right child of root
        // Zig operation
        zagRL(aNode, parent);
      }
    }
}
    
};


#endif
