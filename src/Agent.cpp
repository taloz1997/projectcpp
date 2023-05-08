//
// Created by spl211 on 05/11/2020.
//

#include "../include/Agent.h"
#include "queue"
#include <iostream>

using namespace std;


//constructor
Agent::Agent() {}

Agent::~Agent() {
}


//============ Contact Tracer =============
//constructor
ContactTracer::ContactTracer() {}

ContactTracer *ContactTracer::clone() const {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session) {
    if (!session.GetInfectedQueue().empty()) {//if there are infected nodes
        int indexOfInfected = session.dequeueInfected();
        Graph g = session.getGraph();
        Tree *infectedNode = g.BFS(session, indexOfInfected);
        int index = infectedNode->traceTree();//returns the node we need to disconnect from the graph
        session.setGraph(g.updateGraph(index));
        delete infectedNode;//finished working on this tree
    }
}


//================ Virus =================
//constructor
Virus::Virus(int nodeInd) : nodeInd(nodeInd) {}

Virus *Virus::clone() const {
    return new Virus(*this);
}

void Virus::act(Session &session) {
    if(!session.getGraph().getInfected()[nodeInd]){
        session.getGraph().setIfInfected(nodeInd);//indicate that the node got infected
        session.enqueueInfected(nodeInd);
        session.getGraph().setIfCarry(nodeInd,false);
    }
    if (session.getGraph().haveChildren(nodeInd)) {//if doesn't have children- continue to the next one
        int childIndex = session.getGraph().firstHealthyChild(nodeInd);//returns the index of the first healthy child
        if (childIndex != -1) {//-1 indicates that there are no healthy children
            session.addAgent(Virus(childIndex));  //create new virus and add it to agents
            session.getGraph().setIfCarry(childIndex,true);
        }
    }
}