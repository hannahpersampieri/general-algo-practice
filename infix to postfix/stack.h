
#ifndef STACK_H
#define STACK_H

#include "sll.h"

/// A stack implementation using singly linked list
class stack {

 public:
  /// Don't need to overwrite the default constructor, destructor, 
  /// copy constructor or assignment operator.

  /// Push aValue into the stack
  void push(int aValue)
  {
    mLL.addFront(aValue);
  }
  /// Pop out the top value from the stack
  void pop()
  {
    if (isEmpty()) {
      cout << "Stack is empty. Cannot pop!" << endl;
      return;
    }
    mLL.removeFront();
  }
  /// Fetch the top value from the stack (without deleting it)
  int top()
  {
    return mLL.front();
  }
  /// Check whether the stack is empty
  bool isEmpty()
  {
    return mLL.isEmpty();
  }
 private:
  SLinkedList mLL;

};

#endif
