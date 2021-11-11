#pragma once

#include "Node.h"

class PuzzleConfiguration
{
private:
    vector<int> initialState, goalState;
    bool cornerEmptyTile;
public:
    PuzzleConfiguration(bool cornerEmptyTile);
    const vector<int>& getInitialState() const;
    const vector<int>& getGoalState() const;
    void initializeGoalState();
    void initializeInitialState();
    bool isValidPermutation(vector<int>& state) const;
};