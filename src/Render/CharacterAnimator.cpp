#include "CharacterAnimator.h"
#include <algorithm>
#include <cmath>
#include "SpriteSheet.h"

void CharacterAnimator::SetClip(const std::string& clip, const bool loop)
{
    this->loop = loop;

    if (clip == currentClip)
        return;

    currentClip = clip;
    frameIndex = 0;
    frameTimer = 0.0f;
}

void CharacterAnimator::SetDirection(const Vector2 delta)
{
    if (delta.x == 0.0f && delta.y == 0.0f)
        return;

    float angle = atan2f(delta.y, delta.x) * RAD2DEG;
    if (angle < 0.0f)
        angle += 360.0f;

    const int sector = static_cast<int>((angle + 22.5f) / 45.0f) % 8;

    static constexpr int rows[8]   = { 2, 1, 0, 1, 2, 3, 4, 3 };
    static constexpr bool flips[8] = { true, true, true, false, false, false, true, true };

    directionRow = rows[sector];
    flip = flips[sector];
}

void CharacterAnimator::Update(const float dt)
{
    const SpriteSheet& sheet = GetSpriteSheet(spriteFolder, spritePrefix, currentClip);

    frameTimer += dt;
    if (frameTimer >= frameDuration)
    {
        frameTimer -= frameDuration;

        if (loop)
        {
            frameIndex = (frameIndex + 1) % sheet.columns;
            if (frameIndex == 0)
                justLooped = true;
        }
        else
        {
            frameIndex = std::min(frameIndex + 1, sheet.columns - 1);
        }
    }
}

bool CharacterAnimator::ConsumeJustLooped()
{
    const bool result = justLooped;
    justLooped = false;
    return result;
}

bool CharacterAnimator::IsFinished() const
{
    const SpriteSheet& sheet = GetSpriteSheet(spriteFolder, spritePrefix, currentClip);
    return !loop && frameIndex >= sheet.columns - 1;
}

void CharacterAnimator::Draw(const Vector2 screenCenter) const
{
    const SpriteSheet& sheet = GetSpriteSheet(spriteFolder, spritePrefix, currentClip);

    Rectangle source = {
        frameIndex * SpriteSheet::FrameSize,
        directionRow * SpriteSheet::FrameSize,
        SpriteSheet::FrameSize,
        SpriteSheet::FrameSize
    };

    if (flip)
        source.width = -source.width;

    const Rectangle dest = { screenCenter.x, screenCenter.y, drawSize, drawSize };
    const Vector2 origin = { drawSize / 2.0f, drawSize };

    DrawTexturePro(sheet.texture, source, dest, origin, 0.0f, WHITE);
}
