#ifndef WILDLIFESIM_NPCSTATUSICONSYSTEM_H
#define WILDLIFESIM_NPCSTATUSICONSYSTEM_H

#include <memory>
#include <vector>

class BaseNpc;

class NpcStatusIconSystem
{
public:
    void Draw(const std::vector<std::shared_ptr<BaseNpc>>& npcs) const;
};

#endif
