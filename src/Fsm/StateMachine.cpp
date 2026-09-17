#include "StateMachine.h"

void StateMachine::ChangeState(std::unique_ptr<State> newState)
{
    if (currentState) 
        currentState->Exit();
        
    currentState = std::move(newState);
    currentState->Enter();
}

void StateMachine::Update() const
{
    if (currentState) 
        currentState->Update();
}
