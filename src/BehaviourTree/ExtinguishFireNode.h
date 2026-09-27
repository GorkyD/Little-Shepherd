#ifndef WILDLIFESIM_EXTINGUISHFIRENODE_H
#define WILDLIFESIM_EXTINGUISHFIRENODE_H

#include "Node.h"
#include "Npc/BaseNpc.h"
#include "Goap/Action.h"

class ExtinguishFireNode : public Node
{
    const Action* action;
    bool started = false;
public:
    explicit ExtinguishFireNode(const Action* action) : action(action) {}

    Status Tick(BTContext& ctx) override
    {
        const auto fireTile = ctx.npc->GetKnownFireTile();

        if (!fireTile.has_value())
            return Status::Failure;

        if (!started)
        {
            started = ctx.npc->BeginMove(fireTile.value(), ctx.astar);
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

        if (!ctx.npc->IsKnownFireStillBurning())
        {
            ctx.npc->ClearKnownFireTile();
            return Status::Failure;
        }

        ctx.npc->ExtinguishKnownFire();
        ctx.npc->ApplyActionEffect(action);
        ctx.npc->ClearKnownFireTile();
        return Status::Success;
    }
};

#endif
