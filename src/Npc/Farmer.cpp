#include "Farmer.h"
#include "raymath.h"

std::string Farmer::GetWorkClipFor(const Action* action)
{
    if (action->name == "MoveToField")       return "WalkHoldingTool_Showel";
    if (action->name == "MoveToBarn")        return "WalkHoldingTool_Showel";
    if (action->name == "WorkOnField")       return "Dig_Showel";
    if (action->name == "Sleep")             return "Sit";
    if (action->name == "RunAwayFromDanger") return "Run";
    if (action->name == "RunAwayFromFire")   return "Run";
    if (action->name == "SearchDanger")      return "WalkHoldingTool_Sword";
    if (action->name == "GetWater")          return "Walk";
    if (action->name == "ExtinguishFire")    return "WalkHoldingTool_WaterCan";
    return "Idle";
}

float Farmer::CalculateTileOffsetByName(std::string actionName)
{
    if (actionName == "WorkOnField")
        return -20.0f;
    
    return 0.0f;
}

void Farmer::CalculateLastDirection(std::string actionName)
{
    float offsetAmount = CalculateTileOffsetByName(actionName);
    const Vector2 dir = Vector2Normalize(lastMoveDirection);
    targetWorkOffset = Vector2Scale(Vector2Normalize(dir), offsetAmount);
}

void Farmer::PlayClip(const std::string& clip)
{
    const bool loop = clip != "Sit";
    animator.SetClip(clip, loop);
}

void Farmer::WaitNodeUpdate(std::string actionName)
{
    if (actionName == "WorkOnField")
        world->GetTile(position.row, position.col).digHoleTimer = 0.5f;
}
