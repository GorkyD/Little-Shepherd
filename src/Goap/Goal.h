#ifndef WILDLIFESIM_GOAL_H
#define WILDLIFESIM_GOAL_H

#include <optional>
#include <utility>
#include <vector>

#include "WorldState.h"

struct Goal
{
    int priority = 0;
    
    std::vector<std::pair<Flag, bool>> activationCondition;
    std::vector<std::pair<Flag, bool>> targetConditions;
    std::optional<Location> targetLocation;

    bool IsRelevant(const WorldState& state) const;
    bool IsSatisfied(const WorldState& state) const;
};

#endif
