#pragma once

#include "PuzzleConfiguration.h"

class WeightCompareFunctor
{
public:
    bool operator()(shared_ptr<Node> leftNode, shared_ptr<Node> rightNode)
    {
        return leftNode->getWeight() < rightNode->getWeight();
    }
};

class AStarSearch
{
private:
    vector<shared_ptr<Node>> openList, closedList, shortestPath;
    vector<int> goalState;
    bool puzzleSolved;
    vector<pair<int, string>> movedTiles;
public:
    AStarSearch(shared_ptr<PuzzleConfiguration> puzzleConfiguration);
    shared_ptr<Node> getMinWeightChildNode();
    void expandNode(shared_ptr<Node> minWeightChildNode);
    bool listContains(vector<shared_ptr<Node>>& list, vector<int>& state) const;
    void printShortestPath() const;
    void printMovedTiles() const;
    void recreateTilesMovement();
    void search();
};