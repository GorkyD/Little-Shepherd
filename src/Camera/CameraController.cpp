#include "CameraController.h"
#include "raymath.h"

void CameraController::Start(const Vector2 min, const Vector2 max)
{
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
