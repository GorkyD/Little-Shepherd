#ifndef WILDLIFESIM_MOVETORANDOMNODE_H
#define WILDLIFESIM_MOVETORANDOMNODE_H

#include "Node.h"

#include <utility>

class MoveToRandomNode : public Node
{
    std::string clipName;
    GridPos targetPosition;
    bool started = false;
public:
    explicit MoveToRandomNode(GridPos randomPosition, std::string clipName) : targetPosition(randomPosition), clipName(std::move(clipName)) {}
    Status Tick(BTContext& ctx) override
    {
        if (!started) { started = ctx.npc->BeginMove(targetPosition, ctx.astar); if (!started) return Status::Failure; }
        if (ctx.npc->IsMoving())
        {
            ctx.npc->PlayClip(clipName);
            ctx.npc->AdvanceMove(ctx.deltaTime);
            return Status::Running;
        }
        started = false;
        return Status::Success;
    }
};


#endif
