#ifndef WILDLIFESIM_TILEATLAS_H
#define WILDLIFESIM_TILEATLAS_H

#include "raylib.h"
#include "World/ZoneType.h"

Texture2D GetTileTexture(ZoneType zone);
Texture2D GetTileOverlayTexture(ZoneType zone);
Texture2D GetTreeTextureByVariant(int variant);
Texture2D GetDigHoleTexture();
Texture2D GetBarnBuildingTexture();
Texture2D GetFireTexture(int frame);

#endif
