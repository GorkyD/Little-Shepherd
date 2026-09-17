#ifndef WILDLIFESIM_TILE_H
#define WILDLIFESIM_TILE_H

#include "ZoneType.h"

struct Tile
{
    static constexpr int TreeVariantCount = 4;

    ZoneType zone = ZoneType::Empty;
    bool walkable = true;
    bool isBusy = false;
    bool onFire = false;

    int treeVariant = -1;
    float chopFlash = 0.0f;
    float digHoleTimer = 0.0f;

    explicit Tile(const ZoneType zoneType, const bool isWalkable = true) : zone(zoneType), walkable(isWalkable){}
};

#endif
