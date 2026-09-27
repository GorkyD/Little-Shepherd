#ifndef WILDLIFESIM_ATTACKSTATE_H
#define WILDLIFESIM_ATTACKSTATE_H

#include "WolfState.h"
#include "Enemies/Wolf.h"

class AttackState : public WolfState
{
    Wolf* wolf;
public:
    explicit AttackState(Wolf* wolf) : wolf(wolf) {}
    void Update() override;
    StateId GetId() const override { return StateId::Attack; }
};

#endif
