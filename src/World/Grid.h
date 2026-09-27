#ifndef WILDLIFESIM_GRID_H
#define WILDLIFESIM_GRID_H

#include <cmath>
#include <functional>

#include "raylib.h"
#include "GridPos.h"

namespace Grid
{
    constexpr float TileWidth = 64.0f;
    constexpr float TileHeight = 32.0f;

    inline Vector2 ToScreen(float row, float col)
    {
        return {
            (col - row) * (TileWidth / 2.0f),
            (col + row) * (TileHeight / 2.0f)
        };
    }

    inline BoundingBox GetBoundingBox2D(Vector2 position)
    {
        return BoundingBox(Vector3(position.x - TileWidth / 2.0f, position.y - TileWidth / 2.0f),Vector3(position.x + TileWidth / 2.0f, position.y + TileWidth / 2.0f));
    }
    
    inline Vector2 ToScreen(GridPos pos)
    {
        return ToScreen(static_cast<float>(pos.row), static_cast<float>(pos.col));
    }

    inline GridPos ToGrid(Vector2 screen)
    {
        const float row = (screen.y / (TileHeight / 2.0f) - screen.x / (TileWidth / 2.0f)) / 2.0f;
        const float col = (screen.y / (TileHeight / 2.0f) + screen.x / (TileWidth / 2.0f)) / 2.0f;
        return { static_cast<int>(std::lround(row)), static_cast<int>(std::lround(col)) };
    }
}

#endif
