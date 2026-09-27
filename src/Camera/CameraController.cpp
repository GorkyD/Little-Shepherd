#include "CameraController.h"
#include <algorithm>
#include <utility>
#include "raymath.h"
#include "World/Grid.h"
#include "World/World.h"

namespace
{
    std::pair<Vector2, Vector2> ComputeWorldBounds(const World& world)
    {
        const Vector2 c1 = Grid::ToScreen(0, 0);
        const Vector2 c2 = Grid::ToScreen(world.GetWorldWidth() - 1, 0);
        const Vector2 c3 = Grid::ToScreen(0, world.GetWorldHeight() - 1);
        const Vector2 c4 = Grid::ToScreen(world.GetWorldWidth() - 1, world.GetWorldHeight() - 1);

        return
        {
            Vector2{ std::min({c1.x, c2.x, c3.x, c4.x}), std::min({c1.y, c2.y, c3.y, c4.y}) },
            Vector2{ std::max({c1.x, c2.x, c3.x, c4.x}), std::max({c1.y, c2.y, c3.y, c4.y}) }
        };
    }
}

void CameraController::Start(const World& world)
{
    const auto [min, max] = ComputeWorldBounds(world);

    boundsMin = min;
    boundsMax = max;
    camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.target = Vector2Scale(Vector2Add(min, max), 0.5f);
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void CameraController::Update()
{
    Vector2 move{};

    if (inputSystem->IsActionDown(InputAction::MoveForward)) move.y -= 1.0f;
    if (inputSystem->IsActionDown(InputAction::MoveBack)) move.y += 1.0f;
    if (inputSystem->IsActionDown(InputAction::MoveLeft)) move.x -= 1.0f;
    if (inputSystem->IsActionDown(InputAction::MoveRight)) move.x += 1.0f;

    if (Vector2LengthSqr(move) > 0.0f)
        move = Vector2Scale(Vector2Normalize(move), speed * GetFrameTime());

    camera.target = Vector2Add(camera.target, move);
    camera.target.x = Clamp(camera.target.x, boundsMin.x, boundsMax.x);
    camera.target.y = Clamp(camera.target.y, boundsMin.y, boundsMax.y);
}

Camera2D CameraController::Get() const
{
    return camera;
}
