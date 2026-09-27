#ifndef EXAMPLES_STATEMACHINECONTROLLER_H
#define EXAMPLES_STATEMACHINECONTROLLER_H

#include <memory>
#include <unordered_map>
#include "../../StateMachine.h"
#include "../../Conditions/Transition.h"

class StateMachineController
{
    std::unordered_map<StateId, std::vector<Transition>> transitionTable;
    std::unique_ptr<StateMachine> stateMachine;
public:
    virtual ~StateMachineController() = default;
    virtual StateMachineController& AddTransition(StateId from, Transition transition);
    
    virtual void Initialize();
    virtual void SetTransitionTable() = 0;
    virtual void Update();

protected:
    void ChangeState(std::unique_ptr<State> state) const { stateMachine->ChangeState(std::move(state)); }
};

#endif
