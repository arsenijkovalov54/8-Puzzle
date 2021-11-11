#include "AStarSearch.h"

AStarSearch::AStarSearch(shared_ptr<PuzzleConfiguration> puzzleConfiguration)
{
    goalState = puzzleConfiguration->getGoalState();
    puzzleSolved = false;
    openList.push_back(shared_ptr<Node>(new Node(puzzleConfiguration->getInitialState(), nullptr, 0)));
}

shared_ptr<Node> AStarSearch::getMinWeightChildNode()
{
    auto minWeightChildNodeIter(min_element(openList.begin(), openList.end(), WeightCompareFunctor()));
    closedList.push_back(*minWeightChildNodeIter);
    openList.erase(minWeightChildNodeIter);
    return closedList.back();
}

void AStarSearch::expandNode(shared_ptr<Node> minWeightChildNode)
{
    if (minWeightChildNode->getState() == goalState)
    {
        puzzleSolved = true;
        shared_ptr<Node> finalMinWeightChildNode = closedList.back();
        while (finalMinWeightChildNode)
        {
            shortestPath.push_back(finalMinWeightChildNode);
            finalMinWeightChildNode = finalMinWeightChildNode->getParentNode();
        }
        reverse(shortestPath.begin(), shortestPath.end());
    }
    int emptyTileIndex = minWeightChildNode->getEmptyTileIndex();
    vector<int> adjacentTiles, possibleMinWeightChildNodeState;
    if (emptyTileIndex - Dimension >= 0)
    {		//	Move empty tile up
        adjacentTiles.push_back(emptyTileIndex - 3);
    }
    if (emptyTileIndex % Dimension < Dimension - 1)
    {		//	Move empty tile right
        adjacentTiles.push_back(emptyTileIndex + 1);
    }
    if (emptyTileIndex + Dimension < TotalTilesNumber)
    {		//	Move empty tile down
        adjacentTiles.push_back(emptyTileIndex + 3);
    }
    if (emptyTileIndex % Dimension)
    {		//	Move empty tile left
        adjacentTiles.push_back(emptyTileIndex - 1);
    }
    for (auto adjacentTileIndex : adjacentTiles)
    {
        possibleMinWeightChildNodeState = minWeightChildNode->getState();
        swap(possibleMinWeightChildNodeState[emptyTileIndex], possibleMinWeightChildNodeState[adjacentTileIndex]);
        if (!listContains(closedList, possibleMinWeightChildNodeState))
        {
            openList.push_back(shared_ptr<Node>(new Node(possibleMinWeightChildNodeState, minWeightChildNode, minWeightChildNode->getDepth() + 1)));
        }
    }
}

bool AStarSearch::listContains(vector<shared_ptr<Node>>& list, vector<int>& state) const
{
    for (auto node : list)
    {
        if (node->getState() == state)
        {
            return true;
        }
    }
    return false;
}

void AStarSearch::printShortestPath() const
{
    cout << "Moves required: " << shortestPath.size() - 1 << '\n';
    for (auto node : shortestPath)
    {
        node->printNodeConfiguration();
    }
    cout << '\n';
}

void AStarSearch::printMovedTiles() const
{
    cout << "Directions:" << '\n';
    int i = 1;
    for (auto tile : movedTiles)
    {
        cout << i << ") " << tile.first << ' ' << tile.second << '\n';
        i++;
    }
    cout << '\n';
}

void AStarSearch::recreateTilesMovement()
{
    int i, currentStateEmptyTileIndex, nextStateEmptyTileIndex;
    for (i = 0; i < shortestPath.size() - 1; i++)
    {
        currentStateEmptyTileIndex = shortestPath[i]->getEmptyTileIndex();
        nextStateEmptyTileIndex = shortestPath[i + 1]->getEmptyTileIndex();
        if (currentStateEmptyTileIndex - nextStateEmptyTileIndex == 1)
        {
            movedTiles.push_back(make_pair(shortestPath[i]->getState()[nextStateEmptyTileIndex], "Right"));
        }
        if (currentStateEmptyTileIndex - nextStateEmptyTileIndex == -1)
        {
            movedTiles.push_back(make_pair(shortestPath[i]->getState()[nextStateEmptyTileIndex], "Left"));
        }
        if (currentStateEmptyTileIndex - nextStateEmptyTileIndex == 3)
        {
            movedTiles.push_back(make_pair(shortestPath[i]->getState()[nextStateEmptyTileIndex], "Down"));
        }
        if (currentStateEmptyTileIndex - nextStateEmptyTileIndex == -3)
        {
            movedTiles.push_back(make_pair(shortestPath[i]->getState()[nextStateEmptyTileIndex], "Up"));
        }
    }
}

void AStarSearch::search()
{
    while (!puzzleSolved)
    {
        expandNode(getMinWeightChildNode());
    }
}