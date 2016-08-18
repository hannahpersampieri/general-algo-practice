
#include "sll.h"
#include <iostream>

using namespace std;

int main()
{
  SLinkedList sll;

  sll.addFront(8);
  sll.addFront(3);
  sll.addFront(20);
  sll.addFront(28);
  sll.addFront(50);
  sll.addFront(35);
  sll.addFront(100);
  sll.addFront(46);
  sll.addFront(29);
  sll.addFront(212);

  cout << "List before sorting:" << endl;
  cout << sll;
  
  // Sorting the list
  sll.sort();

  cout << "List after sorting:" << endl;
  cout << sll;

  return 0;
}
