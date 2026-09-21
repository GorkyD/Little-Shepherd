#include "SwitchModeSystem.h"

void SwitchModeSystem::Update() const
{
    if (inputSystem->IsActionPressed(InputAction::FirstStrategySelect))
    {
        interactModeState->SetCurrentType(InteractType::Drag);
        eventBus->Publish(EventType::OnPlayerInteractModeChange);
    }
    
    if (inputSystem->IsActionPressed(InputAction::SecondStrategySelect))
    {
        interactModeState->SetCurrentType(InteractType::Fire);
        eventBus->Publish(EventType::OnPlayerInteractModeChange);
    }
    
    if (inputSystem->IsActionPressed(InputAction::ThirdStrategySelect))
    {
        interactModeState->SetCurrentType(InteractType::Water);
        eventBus->Publish(EventType::OnPlayerInteractModeChange);
    }
    
    if (inputSystem->IsActionPressed(InputAction::FourthStrategySelect))
    {
        interactModeState->SetCurrentType(InteractType::Spawn);
        eventBus->Publish(EventType::OnPlayerInteractModeChange);
    }
}
