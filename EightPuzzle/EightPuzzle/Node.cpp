#include "Node.h"

Node::Node(const vector<int>& state, shared_ptr<Node> parentNode, int depth)
{
    this->state = state;
    this->parentNode = parentNode;
    this->depth = depth;
    weight = calculateManhattanDistance() + calculateHammingDistance() + depth;
}

const vector<int>& Node::getState() const
{
    return state;
}

shared_ptr<Node> Node::getParentNode() const
{
    return parentNode;
}

int Node::getWeight() const
{
    return weight;
}

int Node::getDepth() const
{
    return depth;
}

int Node::getEmptyTileIndex() const
{
    for (int i = 0; i < TotalTilesNumber; ++i)
    {
        if (!state[i])
        {
            return i;
        }
    }
}

int Node::calculateManhattanDistance() const
{
    int manhattanDistance = 0, i;
    for (i = 0; i < TotalTilesNumber; i++)
    {
        if (!state[i])
        {
            continue;
        }
        manhattanDistance += abs((i % Dimension) - ((state[i] - 1) % Dimension)) + abs((i / Dimension) - ((state[i] - 1) / Dimension));
    }
    return manhattanDistance;
}

int Node::calculateHammingDistance() const
{
    int hammingDistance = 0, i;
    for (i = 0; i < TotalTilesNumber; i++)
    {
        if (!state[i])
        {
            continue;
        }
        if (state[i] != i + 1)
        {
            hammingDistance++;
        }
    }
    return hammingDistance;
}

void Node::printNodeConfiguration() const
{
    int i, j;
    for (i = 0; i < Dimension; i++)
    {
        for (j = 0; j < Dimension; j++)
        {
            cout << state[i * Dimension + j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}