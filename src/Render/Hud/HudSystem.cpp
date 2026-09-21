#include "HudSystem.h"
#include "raylib.h"

void HudSystem::Update() const
{
    DrawText(TextFormat("Current Fps: %i", static_cast<int>(1.0f/GetFrameTime())), GetScreenWidth() - 220, 40, 20, GREEN);
    DrawText(TextFormat("1 - Drag Mode | 2 - Fire Mode | 3 - Water Mode | 4 - Spawn Mode"), GetScreenWidth() / 2 - ModeHintOffset,  GetScreenHeight() - 100, 20, BLACK);
    DrawText(TextFormat("Current Mode: %s", Extension::GetTextForEnum(interactModeState->GetCurrentType())), GetScreenWidth() / 2 - CurrentModeOffset,  GetScreenHeight() - 50, 20, RED);
}


