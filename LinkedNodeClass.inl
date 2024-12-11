#include <iostream>
#include "LinkedNodeClass.h"

using namespace std;

// Programmer: Hao-Chun Shih
// Date: 11/25/2024
// Purpose: Define LinkedNodeClass for getting value and setting node's pointer

template < class T >
LinkedNodeClass< T >::LinkedNodeClass(LinkedNodeClass< T >* inPrev, 
                                 const T &inVal, 
                                 LinkedNodeClass< T >* inNext)
{
  prevNode = inPrev;
  nextNode = inNext;
  nodeVal = inVal;
}

template < class T >
T LinkedNodeClass< T >::getValue() const
{
  return nodeVal;
}

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getNext() const
{
  return nextNode;
}

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getPrev() const
{
  return prevNode;
}

template < class T >
void LinkedNodeClass< T >::setNextPointerToNull()
{
  nextNode = NULL;
}

template < class T >
void LinkedNodeClass< T >::setPreviousPointerToNull()
{
  prevNode = NULL;
}

template < class T >
void LinkedNodeClass< T >::setBeforeAndAfterPointers()
{
  if(this->prevNode == NULL)
  {
    this->nextNode->prevNode = this;
  }

  else if(this->nextNode == NULL)
  {
    this->prevNode->nextNode = this;
  }

  else
  {
    this->prevNode->nextNode = this;
    this->nextNode->prevNode = this;
  }
}
