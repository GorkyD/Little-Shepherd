#include "InputSystem.h"

InputSystem::InputSystem(std::unique_ptr<InputStrategy> inputStrategy)
{
    this->inputStrategy = std::move(inputStrategy);
}

Vector2 InputSystem::GetPointerScreenPosition() const
{
    return inputStrategy->GetPointerScreenPosition();
}

bool InputSystem::IsPointerActionUnPressed(PointerInputAction action) const
{
    return inputStrategy->IsPointerUnPressed(action);
}

bool InputSystem::IsPointerActionPressed(PointerInputAction action) const
{
    return inputStrategy->IsPointerPressed(action);
}

bool InputSystem::IsPointerActionDown(PointerInputAction action) const
{
    return inputStrategy->IsPointerDown(action);
}

bool InputSystem::IsActionPressed(InputAction action) const
{
    return inputStrategy->IsActionPressed(action);
}


bool InputSystem::IsActionDown(InputAction action) const
{
    return inputStrategy->IsActionDown(action);
}
