#ifndef WILDLIFESIM_SPAWNMOBSYSTEM_H
#define WILDLIFESIM_SPAWNMOBSYSTEM_H

#include <memory>
#include <utility>
#include <vector>
#include "BaseInteractSystem.h"
#include "Camera/CameraController.h"
#include "Input/InputSystem.h"
#include "World/World.h"

class Wolf;

class SpawnMobSystem : public BaseInteractSystem
{
    std::shared_ptr<CameraController> cameraController;
    std::shared_ptr<InputSystem> inputSystem;
    std::shared_ptr<World> world;
    std::shared_ptr<std::vector<std::shared_ptr<Wolf>>> wolves;

public:
    SpawnMobSystem(std::shared_ptr<CameraController> cameraController, std::shared_ptr<InputSystem> inputSystem, std::shared_ptr<World> world, std::shared_ptr<std::vector<std::shared_ptr<Wolf>>> wolves)
        : cameraController(std::move(cameraController)), inputSystem(std::move(inputSystem)), world(std::move(world)), wolves(std::move(wolves)) {}

    void Start() override;
    void Update() override;
    void Exit() override;
};


#endif
