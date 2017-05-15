/**
 * @file    mstapp.h
 * 
 * @author  Troy Jones
 * @date    5/14/17
 */ 

#include "graph.h"
#include <iostream>

    class MstApp
{
    public:
      void readGraph();

    private:
      Graph myGraph;    // undirected graph
};