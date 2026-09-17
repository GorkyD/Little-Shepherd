#include "Goal.h"

bool Goal::IsRelevant(const WorldState& state) const
{
    for (const auto& [flag, value] : activationCondition)
        if (state.GetFlag(flag) != value)
            return false;
    
    return true;
}

bool Goal::IsSatisfied(const WorldState& state) const
{
    for (const auto& [flag, value] : targetConditions)
        if (state.GetFlag(flag) != value)
            return false;

    if (targetLocation.has_value() && state.location != targetLocation.value())
        return false;

    return true;
}
