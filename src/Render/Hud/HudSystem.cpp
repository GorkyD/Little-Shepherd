#include "HudSystem.h"
#include "raylib.h"

void HudSystem::Update()
{
    DrawText(TextFormat("CURRENT FPS: %i", static_cast<int>(1.0f/GetFrameTime())), GetScreenWidth() - 220, 40, 20, GREEN);
}
