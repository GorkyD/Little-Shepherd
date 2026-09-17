#ifndef WILDLIFESIM_GOAPDOMAIN_H
#define WILDLIFESIM_GOAPDOMAIN_H

#include <vector>
#include "Goap/Action.h"
#include "Goap/Goal.h"
#include "Goap/WorldState.h"

class GoapDomain
{
    std::vector<Action> actions;

public:
    explicit GoapDomain(std::vector<Action> actions) : actions(std::move(actions)) {}

    std::vector<WorldState> GetNeighbors(WorldState state) const;
    const Action* FindAction(WorldState from, WorldState to) const;
    float Heuristic(WorldState state, Goal goal) const;
    float Cost(WorldState from, WorldState to) const;
    bool IsGoalSatisfied(WorldState state, Goal goal) const;
};
#endif
