#include "FireObjectSystem.h"

#include <iostream>

#include "World/Grid.h"

void FireObjectSystem::Start()
{
}

void FireObjectSystem::Update()
{
    if (inputSystem->IsPointerActionPressed(PointerInputAction::BasePointerClick))
    {
        auto pointerWorldPos = GetScreenToWorld2D(inputSystem->GetPointerScreenPosition(), cameraController->Get());
        DrawCircle(pointerWorldPos.x,pointerWorldPos.y,5.0f,RED);
        auto hitGrid = Grid::ToGrid(pointerWorldPos);

        if (hitGrid.row < 0 || hitGrid.row >= world->GetWorldWidth() || hitGrid.col < 0 || hitGrid.col >= world->GetWorldHeight())
            return;

        auto& tile = world->GetTile(hitGrid.row, hitGrid.col);
        
        if (tile.zone != ZoneType::Barn && tile.zone != ZoneType::Water)
            tile.onFire = true;
    }
}

void FireObjectSystem::Exit()
{
}
