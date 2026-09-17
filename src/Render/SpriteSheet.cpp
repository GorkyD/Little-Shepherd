#include "SpriteSheet.h"
#include <unordered_map>

const SpriteSheet& GetSpriteSheet(const std::string& clipName)
{
    static std::unordered_map<std::string, SpriteSheet> cache;

    const auto it = cache.find(clipName);
    if (it != cache.end())
        return it->second;

    SpriteSheet sheet;
    const std::string path = std::string(ASSETS_DIR) + "Character0/Character0_" + clipName + ".png";
    sheet.texture = LoadTexture(path.c_str());
    sheet.columns = sheet.texture.width / static_cast<int>(SpriteSheet::FrameSize);

    if (sheet.columns < 1)
        sheet.columns = 1;

    return cache.emplace(clipName, sheet).first->second;
}
