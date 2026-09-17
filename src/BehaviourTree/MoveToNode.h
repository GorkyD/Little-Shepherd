#ifndef WILDLIFESIM_MOVETONODE_H
#define WILDLIFESIM_MOVETONODE_H

#include "Npc/BaseNpc.h"
#include "Node.h"

class MoveToNode : public Node
{
    const Action* action;
    bool started = false;
public:
    explicit MoveToNode(const Action* action) : action(action) {}
    Status Tick(BTContext& ctx) override
    {
        if (!started)
        {
            started = ctx.npc->BeginMove(Extension::ToZoneType(action->resultingLocation.value()), ctx.astar); 
            if (!started) 
                return Status::Failure;
        }
        
        if (ctx.npc->IsMoving())
        {
            ctx.npc->PlayClip(ctx.npc->GetWorkClipFor(action));
            ctx.npc->AdvanceMove(ctx.deltaTime);
            return Status::Running;
        }
        
        started = false;
        return Status::Success;
    }
};

#endif
