#ifndef WILDLIFESIM_CAMERACONTROLLER_H
#define WILDLIFESIM_CAMERACONTROLLER_H

#include "raylib.h"
#include "Input/InputSystem.h"

class CameraController
{
    std::shared_ptr<InputSystem> inputSystem;
    Camera2D camera{};
    Vector2 boundsMin{};
    Vector2 boundsMax{};
    float speed = 400.0f;

public:
    CameraController(std::shared_ptr<InputSystem> inputSystem) : inputSystem(std::move(inputSystem)){}
    void Start(Vector2 boundsMin, Vector2 boundsMax);
    void Update();
    Camera2D Get() const;
};

#endif
