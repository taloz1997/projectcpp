#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "../include/Tree.h"
#include "list"
#include "../include/Graph.h"
//#include "../include/Session.h"


using namespace std;

class Graph {
public:
    //constructors
    Graph(std::vector<std::vector<int>> matrix);
    Graph();

    //================setters====================
    void setIfInfected(int index);
    void setIfCarry(int index, bool value);
    Graph &updateGraph(int indexToDisconnect);
    //================getters====================
    vector<vector<int>> getEdges();
    vector<bool> getInfected();
    vector<bool> getIfCarry();

    //================other functions====================
    Tree *BFS(Session &session, int root);
    bool isComplete(int cycle);
    bool haveChildren(int index);
    int firstHealthyChild(int nodeIndex);



private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> ifInfected;
    vector<bool> ifCarry;
};

#endif