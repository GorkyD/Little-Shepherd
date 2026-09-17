#include "GridDomain.h"
#include <cmath>

std::vector<GridPos> GridDomain::GetNeighbors(GridPos node) const
{
    std::vector<GridPos> neighbors;
    int newRow = node.row + 1, newCol = node.col;

    if (newRow < world->GetWorldWidth() && world->IsTileWalkable(newRow,newCol) && world->IsTileNotBusy(newRow,newCol))
        neighbors.push_back(GridPos(newRow,newCol));

    newRow = node.row - 1, newCol = node.col;

    if (newRow >= 0 && world->IsTileWalkable(newRow,newCol) && world->IsTileNotBusy(newRow,newCol))
        neighbors.push_back(GridPos(newRow,newCol));

    newRow = node.row, newCol = node.col + 1;

    if (newCol <  world->GetWorldHeight() && world->IsTileWalkable(newRow,newCol) && world->IsTileNotBusy(newRow,newCol))
        neighbors.push_back(GridPos(newRow,newCol));

    newRow = node.row, newCol = node.col - 1;

    if (newCol >= 0 && world->IsTileWalkable(newRow,newCol) && world->IsTileNotBusy(newRow,newCol))
        neighbors.push_back(GridPos(newRow,newCol));
    
    newRow = node.row - 1, newCol = node.col - 1;

    if ( newRow >= 0 && newCol >= 0 && world->IsTileWalkable(newRow,newCol) && world->IsTileNotBusy(newRow,newCol))
        neighbors.push_back(GridPos(newRow,newCol));
    
    newRow = node.row - 1, newCol = node.col + 1;

    if (newRow >= 0 && newCol <  world->GetWorldHeight()  && world->IsTileWalkable(newRow,newCol) && world->IsTileNotBusy(newRow,newCol))
        neighbors.push_back(GridPos(newRow,newCol));
    
    newRow = node.row + 1, newCol = node.col + 1;

    if (newRow < world->GetWorldWidth() && newCol <  world->GetWorldHeight()  && world->IsTileWalkable(newRow,newCol) && world->IsTileNotBusy(newRow,newCol))
        neighbors.push_back(GridPos(newRow,newCol));
    
    newRow = node.row + 1, newCol = node.col - 1;

    if (newRow < world->GetWorldWidth() && newCol >= 0 && world->IsTileWalkable(newRow,newCol) && world->IsTileNotBusy(newRow,newCol))
        neighbors.push_back(GridPos(newRow,newCol));
    
    return neighbors;
}

int GridDomain::Cost(GridPos from, GridPos to) const
{
    return 1;
}

float GridDomain::Heuristic(GridPos node, GridPos goal) const
{
    return ManhattanHeuristic(node.row,node.col,goal.row,goal.col);
}

int GridDomain::ManhattanHeuristic(int row, int col, int targetRow, int targetCol) const
{
    return std::abs(row - targetRow) + std::abs(col - targetCol);
}

float GridDomain::EuqlidHeuristic(int row, int col, int targetRow, int targetCol) const
{
    const float dx = static_cast<float>(row - targetRow);
    const float dy = static_cast<float>(col - targetCol);

    return std::hypot(dx, dy);
}

bool GridDomain::IsGoalSatisfied(GridPos node, GridPos goal) const
{
    return node == goal;
}
