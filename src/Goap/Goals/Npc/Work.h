#ifndef WILDLIFESIM_WORKGOAL_H
#define WILDLIFESIM_WORKGOAL_H

#include "Goap/Goal.h"

inline Goal WorkGoal()
{
    return Goal
    {
        .priority = 1,
        .activationCondition = {{Flag::IsDayTime, true}, {Flag::IsInDanger, false}, {Flag::FireNearby, false}},
        .targetConditions = {{Flag::HasWorked, true}}
    };
}

#endif
