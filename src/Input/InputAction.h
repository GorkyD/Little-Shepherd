#ifndef WILDLIFESIM_INPUTACTION_H
#define WILDLIFESIM_INPUTACTION_H

enum class InputAction : int8_t
{
    MoveLeft, MoveRight, MoveForward, MoveBack, FirstStrategySelect, SecondStrategySelect, ThirdStrategySelect, FourthStrategySelect
};

enum class PointerInputAction : int8_t
{
    BasePointerClick, AdditionalPointerClick
};

#endif
