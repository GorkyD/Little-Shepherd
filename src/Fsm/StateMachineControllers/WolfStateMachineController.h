#ifndef WILDLIFESIM_WOLFSTATEMACHINECONTROLLER_H
#define WILDLIFESIM_WOLFSTATEMACHINECONTROLLER_H

#include "Base/StateMachineController.h"

class Wolf;

struct WolfWorldState
{
    bool IsPlacedOnMap = false;
    bool IsEnemyOnSight = false;
    bool IsInAttackRange = false;
    bool IsTargetLost = false;
    bool IsDead = false;
};

class WolfStateMachineController : public StateMachineController
{
    Wolf* wolf;
    WolfWorldState worldState;
public:
    explicit WolfStateMachineController(Wolf* wolf) : wolf(wolf) {}

    void Initialize() override;
    void SetTransitionTable() override;

    void SetPlacedOnMap(bool value) { worldState.IsPlacedOnMap = value; }
    void SetEnemyOnSight(bool value) { worldState.IsEnemyOnSight = value; }
    void SetInAttackRange(bool value) { worldState.IsInAttackRange = value; }
    void SetTargetLost(bool value) { worldState.IsTargetLost = value; }
    void SetIsDead(bool value) { worldState.IsDead = value; }
};

#endif
