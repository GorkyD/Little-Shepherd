#ifndef WILDLIFESIM_OBJECTMOVESYSTEM_H
#define WILDLIFESIM_OBJECTMOVESYSTEM_H

#include <memory>
#include <utility>
#include "Camera/CameraController.h"
#include "Input/InputSystem.h"
#include "NPC/BaseNpc.h"
#include "World/World.h"

enum class ObjectMoveStrategy : int
{
    NpcDrag, 
};

class ObjectMoveSystem
{
    std::shared_ptr<CameraController> cameraController;
    std::shared_ptr<Astar<GridPos,GridDomain>> astar;
    std::shared_ptr<InputSystem> inputSystem;
    std::shared_ptr<BaseNpc> draggedNpc;

    std::vector<std::shared_ptr<BaseNpc>> allNpcs;

    ObjectMoveStrategy currentStrategy = ObjectMoveStrategy::NpcDrag;
public:
    ObjectMoveSystem(std::shared_ptr<CameraController> cameraController, std::shared_ptr<InputSystem> inputSystem, std::vector<std::shared_ptr<BaseNpc>> allNpcs, std::shared_ptr<Astar<GridPos,GridDomain>> astar) : cameraController(std::move(cameraController)), astar(std::move(astar)), inputSystem(std::move(inputSystem)), allNpcs(std::move((allNpcs))) {}
    
    void Update();
};

#endif
