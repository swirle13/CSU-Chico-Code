/**
 * @file    graph.cpp
 * 
 * @author  Troy Jones
 * @date    5/14/17
 */
#include "graph.h"
// pull request test

using std::pair;
using std::string;
using std::sort;
using std::cout;
using std::endl;

Graph::~Graph()
{
    for (map<string, vector<Neighbor *>>::iterator i = adjList.begin();
         i != adjList.end(); ++i)
    {
        for (unsigned int j = 0; j < i->second.size(); ++j)
        {
            delete i->second[j];
        }
    }
}

/**
 *  Graph::addVertex()
 *
 *  @param  name Name of vertice
 */
void Graph::addVertex(string name)
{
    Vertex *vertex = new Vertex("nill", 100);  // 100 == inf.
    vertices.insert(pair<string, Vertex*>(name, vertex));
}

/**
 *  Graph::addEdge()
 *
 *  Adds edge to adjList
 *
 *  @param  from    Name of source vertice
 *  @param  to      Name of destination vertice
 *  @param  weight  Weight assigned to edge
 */
void Graph::addEdge(string from, string to, unsigned int weight)
{
    map<string, vector<Neighbor *> >::iterator it;
    it = adjList.find(from);
    if (it != adjList.end())    // if found
    {
        Neighbor *neighbor = new Neighbor(to, weight);
        it->second.push_back(neighbor);
    }
    else
    {
        Neighbor *neighbor = new Neighbor(to, weight);
        vector<Neighbor *> neighbors;

        neighbors.push_back(neighbor);
        adjList.insert(pair<string, vector<Neighbor *> >(from, neighbors));
    }
}

/**
 *  Graph::mst()
 *
 *  Adds edge to adjList
 *
 *  @param  r   The entry point vertice to start the algorithm
 */
void Graph::mst(string r)
{
    string u;   // source vertice
    string v;   // destination vertice
    int sumOfAllEdges = 0;

    // loads vertices into minPriority Q
    for (map<string, Vertex *>::iterator it = vertices.begin(); 
        it != vertices.end(); ++it)
    {
        minQ.insert(it->first, it->second->key);
    }

    map<string, vector<Neighbor *> >::iterator usAdjList;
    map<string, Vertex *>::iterator vInQ;

    for (map<string, vector<Neighbor *> >::iterator z = adjList.begin();
         z != adjList.end(); ++z)
    {
        std::sort(z->second.begin(), z->second.end());
         }

         vInQ = vertices.find(r);

         // sets key of entry vertex to 0
         minQ.decreaseKey(r, 0);
         vInQ->second->key = 0;

         do
         {
             // fetches string in minQ with lowest key value
             u = minQ.extractMin();
             if (u != "empty")
             {
                 // return iterator for u's AdjList
                 usAdjList = adjList.find(u);

                 // for every vertex in u's adjList
                 for (unsigned int i = 0; i < usAdjList->second.size(); ++i)
                 {
                     /* returns vertice name at i'th position in vector of 
                    u's AdjList */
                     v = usAdjList->second[i]->name;
                     unsigned int weightUtoV = usAdjList->second[i]->weight;

                     vInQ = vertices.find(v);

                     /* if vertex is in Q and the weight of the edge is less 
                        than current value assigned to key */
                     if ((vertices.end() != vInQ) && 
                        weightUtoV < vInQ->second->key)
                     {
                         vInQ->second->pi = u;
                         minQ.decreaseKey(v, weightUtoV);
                         vInQ->second->key = weightUtoV;
                     }
                 }

                 // prints current line of graph
                 map<string, Vertex *>::iterator vertex;
                 vertex = vertices.find(u);
                 cout << vertex->first << " " << vertex->second->pi << " " <<
                    vertex->second->key << endl;
                 sumOfAllEdges += vertex->second->key;

                 delete vertex->second;
                 vertices.erase(u); // erases vertex from vertices
             }
    } while (u != "empty");
    
    cout << sumOfAllEdges << endl;
}
