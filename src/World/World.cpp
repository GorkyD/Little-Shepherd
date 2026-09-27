#include "World.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include "Grid.h"
#include "Enemies/Wolf.h"
#include "Npc/BaseNpc.h"

World::World() = default;

LoadStatus World::SetMap(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
        return LoadStatus::Failure;

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line))
    {
        ++lineNumber;

        constexpr unsigned char bom0 = 0xEF, bom1 = 0xBB, bom2 = 0xBF;

        if (line.size() >= 3 &&
            static_cast<unsigned char>(line[0]) == bom0 &&
            static_cast<unsigned char>(line[1]) == bom1 &&
            static_cast<unsigned char>(line[2]) == bom2)
        {
            line.erase(0, 3);
        }
        
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
        {
            line.pop_back();
        }

        if (line.empty())
            continue;

        std::vector<Tile> row;
        row.reserve(line.size());

        const int rowIndex = static_cast<int>(map.size());

        for (size_t col = 0; col < line.size(); ++col)
        {
            const char c = line[col];

            if (c < '0' || c > '9')
                return LoadStatus::Failure;

            const int value = c - '0';

            if (value < static_cast<int>(ZoneType::Empty) || value > static_cast<int>(ZoneType::Barn))
                return LoadStatus::Failure;

            const auto zone = static_cast<ZoneType>(value);
            const bool isWalkable = zone != ZoneType::Barn && zone != ZoneType::Water;

            row.emplace_back(zone, isWalkable);

            if (zone == ZoneType::Forest)
            {
                const int colIndex = static_cast<int>(col);
                row.back().treeVariant = ((rowIndex * 31 + colIndex * 17) % Tile::TreeVariantCount + Tile::TreeVariantCount) % Tile::TreeVariantCount;
            }

            zoneTiles[zone].push_back(GridPos{ rowIndex, static_cast<int>(col) });
        }

        map.push_back(row);
    }
    
    width = map.size();
    height = map[0].size();

    return LoadStatus::Success;
}

GridPos World::GetRandomWalkableTileGrid() const
{
    std::random_device dev;
    std::mt19937 rng(dev());
    
    std::uniform_int_distribution<std::mt19937::result_type> row(0,map.size() - 1);
    std::uniform_int_distribution<std::mt19937::result_type> col(0,map[0].size() - 1);
    
    while (true)
    {
        const auto r = row(rng);
        const auto c = col(rng);
 
        if (map[r][c].walkable)
            return GridPos(r, c);
    }
}

Tile& World::GetTile(int row, int cols)
{
    return map[row][cols];
}

int World::GetWorldHeight() const
{
    return height;
}

int World::GetWorldWidth() const
{
    return width;
}

bool World::IsTileWalkable(const int row, const int cols) const
{
    return map[row][cols].walkable;
}

bool World::IsTileNotBusy(const int row, const int cols) const
{
    return !map[row][cols].isBusy;
}

std::optional<GridPos> World::GetNearestTileOfType(const ZoneType type, const GridPos from) const
{
    const auto it = zoneTiles.find(type);

    if (it == zoneTiles.end() || it->second.empty())
        return std::nullopt;

    std::optional<GridPos> nearest;
    int bestDistance = 0;
    
    for (const GridPos& candidate : it->second)
    {
        if (map[candidate.row][candidate.col].isBusy)
            continue;

        const int distance = std::abs(candidate.row - from.row) + std::abs(candidate.col - from.col);

        if (!nearest.has_value() || distance < bestDistance)
        {
            bestDistance = distance;
            nearest = candidate;
        }
    }

    return nearest;
}

std::optional<GridPos> World::GetWalkableNeighbor(const GridPos target, const GridPos from) const
{
    static constexpr int offsets[8][2] =
    {
        {1,0}, {-1,0}, {0,1}, {0,-1},
        {1,1}, {1,-1}, {-1,1}, {-1,-1}
    };

    std::optional<GridPos> nearest;
    int bestDistance = 0;

    for (const auto& offset : offsets)
    {
        const int row = target.row + offset[0];
        const int col = target.col + offset[1];

        if (row < 0 || row >= width || col < 0 || col >= height)
            continue;

        if (!map[row][col].walkable || map[row][col].isBusy)
            continue;

        const int distance = std::abs(row - from.row) + std::abs(col - from.col);

        if (!nearest.has_value() || distance < bestDistance)
        {
            nearest = GridPos{ row, col };
            bestDistance = distance;
        }
    }

    return nearest;
}

std::optional<GridPos> World::GetApproachTarget(const ZoneType type, const GridPos from) const
{
    const auto entranceIt = zoneEntrances.find(type);

    if (entranceIt != zoneEntrances.end() && !entranceIt->second.empty())
    {
        std::optional<GridPos> nearestEntrance;
        int bestEntranceDistance = 0;

        for (const GridPos& entrance : entranceIt->second)
        {
            if (map[entrance.row][entrance.col].isBusy)
                continue;

            const int distance = std::abs(entrance.row - from.row) + std::abs(entrance.col - from.col);

            if (!nearestEntrance.has_value() || distance < bestEntranceDistance)
            {
                nearestEntrance = entrance;
                bestEntranceDistance = distance;
            }
        }

        if (nearestEntrance.has_value())
            return nearestEntrance;
    }

    const auto nearest = GetNearestTileOfType(type, from);

    if (!nearest.has_value())
        return std::nullopt;

    if (IsTileWalkable(nearest->row, nearest->col))
        return nearest;

    return GetWalkableNeighbor(nearest.value(), from);
}

void World::SetZoneEntrance(const ZoneType type, const GridPos entrance)
{
    zoneEntrances[type].push_back(entrance);
}

std::vector<GridPos> World::GetZoneAdjacentWalkableTiles(const ZoneType type) const
{
    static constexpr int offsets[8][2] =
    {
        {1,0}, {-1,0}, {0,1}, {0,-1},
        {1,1}, {1,-1}, {-1,1}, {-1,-1}
    };

    std::vector<GridPos> result;
    const auto it = zoneTiles.find(type);

    if (it == zoneTiles.end())
        return result;

    for (const GridPos& tile : it->second)
    {
        for (const auto& offset : offsets)
        {
            const int row = tile.row + offset[0];
            const int col = tile.col + offset[1];

            if (row < 0 || row >= width || col < 0 || col >= height)
                continue;

            if (!map[row][col].walkable)
                continue;

            const GridPos candidate{ row, col };

            if (std::ranges::find(result, candidate) == result.end())
                result.push_back(candidate);
        }
    }

    return result;
}

const std::vector<GridPos>& World::GetTilesOfType(const ZoneType type) const
{
    static const std::vector<GridPos> empty;
    const auto it = zoneTiles.find(type);
    return it != zoneTiles.end() ? it->second : empty;
}

ZoneType World::GetZoneAt(const GridPos pos) const
{
    for (const auto& [zone, entrances] : zoneEntrances)
        for (const GridPos& entrance : entrances)
            if (entrance == pos)
                return zone;

    static constexpr int offsets[8][2] =
    {
        {1,0}, {-1,0}, {0,1}, {0,-1},
        {1,1}, {1,-1}, {-1,1}, {-1,-1}
    };

    for (const auto& offset : offsets)
    {
        const int row = pos.row + offset[0];
        const int col = pos.col + offset[1];

        if (row < 0 || row >= width || col < 0 || col >= height)
            continue;

        if (map[row][col].zone == ZoneType::Water)
            return ZoneType::Water;
    }

    return map[pos.row][pos.col].zone;
}

std::optional<Vector2> World::GetZoneScreenCenter(const ZoneType type) const
{
    const auto it = zoneTiles.find(type);

    if (it == zoneTiles.end() || it->second.empty())
        return std::nullopt;

    int minRow = it->second[0].row, maxRow = minRow;
    int minCol = it->second[0].col, maxCol = minCol;

    for (const GridPos& tile : it->second)
    {
        minRow = std::min(minRow, tile.row);
        maxRow = std::max(maxRow, tile.row);
        minCol = std::min(minCol, tile.col);
        maxCol = std::max(maxCol, tile.col);
    }

    return Grid::ToScreen((minRow + maxRow) / 2.0f, (minCol + maxCol) / 2.0f);
}

std::optional<Rectangle> World::GetZoneScreenFootprint(const ZoneType type) const
{
    const auto it = zoneTiles.find(type);

    if (it == zoneTiles.end() || it->second.empty())
        return std::nullopt;

    int minRow = it->second[0].row, maxRow = minRow;
    int minCol = it->second[0].col, maxCol = minCol;

    for (const GridPos& tile : it->second)
    {
        minRow = std::min(minRow, tile.row);
        maxRow = std::max(maxRow, tile.row);
        minCol = std::min(minCol, tile.col);
        maxCol = std::max(maxCol, tile.col);
    }

    const Vector2 corners[4] =
    {
        Grid::ToScreen(static_cast<float>(minRow), static_cast<float>(minCol)),
        Grid::ToScreen(static_cast<float>(minRow), static_cast<float>(maxCol)),
        Grid::ToScreen(static_cast<float>(maxRow), static_cast<float>(minCol)),
        Grid::ToScreen(static_cast<float>(maxRow), static_cast<float>(maxCol))
    };

    float minX = corners[0].x, maxX = corners[0].x;
    float minY = corners[0].y, maxY = corners[0].y;

    for (const Vector2& corner : corners)
    {
        minX = std::min(minX, corner.x);
        maxX = std::max(maxX, corner.x);
        minY = std::min(minY, corner.y);
        maxY = std::max(maxY, corner.y);
    }

    minX -= Grid::TileWidth / 2.0f;
    maxX += Grid::TileWidth / 2.0f;
    minY -= Grid::TileHeight / 2.0f;
    maxY += Grid::TileHeight / 2.0f;

    return Rectangle{ minX, minY, maxX - minX, maxY - minY };
}

bool World::GetTimeState() const
{
    return worldState.IsDayNow;
}

void World::SetTimeState(bool isDay)
{
    worldState.IsDayNow = isDay;
    std::cout << worldState.IsDayNow << std::endl;
}

void World::RegisterAgent(const std::shared_ptr<BaseNpc>& npc)
{
    agents.push_back(npc);
}

std::vector<std::shared_ptr<BaseNpc>> World::GetAgents() const
{
    std::vector<std::shared_ptr<BaseNpc>> result;
    result.reserve(agents.size());

    for (const auto& agent : agents)
        if (auto locked = agent.lock())
            result.push_back(std::move(locked));

    return result;
}

bool World::IsAnyAgentSearchingDanger() const
{
    for (const auto& agent : agents)
        if (auto locked = agent.lock())
            if (locked->GetCurrentActionName() == "SearchDanger")
                return true;

    return false;
}

void World::RegisterEnemy(const std::shared_ptr<Wolf>& enemy)
{
    enemies.push_back(enemy);
}

std::vector<std::shared_ptr<Wolf>> World::GetEnemies() const
{
    std::vector<std::shared_ptr<Wolf>> result;
    result.reserve(enemies.size());

    for (const auto& enemy : enemies)
        if (auto locked = enemy.lock())
            result.push_back(std::move(locked));

    return result;
}
