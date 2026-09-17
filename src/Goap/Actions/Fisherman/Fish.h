#ifndef WILDLIFESIM_FISH_H
#define WILDLIFESIM_FISH_H

#include "Goap/Action.h"

inline Action Fish()
{
    return Action
    {
        .name = "Fish",
        .preconditions = {{Flag::IsDayTime, true}, {Flag::IsInDanger, false}},
        .effects = {{Flag::HasWorked, true}},
        .requiredLocation = Location::Water,
        .cost = 1
    };
}

#endif
