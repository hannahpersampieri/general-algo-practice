// Array.h

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <cstdlib>

#define MAX_CAPACITY 1000

using namespace std;

template<typename T>
class Array
{
 public:
  // Default constructor
  Array();
  // Nondefault constructor
  Array(int aSize);
  // Copy constructor
  Array(const Array & other);
  // Assign operator
  Array & operator=(const Array & other);
  // Destructor
  ~Array();

  void output(ostream & s = cout) const;

  void add(T & aItem);

  const T & operator[](int which) const;
  T & operator[](int which);

  int getCapacity() const;
  int getSize() const;

private:
  T * mA; // Type templatized
  int mCapacity;  // Current capacity (based on allocation)
  int mSize;      // Current size (based on content)

  void allocate(int aCapacity);
  void setSize(int aSize);
  void setCapacity(int aCapacity);
  void copy(const Array & other);
  void cleanup();
};

// Default Constructor
template<typename T>
Array<T>::Array()
: mSize(0)
{
  allocate(MAX_CAPACITY);
}

// Non-default constructor
template<typename T>
Array<T>::Array(int aSize)
: mSize(aSize)
{
  allocate(aSize);
}

// Copy constructor
template<typename T>
Array<T>::Array(const Array<T>& other)
{
  copy(other);
}

// Assignment operator
template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
  if (this != &other) {
    cleanup();
    copy(other);
  }
  return *this;
}

// Destructor
template<typename T>
Array<T>::~Array()
{
  cleanup();
}

template<typename T>
void Array<T>::output(ostream & s) const
{
  for (int i = 0; i < mSize; i++) {
    s << (*this)[i];
    if (i != mSize-1)
      s << " | ";
  }
  // s << endl;
}

template<typename T>
void Array<T>::add(T & aItem)
{
  mA[mSize++] = aItem;
  if (mSize == mCapacity) {
    mCapacity *= 2; // double the capacity
    T * mB = new T[mCapacity];
    for (int i = 0; i < mSize; ++i) {
      mB[i] = mA[i];
    }
    delete [] mA;
    mA = mB;
  }
}

template<typename T>
const T & Array<T>::operator[](int i) const
{
  if (i < 0 || i >= mCapacity) {
    cout << "Invalid array index." << endl;
    exit(1);
  }
  return mA[i];
}

template<typename T>
T & Array<T>::operator[](int i)
{
  if (i < 0 || i >= mCapacity) {
    cout << "Invalid array index." << endl;
    exit(1);
  }
  return mA[i];
} 

template<typename T>
int Array<T>::getCapacity() const
{
  return mCapacity;
}

template<typename T>
int Array<T>::getSize() const
{
  return mSize;
}

template<typename T>
void Array<T>::allocate(int aCapacity)
{
  if (aCapacity < 0) {
    cout << "Negative index." << endl;
    mCapacity = 0;
    mSize = 0;
    mA = nullptr;
    return;
  }
  setCapacity(aCapacity);
  // Allocation
  mA = new T [aCapacity];
}

template<typename T>
void Array<T>::setCapacity(int aCapacity)
{
  mCapacity = aCapacity;
}

template<typename T>
void Array<T>::setSize(int aSize)
{
  mSize = aSize;
}

template<typename T>
void Array<T>::copy(const Array<T> & other)
{
  allocate(other.getCapacity());
  setSize(other.getSize());
  for (int i = 0; i < getSize(); i++) {
    (*this)[i] = other[i];
  }
}

template<typename T>
void Array<T>::cleanup()
{
  delete [] mA;
}

template<typename T>
ostream& operator<<(ostream& s, const Array<T>& a)
{
  a.output(s);
  return s;
}

#endif
