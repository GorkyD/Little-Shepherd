#ifndef WILDLIFESIM_PLAYERINTERACTSYSTEM_H
#define WILDLIFESIM_PLAYERINTERACTSYSTEM_H

#include <memory>
#include <utility>
#include "BaseInteractSystem.h"
#include "InteractModeState.h"
#include "InteractType.h"
#include "Astar/Astar.h"
#include "Astar/Domains/GridDomain.h"
#include "Camera/CameraController.h"
#include "Input/InputSystem.h"
#include "NPC/BaseNpc.h"

class Wolf;

class PlayerInteractSystem
{
    std::shared_ptr<InteractModeState> interactModeState;
    std::shared_ptr<CameraController> cameraController;
    std::shared_ptr<Astar<GridPos,GridDomain>> astar;
    std::vector<std::shared_ptr<BaseNpc>> allNpcs;
    std::shared_ptr<InputSystem> inputSystem;
    std::shared_ptr<World> world;
    std::shared_ptr<std::vector<std::shared_ptr<Wolf>>> wolves;

public:
    std::shared_ptr<BaseInteractSystem> currentInteractSystem;

    PlayerInteractSystem(std::shared_ptr<InteractModeState> interactModeState, std::shared_ptr<CameraController> cameraController, std::shared_ptr<InputSystem> inputSystem, std::vector<std::shared_ptr<BaseNpc>> allNpcs, std::shared_ptr<Astar<GridPos,GridDomain>> astar, std::shared_ptr<World> world, std::shared_ptr<std::vector<std::shared_ptr<Wolf>>> wolves) : interactModeState(std::move(interactModeState)), cameraController(std::move(cameraController)), inputSystem(std::move(inputSystem)), allNpcs(std::move(allNpcs)), astar(std::move(astar)), world(std::move(world)), wolves(std::move(wolves)) {}
    std::shared_ptr<BaseInteractSystem> StrategyFactory(InteractType currentInteractType);
    void OnInteractSystemSelect();
    void UpdateCurrentInteractable() const;
};


#endif
