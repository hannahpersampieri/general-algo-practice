#ifndef SLL_H
#define SLL_H

#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class SLLNode {
  public:
    /// Constructors
    SLLNode(T aValue) 
      : mValue(aValue),mNext(NULL)
    {
    }
      
    SLLNode(T aValue, SLLNode *aNext)
      : mValue(aValue), mNext(aNext)
    {
    }
    
    /// Get value
    T value() const
    {
      return mValue;
    }

    /// Get next node for const node receiver
    const SLLNode *next() const
    {
      return mNext;
    }
    
    /// Get next node for non-const node receiver
    SLLNode *next()
    {
      return mNext;
    }

    /// Set next node
    void setNext(SLLNode* aNext)
    {
      mNext = aNext;
    }
    
    /// Insert a new node with aValue after this node
    void insertAfter(T aValue)
    {
      mNext = new SLLNode(aValue, mNext);
    }      

    /// Delete after this node
    void deleteAfter()
    {
	if (mNext == NULL) {
	  return;
	}
	SLLNode *node = mNext;
	mNext = node->next();
	delete node;
    }
    
  private:
    T mValue;
    SLLNode* mNext;
};
  

/// Singly Linked List with a head pointer, a tail pointer and size
template <typename T>
class SLinkedList {
 public:
  /// Constructor
  SLinkedList()
    : mHead(NULL), mTail(NULL), mSize(0)
  {
  }

  /// Insert a node in the front of the list
  void add(T aValue)
  {
    mHead = new SLLNode<T>(aValue, mHead);
    if (mTail == NULL) {
      // First entry
      mTail = mHead;
    }
    mSize++;
  }

  /// Insert a node in the back of the list
  void addBack(T aValue)
  {
    SLLNode<T>* node = new SLLNode<T>(aValue);
    if (mHead == NULL) {
      mHead = mTail = node;
    } else {
      mTail->setNext(node);
      mTail = node;
    }
    mSize++;
  }
    
  /// Delete the node from the front
  void removeFront()
  {
    assert((mHead == NULL && mTail == NULL) ||
	   mSize > 0);
    if (mHead == NULL) {
      return;
    }
    SLLNode<T>* oldHead = mHead;
    mHead = mHead->next();
    if (mHead == NULL) {
      mTail = mHead;
    }
    delete oldHead;
    mSize--;
  }

  /// Delete everything
  void removeAll()
  {
    while(mSize > 0) {
      removeFront();
    }
    mHead = mTail = NULL;
    mSize = 0;
  }
  
  /// Get the value from the front
  T front() const
  {
    if (isEmpty()) {
      cout << "list empty." << endl;
      return NULL;
    }
    return mHead->value();
  }
  
  /// Get the value from the back
  T back() const
  {
    if (isEmpty()) {
      cout << "list empty." << endl;
      return NULL;
    }
    return mTail->value();
  }
    
  /// Check whether the list is empty
  bool isEmpty() const
  {
    return (size() == 0);
  }
  
  /// Get the size of the list
  int size() const
  {
    return mSize;
  }
  
  /// Copy constructor
  SLinkedList(const SLinkedList& other)
    : mHead(NULL), mTail(NULL), mSize(0)
  {
    if (!other.isEmpty()) {
      // Copy from other
      for (const SLLNode<T>* curr = other.head(); curr != NULL; curr = curr->next()) {
	addBack(curr->value());
      }
    }
  }

  /// Assignment operator
  SLinkedList& operator=(const SLinkedList& other)
  {
    if (this == &other) {
      // self-assignment -- return otherwise bad things will happen
      return *this;
    }

    // Cleanup this list
    removeAll();

    // Copy from other
    if (!other.isEmpty()) {
      for (const SLLNode<T>* curr = other.head(); curr != NULL; curr = curr->next()) {
	addBack(curr->value());
      }
    }
    return *this;
  }

  /// Destructor
  ~SLinkedList()
  {
    removeAll();
  }

  /// Get the head pointer
  SLLNode<T>* head()
  {
    return mHead;
  }
  
  /// Get the head pointer
  const SLLNode<T>* head() const
  {
    return mHead;
  }
  
 private:
  
  SLLNode<T>* mHead;
  SLLNode<T>* mTail;
  int mSize;
    
};

#endif
