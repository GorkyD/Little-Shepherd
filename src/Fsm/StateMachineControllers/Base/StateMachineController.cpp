#include "StateMachineController.h"

void StateMachineController::Initialize()
{
    stateMachine = std::make_unique<StateMachine>();
    SetTransitionTable();
}

StateMachineController& StateMachineController::AddTransition(StateId from, Transition transition)
{
    transitionTable[from].push_back(std::move(transition));
    return *this;
}

void StateMachineController::Update()
{
    stateMachine->Update();

    StateId currentId = stateMachine->GetCurrentStateId();
    
    for (auto& transition : transitionTable[currentId])
    {
        if (transition.condition())
        {
            stateMachine->ChangeState(transition.createState());
            break;
        }
    }
}