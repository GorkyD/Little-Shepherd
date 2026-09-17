#ifndef WILDLIFESIM_WORLD_H
#define WILDLIFESIM_WORLD_H

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "GlobalWorldState.h"
#include "GridPos.h"
#include "Tile.h"
#include "ZoneType.h"

enum class LoadStatus : size_t
{
    Failure,
    Success
};

class World
{
    std::vector<std::vector<Tile>> map;
    std::unordered_map<ZoneType, std::vector<GridPos>> zoneTiles;
    std::unordered_map<ZoneType, GridPos> zoneEntrances;

    GlobalWorldState worldState;

    int width,height;
    
public:
    World();
    
    LoadStatus SetMap(const std::string& path);
    GridPos GetRandomWalkableTileGrid() const;
    Tile& GetTile(int row, int cols);

    std::optional<GridPos> GetNearestTileOfType(ZoneType type, GridPos from) const;
    std::optional<GridPos> GetWalkableNeighbor(GridPos target, GridPos from) const;
    std::optional<GridPos> GetApproachTarget(ZoneType type, GridPos from) const;

    ZoneType GetZoneAt(GridPos pos) const;
    
    void SetZoneEntrance(ZoneType type, GridPos entrance);
    void SetTimeState(bool isDay);
    
    int GetWorldHeight() const;
    int GetWorldWidth() const;

    bool IsTileWalkable(int row, int cols) const;
    bool IsTileNotBusy(int row, int cols) const;
    bool GetTimeState() const;
};

#endif
