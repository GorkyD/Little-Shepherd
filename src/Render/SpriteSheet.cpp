#include "SpriteSheet.h"
#include <unordered_map>

const SpriteSheet& GetSpriteSheet(const std::string& folder, const std::string& prefix, const std::string& clipName)
{
    static std::unordered_map<std::string, SpriteSheet> cache;

    const std::string key = folder + "/" + prefix + clipName;

    const auto it = cache.find(key);
    if (it != cache.end())
        return it->second;

    SpriteSheet sheet;
    const std::string path = std::string(ASSETS_DIR) + folder + "/" + prefix + clipName + ".png";
    sheet.texture = LoadTexture(path.c_str());
    sheet.columns = sheet.texture.width / static_cast<int>(SpriteSheet::FrameSize);

    if (sheet.columns < 1)
        sheet.columns = 1;

    return cache.emplace(key, sheet).first->second;
}
