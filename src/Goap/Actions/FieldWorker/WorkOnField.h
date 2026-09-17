#ifndef WILDLIFESIM_WORK_H
#define WILDLIFESIM_WORK_H

#include "Goap/Action.h"

inline Action WorkOnField()
{
    return Action
    {
        .name = "WorkOnField",
        .preconditions = {{Flag::IsDayTime, true}, {Flag::IsInDanger, false}},
        .effects = {{Flag::HasWorked, true}},
        .requiredLocation = Location::Field,
        .cost = 1
    };
}

#endif
