#ifndef WILDLIFESIM_CHOPWOOD_H
#define WILDLIFESIM_CHOPWOOD_H

#include "Goap/Action.h"

inline Action ChopWood()
{
    return Action
    {
        .name = "ChopWood",
        .preconditions = {{Flag::IsDayTime, true}, {Flag::IsInDanger, false}},
        .effects = {{Flag::HasWorked, true}},
        .requiredLocation = Location::Forest,
        .cost = 1
    };
}

#endif
