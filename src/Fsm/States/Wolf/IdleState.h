#ifndef EXAMPLES_IDLESTATE_H
#define EXAMPLES_IDLESTATE_H

#include "WolfState.h"
#include "Enemies/Wolf.h"

class IdleState : public WolfState
{
    Wolf* wolf;
public:
    explicit IdleState(Wolf* wolf) : wolf(wolf) {}
    void Update() override;
    StateId GetId() const override { return StateId::Idle; }
};

#endif
