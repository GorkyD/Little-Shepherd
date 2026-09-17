#include "TileAtlas.h"
#include <iterator>
#include <string>
#include <unordered_map>

namespace
{
    const char* TileTexturePath(const ZoneType zone)
    {
        switch (zone)
        {
            case ZoneType::Empty:  return "Ground/GroundTileDiscreet_Dirt1.png";
            case ZoneType::Field:  return "Ground/GroundTile_Ochre.png";
            case ZoneType::Forest: return "Ground/GroundTileDiscreet_Dirt3.png";
            case ZoneType::Water:  return "Water/GroundTile_Water.png";
            case ZoneType::Barn:   return "Stone/GroundTile_Stone1.png";
            default:               return nullptr;
        }
    }

    const char* TileOverlayPath(const ZoneType zone)
    {
        switch (zone)
        {
            case ZoneType::Field:  return "Grass/TileOverlay_Grass1.png";
            case ZoneType::Forest: return "Grass/TileOverlay_Grass2.png";
            default:                return nullptr;
        }
    }

    Texture2D LoadCached(std::unordered_map<ZoneType, Texture2D>& cache, const ZoneType zone, const char* relativePath)
    {
        const auto it = cache.find(zone);
        if (it != cache.end())
            return it->second;

        Texture2D texture{};

        if (relativePath)
        {
            const std::string path = std::string(ASSETS_DIR) + "Ultimate_Isometric_Pack/Tiles/" + relativePath;
            texture = LoadTexture(path.c_str());
        }

        cache[zone] = texture;
        return texture;
    }
}

Texture2D GetTileTexture(const ZoneType zone)
{
    static std::unordered_map<ZoneType, Texture2D> cache;
    return LoadCached(cache, zone, TileTexturePath(zone));
}

Texture2D GetTileOverlayTexture(const ZoneType zone)
{
    static std::unordered_map<ZoneType, Texture2D> cache;
    return LoadCached(cache, zone, TileOverlayPath(zone));
}

Texture2D GetTreeTextureByVariant(const int variant)
{
    static const char* treeNames[] = { "Oak_Stage3", "Pine_Stage3", "Birch_Stage3", "FantasyTree_Stage3" };
    static std::unordered_map<int, Texture2D> cache;

    if (variant < 0 || variant >= static_cast<int>(std::size(treeNames)))
        return Texture2D{};

    const auto it = cache.find(variant);
    if (it != cache.end())
        return it->second;

    const std::string path = std::string(ASSETS_DIR) + "Ultimate_Isometric_Pack/Tiles/Trees/" + treeNames[variant] + ".png";
    const Texture2D texture = LoadTexture(path.c_str());

    cache[variant] = texture;
    return texture;
}

Texture2D GetDigHoleTexture()
{
    static Texture2D texture{};

    if (texture.id == 0)
    {
        const std::string path = std::string(ASSETS_DIR) + "Ultimate_Isometric_Pack/Tiles/Ground/TileOverlay_Hole.png";
        texture = LoadTexture(path.c_str());
    }

    return texture;
}

Texture2D GetBarnBuildingTexture()
{
    static Texture2D texture{};

    if (texture.id == 0)
    {
        const std::string path = std::string(ASSETS_DIR) + "FreeCityBuilder/FreeAssets/Building_House4.png";
        texture = LoadTexture(path.c_str());
    }

    return texture;
}
