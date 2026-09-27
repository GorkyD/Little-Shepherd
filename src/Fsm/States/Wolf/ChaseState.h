#ifndef WILDLIFESIM_CHASESTATE_H
#define WILDLIFESIM_CHASESTATE_H

#include "WolfState.h"
#include "Enemies/Wolf.h"
#include "World/GridPos.h"

class ChaseState : public WolfState
{
    Wolf* wolf;
    GridPos pathTarget{};
    bool hasPathTarget = false;
public:
    explicit ChaseState(Wolf* wolf) : wolf(wolf) {}
    void Update() override;
    StateId GetId() const override { return StateId::Chase; }
};

#endif
