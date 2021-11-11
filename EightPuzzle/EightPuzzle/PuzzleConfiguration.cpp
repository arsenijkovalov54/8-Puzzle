#include "PuzzleConfiguration.h"

PuzzleConfiguration::PuzzleConfiguration(bool cornerEmptyTile)
{
    this->cornerEmptyTile = cornerEmptyTile;
    initializeGoalState();
    initializeInitialState();
}

const vector<int>& PuzzleConfiguration::getInitialState() const
{
    return initialState;
}

const vector<int>& PuzzleConfiguration::getGoalState() const
{
    return goalState;
}

void PuzzleConfiguration::initializeGoalState()
{
    int i;
    for (i = 0; i < TotalTilesNumber; i++)
    {
        if (TotalTilesNumber - i == 1)
        {
            goalState.push_back(0);
        }
        else
        {
            goalState.push_back(i + 1);
        }
    }
}

void PuzzleConfiguration::initializeInitialState()
{
    vector<int> possibleInitialState = goalState;
    int movingTilesNumber, i;
    if (cornerEmptyTile)
    {
        movingTilesNumber = TotalTilesNumber - 1;
    }
    else
    {
        movingTilesNumber = TotalTilesNumber;
    }
    do
    {
        for (i = 0; i < movingTilesNumber; i++)
        {
            swap(possibleInitialState[i], possibleInitialState[rand() % movingTilesNumber]);
        }
    } while (!isValidPermutation(possibleInitialState));
    initialState = possibleInitialState;
}

bool PuzzleConfiguration::isValidPermutation(vector<int>& state) const
{
    int inversions = 0, i, j;
    for (i = 0; i < TotalTilesNumber; i++)
    {
        if (state[i])
        {
            for (j = i + 1; j < TotalTilesNumber; j++)
            {
                if (state[j] && state[j] < state[i])
                {
                    inversions++;
                }
            }
        }
        else
        {
            if (!(Dimension & 1))
            {
                inversions += (1 + i / Dimension);
            }
        }
    }
    if (inversions & 1)
    {
        return false;
    }
    return true;
}