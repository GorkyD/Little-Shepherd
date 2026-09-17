#ifndef WILDLIFESIM_INPUTSYSTEM_H
#define WILDLIFESIM_INPUTSYSTEM_H

#include <memory>
#include "InputAction.h"
#include "raylib.h"
#include "InputStrategy/InputStrategy.h"

class InputSystem
{
    std::unique_ptr<InputStrategy> inputStrategy;
public:
    InputSystem(std::unique_ptr<InputStrategy> inputStrategy);
    
    Vector2 GetPointerScreenPosition() const;
    bool IsPointerActionUnPressed(PointerInputAction action) const;
    bool IsPointerActionPressed(PointerInputAction action) const;
    bool IsPointerActionDown(PointerInputAction action) const;
    bool IsActionDown(InputAction action) const;
};

#endif
