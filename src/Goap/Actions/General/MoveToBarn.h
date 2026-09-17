#ifndef WILDLIFESIM_MOVETOBARN_H
#define WILDLIFESIM_MOVETOBARN_H

#include "Goap/Action.h"

inline Action MoveToBarn()
{
    return Action
    {
        .name = "MoveToBarn",
        .preconditions = {{Flag::IsDayTime, false}, {Flag::IsInDanger, false}},
        .resultingLocation = Location::Barn,
        .cost = 1
    };
}

#endif
