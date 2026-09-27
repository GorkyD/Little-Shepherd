#include "WolfStateMachineController.h"
#include "FSM/States/Wolf/IdleState.h"
#include "FSM/States/Wolf/SearchingState.h"
#include "FSM/States/Wolf/ChaseState.h"
#include "FSM/States/Wolf/AttackState.h"
#include "FSM/States/Wolf/DeathState.h"

void WolfStateMachineController::Initialize()
{
    StateMachineController::Initialize();
    ChangeState(std::make_unique<IdleState>(wolf));
}

void WolfStateMachineController::SetTransitionTable()
{
    AddTransition(StateId::Idle,
    {
        .targetId = StateId::Death,
        .condition = [this]() { return worldState.IsDead; },
        .createState = [this]() { return std::make_unique<DeathState>(wolf); }
    })
    .AddTransition(StateId::Idle,
    {
        .targetId = StateId::Searching,
        .condition = [this]() { return worldState.IsPlacedOnMap; },
        .createState = [this]() { return std::make_unique<SearchingState>(wolf); }
    })
    .AddTransition(StateId::Searching,
    {
        .targetId = StateId::Death,
        .condition = [this]() { return worldState.IsDead; },
        .createState = [this]() { return std::make_unique<DeathState>(wolf); }
    })
    .AddTransition(StateId::Searching,
    {
        .targetId = StateId::Chase,
        .condition = [this]() { return worldState.IsEnemyOnSight; },
        .createState = [this]() { return std::make_unique<ChaseState>(wolf); }
    })
    .AddTransition(StateId::Chase,
    {
        .targetId = StateId::Death,
        .condition = [this]() { return worldState.IsDead; },
        .createState = [this]() { return std::make_unique<DeathState>(wolf); }
    })
    .AddTransition(StateId::Chase,
    {
        .targetId = StateId::Attack,
        .condition = [this]() { return worldState.IsInAttackRange; },
        .createState = [this]() { return std::make_unique<AttackState>(wolf); }
    })
    .AddTransition(StateId::Chase,
    {
        .targetId = StateId::Searching,
        .condition = [this]() { return worldState.IsTargetLost; },
        .createState = [this]() { return std::make_unique<SearchingState>(wolf); }
    })
    .AddTransition(StateId::Attack,
    {
        .targetId = StateId::Death,
        .condition = [this]() { return worldState.IsDead; },
        .createState = [this]() { return std::make_unique<DeathState>(wolf); }
    })
    .AddTransition(StateId::Attack,
    {
        .targetId = StateId::Searching,
        .condition = [this]() { return worldState.IsTargetLost; },
        .createState = [this]() { return std::make_unique<SearchingState>(wolf); }
    })
    .AddTransition(StateId::Attack,
    {
        .targetId = StateId::Chase,
        .condition = [this]() { return !worldState.IsInAttackRange; },
        .createState = [this]() { return std::make_unique<ChaseState>(wolf); }
    });
}
