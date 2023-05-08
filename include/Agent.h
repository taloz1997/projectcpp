#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "../include/Session.h"
#include "queue"

using namespace std;


class Agent {
public:
    //constructor
    Agent();

    virtual ~Agent();
//================other functions====================
    virtual Agent *clone() const = 0;
    virtual void act(Session &session) = 0;
};

class ContactTracer : public Agent {
public:
    //constructor
    ContactTracer();

    //================other functions====================
    virtual ContactTracer* clone() const;
    virtual void act(Session &session);
};


class Virus : public Agent {
public:
    //constructor
    Virus(int nodeInd);

    //================other functions====================
    virtual Virus *clone() const;
    virtual void act(Session &session);

private:
    const int nodeInd;
};

#endif