#ifndef WILDLIFESIM_VISUALSENSOR_H
#define WILDLIFESIM_VISUALSENSOR_H

#include "Sensor.h"

class VisualSensor : public Sensor
{
    int radius;
    float halfAngleCos;

public:
    explicit VisualSensor(int radius = 5, float coneAngleDegrees = 120.0f);

    void Scan(BaseNpc* npc, const std::shared_ptr<World>& world, const std::shared_ptr<Astar<GridPos, GridDomain>>& astar) override;
};

#endif
