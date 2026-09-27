#ifndef WILDLIFESIM_NPCSTATUSICONSYSTEM_H
#define WILDLIFESIM_NPCSTATUSICONSYSTEM_H

#include <memory>

class BaseNpc;

class NpcStatusIconSystem
{
public:
    void DrawFor(const std::shared_ptr<BaseNpc>& npc) const;
};

#endif
