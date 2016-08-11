// PoorQuickSort.h

#ifndef POOR_QUICK_SORT_H
#define POOR_QUICK_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"
#include <cstdlib>

class PoorQuickSort : public SortingAlgorithm {
 
 public:
  virtual void sort(Array& A)
  {
    poorquicksort(A,0,A.length()-1);
  }
  void poorquicksort(Array& A, int low, int high){
  		int i = low + 1;
      int j = high;
      int temp;
      if(i > j){
        return;
      }
      while( i <= j){
        if(A[i] < A[low]){
          i++;
        }
        else if(A[j] > A[low]){
          j--;
        }
        else if (i <= j){
          temp = A[i];
          A[i] = A[j];
          A[j] = temp;
        }
      }
      temp = A[low];
      A[low] = A[j];
      A[j] = temp;
      poorquicksort(A, low, j - 1);
      poorquicksort(A, j+1, high);
  }
 
};

#endif

