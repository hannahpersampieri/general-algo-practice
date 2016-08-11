// ExchangeSort.h

#ifndef EXCHANGE_SORT_H
#define EXCHANGE_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"

class ExchangeSort : public SortingAlgorithm {
 public:
  virtual void sort(Array& A)
  {
    for (int i = 0; i < A.length(); ++i) {
      for (int j = i + 1; j < A.length(); ++j) {
	if (A[i] > A[j]) {
	  // Exchange
	  int temp = A[i];
	  A[i] = A[j];
	  A[j] = temp;
	}
      }
    }
  }
};

#endif

