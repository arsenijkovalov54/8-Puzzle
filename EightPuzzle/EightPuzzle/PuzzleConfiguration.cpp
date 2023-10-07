#include "PuzzleConfiguration.h"

PuzzleConfiguration::PuzzleConfiguration()
{
    initializeGoalState();
    while (true)
    {
        bool manually;
        cout << "Would you like to enter the state manually? (Yes - 1 / No - 0)" << '\n';
        cin >> manually;
        if (manually)
        {
            string rawInitialState;
            cout << "Enter 9 digits (0 to 8), separated by comma: ";
            cin >> rawInitialState;
            stringstream ss(rawInitialState);
            vector<int> initialState;
            for (int i; ss >> i;)
            {
                initialState.push_back(i);
                if (ss.peek() == ',')
                    ss.ignore();
            }
            if (isValidPermutation(initialState))
            {
                this->initialState = initialState;
                break;
            }
            else
            {
                // E.g. 8,1,2,0,4,3,7,6,5
                cout << "Impossible to solve this combination" << '\n';
            }
        }
        else
        {
            bool cornerEmptyTile;
            cout << "Generating state..." << '\n';
            cout << "Empty corner tile? (Yes - 1 / No - 0)" << '\n';
            cin >> cornerEmptyTile;
            this->cornerEmptyTile = cornerEmptyTile;
            initializeInitialState();
            break;
        }
    }
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
    this->initialState = possibleInitialState;
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