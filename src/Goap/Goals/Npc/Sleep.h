#ifndef WILDLIFESIM_SLEEPGOAL_H
#define WILDLIFESIM_SLEEPGOAL_H

#include "Goap/Goal.h"

inline Goal SleepGoal()
{
    return Goal
    {
        .priority = 2,
        .activationCondition = {{Flag::IsDayTime, false}, {Flag::IsInDanger, false}, {Flag::FireNearby, false}},
        .targetConditions = {{Flag::HasSlept, true}}
    };
}

#endif
