#ifndef WILDLIFESIM_PCINPUTSTRATEGY_H
#define WILDLIFESIM_PCINPUTSTRATEGY_H

#include <cassert>
#include "InputStrategy.h"
#include "raylib.h"
#include "Input/InputAction.h"

class PcInputStrategy : public InputStrategy
{
    std::unordered_map<InputAction, int> inputActionMap = 
    {
        {InputAction::MoveBack, KEY_S},
        {InputAction::MoveRight, KEY_D},
        {InputAction::MoveLeft, KEY_A},
        {InputAction::MoveForward, KEY_W},
        {InputAction::FirstStrategySelect, KEY_ONE},
        {InputAction::SecondStrategySelect, KEY_TWO},
        {InputAction::ThirdStrategySelect, KEY_THREE},
        {InputAction::FourthStrategySelect, KEY_FOUR}
    };
    
    std::unordered_map<PointerInputAction, int> pointerInputActionMap = 
    {
        {PointerInputAction::BasePointerClick, MOUSE_LEFT_BUTTON},
        {PointerInputAction::AdditionalPointerClick, MOUSE_RIGHT_BUTTON}
    };
    
public:
    Vector2 GetPointerScreenPosition() override
    {
        return GetMousePosition();
    }
    
    bool IsPointerPressed(PointerInputAction action) override
    {
        return IsMouseButtonPressed(pointerInputActionMap[action]);
    }
    
    bool IsPointerUnPressed(PointerInputAction action) override
    {
        return IsMouseButtonUp(pointerInputActionMap[action]);
    }

    bool IsPointerDown(PointerInputAction action) override
    {
        return IsMouseButtonDown(pointerInputActionMap[action]);
    }

    bool IsActionPressed(InputAction action) override
    {
        return IsKeyPressed(inputActionMap[action]);
    }
    
    bool IsActionDown(InputAction action) override
    {
        return IsKeyDown(inputActionMap[action]);
    };
};

#endif
