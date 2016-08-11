// QuickSort.h

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"
#include <cstdlib>

class QuickSort : public SortingAlgorithm {
 
 public:
  virtual void sort(Array& A)
  {
    quicksort(A,0,A.length());
  }
void quicksort(Array& A, int low, int high){
  		//base case
  		if(high - low < 2){
  			return;
  		}
  		int pivot = midof3(A, low, high);
      quicksort(A, low, pivot);
      quicksort(A, pivot, high);
  		
}
int midof3(Array& A, int low, int high){
  	int x = A[low];
    int y = A[(high-low)/(2+low)];
    int z = A[high-1];
    int i = low-1;
    int j = high;
    int temp;
    if(((y > x) and (y < x)) or ((y >z) and (y < x))){
      x = y;
    }
    else if (((z > x) and (z < y)) or ((z > y) and (z < x))){
      x = z;
    }
    while(1){
      do{
        j--;
      } while(A[j] > x);
      do {
        i++;
      }while(A[i] < x);
      if (i < j){
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
      } 
      else {
        return (j + 1);
      }
    }
  }
};

#endif

