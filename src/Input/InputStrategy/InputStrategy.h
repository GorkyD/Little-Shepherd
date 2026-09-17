#ifndef WILDLIFESIM_INPUTSTRATEGY_H
#define WILDLIFESIM_INPUTSTRATEGY_H

class InputStrategy
{
public:
    virtual Vector2 GetPointerScreenPosition() = 0;
    virtual bool IsPointerUnPressed(PointerInputAction action) = 0;
    virtual bool IsPointerPressed(PointerInputAction action) = 0;
    virtual bool IsPointerDown(PointerInputAction action) = 0;
    virtual bool IsActionPressed(InputAction action) = 0;
    virtual bool IsActionDown(InputAction action) = 0;
    virtual ~InputStrategy() = default;
};

#endif
