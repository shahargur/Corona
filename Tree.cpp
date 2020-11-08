#include "/home/spl211/CLionProjects/208482216-315741454/Include/Tree.h"
#include "/home/spl211/CLionProjects/208482216-315741454/Include/Graph.h"
#include "/home/spl211/CLionProjects/208482216-315741454/Include/Session.h"
#include <queue>
#include <vector>

using namespace std;

Tree:: Tree(int rootLabel): node(rootLabel),children(vector<Tree*>()) {};
Tree::Tree(Tree &copyTree) {
    node = copyTree.node;
    for(int j = 0 ; j < copyTree.children.size();j++){
        children.push_back(copyTree.children[j]);
    }
};
Tree::~Tree() {
    children.~vector();
}
Tree & Tree::operator=(const Tree &other) {
    if(this != &other){
        for(int i=0; i<children.size(); i++){
            delete children[i];
        }
        node = other.node;
        maxRankNode = other.maxRankNode;
        for(int i=0; i<other.children.size(); i++){
            children.push_back(other.children[i]);
        }
    }
    return *this;
}
void Tree::addChild(const Tree &child) {
    children.push_back(child);
}
Tree* Tree::createTree(const Session &session, int rootLabel) {
    if(session.getTreeType() == MaxRank){
        MaxRankTree output(rootLabel);
        return &output;
    }
    if(session.getTreeType() == Root){
        RootTree output(rootlabel);
        return &output;
    }
    else{
        CycleTree output(session.getCurrCycle(),rootLabel);
        return &output;
    }
}

void Tree::bfs(const Session &session, int rootLabel) {
    //creating a tree with the starting node rootLabel
    Tree* currTree = Tree::createTree(session,rootLabel);
    //reading the graph from the session
    Graph g = session.getGraph();
    vector<vector<int>> matrix = g.getEdges();
    queue<Tree*> nodeQueue;
    //starting node enter to the queue
    nodeQueue.push(currTree);
    bool isVisited[matrix.size()];
    //initialize the bool array
    for(int i = 0 ; i < matrix.size(); i++){
        isVisited[i] = false;
    }
    //starting the bfs "traveling"
    while(!nodeQueue.empty()){
        Tree* nextTree = nodeQueue.front();
        nodeQueue.pop();
        //searching for nextTree neighbors
        for(int i = 0; i < matrix[nextTree->node].size(); i++){
            if(i != nextTree->node && matrix[nextTree->node][i] == 1 && !isVisited[i]){
                isVisited[i] = true;
                Tree* newTree = Tree::createTree(session,i);
                nextTree->addChild(*newTree);
                nodeQueue.push(newTree);
            }
        }
        //update the node with the max rank
        if(nextTree->children.size() > maxRankNode)
            maxRankNode = nextTree->node;
    }
}


//CycleTree
CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel),currCycle(currCycle) {};
int CycleTree::traceTree() {
    Tree* output(node);
    for(int i = 0; i != currCycle; i++){
        output = output
    }
    return output.node;
}

//MaxRankTree
MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel) {};
int MaxRankTree::traceTree() {
    int output = Parent:: maxRankNode;
    return output;
}

//RootTree
RootTree::RootTree(int rootLabel): Tree(rootLabel) {};
int RootTree::traceTree() {
    return Parent::node;
}