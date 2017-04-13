#ifndef MINPRIORITYQ_H
#define MINPRIORITYQ_H

#include <iostream>
#include <string>
#include <vector>

class MinPriorityQ
{
public:
  ~MinPriorityQ();
  void insert(std::string, unsigned int);
  void decreaseKey(std::string, unsigned int);
  std::string extractMin();
  bool isMember(std::string);

private:
  class Element
  {
      public:
      std::string id;
      int key;
      Element(std::string id, int key)
      {
          this->id = id;
          this->key = key;
      }
  };

  std::vector<Element*> minHeap;
    void buildMinHeap();
    void minHeapify(unsigned int);
    int findIndex(std::string);
    int parent(int);
    int left(int);
    int right(int);
    std::string popAndReturn();
};

#endif