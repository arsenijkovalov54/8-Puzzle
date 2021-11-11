#pragma once

#include "stdafx.h"

class Node
{
private:
    vector<int> state;
    shared_ptr<Node> parentNode;
    int weight, depth;
public:
    Node(const vector<int>& state, shared_ptr<Node> parentNode, int depth);
    const vector<int>& getState() const;
    shared_ptr<Node> getParentNode() const;
    int getWeight() const;
    int getDepth() const;
    int getEmptyTileIndex() const;
    int calculateManhattanDistance() const;
    int calculateHammingDistance() const;
    void printNodeConfiguration() const;
};