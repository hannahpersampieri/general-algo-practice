// Array.h

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

template <typename T>
class Array
{
 public:
  // Default constructor
  Array<T>();
  // Nondefault constructor
  Array<T>(int aLen);
  // Copy constructor
  Array<T>(const Array<T> & other);
  // Assign operator
  Array<T> & operator=(const Array<T> & other);
  // Destructor
  ~Array<T>();

  void input(std::istream & s = std::cin);
  void output(std::ostream & s = std::cout) const;

  const T & operator[](int which) const;
  T & operator[](int which);

  int length() const;

 private:
  T * mA;
  int mLen;
  
  void allocate(int aLen);
  void setLength(int aLen);
  void copy(const Array<T> & other);
  void cleanup();
};

// Default Constructor
template <typename T>
Array<T>::Array()
  : mLen(0), mA(NULL)
{
}

// Non-default constructor
template <typename T>
Array<T>::Array(int aLen)
{
  allocate(aLen);
  
  for (int i = 0; i < length(); i++) {
    (*this)[i] = 0;
  }
}

// Copy constructor
template <typename T>
Array<T>::Array(const Array& other)
{
  copy(other);
}

// Assignment operator
template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
  if (this != &other) {
    // cleanup();
    copy(other);
  }
  return *this;
}

// Destructor
template <typename T>
Array<T>::~Array()
{
  cleanup();
}

template <typename T>
void Array<T>::input(std::istream & s)
{
  int len = 0;
  std::cout << "Length of array: ";
  s >> len;
  allocate(len);

  for (int i = 0; i < length(); i++) {
    std::cout << "A[" << i << "] = ";
    s >> (*this)[i];
  }
}

template <typename T>
void Array<T>::output(std::ostream & s) const
{
  s << "{";
  for (int i = 0; i < mLen; i++) {
    if (i % 20 == 0) {
      s << std::endl;
    }
    s << " " << (*this)[i];
  }
  s << " }";
  s << std::endl;
}

template <typename T>
const T & Array<T>::operator[](int i) const
{
  if (i < 0 || i >= mLen) {
    std::cout << "Invalid array index." << std::endl;
    exit(1);
  }
  return mA[i];
}

template <typename T>
T & Array<T>::operator[](int i)
{
  if (i < 0 || i >= mLen) {
    std::cout << "Invalid array index." << std::endl;
    exit(1);
  }
  return mA[i];
} 

template <typename T>
int Array<T>::length() const
{
  return mLen;
}

template <typename T>
void Array<T>::allocate(int aLen)
{
  if (aLen < 0) {
    std::cout << "Negative index." << std::endl;
    mLen = 0;
    mA = NULL;
    return;
  }
  setLength(aLen);
  mA = new T [aLen];
}

template <typename T>
void Array<T>::setLength(int aLen)
{
  mLen = aLen;
}

template <typename T>
void Array<T>::copy(const Array<T> & other)
{
  allocate(other.length());
  
  for (int i = 0; i < length(); i++) {
    (*this)[i] = other[i];
  }
}

template <typename T>
void Array<T>::cleanup()
{
  delete [] mA;
}


#endif
