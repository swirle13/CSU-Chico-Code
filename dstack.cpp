// dstack.cpp
// Jones, Troy
// tjones71
#include "dstack.h"
#ifndef DSTACK_H
#define DSTACK_H
using std::cout;
using std::endl;
using std::string;

bool Dstack::empty(int& itemsInStack)
{
    if (itemsInStack == 0)  /* is incremented in Dstack::push()
    {                           decremented in Dstack::pop() */
        return true;
    else
        return false;
}

double Dstack::pop(int& itemsInStack)
{
    Node* ptr = mHead;
    mHead = ptr->mNext;
    itemsInStack--;
    double value = ptr->mValue;
    delete ptr;
    return value;
}

void Dstack::push(double value, int& itemsInStack)
{
    mHead = new Node(value, mHead);
    itemsInStack++;
}

#endif