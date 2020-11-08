#ifndef TREE_H_
#define TREE_H_
#include "/home/spl211/CLionProjects/208482216-315741454/Include/Graph.h"
#include <vector>

class Session;

class Tree{

public:
    Tree(int rootLabel);
    Tree(Tree &copyTree);
    ~Tree();
    Tree& operator=(const Tree& other);
    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);
    void bfs(const Session& session,int rootLabel);
    virtual Tree* clone()=0;
    virtual int traceTree()=0;

protected:
    int maxRankNode = -1;
    int node;
    std::vector<Tree*> children;

};


class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual Tree* clone();
    virtual int traceTree();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual Tree* clone();
    virtual int traceTree();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual Tree* clone();
    virtual int traceTree();
};

#endif
