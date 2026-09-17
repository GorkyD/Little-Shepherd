#include "WolfStateMachineController.h"
#include "FSM/States/Wolf/IdleState.h"
#include "FSM/States/Wolf/SearchingState.h"

void WolfStateMachineController::SetTransitionTable()
{
    AddTransition(StateId::Idle,
    {
        .targetId = StateId::Searching,
        .condition = [this]() { return worldState.IsPlacedOnMap;},
        .createState = []() { return std::make_unique<SearchingState>(); }})
    .AddTransition(StateId::Searching,    
{
        .targetId = StateId::Idle,
        .condition = [this]() { return worldState.IsPlacedOnMap && !worldState.IsEnemyOnSight;},
        .createState = []() { return std::make_unique<IdleState>(); }});
}
