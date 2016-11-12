// pqueue.h
// Jones, Troy
// tjones71
#include "cust.h"
#include <string>

class Pqueue
{
public:
    // create customers and put them in arrival queue
    void createCust(std::string name, bool shopper, int arrivalTime, int numOfItems);

    // get customer and take off queue
    Cust* dequeueCustomer(Pqueue&);

    // return the number of customers in arrival queue
    int getNumCustomers();

    // returns the time a customer is done shopping
    int getTimeDoneShopping(Pqueue);

    // returns the time a customer entered the arrival queue
    int getTimeEnteredStore(Pqueue);

    // get the customer in queue without dequeueing
    Cust* getCustomer(Pqueue);

    // moves cust from arrivalQ to shoppingQ
    void transferToQ(Pqueue&, Pqueue&);

    // adds 1 to mNumCustomers
    void tallyCustomer();

private:

    class Node
    {
    public:
        Node(Cust* cust, Node* next)
        {
            mCust = cust;
            mNext = next;
        }
        Cust* mCust = NULL;
        Node* mNext = NULL;
    };
    Node* mHead = NULL;
    int mNumCustomers = 0;
    void untallyCustomer();
};