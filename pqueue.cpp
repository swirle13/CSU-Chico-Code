// pqueue.cpp
// Jones, Troy
// tjones71
#include "pqueue.h"
using namespace std;

void Pqueue::createCust(std::string name, bool shopper, int arrivalTime, int numOfItems)
{
    Cust* cust = NULL;
    cust = new Cust(name, shopper, arrivalTime, numOfItems);


    if (mHead == NULL || cust->getArrivalTime(cust) < mHead->mCust->getArrivalTime(mHead->mCust))
    {
        mHead = new Node(cust, mHead);
    }
    else
    {
        Node* ptr = mHead;
        
        while (ptr->mNext != NULL && cust->getArrivalTime(cust) >= ptr->mNext->mCust->getArrivalTime(ptr->mNext->mCust))
        {
            ptr = ptr->mNext;
        }
        ptr->mNext = new Node(cust, ptr->mNext);    
    }
}

Cust* Pqueue::dequeueCustomer(Pqueue& queue)
{
    if (queue.mHead != NULL)
    {
        Node* temp = queue.mHead;
        Cust* cust = queue.mHead->mCust;
        queue.mHead = queue.mHead->mNext;
        delete temp;
        queue.untallyCustomer();
        return cust;
    }
    else
        return NULL;
}

Cust* Pqueue::getCustomer(Pqueue queue)
{
    return queue.mHead->mCust;
}

int Pqueue::getNumCustomers()
{
    return mNumCustomers;
}

int Pqueue::getTimeDoneShopping(Pqueue shoppingQ)
{
    return shoppingQ.mHead->mCust->getTimeShoppingDone(shoppingQ.mHead->mCust);
}

int Pqueue::getTimeEnteredStore(Pqueue arrivalQ)
{
    return arrivalQ.mHead->mCust->getArrivalTime(arrivalQ.mHead->mCust);
}

void Pqueue::transferToQ(Pqueue& fromQ, Pqueue& toQ)
{

    Node* toPtr = toQ.mHead;

    // if toQ is empty or fromQ cust checkoutTime is less then first element in toQ
    if(toPtr == NULL || fromQ.mHead->mCust->getCheckoutTime(fromQ.mHead->mCust) < toPtr->mCust->getCheckoutTime(toPtr->mCust))
    {
        toQ.mHead = new Node(fromQ.mHead->mCust, toPtr);
        toQ.tallyCustomer();
        Node* temp = fromQ.mHead;
        fromQ.mHead = fromQ.mHead->mNext;
        delete temp;
        fromQ.untallyCustomer();
    }
    else
    {
        // if fromQ is empty
        if (fromQ.mHead == NULL)
            return;
        // if fromQ checkoutTime > toQ.mHead checkoutTime
        else 
        {
            // if one item in toPtr
            if (toPtr->mNext == NULL)
            {
                toPtr->mNext = new Node(fromQ.mHead->mCust, toPtr->mNext);
                toQ.tallyCustomer();
                Node* temp = fromQ.mHead;
                fromQ.mHead = fromQ.mHead->mNext;
                delete temp;
                fromQ.untallyCustomer();
            }    
            else
            {
                while(toPtr->mNext != NULL && fromQ.mHead->mCust->getCheckoutTime(fromQ.mHead->mCust) >= toPtr->mCust->getCheckoutTime(toPtr->mNext->mCust))
                {
                    toPtr = toPtr->mNext;
                }
                Node* newPtr = toPtr;
                newPtr = new Node(fromQ.mHead->mCust, toPtr->mNext);
                toPtr->mNext = newPtr;
                toQ.tallyCustomer();
                Node* temp = fromQ.mHead;
                fromQ.mHead = fromQ.mHead->mNext;
                delete temp;
                fromQ.untallyCustomer();
            }
        }
    }
}

void Pqueue::tallyCustomer()
{
    mNumCustomers += 1;
}

void Pqueue::untallyCustomer()
{
    mNumCustomers -= 1;
}