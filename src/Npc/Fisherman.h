#ifndef WILDLIFESIM_FISHERMAN_H
#define WILDLIFESIM_FISHERMAN_H

#include "BaseNpc.h"

class Fisherman : public BaseNpc, public std::enable_shared_from_this<Fisherman>
{
public:
    Fisherman(GridPos startPosition, std::string name) : BaseNpc(startPosition, name) {}

    std::string GetWorkClipFor(const Action* action) override;
    float CalculateTileOffsetByName(std::string name) override;
    
    void CalculateLastDirection(std::string name) override;
    void PlayClip(const std::string& clip) override;
    void WaitNodeUpdate(std::string actionName) override;
};
#endif
