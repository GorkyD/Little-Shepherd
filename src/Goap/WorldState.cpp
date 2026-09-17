#include "WorldState.h"

bool WorldState::GetFlag(Flag flag) const
{
    switch (flag)
    {
        case Flag::IsDayTime: return isDayTime;
        case Flag::HasWorked: return hasWorked;
        case Flag::HasSlept:  return hasSlept;
        case Flag::IsInDanger: return isInDanger;
        case Flag::IsDragged: return isDragged;
        case Flag::HasWeapon: return hasWeapon;
    }
    return false;
}

void WorldState::SetFlag(Flag flag, bool value)
{
    switch (flag)
    {
        case Flag::IsDayTime: isDayTime = value; break;
        case Flag::HasWorked: hasWorked = value; break;
        case Flag::HasSlept:  hasSlept = value; break;
        case Flag::IsInDanger: isInDanger = value; break;
        case Flag::IsDragged: isDragged = value; break;
        case Flag::HasWeapon: hasWeapon = value; break;
    }
}
