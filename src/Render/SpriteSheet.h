#ifndef WILDLIFESIM_SPRITESHEET_H
#define WILDLIFESIM_SPRITESHEET_H

#include <string>
#include "raylib.h"

struct SpriteSheet
{
    static constexpr float FrameSize = 460.0f;
    static constexpr int Rows = 5;

    Texture2D texture{};
    int columns = 1;
};

const SpriteSheet& GetSpriteSheet(const std::string& folder, const std::string& prefix, const std::string& clipName);

#endif
