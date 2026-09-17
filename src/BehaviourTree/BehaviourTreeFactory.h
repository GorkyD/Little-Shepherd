#ifndef WILDLIFESIM_BEHAVIOURTREEFACTORY_H
#define WILDLIFESIM_BEHAVIOURTREEFACTORY_H

#include <memory>
#include "Node.h"
#include "Selector.h"
#include "Sequence.h"
#include "Goap/Action.h"


class BehaviourTreeFactory
{
    std::shared_ptr<World> world;
    
    std::unique_ptr<Sequence> BuildBaseMoveSequence(BaseNpc* npc, const Action* action) const;
    std::unique_ptr<Sequence> BuildRunAwaySequence(BaseNpc* npc, const Action* action) const;
    std::unique_ptr<Selector> BuildSearchDangerSequence(BaseNpc* npc, const Action* action) const;

public:
    BehaviourTreeFactory(std::shared_ptr<World> world) : world(std::move(world)){}
    std::unique_ptr<Node> BuildBehaviorFor(BaseNpc* npc, const Action* action);
};


#endif
