// MergeSort.h

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"

class MergeSort : public SortingAlgorithm {

 public:
  virtual void sort(Array& A){
    mergesort(A, A.length());
  }
  void mergesort(Array& A, int size)
{
   if(size > 1){
        int subsize1= size/2;
        int subsize2 = size - subsize1;
        mergesort(A, subsize1); //sort from 0 to subsize 1
        Array B = Array(subsize2);
            for(int i = 0; i < subsize2; i++){
                B[i] = A[subsize1+i];
            }
        mergesort(B, subsize2); //sort from subsize 1 to the end
        merge(A, B, subsize1,subsize2);
   }
}
void merge(Array& A, Array& B, int n1, int n2)
{
     Array temp = Array(n1+n2);
     int copied  = 0;
     int copied1 = 0;
     int copied2 = 0;

     //merge elements into a temporary array
     while((copied1 < n1) && (copied2 < n2)){
        if(A[copied1] <= B[copied2]){
            temp[copied] = A[copied1];
            copied++;
            copied1++;
        }
        else{
            temp[copied] = B[copied2];
            copied++;
            copied2++;
        }
     }
     // copy remaining entires
     while(copied1 < n1){
        temp[copied] = A[copied1];
        copied1++;
        copied++;
     }
     while(copied2 < n2){
        temp[copied] = B[copied2];
        copied2++;
        copied++;
     }
     //now, copy A to temp
     for(int i =0; i < n1+n2; i++){
        A[i] = temp[i];
     }

}

};

#endif

