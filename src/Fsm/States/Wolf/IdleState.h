#ifndef EXAMPLES_IDLESTATE_H
#define EXAMPLES_IDLESTATE_H

#include "WolfState.h"
#include "../State.h"

class IdleState : public WolfState
{
    void Enter() override;
    void Exit() override;
    void Update() override;
    StateId GetId() const override;
};

#endif
