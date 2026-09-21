#ifndef WILDLIFESIM_HUDSYSTEM_H
#define WILDLIFESIM_HUDSYSTEM_H

#include <utility>
#include "Player/PlayerInteractSystem.h"

class HudSystem
{
    const int ModeHintOffset = 350;
    const int CurrentModeOffset = 150;
    
    std::shared_ptr<InteractModeState> interactModeState; 
public:
    HudSystem(std::shared_ptr<InteractModeState> interactModeState) : interactModeState(std::move(interactModeState)) {}
    void Update() const;
};


#endif
