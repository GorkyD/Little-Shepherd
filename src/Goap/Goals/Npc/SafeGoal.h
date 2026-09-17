#ifndef WILDLIFESIM_SAFEGOAL_H
#define WILDLIFESIM_SAFEGOAL_H

#include "Goap/Goal.h"

inline Goal SafeGoal()
{
    return Goal
    {
        .priority = 5,
        .activationCondition = {{Flag::IsInDanger, true}},
        .targetConditions = {{Flag::IsInDanger, false}}
    };
}

#endif
