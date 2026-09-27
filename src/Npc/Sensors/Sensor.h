#ifndef WILDLIFESIM_SENSOR_H
#define WILDLIFESIM_SENSOR_H

#include <memory>
#include "Astar/Astar.h"
#include "Astar/Domains/GridDomain.h"
#include "World/GridPos.h"

class BaseNpc;
class World;

class Sensor
{
public:
    virtual ~Sensor() = default;
    virtual void Scan(BaseNpc* npc, const std::shared_ptr<World>& world, const std::shared_ptr<Astar<GridPos, GridDomain>>& astar) = 0;
};

#endif
