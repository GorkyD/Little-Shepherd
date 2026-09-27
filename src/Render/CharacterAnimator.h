#ifndef WILDLIFESIM_CHARACTERANIMATOR_H
#define WILDLIFESIM_CHARACTERANIMATOR_H

#include <string>
#include <utility>
#include "raylib.h"

class CharacterAnimator
{
    std::string spriteFolder;
    std::string spritePrefix;
    float drawSize;

    std::string currentClip = "Idle";
    int frameIndex = 0;
    float frameTimer = 0.0f;
    const float frameDuration = 0.1f;

    int directionRow = 0;
    bool flip = false;
    bool loop = true;
    bool justLooped = false;

public:
    explicit CharacterAnimator(std::string spriteFolder = "Character0", std::string spritePrefix = "Character0_", float drawSize = 96.0f)
        : spriteFolder(std::move(spriteFolder)), spritePrefix(std::move(spritePrefix)), drawSize(drawSize) {}

    void SetClip(const std::string& clip, bool loop = true);
    void SetDirection(Vector2 movementDelta);
    void Update(float dt);
    void Draw(Vector2 screenCenter) const;
    bool ConsumeJustLooped();
    bool IsFinished() const;
    const std::string& CurrentClip() const { return currentClip; }
};

#endif
