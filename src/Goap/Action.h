#ifndef WILDLIFESIM_ACTION_H
#define WILDLIFESIM_ACTION_H

#include <optional>
#include <string>
#include <utility>
#include <vector>
#include "WorldState.h"

struct Action
{
    std::string name;
    std::vector<std::pair<Flag, bool>> preconditions;
    std::vector<std::pair<Flag, bool>> effects;

    std::optional<Location> requiredLocation;
    std::optional<Location> resultingLocation;

    int cost = 1;

    bool IsApplicable(const WorldState& state) const;
    WorldState Apply(const WorldState& state) const;
};

#endif
