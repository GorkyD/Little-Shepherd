#ifndef WILDLIFESIM_SLEEP_H
#define WILDLIFESIM_SLEEP_H

#include "Goap/Action.h"

inline Action Sleep()
{
    return Action
    {
        .name = "Sleep",
        .preconditions = {{Flag::IsDayTime, false}, {Flag::IsInDanger, false}},
        .effects = {{Flag::HasWorked, false},{Flag::HasSlept, true}},
        .requiredLocation = Location::Barn,
        .cost = 1
    };
}

#endif
