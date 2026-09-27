#include "RenderSystem.h"
#include <algorithm>
#include <cmath>
#include "TileAtlas.h"

void RenderSystem::Update()
{
    const int width = world->GetWorldWidth();
    const int height = world->GetWorldHeight();

    for (int diagonal = 0; diagonal < width + height - 1; diagonal++)
    {
        for (int row = 0; row < width; row++)
        {
            const int column = diagonal - row;

            if (column < 0 || column >= height)
                continue;

            DrawTile(Grid::ToScreen(row, column), world->GetTile(row, column));
        }
    }
}

namespace
{
    constexpr float BarnDoorAlignOffsetX = -13.0f;
    constexpr float BarnDoorAlignOffsetY = -29.0f;
}

std::optional<float> RenderSystem::GetBarnBuildingAnchorY() const
{
    const auto footprint = world->GetZoneScreenFootprint(ZoneType::Barn);

    if (!footprint.has_value())
        return std::nullopt;

    return footprint->y + footprint->height + BarnDoorAlignOffsetY;
}

std::optional<float> RenderSystem::GetBarnBuildingFrontDepth() const
{
    const auto anchorY = GetBarnBuildingAnchorY();

    if (!anchorY.has_value())
        return std::nullopt;

    return *anchorY / (Grid::TileHeight / 2.0f);
}

void RenderSystem::DrawBarnBuilding() const
{
    const auto footprint = world->GetZoneScreenFootprint(ZoneType::Barn);
    const auto anchorY = GetBarnBuildingAnchorY();

    if (!footprint.has_value() || !anchorY.has_value())
        return;

    const Texture2D texture = GetBarnBuildingTexture();

    if (texture.id == 0)
        return;

    const float drawWidth = footprint->width;
    const float drawHeight = drawWidth * (static_cast<float>(texture.height) / static_cast<float>(texture.width));

    const float anchorX = footprint->x + footprint->width / 2.0f + BarnDoorAlignOffsetX;

    const Rectangle source = { 0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    const Rectangle dest = { anchorX, *anchorY, drawWidth, drawHeight };
    const Vector2 origin = { drawWidth / 2.0f, drawHeight * 0.8f };

    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}

void RenderSystem::DrawSleepIndicator() const
{
    const auto footprint = world->GetZoneScreenFootprint(ZoneType::Barn);
    const auto anchorY = GetBarnBuildingAnchorY();

    if (!footprint.has_value() || !anchorY.has_value())
        return;

    constexpr float Pi = 3.14159265358979323846f;
    constexpr float cycleDuration = 1.8f;
    constexpr int zCount = 3;
    constexpr float driftHeight = 34.0f;
    constexpr float driftWidth = 16.0f;
    constexpr float roofOffset = 130.0f;

    const float baseX = footprint->x + footprint->width / 2.0f + BarnDoorAlignOffsetX;
    const float baseY = *anchorY - roofOffset;

    const float time = static_cast<float>(GetTime());

    for (int i = 0; i < zCount; i++)
    {
        const float phase = std::fmod(time / cycleDuration + static_cast<float>(i) / zCount, 1.0f);

        const float x = baseX + phase * driftWidth;
        const float y = baseY - phase * driftHeight;

        const float alpha = std::sin(phase * Pi);
        const int fontSize = 14 + i * 4;

        const Color color = { 255, 255, 255, static_cast<unsigned char>(std::clamp(alpha, 0.0f, 1.0f) * 255.0f) };

        DrawText("Z", static_cast<int>(x), static_cast<int>(y), fontSize, color);
    }
}

void RenderSystem::DrawTile(Vector2 center, Tile& tile)
{
    const ZoneType type = tile.zone;
    const Texture2D texture = GetTileTexture(type);

    if (texture.id != 0)
    {
        constexpr float drawSize = 84.0f;
        const Rectangle dest = { center.x, center.y, drawSize, drawSize };
        constexpr Vector2 origin = { drawSize / 2.0f, drawSize * 0.3f };

        const Rectangle source = { 0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height) };
        DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);

        const Texture2D overlay = GetTileOverlayTexture(type);
        if (overlay.id != 0)
        {
            const Rectangle overlaySource = { 0, 0, static_cast<float>(overlay.width), static_cast<float>(overlay.height) };
            DrawTexturePro(overlay, overlaySource, dest, origin, 0.0f, WHITE);
        }

        if (tile.digHoleTimer > 0.0f)
        {
            const Texture2D hole = GetDigHoleTexture();
            if (hole.id != 0)
            {
                const Rectangle holeSource = { 0, 0, static_cast<float>(hole.width), static_cast<float>(hole.height) };
                DrawTexturePro(hole, holeSource, dest, origin, 0.0f, WHITE);
            }

            tile.digHoleTimer -= GetFrameTime();
            if (tile.digHoleTimer < 0.0f)
                tile.digHoleTimer = 0.0f;
        }
        
        if (type == ZoneType::Forest && tile.treeVariant >= 0)
        {
            const Texture2D tree = GetTreeTextureByVariant(tile.treeVariant);

            if (tree.id != 0)
            {
                constexpr float treeWidth = 126.0f;
                const float treeHeight = treeWidth * (static_cast<float>(tree.height) / static_cast<float>(tree.width));
                const Rectangle treeSource = { 0, 0, static_cast<float>(tree.width), static_cast<float>(tree.height) };
                const Rectangle treeDest = { center.x, center.y, treeWidth, treeHeight };
                const Vector2 treeOrigin = { treeWidth / 2.0f, treeHeight * 0.62f };

                DrawTexturePro(tree, treeSource, treeDest, treeOrigin, 0.0f, WHITE);

                if (tile.chopFlash > 0.0f)
                {
                    BeginBlendMode(BLEND_ADDITIVE);
                    const Color flashTint = { 255, 255, 255, static_cast<unsigned char>(255.0f * tile.chopFlash) };
                    DrawTexturePro(tree, treeSource, treeDest, treeOrigin, 0.0f, flashTint);
                    EndBlendMode();

                    tile.chopFlash -= GetFrameTime() * 4.0f;
                    if (tile.chopFlash < 0.0f)
                        tile.chopFlash = 0.0f;
                }
            }
        }
        
        if (tile.onFire)
        {
            constexpr float frameDuration = 0.09f;
            constexpr int frameCount = 8;
            const int frame = static_cast<int>(GetTime() / frameDuration) % frameCount;

            const Texture2D fire = GetFireTexture(frame);
            if (fire.id != 0)
            {
                constexpr float fireWidth = 48.0f;
                const float fireHeight = fireWidth * (static_cast<float>(fire.height) / static_cast<float>(fire.width));
                const Rectangle fireSource = { 0, 0, static_cast<float>(fire.width), static_cast<float>(fire.height) };
                const Rectangle fireDest = { center.x, center.y, fireWidth, fireHeight };
                const Vector2 fireOrigin = { fireWidth / 2.0f, fireHeight * 0.75f };
                DrawTexturePro(fire, fireSource, fireDest, fireOrigin, 0.0f, WHITE);
            }
        }

        return;
    }

    const Color color = GetColorByZoneType(type);

    const Vector2 top    = { center.x, center.y - Grid::TileHeight / 2.0f };
    const Vector2 right  = { center.x + Grid::TileWidth / 2.0f, center.y };
    const Vector2 bottom = { center.x, center.y + Grid::TileHeight / 2.0f };
    const Vector2 left   = { center.x - Grid::TileWidth / 2.0f, center.y };

    DrawTriangle(top, left, bottom, color);
    DrawTriangle(top, bottom, right, color);

    DrawLineV(top, right, GRID_COLOR);
    DrawLineV(right, bottom, GRID_COLOR);
    DrawLineV(bottom, left, GRID_COLOR);
    DrawLineV(left, top, GRID_COLOR);
}

Color RenderSystem::GetColorByZoneType(const ZoneType type)
{
    return typeMap[type];
}
