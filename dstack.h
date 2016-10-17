// dstack.h
// Jones, Troy
// tjones71
#include <iostream>
#include <string>
#include <cmath>

class Dstack
{
public:
    ~Dstack()
    {
        if (mHead != NULL)
            {
                Node* ptr = mHead;
                while (ptr->mNext != NULL)
                {
                    Node* temp = ptr;
                    ptr = ptr->mNext;
                    delete temp;
                }
            }   
    };
    void push(double, int&);    // pushes doubles onto the stack
    bool empty(int&);   // checks to see if stack is empty
    double pop(int&);   // pops value off of stack
private:
    class Node
    {
    public: 
        Node(double value, Node* next)
        {
            mValue = value;
            mNext = next;
        };
        Node* mNext;
        double mValue;  
    };
    Node* mHead = NULL;
};