#ifndef WILDLIFESIM_WAITUNTILPLACED_H
#define WILDLIFESIM_WAITUNTILPLACED_H

#include "Goap/Action.h"
#include "Goap/WorldState.h"

inline Action WaitUntilPlaced()
{
    return Action
    {
        .name = "WaitUntilPlaced",
        .preconditions = {{Flag::IsInDanger, true}, {Flag::IsDragged, true}},
        .effects = {{Flag::IsDragged, false}},
        .cost = 1
    };
}

#endif
