#include <iostream>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"


using namespace std;
// Programmer: Hao-Chun Shih
// Date: 11/25/2024
// Purpose: Define SortedListClass for insering, removing, printing
//          and getting element of specified index

const int MIN_INDEX = 0;

template < class T >
SortedListClass< T >::SortedListClass()
{
  head = NULL;
  tail = NULL;
}

template < class T >
SortedListClass< T >::SortedListClass(const SortedListClass< T > &rhs)
{
  head = NULL;
  tail = NULL;

  if(rhs.head == NULL)
  {
    return;
  }

  LinkedNodeClass< T >* copy = rhs.head;
  while(copy)
  {
    this->insertValue(copy->getValue());
    copy = copy->getNext();
  }
}

template < class T >
SortedListClass< T >::~SortedListClass()
{
  clear();
}

template < class T >
SortedListClass< T >& SortedListClass< T >::operator=(const SortedListClass< T > &rhs)
{
  this->clear();

  if(rhs.head == NULL)
  {
    return *this;
  }

  LinkedNodeClass< T >* copy = rhs.head;

  while(copy)
  {
    this->insertValue(copy->getValue());
    copy = copy->getNext();
  }

  return *this;
}

template < class T >
void SortedListClass< T >::clear()
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

template < class T >
void SortedListClass< T >::insertValue(const T &valToInsert)
{
  if(head == NULL)
  {
    head = new LinkedNodeClass< T >(NULL, valToInsert, NULL);
    tail = head;
  }

  else
  {
    LinkedNodeClass< T >* currentNode = head;
    while(currentNode != NULL && currentNode->getValue() <= valToInsert)
    {
      currentNode = currentNode->getNext();
    }
    
    if(currentNode == head)
    {
      LinkedNodeClass< T >* newNode;
      newNode = new LinkedNodeClass< T >(NULL, valToInsert, head);
      newNode->setBeforeAndAfterPointers();
      head = newNode;
    }

    else if(currentNode == NULL)
    {
      LinkedNodeClass< T >* newNode;
      newNode = new LinkedNodeClass< T >(tail, valToInsert, NULL);
      newNode->setBeforeAndAfterPointers();
      tail = newNode;
    }

    else
    {
      LinkedNodeClass< T >* newNode;
      newNode = new LinkedNodeClass< T >(currentNode->getPrev(),
                                    valToInsert, currentNode);
      newNode->setBeforeAndAfterPointers();
    }
  }
}

template < class T >
void SortedListClass< T >::printForward() const
{
  LinkedNodeClass< T >* tempPtr = head;
  cout << "Forward List Contents Follow:" << endl;
  while(tempPtr != NULL)
  {
    cout << "  " << tempPtr->getValue() << endl;
    tempPtr = tempPtr->getNext();
  }

  cout << "End Of List Contents" << endl;
}

template < class T >
void SortedListClass< T >::printBackward() const
{
  LinkedNodeClass< T >* tempPtr = tail;
  cout << "Backward List Contents Follow:" << endl;

  while(tempPtr != NULL)
  {
    cout << "  " << tempPtr->getValue() << endl;
    tempPtr = tempPtr->getPrev();
  }

  cout << "End Of List Contents" << endl;
}

template < class T >
bool SortedListClass< T >::removeFront(T &theVal)
{
  if(head == NULL)
  {
    return false;
  }
  
  else if(head == tail)
  {
    theVal = head->getValue();
    delete head;
    head = NULL;
    tail = NULL;
    return true;
  }

  else
  {
    theVal = head->getValue();
    head = head->getNext();
    delete head->getPrev();
    head->setPreviousPointerToNull();
    return true;
  }
}

template < class T >
bool SortedListClass< T >::removeLast(T &theVal)
{
  if(head == NULL)
  {
    return false;
  }

  else if(head == tail)
  {
    theVal = head->getValue();
    delete head;
    head = NULL;
    tail = NULL;
    return true;
  }

  else 
  {
    theVal = tail->getValue();
    tail = tail->getPrev();
    delete tail->getNext();
    tail->setNextPointerToNull();
    return true;
  }

}

template < class T >
int SortedListClass< T >::getNumElems() const
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
bool SortedListClass< T >::getElemAtIndex(const int index, T &outVal) const
{
  bool isSuccess = true;
  LinkedNodeClass< T >* tempPtr = head;
  
  if(index < MIN_INDEX || index >= getNumElems() || tempPtr == NULL)
  {
    isSuccess = false;
  }

  else
  {
    for(int i = 0; i < index; i++)
    {
      tempPtr = tempPtr->getNext();
    }
    outVal = tempPtr->getValue();
  }

  return isSuccess;
}