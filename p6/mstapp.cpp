/**
 * @file    mstapp.cpp
 * 
 * @author  Troy Jones
 * @date    5/14/17
 */
#include "mstapp.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    MstApp app;
    app.readGraph();
}

//////////////////////////////////////////////////////////////////////////////
/**
 *  MstApp::readGraph()
 *  
 *  Reads in list of vertices on first line, edges with weight on every line
 *  thereafter.
 *  e.g.
 *  A B C D
 *  A B 4
 *  B C 5
 *
 *  Calculates best tree and prints sum
 */
void MstApp::readGraph()
{
    string verticeList = "";
    string firstItem;   // stores first vertice entered
    getline(cin, verticeList);

    // get vertices and add to graph
    int beginIndex = 0;
    int endIndex = 0;
    int lengthOfWord = 0;
    bool firstEntry = true;
    for (unsigned int i = 0; i <= verticeList.length(); ++i)
    {
        // if index is at a space or the next char is null
        if (verticeList[i] == ' ' || verticeList[i] == 0)
        {
            lengthOfWord = endIndex - beginIndex;
            string str = verticeList.substr(beginIndex, lengthOfWord);
            if (firstEntry)
            {
                firstItem = str;
            }
            firstEntry = false;
            myGraph.addVertex(str);
            beginIndex = endIndex + 1;
        }
        ++endIndex;
    }

    // get and add edges to graph
    string edgeList = "";
    string from = "";
    string to = "";
    unsigned int weight = 0;
    while (cin >> from)
    {
        cin >> to;
        cin >> weight;
        cin.ignore();
        myGraph.addEdge(from, to, weight);
        myGraph.addEdge(to, from, weight);
    }

    myGraph.mst(firstItem);
}