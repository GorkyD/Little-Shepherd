#ifndef WILDLIFESIM_SEARCHDANGER_H
#define WILDLIFESIM_SEARCHDANGER_H

#include "Goap/Action.h"

inline Action SearchDanger()
{
    return Action
    {
        .name = "SearchDanger",
        .preconditions = {{Flag::IsInDanger, true}, {Flag::IsDragged, false}, {Flag::HasWeapon, true}},
        .effects = {{Flag::IsInDanger, false}},
        .cost = 3
    };
}

#endif
