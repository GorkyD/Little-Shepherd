#ifndef WILDLIFESIM_EXTENSION_H
#define WILDLIFESIM_EXTENSION_H

#include "Goap/WorldState.h"
#include "Player/InteractType.h"
#include "World/Grid.h"
#include "World/ZoneType.h"

namespace Extension
{
    static ZoneType ToZoneType(Location location)
    {
        switch (location)
        {
        case Location::Barn:   return ZoneType::Barn;
        case Location::Field:  return ZoneType::Field;
        case Location::Forest: return ZoneType::Forest;
        case Location::Water:  return ZoneType::Water;
        default:               return ZoneType::Empty;
        }
    }

    static Location ToLocation(ZoneType zone)
    {
        switch (zone)
        {
        case ZoneType::Barn:   return Location::Barn;
        case ZoneType::Field:  return Location::Field;
        case ZoneType::Forest: return Location::Forest;
        case ZoneType::Water:  return Location::Water;
        default:               return Location::None;
        }
    } 
    
    static Vector2 ToWorld(GridPos pos)
    {
        return Grid::ToScreen(pos);
    }

    static  const char* GetTextForEnum(InteractType currentType)
    {
        switch(currentType)
        {
            case InteractType::Drag:
                return "Drag Mode";
            case InteractType::Fire:
                return "Fire Mode";
            case InteractType::Water:
                return "Water Mode";
            case InteractType::Spawn:
                return "Spawn Mode";
            default:
                return "*Unknown Interaction Type*";
        }
    }
}

#endif
