// Heap.h

#ifndef HEAP_H
#define HEAP_H

#include "Array.h"

using namespace std;

template <typename T>
class Heap {

 public:

  Heap(int aLen) : hA(aLen+1), mLen(0)
  {}

  // Just insert the elements into the heap array
  // ignoring the heap order property
  void insertIgnoringHeapOrder(T aElem)
  {
    if (mLen == hA.length()) {
      std::cout << "Cannot take in any more data into the allocated heap." << std::endl;
      return;
    }
    hA[++mLen] = aElem;
  }

  // Extract the min and delete the entry from heap
  // -- O(lg n)
  T removeMin()
  {
    T result = hA[1];
    hA[1] = hA[mLen];
    mLen--;
    bubbleDown(1);
    return result;
  }

  // Heapify -- O(n)
  void bottomUpMinHeap()
  {
    // Go through all the internal nodes
    for (int j = mLen/2; j > 0; j--) {
      // Bubble down hA[j] finding an appropriate place
      bubbleDown(j);
    }
  }

  // In-place sort in descending order
  void sort()
  {
    // Heapify -- O(n)
    bottomUpMinHeap();
    std::cout << "Sorted output: " << std::endl;
    // In-place sort within hA
    for (int i = 1; i < hA.length(); ++i) {
      // Remove the min -- O(lg n)
      T min = removeMin(); 
      // Prepend in the sorted section
      // Remove min has decremented mLen 
      // so need to increment the mLen by 1
      hA[mLen+1] = min;
      std::cout << min->key() << std::endl;
    }
  }

  // Check if the heap is empty
  bool isEmpty() const
  {
    return (mLen == 0);
  }

 private:
  // Bubble down hA[j] to an appropriate place
  void bubbleDown(int j)
  {
    int k = j * 2; 
    while (k <= mLen) {
      int min;
      int nextk;
      if (k == mLen) {
	// No right child
	min = hA[k]->key();
	nextk = k;
      } else if (hA[k]->key() < hA[k+1]->key()) {
	min = hA[k]->key();
	nextk = k;
      } else {
	// hA[k]->key() >= hA[k+1]->key()
	min = hA[k+1]->key();
	nextk = k+1;
      }
      // If parent is greater than min, swap with min
      if (hA[j]->key() > min) {
	// Swap hA[j] and the entry having the min key
	T t = hA[j];
	hA[j] = hA[nextk];
	hA[nextk] = t;
	// Update k for the next iteration
	j = nextk;
	k = nextk * 2;
      } else {
	break;
      }
    }
  }

 private:
  Array<T> hA;
  int mLen;
};

#endif

