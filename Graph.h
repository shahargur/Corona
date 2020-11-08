#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    const vector<vector<int>> getEdges() const;
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

private:
    std::vector<std::vector<int>> edges;
};

#endif
