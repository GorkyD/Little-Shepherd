#ifndef WILDLIFESIM_INTERACTMODESTATE_H
#define WILDLIFESIM_INTERACTMODESTATE_H

#include "InteractType.h"

class InteractModeState
{
    InteractType currentType = InteractType::None;

public:
    InteractType GetCurrentType() const { return currentType; }
    void SetCurrentType(InteractType newType) { currentType = newType; }
};

#endif
