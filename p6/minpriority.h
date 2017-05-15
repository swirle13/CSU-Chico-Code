/**
 * @file    minpriority.h
 * 
 * @author  Troy Jones
 * @date    4/13/17
 */
#ifndef MINPRIORITYQ_H
#define MINPRIORITYQ_H

#include <iostream>
#include <string>
#include <vector>

using std::string;

class MinPriorityQ
{
  public:
    ~MinPriorityQ();
    void insert(string, unsigned int);
    void decreaseKey(string, unsigned int);
    string extractMin();

  private:
    class Element
    {
      public:
        string id;
        int key;
        Element(string id, int key)
        {
            this->id = id;
            this->key = key;
        }
    };

    std::vector<Element *> minHeap;
    void buildMinHeap();
    void minHeapify(int);
    int findIndex(string);
    int left(int);
    int right(int);
    int parent(int);
    string popAndReturn();
};

#endif