#include "AStarSearch.h"

int main()
{
    srand(time(0));
    bool flag = false;
    cout << "Empty corner tile (Yes - 1 / No - 0)" << '\n';
    cin >> flag;
    AStarSearch aSearch(shared_ptr<PuzzleConfiguration>(new PuzzleConfiguration(flag)));
    aSearch.search();
    aSearch.recreateTilesMovement();
    aSearch.printShortestPath();
    aSearch.printMovedTiles();
    return 0;
}