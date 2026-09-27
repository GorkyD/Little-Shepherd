#ifndef WILDLIFESIM_EXTINGUISHFIRE_H
#define WILDLIFESIM_EXTINGUISHFIRE_H

#include "Goap/Action.h"

inline Action ExtinguishFire()
{
    return Action
    {
        .name = "ExtinguishFire",
        .preconditions = {{Flag::FireNearby, true}, {Flag::HasWater, true}},
        .effects = {{Flag::FireNearby, false}, {Flag::HasWater, false}},
        .cost = 1
    };
}

#endif
