#include "AStarSearch.h"

int main()
{
    srand(time(0));
    AStarSearch aSearch(shared_ptr<PuzzleConfiguration>(new PuzzleConfiguration()));
    aSearch.search();
    aSearch.recreateTilesMovement();
    aSearch.printShortestPath();
    aSearch.printMovedTiles();
    system("pause");
    return 0;
}