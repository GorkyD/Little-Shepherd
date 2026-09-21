#ifndef WILDLIFESIM_FIREOBJECTSYSTEM_H
#define WILDLIFESIM_FIREOBJECTSYSTEM_H

#include "BaseInteractSystem.h"

class FireObjectSystem : public BaseInteractSystem
{
public:
    FireObjectSystem() = default;
    void Start() override;
    void Update() override;
    void Exit() override;
};


#endif
