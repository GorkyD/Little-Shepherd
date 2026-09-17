#ifndef WILDLIFESIM_WOODCUTTER_H
#define WILDLIFESIM_WOODCUTTER_H

#include <random>

#include "BaseNpc.h"

class WoodCutter : public BaseNpc, public std::enable_shared_from_this<WoodCutter>
{
public:
    WoodCutter(GridPos startPosition, std::string name) : BaseNpc(startPosition, name) {currentState.hasWeapon = true; std::mt19937 rng(std::random_device{}()); npcBehaviour.courage = std::uniform_int_distribution(0, 3)(rng);}

    std::string GetWorkClipFor(const Action* action) override;
    float CalculateTileOffsetByName(std::string name) override;
    
    void Update(const std::shared_ptr<Astar<GridPos, GridDomain>>& astar, const std::shared_ptr<RenderSystem>& renderer) override;
    void CalculateLastDirection(std::string name) override;
    void PlayClip(const std::string& clip) override;
    void WaitNodeUpdate(std::string actionName) override;
};
#endif