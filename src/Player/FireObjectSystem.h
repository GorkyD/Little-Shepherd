#ifndef WILDLIFESIM_FIREOBJECTSYSTEM_H
#define WILDLIFESIM_FIREOBJECTSYSTEM_H

#include <utility>
#include "BaseInteractSystem.h"
#include "Camera/CameraController.h"
#include "Input/InputSystem.h"
#include "World/World.h"

class FireObjectSystem : public BaseInteractSystem
{
    std::shared_ptr<CameraController> cameraController;
    std::shared_ptr<InputSystem> inputSystem;
    std::shared_ptr<World> world;
public:
    FireObjectSystem(std::shared_ptr<CameraController> cameraController, std::shared_ptr<InputSystem> inputSystem, std::shared_ptr<World> world) : cameraController(std::move(cameraController)), inputSystem(std::move(inputSystem)), world(std::move(world)) {};
    void Start() override;
    void Update() override;
    void Exit() override;
};


#endif
