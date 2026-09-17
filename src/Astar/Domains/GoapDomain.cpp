#include "GoapDomain.h"

std::vector<WorldState> GoapDomain::GetNeighbors(WorldState state) const
{
    std::vector<WorldState> neighbors;
    
    for (const auto& action : actions)
        if (action.IsApplicable(state))
            neighbors.push_back(action.Apply(state));
    
    return neighbors;
}

const Action* GoapDomain::FindAction(WorldState from, WorldState to) const
{
    const Action* best = nullptr;

    for (const Action& action : actions)
        if (action.IsApplicable(from) && action.Apply(from) == to)
            if (!best || action.cost < best->cost)
                best = &action;

    return best;
}

float GoapDomain::Cost(WorldState from, WorldState to) const
{
    auto action = FindAction(from, to);
    return action ? static_cast<float>(action->cost) : 1;
}

float GoapDomain::Heuristic(WorldState state, Goal goal) const
{
    int unmet = 0;

    for (const auto& [flag, value] : goal.targetConditions)
        if (state.GetFlag(flag) != value)
            unmet++;

    if (goal.targetLocation.has_value() && state.location != goal.targetLocation.value())
        unmet++;

    return static_cast<float>(unmet);
}

bool GoapDomain::IsGoalSatisfied(WorldState state, Goal goal) const
{
    return goal.IsSatisfied(state);
}
