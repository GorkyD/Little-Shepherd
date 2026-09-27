#ifndef WILDLIFESIM_GETWATER_H
#define WILDLIFESIM_GETWATER_H

#include "Goap/Action.h"

inline Action GetWater()
{
    return Action
    {
        .name = "GetWater",
        .preconditions = {{Flag::FireNearby, true}, {Flag::HasWater, false}},
        .effects = {{Flag::HasWater, true}},
        .cost = 1
    };
}

#endif
