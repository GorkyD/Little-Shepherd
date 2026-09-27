#ifndef WILDLIFESIM_EXTINGUISH_H
#define WILDLIFESIM_EXTINGUISH_H

#include "Goap/Goal.h"

inline Goal ExtinguishGoal()
{
    return Goal
    {
        .priority = 3,
        .activationCondition = {{Flag::FireNearby, true}},
        .targetConditions = {{Flag::FireNearby, false}}
    };
}

#endif
