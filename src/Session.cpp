//
// Created by spl211 on 05/11/2020.
//
#include <fstream>
#include "../include/Session.h"
#include "../include/json.hpp"
#include <iostream>


using json = nlohmann::json;
using namespace std;

//constructors
Session::Session(const string &path) : g(), treeType(), agents(), infectedQueue(), cycle(0) {
    ifstream i(path);
    json input;
    i >> input;
    g = Graph(input["graph"]);

    string inputTreeType = input["tree"];
    if (inputTreeType == "M")
        treeType = MaxRank;
    else if (inputTreeType == "C")
        treeType = Cycle;
    else treeType = Root;

    vector <pair<string, int>> agentVector = input["agents"];
    Agent *newAgent;
    for (auto &elem:input["agents"]) {
        if (elem[0] == "C") {
            newAgent = new ContactTracer();
        } else {
            newAgent = new Virus(elem[1]);
            g.setIfCarry(elem[1], true);
        }
        agents.push_back(newAgent);
    }
}

Session::Session() : g(), treeType(), agents(), infectedQueue(), cycle() {
}

//================Rule of 5====================
//destructor
Session::~Session() {
    clear();
}

void Session::clear() {
    for (size_t i = 0; i < agents.size(); ++i) {
        if (agents[i] != nullptr) {
            delete agents[i];
        }
    }
}

//copy constructor
Session::Session(const Session &other) : g(other.g), treeType(other.treeType), agents(), infectedQueue(), cycle() {
    for (size_t i = 0; i < other.agents.size(); ++i) {
        agents.push_back( other.agents[i]->clone());
    }
}

//copy assignment operator
const Session &Session::operator=(const Session &other) {
    if (this != &other) {
        clear();
        g = other.g;
        treeType = other.treeType;
        for (size_t i = 0; i < other.agents.size(); ++i) {
            agents.push_back( other.agents[i]->clone());
        }
        infectedQueue = other.infectedQueue;
        cycle = other.cycle;
    }
    return *this;
}

//move constructor
Session::Session(Session &&other) : g(other.g), treeType(other.treeType), agents(other.agents),
                                    infectedQueue(other.infectedQueue), cycle(other.cycle) {
    for (size_t i = 0; i < other.agents.size(); ++i) {
        other.agents[i] = nullptr;
    }
}

//move assignment operator
const Session &Session::operator=(Session &&other) {
    if (this != &other) {
        clear();
        g = other.g;
        treeType = other.treeType;
        agents = other.agents;
        for (size_t i = 0; i < agents.size(); ++i) {
            other.agents[i] = nullptr;
        }
        infectedQueue = other.infectedQueue;
        cycle = other.cycle;

        other.agents.clear();
    }
    return *this;
}


//================getters====================
TreeType Session::getTreeType() const {
    return treeType;
}

Graph &Session::getGraph() {
    return g;
}


queue<int> Session::GetInfectedQueue() {
    return infectedQueue;
}

int Session::getCycle() const {
    return cycle;
}

//================setters====================
void Session::setGraph(const Graph &graph) {
    g = graph;
}

//================other functions====================
void Session::simulate() {
    size_t size;
    while (!g.isComplete(cycle)) {//the chain of infection continues
        size = agents.size();
        for (size_t i = 0; i < size; ++i) {
            agents[i]->act(*this);//the agent will act
        }
        cycle = cycle + 1;
    }
    output();
}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

void Session::enqueueInfected(int nodeToInsert) {
    infectedQueue.push(nodeToInsert);
}

int Session::dequeueInfected() {
    int infectedIndex = infectedQueue.front();
    infectedQueue.pop();
    return infectedIndex;
}

void Session::output() {
    nlohmann::json outputJ;
    outputJ["graph:"] = g.getEdges();
    vector<int> infectedV;
    for (size_t i = 0; i < g.getInfected().size(); ++i) {
        if (g.getInfected()[i]) {
            infectedV.push_back(i);
        }
    }
    outputJ["graph"] = g.getEdges();
    outputJ["infected"] = infectedV;
    ofstream i("./output.json");
    i << outputJ;
}