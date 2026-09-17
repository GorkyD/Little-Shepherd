#ifndef WILDLIFESIM_APPLYEFFECTNODE_H
#define WILDLIFESIM_APPLYEFFECTNODE_H

#include "Node.h"
#include "Npc/BaseNpc.h"
#include "Goap/Action.h"

class ApplyEffectNode : public Node
{
    const Action* action;
public:
    explicit ApplyEffectNode(const Action* action) : action(action) {}
    
    Status Tick(BTContext& ctx) override
    {
        ctx.npc->ApplyActionEffect(action);
        return Status::Success;
    }
};

#endif
