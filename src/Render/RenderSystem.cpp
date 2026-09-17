#include "RenderSystem.h"
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
