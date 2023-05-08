#ifndef TREE_H_
#define TREE_H_

#include <vector>
using namespace std;

class Session;

class Tree{
public:
    //constructor
    Tree(int rootLabel);
    Tree();
//================Rule of 5====================
    virtual ~Tree();//destructor
    void clear();
    Tree(const Tree &other); //copy constructor
    const Tree &operator=(const Tree &other);//copy assignment operator
    Tree(Tree &&other);//move constructor
    const Tree &operator=(Tree &&other);//move assignment operator

//================getters====================
    int getNode() const;
    vector<Tree*> getChildren() const;


//================other functions====================
    virtual Tree *clone() const = 0;
    void addChild(const Tree& child);
    void addChild( Tree* child);

    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    int maxDegreeNodes();

private:
    int node;
    std::vector<Tree*> children;


};
class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual CycleTree *clone() const;
    virtual int traceTree();

private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual MaxRankTree *clone() const;
    virtual int traceTree() ;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual RootTree *clone() const;
    virtual int traceTree();
};

#endif