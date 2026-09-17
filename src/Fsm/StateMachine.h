#ifndef EXAMPLES_STATEMACHINE_H
#define EXAMPLES_STATEMACHINE_H

#include <memory>
#include "States/State.h"

class StateMachine
{
    std::unique_ptr<State> currentState;
public:
    void ChangeState(std::unique_ptr<State> newState);
    void Update() const;
    StateId GetCurrentStateId() const { return currentState->GetId(); }
};

#endif