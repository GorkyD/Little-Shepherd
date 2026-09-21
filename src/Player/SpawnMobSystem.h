#ifndef WILDLIFESIM_SPAWNMOBSYSTEM_H
#define WILDLIFESIM_SPAWNMOBSYSTEM_H

#include "BaseInteractSystem.h"

class SpawnMobSystem : public BaseInteractSystem
{
public:
    SpawnMobSystem() = default;
    void Start() override;
    void Update() override;
    void Exit() override;
};


#endif
