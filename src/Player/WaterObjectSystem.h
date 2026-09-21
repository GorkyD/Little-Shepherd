#ifndef WILDLIFESIM_WATEROBJECTSYSTEM_H
#define WILDLIFESIM_WATEROBJECTSYSTEM_H

#include "BaseInteractSystem.h"

class WaterObjectSystem : public BaseInteractSystem
{
public:
    WaterObjectSystem() = default;
    void Start() override;
    void Update() override;
    void Exit() override;
};


#endif
