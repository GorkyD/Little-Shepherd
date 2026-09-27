#include "SpawnMobSystem.h"
#include "Enemies/Wolf.h"
#include "World/Grid.h"

void SpawnMobSystem::Start()
{
}

void SpawnMobSystem::Update()
{
    if (!inputSystem->IsPointerActionPressed(PointerInputAction::BasePointerClick))
        return;

    const auto pointerWorldPos = GetScreenToWorld2D(inputSystem->GetPointerScreenPosition(), cameraController->Get());
    const auto hitGrid = Grid::ToGrid(pointerWorldPos);

    if (hitGrid.row < 0 || hitGrid.row >= world->GetWorldWidth() || hitGrid.col < 0 || hitGrid.col >= world->GetWorldHeight())
        return;

    if (!world->IsTileWalkable(hitGrid.row, hitGrid.col) || !world->IsTileNotBusy(hitGrid.row, hitGrid.col))
        return;

    auto wolf = std::make_shared<Wolf>();
    wolf->Init(world, hitGrid);

    world->RegisterEnemy(wolf);
    wolves->push_back(wolf);
}

void SpawnMobSystem::Exit()
{
}
