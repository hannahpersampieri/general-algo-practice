#ifndef SLL_H
#define SLL_H

#include <iostream>
#include <cassert>

using namespace std;

/// Singly Linked List with a head pointer, a tail pointer and size
class SLinkedList {
 private:
  class SLLNode;

 public:
  /// Constructor
  SLinkedList()
    : mHead(NULL), mTail(NULL), mSize(0)
  {
  }

  /// Insert a node in the front of the list
  void addFront(int aValue)
  {
    mHead = new SLLNode(aValue, mHead);
    if (mTail == NULL) {
      // First entry
      mTail = mHead;
    }
    mSize++;
  }

  /// Insert a node in the back of the list
  void addBack(int aValue)
  {
    SLLNode* node = new SLLNode(aValue);
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
    SLLNode *oldHead = mHead;
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
  int front() const
  {
    if (isEmpty()) {
      cout << "list empty." << endl;
      return -1;
    }
    return mHead->value();
  }
  
  /// Get the value from the back
  int back() const
  {
    if (isEmpty()) {
      cout << "list empty." << endl;
      return -1;
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
  
  /// Get the n-th value from the list
  int nth(int n) const
  {
    if (mSize == 0) {
      cout << "list empty." << endl;
      return -1;
    }
    if (n >= mSize) {
      cout << "list size smaller than the index." << endl;
      return -1;
    }
    SLLNode *nthNode = mHead->nth(n);
    assert(nthNode != NULL);
    return nthNode->value();
  }
  
  /// Print list
  void output(ostream& s = cout) const
  {
    s << "List:" << endl;
    if (mSize == 0) {
      s << "Empty!" << endl;
      return;
    }
    SLLNode *node = mHead;
    for (int i = 0; i < mSize; ++i) {
      s << node->value() << " ";
      node = node->next();
    }
    s << endl;
  }

  /// Copy constructor
  SLinkedList(const SLinkedList& other)
    : mHead(NULL), mTail(NULL), mSize(0)
  {
    if (!other.isEmpty()) {
      // Copy from other
      for (const SLLNode* curr = other.head(); curr != NULL; curr = curr->next()) {
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
      for (const SLLNode* curr = other.head(); curr != NULL; curr = curr->next()) {
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
  SLLNode* head()
  {
    return mHead;
  }
  
  /// Get the head pointer
  const SLLNode* head() const
  {
    return mHead;
  }
  
 private:
  
  /// Subclassing so that SLLNode cannot be instantiated publicly
  class SLLNode {
  public:
    /// Constructors
    SLLNode(int aValue) 
      : mValue(aValue),mNext(NULL)
    {
    }
      
    SLLNode(int aValue, SLLNode *aNext)
      : mValue(aValue), mNext(aNext)
    {
    }
    
    /// Get value
    int value() const
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

    /// Return the n-th node w.r.t. this node
    SLLNode* nth(int n)
    {
      if (n == 0) {
	return this;
      } else if (n < 0 || mNext == NULL) {
	return NULL;
      } else {
	return mNext->nth(n-1);
      }
    }
    
    /// Insert a new node with aValue after this node
    void insertAfter(int aValue)
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
    int mValue;
    SLLNode* mNext;
  };
  
  SLLNode* mHead;
  SLLNode* mTail;
  int mSize;
    
};

/// Overloaded operator<< for outputing a list
ostream& operator<<(ostream& s, const SLinkedList& aList)
{
  aList.output(s);
  return s;
}

#endif
