#include <iostream>
#include "FIFOQueueClass.h"

using namespace std;

// Programmer: Hao-Chun Shih
// Date: 11/25/2024
// Purpose: Define FIFOQueueClass for constructing a queue using
//          LinkedNodeClass and SortedListClass

template < class T >
FIFOQueueClass< T >::FIFOQueueClass()
{
  head = NULL;
  tail = NULL;
}

template < class T >
FIFOQueueClass< T >::~FIFOQueueClass()
{
  clear();
}

template < class T >
void FIFOQueueClass< T >::enqueue(const T &newItem)
{  
  LinkedNodeClass< T >* newNode = NULL;
  
  if(head == NULL)
  {
    head = new LinkedNodeClass< T >(NULL, newItem, NULL);
    tail = head;
  }

  else
  {
    newNode = new LinkedNodeClass< T >(tail, newItem, NULL);
    tail = newNode;
    newNode->setBeforeAndAfterPointers();
  }
}

template < class T >
bool FIFOQueueClass< T >::dequeue(T &outItem)
{
  if(head == NULL)
  {
    return false;
  }

  else if(head == tail)
  {
    outItem = head->getValue();
    delete head;
    head = NULL;
    tail = NULL;
    return true;
  }

  else
  {
    LinkedNodeClass< T >* tempNode = head;
    outItem = head->getValue();
    head = head->getNext();
    delete tempNode;
    head->setPreviousPointerToNull();
    return true;
  }
}

template < class T >
void FIFOQueueClass< T >::print() const
{
  LinkedNodeClass< T >* tempPtr = head;

  while(tempPtr != NULL)
  {
    cout << tempPtr->getValue() << " " ;
    tempPtr = tempPtr->getNext();
  }

  cout << endl;
}

template < class T >
int FIFOQueueClass< T >::getNumElems() const
{
  int numElements = 0;
  LinkedNodeClass< T >* tempPtr = head;

  while(tempPtr != NULL)
  {
    numElements++;
    tempPtr = tempPtr->getNext();
  }
  
  return numElements;
}

template < class T >
void FIFOQueueClass< T >::clear()
{  
  LinkedNodeClass< T >* deleteNode = NULL;

  while(head != NULL)
  {
    deleteNode = head;
    head = head->getNext();
    delete deleteNode;
  }
  
  tail = NULL;
}