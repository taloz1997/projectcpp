#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "../include/Graph.h"
#include "queue"
#include "../include/Agent.h"

using namespace std;

class Agent;

enum TreeType {
    Cycle,
    MaxRank,
    Root
};

class Session {
public:
    //constructors
    Session(const std::string &path);
    Session();

    //================Rule of 5====================
    virtual ~Session();//destructor
    void clear();
    Session(const Session &other); //copy constructor
    const Session &operator=(const Session &other);//copy assignment operator
    Session(Session &&other);//move constructor
    const Session &operator=(Session &&other);//move assignment operator

    //================getters====================
    TreeType getTreeType() const;
    Graph& getGraph();
    queue<int> GetInfectedQueue();
    int getCycle() const;


    //================setters====================
    void setGraph(const Graph &graph);

    //================other functions====================
    void simulate();
    void addAgent(const Agent &agent);
    void enqueueInfected(int nodeToInsert);
    int dequeueInfected();
    void output();


private:
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;
    queue<int> infectedQueue;
    int cycle;

};

#endif