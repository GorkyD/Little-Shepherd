#ifndef WILDLIFESIM_PROCEDURALBACKGROUND_H
#define WILDLIFESIM_PROCEDURALBACKGROUND_H

#include "World/TimeSystem/TimeSystem.h"
#include "raylib.h"
#include "raymath.h"

struct Puff
{
    float x;
    float y;
    float radius;
};

struct Cloud
{
    float x;
    float y;
    float speed;
    Puff puffArray[4];
};

class ProceduralBackground
{
    std::shared_ptr<TimeSystem> timeSystem;
    std::shared_ptr<World> world;
    
    Cloud clouds[5] =
    {
        { 100.0f,  70.0f,  25.0f,{ {0,0,30}, {35,10,25}, {-30,10,22}, {15,-15,20} }},
        { 480.0f, 130.0f,  23.5f, { {0,0,38}, {42,14,28}, {-38,10,26}, {8,-18,22} } },
        { 860.0f,  50.0f,  26.0f,{ {0,0,24}, {28,8,20},  {-24,8,18},  {0,0,0} } },
        { 1240.0f,170.0f,   24.8f,{ {0,0,34}, {38,12,25}, {-34,10,23}, {4,-16,19} }},
        { 1620.0f, 90.0f,  22.75f,{ {0,0,28}, {32,10,21}, {-28,8,19},  {0,0,0} }},
    };
    
public:
    Color blueTop      = {135, 206, 250, 255};
    Color blueBottom   = {224, 242, 254, 255};
    Color sunsetTop    = {255, 140,  60, 255};
    Color sunsetBottom = {255, 205, 120, 255};
    Color nightTop     = {  8,  10,  35, 255};
    Color nightBottom  = { 35,  25,  60, 255};
    
    ProceduralBackground(std::shared_ptr<TimeSystem> timeSystem, std::shared_ptr<World> world) : timeSystem(std::move(timeSystem)), world(std::move(world)){}

    Color ColorLerp(Color& start, Color& end, const float deltaTime)
    {
        return Color(start.r * (1-deltaTime) + end.r * deltaTime,
            start.g * (1-deltaTime) + end.g * deltaTime,
            start.b * (1-deltaTime) + end.b * deltaTime,
            start.a * (1-deltaTime) + end.a * deltaTime);
    }
    
    float Clamp01(const float value)
    {
        if (value < 0.0f) return 0.0f;
        if (value > 1.0f) return 1.0f;
        return value;
    }
    
    float ComputeSkyT(const bool isDayTime, const float phaseProgress)
    {
        if (isDayTime)
        {
            constexpr float dawnEnd = 0.3f;
            constexpr float sunsetStart = 0.7f;

            if (phaseProgress <= dawnEnd)
            {
                const float t = phaseProgress / dawnEnd;
                return 1.0f - t;
            }

            if (phaseProgress >= sunsetStart)
            {
                const float t = (phaseProgress - sunsetStart) / (1.0f - sunsetStart);
                return t * 0.5f;
            }

            return 0.0f;
        }

        constexpr float duskEnd = 0.3f;
        if (phaseProgress >= duskEnd)
            return 1.0f;

        const float t = phaseProgress / duskEnd;
        return 0.5f + t * 0.5f;
    }

    void DrawProceduralBackground()
    {
        auto isDayTime = world->GetTimeState();
        auto dayTimeProgress = timeSystem->GetCurrentDayTimeProgress();
        
        auto deltaTime = ComputeSkyT(isDayTime, dayTimeProgress);
        
        Color baseTopColor, baseBottomColor;
        
        if (deltaTime <= 0.5f)
        {
            const float t = deltaTime * 2.0f;
            baseTopColor = ColorLerp(blueTop, sunsetTop, t);
            baseBottomColor = ColorLerp(blueBottom, sunsetBottom, t);
        }
        else
        {
            const float t = (deltaTime - 0.5f) * 2.0f;
            baseTopColor = ColorLerp(sunsetTop, nightTop, t);
            baseBottomColor = ColorLerp(sunsetBottom, nightBottom, t);
        }
        
        DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), baseTopColor,baseBottomColor);
        
        DrawClouds(deltaTime);
        DrawStars(deltaTime);
    }
    
    void DrawClouds(float dayTimeProgress)
    {
        const unsigned char alpha = static_cast<unsigned char>(235.0f * (1.0f - dayTimeProgress));
        
            for (const auto& cloud : clouds)
            {
                for (const auto& puff : cloud.puffArray)
                {
                    auto x = fmodf(cloud.x + puff.x + cloud.speed * GetTime(), GetScreenWidth() + 400.0f) - 200.0f;
                    DrawCircle(x,cloud.y + puff.y, puff.radius, Color(255,255,255,alpha));
                }
            }
    }
    
    void DrawStars(float dayTimeProgress)
    {
        const float starAlphaScale = Clamp01((dayTimeProgress - 0.5f) / 0.5f);
        if (starAlphaScale > 0.01f)
        {
            constexpr int starCount = 70;
            const float time = static_cast<float>(GetTime());

            for (int i = 0; i < starCount; i++)
            {
                const float sx = fmodf(static_cast<float>(i) * 137.0f, static_cast<float>(GetScreenWidth()));
                const float sy = fmodf(static_cast<float>(i) * 71.0f, static_cast<float>(GetScreenHeight()) * 0.75f);
                const float twinkle = 0.5f + 0.5f * sinf(time * 2.0f + static_cast<float>(i));
                const unsigned char alpha = static_cast<unsigned char>((140.0f + 110.0f * twinkle) * starAlphaScale);
                const float radius = (i % 5 == 0) ? 2.0f : 1.2f;

                DrawCircle(static_cast<int>(sx), static_cast<int>(sy), radius, Color{255, 255, 255, alpha});
            }
        }
    }
};

#endif
