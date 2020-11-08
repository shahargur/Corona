#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include <queue>
using namespace std;

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    queue<int> infectNodes;
    Session(const std::string& path);
    Session(Session &other);
    virtual ~Session();
    Session& operator=(const Session& other);
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    Graph getGraph() const;
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    int getCurrCycle()const;
    static TreeType readTypeFromJson(const json readInput);
    static Graph readGraphFromJson(const json readInput);
    static vector<Agent*> readAgentFromJson(const json readInput);
    
private:
    int activeViruses = 0;
    int currCycle = 0;
    Graph g;
    TreeType treeType;
    vector<Agent*> agents;
};

#endif
