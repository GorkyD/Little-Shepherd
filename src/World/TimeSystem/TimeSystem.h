#ifndef WILDLIFESIM_TIMESYSTEM_H
#define WILDLIFESIM_TIMESYSTEM_H

#include <memory>
#include <utility>
#include "EventBus/EventBus.h"
#include "World/World.h"

class TimeSystem
{
    std::shared_ptr<World> world;
    std::shared_ptr<EventBus> eventBus;

    float nightDuration = 18.0f;
    float dayDuration = 24.0f;
    float elapsed = 0.0f;

    void TimeOfDayChange() const;
public:
    TimeSystem(std::shared_ptr<World> world, std::shared_ptr<EventBus> eventBus) : world(std::move(world)), eventBus(std::move(eventBus)){}
    void Start() const;
    void Update();
    float GetCurrentDayTimeProgress() const;
};


#endif
