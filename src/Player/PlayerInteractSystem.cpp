#include "PlayerInteractSystem.h"
#include "FireObjectSystem.h"
#include "ObjectMoveSystem.h"
#include "SpawnMobSystem.h"
#include "WaterObjectSystem.h"

std::shared_ptr<BaseInteractSystem> PlayerInteractSystem::StrategyFactory(InteractType currentInteractType)
{
    switch (currentInteractType)
    {
        case InteractType::Drag:
            return std::make_shared<ObjectMoveSystem>(cameraController, inputSystem, allNpcs, astar);
        case InteractType::Fire:
            return std::make_shared<FireObjectSystem>(cameraController, inputSystem, world);
        case InteractType::Water:
            return std::make_shared<WaterObjectSystem>(cameraController, inputSystem, world);
        case InteractType::Spawn:
            return std::make_shared<SpawnMobSystem>(cameraController, inputSystem, world, wolves);
        default: return nullptr;
    }
}

void PlayerInteractSystem::OnInteractSystemSelect()
{
    if (currentInteractSystem)
        currentInteractSystem->Exit();
    
    currentInteractSystem = StrategyFactory(interactModeState->GetCurrentType());
    currentInteractSystem->Start();
}

void PlayerInteractSystem::UpdateCurrentInteractable() const
{
    currentInteractSystem->Update();
}
