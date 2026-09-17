#ifndef WILDLIFESIM_GRIDDOMAIN_H
#define WILDLIFESIM_GRIDDOMAIN_H

#include <memory>
#include "World/World.h"
#include "World/GridPos.h"

class GridDomain
{
    std::shared_ptr<World> world;
public:
    explicit GridDomain(const std::shared_ptr<World>& world) : world(world) {}

    std::vector<GridPos> GetNeighbors(GridPos node) const;
    float Heuristic(GridPos node, GridPos goal) const;
    int Cost(GridPos from, GridPos to) const;
    int ManhattanHeuristic(int row, int col, int targetRow, int targetCol) const;
    float EuqlidHeuristic(int row, int col, int targetRow, int targetCol) const;
    bool IsGoalSatisfied(GridPos node, GridPos goal) const;
};


#endif
