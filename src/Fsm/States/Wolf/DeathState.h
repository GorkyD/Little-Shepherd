#ifndef WILDLIFESIM_DEATHSTATE_H
#define WILDLIFESIM_DEATHSTATE_H

#include "WolfState.h"
#include "Enemies/Wolf.h"

class DeathState : public WolfState
{
    Wolf* wolf;
public:
    explicit DeathState(Wolf* wolf) : wolf(wolf) {}
    void Update() override;
    StateId GetId() const override { return StateId::Death; }
};

#endif
