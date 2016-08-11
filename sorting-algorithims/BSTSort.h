// BSTSort.h

#ifndef BST_SORT_H
#define BST_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"
#include "bst.h"

class BSTSort : public SortingAlgorithm {
 public:
  virtual void sort(Array& A)
  {
    BST bst;
    for (int i = 0; i < A.length(); ++i) {
      bst.insert(A[i]);
    }
    int startIndex = 0;
    bst.inorder(A, startIndex);
  }
};

#endif

