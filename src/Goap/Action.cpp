#include "Action.h"

bool Action::IsApplicable(const WorldState& state) const
{
    for (const auto& [flag, value] : preconditions)
        if (state.GetFlag(flag) != value)
            return false;

    if (requiredLocation.has_value() && state.location != requiredLocation.value())
        return false;

    return true;
}

WorldState Action::Apply(const WorldState& state) const
{
    WorldState result = state;

    for (const auto& [flag, value] : effects)
        result.SetFlag(flag, value);

    if (resultingLocation.has_value())
        result.location = resultingLocation.value();

    return result;
}
