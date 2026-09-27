#ifndef EXAMPLES_PATROLSTATE_H
#define EXAMPLES_PATROLSTATE_H

#include "WolfState.h"
#include "Enemies/Wolf.h"

class SearchingState : public WolfState
{
    Wolf* wolf;
public:
    explicit SearchingState(Wolf* wolf) : wolf(wolf) {}
    void Update() override;
    StateId GetId() const override { return StateId::Searching; }
};

#endif
