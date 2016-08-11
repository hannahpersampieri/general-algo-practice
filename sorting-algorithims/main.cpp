// main.cpp
#include <iostream>
#include <ctime>
#include <sys/time.h>

#include "Array.h"  
#include "ExchangeSort.h"  
#include "HeapSort.h"
#include "InsertionSort.h"  
#include "MergeSort.h"  
#include "QuickSort.h"  
#include "SelectionSort.h"  
#include "SortingAlgorithm.h"
#include "BSTSort.h"
#include "SplaySort.h"
#include "PoorQuickSort.h"

using namespace std;

inline unsigned long getTime()
{
  timeval t;
  gettimeofday(&t, NULL);
  return t.tv_usec;
}

// All sorting is performed in the ascending order

int main()
{
  Array A(1000);
  
  SortingAlgorithm* algorithm;

  // Please comment out portions except for the three algorithms
  // you are interested in
  
  ////////////////////////////////////////////////
  // EXCHANGE SORT
  // Set the inputs in the descending order
  for (int i = 0; i < 1000; ++i) {
    A[i] = 1000-i;
  }
  // Sorting using Exchange sort
  algorithm = new ExchangeSort();
  A.setSortingAlgorithm(algorithm);
  // Sort in the ascending order
  unsigned long t1 = getTime();
  A.sort();
  unsigned long t2 = getTime();
  // Print after sorting
  cout << "After sorting with exchange sort: " << endl;
  cout << A;
  unsigned long exchangeSortTime = t2 - t1;
  delete algorithm;

  ////////////////////////////////////////////////

  /*////////////////////////////////////////////////
  // HEAP SORT
  // Set the inputs in the descending order
  for (int i = 0; i < 1000; ++i) {
    A[i] = 1000-i;
  }
  // Sorting using Heap sort
  algorithm = new HeapSort(A);
  A.setSortingAlgorithm(algorithm);
  // Sort in the ascending order
  t1 = getTime();
  A.sort();
  t2 = getTime();
  // Print after sorting
  cout << "After sorting with heap sort: " << endl;
  cout << A;
  unsigned long heapSortTime = t2 - t1;
  delete algorithm; */

 ////////////////////////////////////////////////
  // INSERTION SORT
  // Set the inputs in the descending order
  for (int i = 0; i < 1000; ++i) {
    A[i] = 1000-i;
  }
  // Sorting using Insertion sort
  algorithm = new InsertionSort();
  A.setSortingAlgorithm(algorithm);
  // Sort in the ascending order
  t1 = getTime();
  A.sort();
  t2 = getTime();
  // Print after sorting
  cout << "After sorting with insertion sort: " << endl;
  cout << A;
  unsigned long insertionSortTime = t2 - t1;
  delete algorithm; 

  ////////////////////////////////////////////////
  // MERGE SORT
  // Set the inputs in the descending order
  for (int i = 0; i < 1000; ++i) {
    A[i] = 1000-i;
  }
  // Sorting using Merge sort
  algorithm = new MergeSort();
  A.setSortingAlgorithm(algorithm);
  // Sort in the ascending order
  t1 = getTime();
  A.sort();
  t2 = getTime();
  // Print after sorting
  cout << "After sorting with merge sort: " << endl;
  cout << A;
  unsigned long mergeSortTime = t2 - t1;
  delete algorithm;

  ////////////////////////////////////////////////
  // QUICK SORT
  // Set the inputs in the descending order
  for (int i = 0; i < 1000; ++i) {
    A[i] = 1000-i;
  }
  // Sorting using Quick sort
  algorithm = new QuickSort();
  A.setSortingAlgorithm(algorithm);
  // Sort in the ascending order
  t1 = getTime();
  A.sort();
  t2 = getTime();
  // Print after sorting
  cout << "After sorting with quick sort: " << endl;
  cout << A;
  unsigned long quickSortTime = t2 - t1;
  delete algorithm;
////////////////////////////////////////////////
  // Poor QUICK SORT
  // Set the inputs in the descending order
  for (int i = 0; i < 1000; ++i) {
    A[i] = 1000-i;
  }
  // Sorting using Quick sort
  algorithm = new PoorQuickSort();
  A.setSortingAlgorithm(algorithm);
  // Sort in the ascending order
  t1 = getTime();
  A.sort();
  t2 = getTime();
  // Print after sorting
  cout << "After sorting with quick sort: " << endl;
  cout << A;
  unsigned long poorquickSortTime = t2 - t1;
  delete algorithm; 

  /* ////////////////////////////////////////////////
  // SELECTION SORT
  // Set the inputs in the descending order
  for (int i = 0; i < 1000; ++i) {
    A[i] = 1000-i;
  }
  // Sorting using Selection sort
  algorithm = new SelectionSort();
  A.setSortingAlgorithm(algorithm);
  // Sort in the ascending order
  t1 = getTime();
  A.sort();
  t2 = getTime();
  // Print after sorting
  cout << "After sorting with selection sort: " << endl;
  cout << A;
  unsigned long selectionSortTime = t2 - t1;
  delete algorithm;*/
 
  /*////////////////////////////////////////////////
  // BST SORT
  // Set the inputs in the descending order
  for (int i = 0; i < 1000; ++i) {
    A[i] = 1000-i;
  }
  // Sorting using BST sort
  algorithm = new BSTSort();
  A.setSortingAlgorithm(algorithm);
  // Sort in the ascending order
  t1 = getTime();
  A.sort();
  t2 = getTime();
  // Print after sorting
  cout << "After sorting with BST sort: " << endl;
  cout << A;
  unsigned long bstSortTime = t2 - t1;
  delete algorithm; */

  /*////////////////////////////////////////////////
  // SPLAY SORT
  // Set the inputs in the descending order
  for (int i = 0; i < 1000; ++i) {
    A[i] = 1000-i;
  }
  // Sorting using Splay sort
  algorithm = new SplaySort();
  A.setSortingAlgorithm(algorithm);
  // Sort in the ascending order
  t1 = getTime();
  A.sort();
  t2 = getTime();
  // Print after sorting
  cout << "After sorting with splay sort: " << endl;
  cout << A;
  unsigned long splaySortTime = t2 - t1;
  delete algorithm; */

  cout << "----------------------------------------" << endl;
  cout << "TIME TAKEN BY VARIOUS SORTING ALGORITHMS" << endl;
  cout << "----------------------------------------" << endl;
  cout << "Exchange Sort: " << exchangeSortTime << endl;
  //cout << "Heap Sort: " << heapSortTime << endl;
  cout << "Insertion Sort: " << insertionSortTime << endl;
  cout << "Merge Sort: " << mergeSortTime << endl;
  cout << "Quick Sort: " << quickSortTime << endl;
  cout << "Poor Quick Sort:" << poorquickSortTime << endl;
  //cout << "Selection Sort: " << selectionSortTime << endl;
  //cout << "Binary Search Tree Sort: " << bstSortTime << endl;
  //cout << "Splay Tree Sort: " << splaySortTime << endl;

  return 0;
}

