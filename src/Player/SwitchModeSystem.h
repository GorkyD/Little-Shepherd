#ifndef WILDLIFESIM_SWITCHMODESYSTEM_H
#define WILDLIFESIM_SWITCHMODESYSTEM_H

#include <memory>
#include <utility>

#include "InteractModeState.h"
#include "EventBus/EventBus.h"
#include "Input/InputSystem.h"


class SwitchModeSystem
{
    std::shared_ptr<InteractModeState> interactModeState;
    std::shared_ptr<InputSystem> inputSystem;
    std::shared_ptr<EventBus> eventBus;

public:
    SwitchModeSystem(std::shared_ptr<InteractModeState> interactModeState, std::shared_ptr<InputSystem> inputSystem, std::shared_ptr<EventBus> eventBus) : interactModeState(std::move(interactModeState)), inputSystem(std::move(inputSystem)), eventBus(std::move(eventBus)) {}
    void Update() const;
};


#endif
