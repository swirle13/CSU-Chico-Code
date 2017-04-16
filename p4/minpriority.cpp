/**
 * @file minpriority.cpp   implements a priority queue
 *
 * @brief
 *      Includes functions to insert, remove, and extract values from a priority
 *  queue. 
 *
 * @author Troy Jones (tjones71)
 * @date 4/13/17
 */
#include "minpriority.h"

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/**
 *  MinPriorityQ::~MinPriorityQ() 
 *
 *  Deconstructor that erases the priority queue
 */
MinPriorityQ::~MinPriorityQ()
{
    minHeap.clear();
}

/**
 *  MinPriorityQ::buildMinHeap()
 *
 *  Calls minHeapify which creates a minHeap
 */
void MinPriorityQ::buildMinHeap()
{
    // Build MinHeap Priority Queue
    unsigned int heapSize = minHeap.size();
    for (int i = (heapSize / 2); i >= 0; --i)
    {
        minHeapify(i);
    }
}

/**
 *  UNDER CONSTRUCTION
 */
/*void MinPriorityQ::decreaseKey(string str, unsigned int key)
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
}*/

/**
 *  MinPriorityQ::extractMin()
 *
 *  extracts and rebuilds minHeap
 */
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

/**
 *  MinPriorityQ::findIndex()
 *
 *  Finds and returns the index of the string passed in
 *
 *  @param str string of desired id
 */
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
 *  MinPriorityQ::decreaseKey()
 *
 *  Locates string passed in and changes key value
 *
 *  @param 
 *      str String of desired id to be changed
 *      key Value of new key desired
 */
void MinPriorityQ::decreaseKey(string str, unsigned int key)
{
    int index = findIndex(str);
    minHeap[index]->key = key;
}

/*
UNDER CONSTRUCTION
*/
/*void MinPriorityQ::heapDecreaseKey(int i, int key)
{
    if(minHeap.size() != 0)
    {
        if(key < minHeap[i]->key)
        {
            cerr << "new key is smaller than current key" << endl;
        }
        else
        {
            minHeap[i]->key = key;
            while(i > 0 && minHeap[parent(i)]->key > minHeap[i]->key)
            {
                Element* temp = minHeap[i];
                minHeap[i] = minHeap[parent(i)];
                minHeap[parent(i)] = temp;
                i = parent(i);
            }
        }
    }
}*/

/**
 *  UNDER CONSTRUCTION
 */
/*Element* MinPriorityQ::heapExtractMin()
{
    Element* minObject = NULL:
    if (minHeap.size() == 0)
    {
        std::cerr << "nothing to extract" << endl;
    }
    else
    {
        minObject = minHeap[0];
        minHeap[0] = minHeap[minHeap.size() - 2];
        minHeapify(0);
    }
    return minObject;
}*/

/**
 *  MinPriorityQ::insert()
 *
 *  Inserts id and key into minHeap
 *
 *  @param  
 *      str     id to be inserted into minHeap
 *      key     key value to be inserted into minHeap
 */
void MinPriorityQ::insert(string str, unsigned int key)
{
    Element* object = new Element(str, key);
    minHeap.push_back(object);
}

/*
UNDER CONSTRUCTION
*/
/*bool MinPriorityQ::isMember(string str)
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
}*/

/**
 *  MinPriorityQ::left()
 *
 *  Returns position of left child
 *
 *  @param  
 *      currentIndex    current position in heap
 */
int MinPriorityQ::left(int currentIndex)
{
    return (currentIndex * 2) + 1;
}

/**
 *  MinPriorityQ::minHeapify()
 *
 *  Creates minHeap
 *
 *  @param  
 *      currentIndex    current position in heap
 */
void MinPriorityQ::minHeapify(int index)
{

    int smallest = -1;
    int heapSize = minHeap.size() - 1;
    int i = index;
    int l = left(i);
    int r = right(i);

    if(l <= heapSize && (minHeap[l]->key < minHeap[i]->key))
    {
        smallest = l;
    }
    else
    {
        smallest = i;
    }

    if(r <= heapSize && (minHeap[r]->key < minHeap[smallest]->key))
    {
        smallest = r;
    }

    if(smallest != i)
    {
        Element* temp = minHeap[i];
        minHeap[i] = minHeap[smallest];
        minHeap[smallest] = temp;
        minHeapify(smallest);
    }
}
/*
UNDER CONSTRUCTION
*/
/*void MinPriorityQ::minHeapInsert(int key)
{
    minHeap.push_back(NULL);
    key++;
}*/

/**
 *  MinPriorityQ::parent()
 *
 *  Returns position of parent
 *
 *  @param  
 *      currentIndex    current position in heap
 */
int MinPriorityQ::parent(int currentIndex)
{
    int parentIndex;
    parentIndex = currentIndex / 2;     // returns the floor of division
    return parentIndex;
}

/**
 *  MinPriorityQ::popAndReturn()
 *
 *  Returns id of lowest key value in minHeap
 */
std::string MinPriorityQ::popAndReturn()
{
    std::string str = minHeap.front()->id;
    minHeap.erase(minHeap.begin());
    return str;
}

/**
 *  MinPriorityQ::right()
 *
 *  Returns position of right child
 *
 *  @param  
 *      currentIndex    current position in heap
 */
int MinPriorityQ::right(int currentIndex)
{
    return (currentIndex * 2) + 2;
}