#ifndef WILDLIFESIM_WAITNODE_H
#define WILDLIFESIM_WAITNODE_H

#include <string>
#include <utility>
#include "Node.h"
#include "Npc/BaseNpc.h"
#include "World/ZoneType.h"

class WaitNode : public Node
{
    std::string clip;
    std::string name;
    ZoneType faceZone;
public:
    WaitNode(std::string clip, std::string name, ZoneType faceZone) : clip(std::move(clip)), name(std::move(name)), faceZone(faceZone) {}

    Status Tick(BTContext& ctx) override
    {
        ctx.npc->PlayClip(clip);
        ctx.npc->FaceZone(faceZone);
        ctx.npc->CalculateLastDirection(name);
        ctx.npc->WaitNodeUpdate(name);

        return Status::Running;
    }
};

#endif
