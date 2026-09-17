#ifndef EXAMPLES_PATROLSTATE_H
#define EXAMPLES_PATROLSTATE_H

#include "WolfState.h"
#include "../State.h"

class SearchingState : public WolfState
{
    void Enter() override;
    void Exit() override;
    void Update() override;
    StateId GetId() const override;
};

#endif
