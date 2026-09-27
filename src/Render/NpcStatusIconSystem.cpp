#include "NpcStatusIconSystem.h"
#include <algorithm>
#include <string>
#include <unordered_map>
#include "raylib.h"
#include "Npc/BaseNpc.h"

namespace
{
    constexpr float IconSize = 28.0f;
    constexpr float IconYOffset = -90.0f;

    Texture2D GetIconTexture(const char* fileName)
    {
        static std::unordered_map<std::string, Texture2D> cache;

        const auto it = cache.find(fileName);
        if (it != cache.end())
            return it->second;

        const std::string path = std::string(ASSETS_DIR) + "Ui/Icons/" + fileName;
        const Texture2D texture = LoadTexture(path.c_str());
        cache[fileName] = texture;
        return texture;
    }

    void DrawTextureIcon(Texture2D texture, Vector2 anchor, bool isMirroredY = false)
    {
        if (texture.id == 0)
            return;

        const float scale = IconSize / std::max(texture.width, texture.height);
        const float destWidth = texture.width * scale;
        const float destHeight = texture.height * scale;

        const Rectangle source = { 0, 0, static_cast<float>(texture.width), isMirroredY ? -static_cast<float>(texture.height) : static_cast<float>(texture.height) };
        const Rectangle dest = { anchor.x, anchor.y + IconYOffset, destWidth, destHeight };
        const Vector2 origin = { destWidth / 2.0f, destHeight / 2.0f };

        DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
    }
}

void NpcStatusIconSystem::Draw(const std::vector<std::shared_ptr<BaseNpc>>& npcs) const
{
    for (const auto& npc : npcs)
    {
        const std::string& action = npc->GetCurrentActionName();

        if (action == "RunAwayFromDanger" || action == "RunAwayFromFire")
            DrawTextureIcon(GetIconTexture("Icon_Small_Blank_Help.png"), npc->GetActualPosition());
        else if (action == "SearchDanger" || action == "GetWater" || action == "ExtinguishFire")
            DrawTextureIcon(GetIconTexture("Icon_Small_Blank_Info.png"), npc->GetActualPosition(), true);
    }
}
