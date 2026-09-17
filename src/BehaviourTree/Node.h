#ifndef WILDLIFESIM_NODE_H
#define WILDLIFESIM_NODE_H

#include <memory>
#include "Astar/Astar.h"
#include "Astar/Domains/GridDomain.h"
#include "World/GridPos.h"

class BaseNpc;
class RenderSystem;

enum class Status { Success, Failure, Running };

struct BTContext
{
    BaseNpc* npc;
    std::shared_ptr<Astar<GridPos, GridDomain>> astar;
    std::shared_ptr<RenderSystem> renderer;
    float deltaTime;
};

class Node
{
public:
    virtual ~Node() = default;
    virtual Status Tick(BTContext& ctx) = 0;
};

#endif
