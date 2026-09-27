#ifndef WILDLIFESIM_WORLDSTATE_H
#define WILDLIFESIM_WORLDSTATE_H

#include <functional>

enum class Flag
{
    IsDayTime,
    HasWorked,
    HasSlept,
    IsInDanger,
    IsDragged,
    HasWeapon,
    FireNearby,
    HasWater
};

enum class Location
{
    None,
    Barn,
    Field,
    Forest,
    Water
};

struct NpcBehaviour
{
    int courage = 0;
};

struct WorldState
{
    bool isDayTime = false;
    bool hasWorked = false;
    bool hasSlept = false;
    bool isInDanger = false;
    bool isDragged = false;
    bool hasWeapon = false;
    bool fireNearby = false;
    bool hasWater = false;

    Location location = Location::None;

    bool operator==(const WorldState&) const = default;

    bool GetFlag(Flag flag) const;
    void SetFlag(Flag flag, bool value);
};

template<>
struct std::hash<WorldState>
{
    size_t operator()(const WorldState& state) const noexcept
    {
        size_t h = std::hash<int>()(static_cast<int>(state.location));
        h = h * 31 + std::hash<bool>()(state.isDayTime);
        h = h * 31 + std::hash<bool>()(state.hasWorked);
        h = h * 31 + std::hash<bool>()(state.hasSlept);
        h = h * 31 + std::hash<bool>()(state.isInDanger);
        h = h * 31 + std::hash<bool>()(state.isDragged);
        h = h * 31 + std::hash<bool>()(state.hasWeapon);
        h = h * 31 + std::hash<bool>()(state.fireNearby);
        h = h * 31 + std::hash<bool>()(state.hasWater);
        return h;
    }
};

#endif
