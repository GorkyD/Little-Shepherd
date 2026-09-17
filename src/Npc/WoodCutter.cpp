#include "WoodCutter.h"
#include "raymath.h"

std::string WoodCutter::GetWorkClipFor(const Action* action)
{
    if (action->name == "MoveToForest")         return "WalkHoldingTool_Axe";
    if (action->name == "MoveToBarn")           return "WalkHoldingTool_Axe";
    if (action->name == "ChopWood")             return "Swing_Axe";
    if (action->name == "Sleep")                return "Sit";
    if (action->name == "RunAwayFromDanger")    return "Run";
    if (action->name == "SearchDanger")         return "WalkHoldingTool_Sword";
    return "Idle";
}

float WoodCutter::CalculateTileOffsetByName(std::string actionName)
{
    if (actionName == "ChopWood")
        return -20.0f;
    
    return 0.0f;
}

void WoodCutter::Update(const std::shared_ptr<Astar<GridPos, GridDomain>>& astar, const std::shared_ptr<RenderSystem>& renderer)
{
    BaseNpc::Update(astar, renderer);
    
    if (animator.CurrentClip() == "Swing_Axe" && animator.ConsumeJustLooped())
        world->GetTile(position.row, position.col).chopFlash = 1.0f;
}

void WoodCutter::CalculateLastDirection(std::string actionName)
{
    float offsetAmount = CalculateTileOffsetByName(actionName);
    const Vector2 dir = Vector2Normalize(lastMoveDirection);
    targetWorkOffset = Vector2Scale(Vector2Normalize(dir), offsetAmount);
}

void WoodCutter::PlayClip(const std::string& clip)
{
    const bool loop = clip != "Sit";
    animator.SetClip(clip, loop);
}

void WoodCutter::WaitNodeUpdate(std::string actionName)
{
}