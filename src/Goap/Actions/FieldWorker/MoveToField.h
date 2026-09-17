#ifndef WILDLIFESIM_MOVETOFIELD_H
#define WILDLIFESIM_MOVETOFIELD_H

#include "Goap/Action.h"

inline Action MoveToField()
{
    return Action
    {
        .name = "MoveToField",
        .preconditions = {{Flag::IsDayTime, true}, {Flag::IsInDanger, false}},
        .effects = {{Flag::HasSlept, false}},
        .resultingLocation = Location::Field,
        .cost = 1
    };
}

#endif
