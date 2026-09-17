#ifndef WILDLIFESIM_WOLFSTATEMACHINECONTROLLER_H
#define WILDLIFESIM_WOLFSTATEMACHINECONTROLLER_H

#include "Base/StateMachineController.h"

struct WolfWorldState
{
    bool IsPlacedOnMap = false;
    bool IsEnemyOnSight = false;
};

class WolfStateMachineController : public StateMachineController
{
    WolfWorldState worldState;
public:
    void SetTransitionTable() override;
};

#endif
