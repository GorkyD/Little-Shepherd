#ifndef WILDLIFESIM_RUNAWAYFROMFIRE_H
#define WILDLIFESIM_RUNAWAYFROMFIRE_H

#include "Goap/Action.h"

inline Action RunAwayFromFire()
{
    return Action
    {
        .name = "RunAwayFromFire",
        .preconditions = {{Flag::FireNearby, true}},
        .effects = {{Flag::FireNearby, false}},
        .cost = 3
    };
}

#endif
