#include "../Include/Graph.h"
#include "../Include/Agent.h"
#include "../Include/Tree.h"
#include "../Include/Session.h"
#include "../Include/json.hpp"
#include <fstream>
#include <vector>
#include <utility>
using json=nlohmann:: json;
using namespace std;

Session::Session(const std::string &path) : g(vector<vector<int>>()) {
    json readInput;
    ifstream readInput_file(path, std::ifstream::binary);
    readInput_file >> readInput;
    g = readGraphFromJson(readInput);
    treeType = readTypeFromJson(readInput);
    agents = readAgentFromJson(readInput);
}
//reading the Graph input from the json file
Graph Session::readGraphFromJson(const int readInput) {
    vector<vector<int>> matrix;
    vector<int> row;
    for(int i=0; i < ((vector<vector<int>>)readInput["graph"]).size();i++){
        for(int j=0;j<((vector<vector<int>>)readInput["graph"]).size();j++){
            row.push_back(((vector<vector<int>>)readInput["graph"])[i][j]);
        }
        matrix.push_back(row);
        row.clear();
    }
    return Graph(matrix);
}
//reading the treeType input from the json file
TreeType Session::readTypeFromJson(const int readInput) {
    if(readInput["tree"] == 'M')
        return MaxRank;
    if(readInput["tree"] == 'C')
        return Cycle;
    return Root;
}
//reading the Agents input from the json file
vector<Agent*> Session::readAgentFromJson(const int readInput) {
    vector<pair<char,int>> inputVector(((vector<pair<char,int>>)(readInput["agents"])));
    vector<Agent*> output;
    for(int i = 0 ; i < inputVector.size(); i++){
        if(inputVector[i].first == 'V') {
            Virus newAgent(inputVector[i].second);
            output.push_back(&newAgent);
            activeViruses++;
        }
        else{
            ContactTracer newAgent;
            output.push_back(&newAgent);
        }
    }
    return output;
}
//copy constructor
Session::Session(Session &other): g(vector<vector<int>>()) {
    currCycle = other.currCycle;
    treeType = other.treeType;
    g = other.g;
    for(int i = 0; i < other.agents.size(); i++){
        agents[i] = other.agents[i];
    }

}
//destructor
Session::~Session() {
    agents.~vector();
}
Session& Session::operator=(const Session &other) {

}
void Session::simulate() {
    while(activeViruses != 0){
        currCycle++;
        for(int i = 0; i < agents.size() ; i++){
            agents[i]->act(this);
        }
    }
}

void Session::addAgent(const Agent &agent) {
    Agent* newAgent = agent.clone();
    agents.push_back(newAgent);
}

void Session::setGraph(const Graph &graph) {

}

void Session::enqueueInfected(int) {

}

int Session::dequeueInfected() {

}

TreeType Session::getTreeType() const {
    return treeType;
}

Graph Session::getGraph() const {
    return g;
}

