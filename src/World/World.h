#ifndef WILDLIFESIM_WORLD_H
#define WILDLIFESIM_WORLD_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "raylib.h"
#include "GlobalWorldState.h"
#include "GridPos.h"
#include "Tile.h"
#include "ZoneType.h"

class BaseNpc;

enum class LoadStatus : size_t
{
    Failure,
    Success
};

class World
{
    std::vector<std::vector<Tile>> map;
    std::unordered_map<ZoneType, std::vector<GridPos>> zoneTiles;
    std::unordered_map<ZoneType, std::vector<GridPos>> zoneEntrances;
    std::vector<std::weak_ptr<BaseNpc>> agents;

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
    std::vector<GridPos> GetZoneAdjacentWalkableTiles(ZoneType type) const;

    ZoneType GetZoneAt(GridPos pos) const;
    std::optional<Vector2> GetZoneScreenCenter(ZoneType type) const;
    std::optional<Rectangle> GetZoneScreenFootprint(ZoneType type) const;
    
    void SetZoneEntrance(ZoneType type, GridPos entrance);
    void SetTimeState(bool isDay);

    void RegisterAgent(const std::shared_ptr<BaseNpc>& npc);
    std::vector<std::shared_ptr<BaseNpc>> GetAgents() const;
    bool IsAnyAgentSearchingDanger() const;
    
    int GetWorldHeight() const;
    int GetWorldWidth() const;

    bool IsTileWalkable(int row, int cols) const;
    bool IsTileNotBusy(int row, int cols) const;
    bool GetTimeState() const;
};

#endif
