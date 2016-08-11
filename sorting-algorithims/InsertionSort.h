// InsertionSort.h

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"

class InsertionSort : public SortingAlgorithm {
 public:
  virtual void sort(Array& A)
  {
    int length = A.length();
 	for (int i = 1; i < length; i++) {
 		int j = i;
 		while (j > 0 && A[j - 1] > A[j]) {
 			int tmp = A[j];
 			A[j] = A[j - 1];
 			A[j - 1] = tmp;
 			j--;
 		}
  	}
  }
};

#endif

