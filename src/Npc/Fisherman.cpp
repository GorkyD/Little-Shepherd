#include "Fisherman.h"
#include "raymath.h"

std::string Fisherman::GetWorkClipFor(const Action* action)
{
    if (action->name == "MoveToWater")          return "WalkHoldingTool_Fishingpole";
    if (action->name == "MoveToBarn")           return "WalkHoldingTool_Fishingpole";
    if (action->name == "Fish")                 return "Fish_Fishingpole";
    if (action->name == "Sleep")                return "Sit";
    if (action->name == "RunAwayFromDanger")    return "Run";
    return "Idle";
}

float Fisherman::CalculateTileOffsetByName(std::string actionName)
{
    if (actionName == "Fish")
        return 20.0f;
    
    return 0.0f;
}

void Fisherman::CalculateLastDirection(std::string actionName)
{
    float offsetAmount = CalculateTileOffsetByName(actionName);
    const Vector2 dir = Vector2Normalize(lastMoveDirection);
    targetWorkOffset = Vector2Scale(Vector2Normalize(dir), offsetAmount);
}

void Fisherman::PlayClip(const std::string& clip)
{
    const bool loop = clip != "Sit" && clip != "Fish_Fishingpole";
    animator.SetClip(clip, loop);
}

void Fisherman::WaitNodeUpdate(std::string actionName)
{
}