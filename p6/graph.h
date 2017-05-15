/**
 * @file    graph.h
 * 
 * @author  Troy Jones
 * @date    5/14/17
 */

#include "minpriority.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using std::map;
using std::string;
using std::vector;

class Graph
{
    public:
      Graph(){}
      ~Graph();
      void addVertex(string);   // adds vertice to list
      void addEdge(string, string, unsigned int);   // adds edge to list
      void mst(string); // implements Prim's algorithm

    private:
      class Vertex
      {
          public:
            Vertex(string pi, unsigned int key)
            {
                this->pi = pi;      
                this->key = key;    
            }

            string pi;          // predecessor
            unsigned int key;   // weight assigned
      };
  
      class Neighbor
      {
          public:
            Neighbor(string name, unsigned int weight)
            {
                this->name = name;
                this->weight = weight;
            }
            string name;            // name of destination vertice
            unsigned int weight;    // weight of edge
      };
  
      map<string, Vertex*> vertices;    // list of vertices
      map<string, vector<Neighbor*> > adjList;  // adjacency list
      MinPriorityQ minQ;    // minimum priority Q
};