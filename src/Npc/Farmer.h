#ifndef WILDLIFESIM_FARMER_H
#define WILDLIFESIM_FARMER_H

#include "BaseNpc.h"

class Farmer : public BaseNpc, public std::enable_shared_from_this<Farmer>
{
public:
    Farmer(GridPos startPosition, std::string name, std::string archetype = "Farmer") : BaseNpc(startPosition, name) { ApplyBehaviourProfile(archetype); }
    
    std::string GetWorkClipFor(const Action* action) override;
    float CalculateTileOffsetByName(std::string name) override;
    
    void CalculateLastDirection(std::string name) override;
    void PlayClip(const std::string& clip) override;
    void WaitNodeUpdate(std::string actionName) override;
};
#endif
