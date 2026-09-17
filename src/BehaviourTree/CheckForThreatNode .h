#ifndef WILDLIFESIM_CHECKFORTHREATNODE_H
#define WILDLIFESIM_CHECKFORTHREATNODE_H

#include "Node.h"
#include "NPC/BaseNpc.h"

class CheckForThreatNode : public Node
{
public:
    Status Tick(BTContext& ctx) override
    {
        if (ctx.npc->HasNearbyThreat())
            return Status::Failure;      
        return Status::Success;       
    }
};

#endif
