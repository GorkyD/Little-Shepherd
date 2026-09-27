#include "WaterObjectSystem.h"
#include "World/Grid.h"

void WaterObjectSystem::Start()
{
}

void WaterObjectSystem::Update()
{
    if (inputSystem->IsPointerActionPressed(PointerInputAction::BasePointerClick))
    {
        auto pointerWorldPos = GetScreenToWorld2D(inputSystem->GetPointerScreenPosition(), cameraController->Get());
        DrawCircle(pointerWorldPos.x,pointerWorldPos.y,5.0f,BLUE);
        auto hitGrid = Grid::ToGrid(pointerWorldPos);

        if (hitGrid.row < 0 || hitGrid.row >= world->GetWorldWidth() || hitGrid.col < 0 || hitGrid.col >= world->GetWorldHeight())
            return;

        auto& tile = world->GetTile(hitGrid.row, hitGrid.col);
        tile.onFire = false;
    }
}

void WaterObjectSystem::Exit()
{
}
