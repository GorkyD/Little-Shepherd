#ifndef WILDLIFESIM_TILERENDERER_H
#define WILDLIFESIM_TILERENDERER_H

#include <memory>
#include <optional>
#include <unordered_map>
#include <utility>
#include "raylib.h"
#include "World/Grid.h"
#include "World/Tile.h"
#include "World/World.h"
#include "World/ZoneType.h"

class RenderSystem
{
    std::shared_ptr<World> world;

    const Color GRID_COLOR = BLACK;

    std::unordered_map<ZoneType, Color> typeMap
    {
        {ZoneType::Empty, WHITE},
        {ZoneType::Barn, BROWN},
        {ZoneType::Field, YELLOW},
        {ZoneType::Forest,GREEN},
        {ZoneType::Water, BLUE}
    };

public:
    RenderSystem(std::shared_ptr<World> world) : world(std::move(world)){};
    void Update();
    void DrawTile(Vector2 position, Tile& tile);
    void DrawBarnBuilding() const;
    void DrawSleepIndicator() const;
    std::optional<float> GetBarnBuildingAnchorY() const;
    std::optional<float> GetBarnBuildingFrontDepth() const;
    Color GetColorByZoneType(ZoneType type);
};

#endif
