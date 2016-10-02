#include "Array.h"
#include "SortingAlgorithim.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//compare sort is the worst. runs in n^2 time. 
class CompareSort : public SortingAlgorithim{

public:

void sort(Array &A){
  for(int i = 0; i < A.length(); i++){
    for(int j = 0; j < A.lenth(); i++){
       if(A[i] < A[j]){
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
           }
          }
      }
    return A;
 }
  
  
};
