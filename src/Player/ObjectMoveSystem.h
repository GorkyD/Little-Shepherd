#ifndef WILDLIFESIM_OBJECTMOVESYSTEM_H
#define WILDLIFESIM_OBJECTMOVESYSTEM_H

#include <memory>
#include <utility>
#include "BaseInteractSystem.h"
#include "Camera/CameraController.h"
#include "Input/InputSystem.h"
#include "NPC/BaseNpc.h"

class ObjectMoveSystem : public BaseInteractSystem
{
    const float Radius = 100.0f;
    const std::string SkipState = "Sleep";
    const int ConfirmFrames = 10;

    bool confirmedButtonDown = false;
    int agreementStreak = 0;
    
    std::shared_ptr<CameraController> cameraController;
    std::shared_ptr<Astar<GridPos,GridDomain>> astar;
    std::shared_ptr<InputSystem> inputSystem;
    std::shared_ptr<BaseNpc> draggedNpc;

    std::vector<std::shared_ptr<BaseNpc>> allNpcs;

public:
    ObjectMoveSystem(std::shared_ptr<CameraController> cameraController, std::shared_ptr<InputSystem> inputSystem, std::vector<std::shared_ptr<BaseNpc>> allNpcs, std::shared_ptr<Astar<GridPos,GridDomain>> astar) : cameraController(std::move(cameraController)), astar(std::move(astar)), inputSystem(std::move(inputSystem)), allNpcs(std::move((allNpcs))) {}
    void Start() override;
    void Update() override;
    void Exit() override;
};

#endif
