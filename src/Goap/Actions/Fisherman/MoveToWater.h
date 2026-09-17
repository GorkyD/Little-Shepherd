#ifndef WILDLIFESIM_MOVETOWATER_H
#define WILDLIFESIM_MOVETOWATER_H

#include "Goap/Action.h"

inline Action MoveToWater()
{
    return Action
    {
        .name = "MoveToWater",
        .preconditions = {{Flag::IsDayTime, true}, {Flag::IsInDanger, false}},
        .resultingLocation = Location::Water,
        .cost = 1
    };
}

#endif
