#ifndef WILDLIFESIM_RUNAWAYFROMDANGER_H
#define WILDLIFESIM_RUNAWAYFROMDANGER_H
#include "Goap/Action.h"

inline Action RunAwayFromDanger()
{
    return Action
    {
        .name = "RunAwayFromDanger",
        .preconditions = {{Flag::IsInDanger, true}, {Flag::IsDragged, false}},
        .effects = {{Flag::IsInDanger, false}},
        .cost = 3
    };
}


#endif
