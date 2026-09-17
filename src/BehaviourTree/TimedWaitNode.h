#ifndef WILDLIFESIM_TIMEDWAITNODE_H
#define WILDLIFESIM_TIMEDWAITNODE_H

#include "Node.h"
#include "raylib.h"

class TimedWaitNode : public Node
{
    std::string clip;
    std::string name;
    ZoneType faceZone;
    float waitTime;
public:
    TimedWaitNode(std::string clip, std::string name, ZoneType faceZone, float waitTime) : clip(std::move(clip)), name(std::move(name)), faceZone(faceZone), waitTime(waitTime) {}

    Status Tick(BTContext& ctx) override
    {
        while (waitTime > 0)
        {
            ctx.npc->PlayClip(clip);
            ctx.npc->FaceZone(faceZone);
            ctx.npc->CalculateLastDirection(name);
            ctx.npc->WaitNodeUpdate(name);
            waitTime -= GetFrameTime();
            return Status::Running;
        }

        return Status::Success;
    }
};


#endif
