//
// Created by spl211 on 05/11/2020.
//

#include <iostream>

#include "../include/Tree.h"
#include "../include/Session.h"


using namespace std;

//constructor
Tree::Tree(int rootLabel) : node(rootLabel), children() {
}

Tree::Tree() : node(), children() {
}

//================Rule of 5====================
//destructor
Tree::~Tree() {
    clear();
}

void Tree::clear() {
    for (Tree *x:children) {
        if (x != nullptr)
            delete x;
    }
}

//copy constructor
Tree::Tree(const Tree &other) : node(other.node), children() {
    for (size_t i = 0; i < other.children.size(); ++i) {
        children.push_back(other.children[i]->clone());
    }
}

//copy assignment operator
const Tree &Tree::operator=(const Tree &other) {
    if (this != &other) {
        clear();
        node = other.node;
        for (size_t i = 0; i < other.children.size(); ++i) {
            children.push_back(other.children[i]->clone());
        }
    }
    return *this;
}

//move constructor
Tree::Tree(Tree &&other) : node(other.node), children(other.children) {
    for (size_t i = 0; i < other.children.size(); ++i) {
        other.children[i] = nullptr;
    }
}

//move assignment operator
const Tree &Tree::operator=(Tree &&other) {
    if (this != &other) {
        clear();
        node = other.node;
        children = other.children;
        for (size_t i = 0; i < other.children.size(); ++i) {
            other.children[i] = nullptr;
        }
        other.children.clear();
    }
    return *this;
}


//====================================
void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}


void Tree::addChild(Tree *child) {
    children.push_back(child);

}


Tree *Tree::createTree(const Session &session, int rootLabel) {
    if (session.getTreeType() == Root) {
        return new RootTree(rootLabel);
    } else if (session.getTreeType() == MaxRank) {
        return new MaxRankTree(rootLabel);
    } else {//means that TreeType==Cycle
        return new CycleTree(rootLabel, session.getCycle());
    }

}

int Tree::getNode() const {
    return node;
}

vector<Tree *> Tree::getChildren() const {
    return children;
}


int Tree::maxDegreeNodes() {//the function returns a vector includes all nodes with max degree
    int maxRank = this->children.size();
    int maxNode = this->node;
    queue<Tree *> bfsNextNode;
    bfsNextNode.push(this);
    Tree *currNode;
    int size = 0;
    while (!bfsNextNode.empty()) {
        currNode = bfsNextNode.front();
        bfsNextNode.pop();
        size = currNode->getChildren().size();
        if (size > maxRank) {
            maxRank = currNode->getChildren().size();
            maxNode = currNode->getNode();
        }

        for (size_t i = 0; i < currNode->getChildren().size(); ++i) {
            bfsNextNode.push(currNode->getChildren()[i]);
        }
    }
    return maxNode;
}


//================CycleTree====================
//constructor
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {
}

int CycleTree::traceTree() {
    Tree *cycleNode = this;
    while (currCycle > 0 && !cycleNode->getChildren().empty()) //if the node has children
    {
        cycleNode = cycleNode->getChildren()[0]; //get the lest most child
        currCycle--;
    }
    return cycleNode->getNode();
}

CycleTree *CycleTree::clone() const {
    return new CycleTree(*this);
}


//================MaxRankTree====================
//constructor
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {
}

int MaxRankTree::traceTree() {
    return maxDegreeNodes();//returns the one with smallest depth and index
}

MaxRankTree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}


//================RootTree====================
//constructor
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {
}

RootTree *RootTree::clone() const {
    return new RootTree(*this);
}

int RootTree::traceTree() {
    return getNode();
}


