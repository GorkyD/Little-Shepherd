#include "NpcBehaviourConfig.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace
{
    bool ParseBool(const std::string& value)
    {
        return value == "true" || value == "1";
    }

    std::unordered_map<std::string, NpcBehaviourProfile> LoadProfiles()
    {
        std::unordered_map<std::string, NpcBehaviourProfile> profiles;
        std::ifstream file(std::string(ASSETS_DIR) + "Config/NpcBehaviour.txt");

        std::string line;

        while (std::getline(file, line))
        {
            std::istringstream lineStream(line);
            std::string archetype;

            if (!(lineStream >> archetype) || archetype.empty() || archetype[0] == '#')
                continue;

            NpcBehaviourProfile profile;
            std::string token;

            while (lineStream >> token)
            {
                const size_t separator = token.find('=');

                if (separator == std::string::npos)
                    continue;

                const std::string key = token.substr(0, separator);
                const std::string value = token.substr(separator + 1);

                if (key == "CourageMin") profile.courageMin = std::stoi(value);
                else if (key == "CourageMax") profile.courageMax = std::stoi(value);
                else if (key == "HasWeapon") profile.hasWeapon = ParseBool(value);
            }

            profiles[archetype] = profile;
        }

        return profiles;
    }
}

const NpcBehaviourProfile& GetNpcBehaviourProfile(const std::string& archetype)
{
    static const std::unordered_map<std::string, NpcBehaviourProfile> profiles = LoadProfiles();
    static const NpcBehaviourProfile fallback{};

    const auto it = profiles.find(archetype);
    return it != profiles.end() ? it->second : fallback;
}
