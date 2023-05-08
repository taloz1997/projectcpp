//
// Created by spl211 on 05/11/2020.
//

#include "../include/Graph.h"
#include "queue"


using namespace std;

//constructor
Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), ifInfected(edges.size(), false),
                                                     ifCarry(edges.size(),
                                                             false) {
}

Graph::Graph() : edges(), ifInfected(),
                 ifCarry() {

}

//================setters====================

void Graph::setIfInfected(int index) {
    ifInfected[index] = true;
}

void Graph::setIfCarry(int index, bool value) {
    ifCarry[index] = value;
}

Graph &Graph::updateGraph(int indexToDisconnect) {
    for (size_t i = 0; i < edges.size(); ++i) {//delete the edges
        edges[indexToDisconnect][i] = 0;
        edges[i][indexToDisconnect] = 0;
    }
    return *this;
}


vector<vector<int>> Graph::getEdges() {
    return edges;
}


//================other functions====================
Tree *Graph::BFS(Session &session, int root) {
    Tree *bfsTree = Tree::createTree(session, root);//creating one-node tree
    queue<Tree *> bfsNextNode;
    vector<bool> visited(edges.size(),
                         false);//initialize the vector that indicates which nodes we already had visited
    visited[root] = true;
    bfsNextNode.push(bfsTree);
    Tree *currNode;
    while (!bfsNextNode.empty()) {
        currNode = bfsNextNode.front();
        bfsNextNode.pop();
        for (size_t i = 0; i < edges.size(); ++i) {
            if (edges[currNode->getNode()][i] == 1) {//if currNode has children (from smallest to biggest child)
                if (!visited[i]) {
                    visited[i] = true;
                    Tree *newChild = Tree::createTree(session, i);//crate a tree for this child
                    currNode->addChild(newChild);//connecting the child to his parent (in the BFS tree)
                    bfsNextNode.push(newChild);
                }
            }
        }
    }
    return bfsTree;
}

bool Graph::isComplete(int cycle) {//the function indicates if the chain of infection stopped
    if (cycle == 0)
        return false;
    for (size_t i = 0; i < ifInfected.size(); ++i) {
        if (ifInfected[i] && haveChildren(i)) {
            for (size_t j = 0; j < ifInfected.size(); ++j) {
                if (edges[i][j] == 1 && !ifInfected[j])//check if there is an healthy child (of a sick parent)
                    return false;
            }
        }
        if (ifCarry[i])
            return false;
    }
    return true;
}

bool Graph::haveChildren(int index) {
    for (size_t i = 0; i < edges.size(); ++i) {
        if (edges[index][i] == 1)//if we find  at least one child-> true
            return true;
    }
    return false;
}

int Graph::firstHealthyChild(int nodeIndex) {//returns the index of the first healthy child
    for (size_t i = 0; i < edges.size(); ++i) {
        if (edges[nodeIndex][i] == 1 && (!ifInfected[i] && !ifCarry[i])) {
            return i;
        }
    }
    return -1; //indication for not having healthy children.
}

vector<bool> Graph::getInfected() {
    return ifInfected;
}

