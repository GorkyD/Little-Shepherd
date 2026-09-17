#ifndef WILDLIFESIM_MOVETOFOREST_H
#define WILDLIFESIM_MOVETOFOREST_H

#include "Goap/Action.h"

inline Action MoveToForest()
{
    return Action
    {
        .name = "MoveToForest",
        .preconditions = {{Flag::IsDayTime, true}, {Flag::IsInDanger, false}},
        .effects = {{Flag::HasSlept, false}},
        .resultingLocation = Location::Forest,
        .cost = 1
    };
}

#endif
