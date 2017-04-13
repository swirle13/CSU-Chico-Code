#include "minpriority.h"

using std::string;
using std::vector;

MinPriorityQ::~MinPriorityQ()
{
    minHeap.clear();
}


void MinPriorityQ::buildMinHeap()
{
    // Build MinHeap Priority Queue
    unsigned int heapSize = minHeap.size();
    for (int i = (heapSize / 2); i >= 0; --i)
    {
        minHeapify(i);
    }
}

void MinPriorityQ::decreaseKey(string str, unsigned int key)
{
    if(isMember(str))
    {
        int size = minHeap.size();
        int index = findIndex(str);
        // change element key to new key
        if((index >= 0) && (index < size))
        {
            minHeap[index]->key = key;
        }
    }
    else
    {
        std::cout << "name not found" << std::endl;
    }
}


std::string MinPriorityQ::extractMin()
{
    if(minHeap.size() > 0)
    {
        //sort
        buildMinHeap();
        //extract
        return popAndReturn();
    }
    else
    {
        return "empty";
    }
}

int MinPriorityQ::findIndex(string str)
{
    unsigned int index = -1;
    if (!minHeap.empty())
    {
        unsigned int i = 0;
        while ((i < minHeap.size()) && (minHeap[i] != NULL))
        {
            if (minHeap[i]->id == str)
            {
                return i;
            }

            ++i;
        }
    }
    return index;
}


/**
 *  @brief: inserts string and priority into vector
 */
void MinPriorityQ::insert(string str, unsigned int key)
{
    Element* object = new Element(str, key);
    minHeap.push_back(object);
}


bool MinPriorityQ::isMember(string str)
{
    if (!minHeap.empty())
    {
        unsigned int i = 0;
        while ((i < minHeap.size()) && (minHeap[i] != NULL))
        {
            if (minHeap[i]->id == str)
            {
                return true;
            }

            ++i;
        }
    }

    return false;
}

/**
 *  @breif: returns index of current node's left child
 */
int MinPriorityQ::left(int currentIndex)
{
    return currentIndex * 2;
}

void MinPriorityQ::minHeapify(unsigned int index)
{

    int largest = -1;
    int heapSize = minHeap.size() - 1;
    int i = index;
    int l = left(i);
    int r = right(i);

    if(l <= heapSize && (minHeap[l]->key < minHeap[i]->key))
    {
        largest = l;
    }
    else
    {
        largest = i;
    }

    if(r <= heapSize && (minHeap[r]->key < minHeap[largest]->key))
    {
        largest = r;
    }

    if(largest != i)
    {
        Element* temp = minHeap[i];
        minHeap[i] = minHeap[largest];
        minHeap[largest] = temp;
        minHeapify(largest);
    }
}

/**
 *  @breif: returns index of current node's parent
 */
int MinPriorityQ::parent(int currentIndex)
{
    int parentIndex;
    parentIndex = currentIndex / 2;     // returns the floor of division
    return parentIndex;
}


std::string MinPriorityQ::popAndReturn()
{
    std::string str = minHeap.front()->id;
    minHeap.erase(minHeap.begin());
    return str;
}

/**
 *  @breif: returns index of current node's right child
 */
int MinPriorityQ::right(int currentIndex)
{
    return (currentIndex * 2) + 1;
}