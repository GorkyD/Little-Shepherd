#include "BehaviourTreeFactory.h"
#include <vector>
#include "ApplyEffectNode.h"
#include "CheckForThreatNode .h"
#include "EngageThreatSequence.h"
#include "MoveToNode.h"
#include "MoveToRandomNode.h"
#include "raymath.h"
#include "Selector.h"
#include "Sequence.h"
#include "TimedWaitNode.h"
#include "WaitNode.h"
#include "Extension/Extension.h"


std::unique_ptr<Node> BehaviourTreeFactory::BuildBehaviorFor(BaseNpc* npc, const Action* action)
{
    if (action->name == "RunAwayFromDanger")
        return BuildRunAwaySequence(npc, action);

    if (action->name == "SearchDanger")
        return BuildSearchDangerSequence(npc, action);

    return BuildBaseMoveSequence(npc, action);
}

std::unique_ptr<Selector> BehaviourTreeFactory::BuildSearchDangerSequence(BaseNpc* npc, const Action* action) const
{
    const ZoneType faceZone = action->requiredLocation.has_value()? Extension::ToZoneType(action->requiredLocation.value()) : ZoneType::Empty;
    
    auto searchAndCheck = std::vector<std::unique_ptr<Node>>();
    searchAndCheck.push_back(std::make_unique<MoveToRandomNode>(world->GetRandomWalkableTileGrid(), npc->GetWorkClipFor(action)));
    searchAndCheck.push_back(std::make_unique<TimedWaitNode>(npc->GetWorkClipFor(action), action->name, faceZone, 2.0f));
    searchAndCheck.push_back(std::make_unique<CheckForThreatNode>());
    searchAndCheck.push_back(std::make_unique<ApplyEffectNode>(action));
    
    auto engageThreat = std::make_unique<EngageThreatSequence>();
    
    auto root = std::vector<std::unique_ptr<Node>>();
    root.push_back(std::move(engageThreat));
    root.push_back(std::make_unique<Sequence>(std::move(searchAndCheck)));
    
    return std::make_unique<Selector>(std::move(root));
}

std::unique_ptr<Sequence> BehaviourTreeFactory::BuildRunAwaySequence(BaseNpc* npc, const Action* action) const
{
    const ZoneType faceZone = action->requiredLocation.has_value()? Extension::ToZoneType(action->requiredLocation.value()) : ZoneType::Empty;
    auto steps = std::vector<std::unique_ptr<Node>>();
    steps.push_back(std::make_unique<MoveToRandomNode>(world->GetRandomWalkableTileGrid(), npc->GetWorkClipFor(action)));
    steps.push_back(std::make_unique<TimedWaitNode>(npc->GetWorkClipFor(action), action->name, faceZone, 2.0f));
    steps.push_back(std::make_unique<ApplyEffectNode>(action));
    return std::make_unique<Sequence>(std::move(steps));
}
             
std::unique_ptr<Sequence> BehaviourTreeFactory::BuildBaseMoveSequence(BaseNpc* npc, const Action* action) const
{
    auto steps = std::vector<std::unique_ptr<Node>>();
        
    if (action->resultingLocation.has_value())
        steps.push_back(std::make_unique<MoveToNode>(action));
    else
    {
        const ZoneType faceZone = action->requiredLocation.has_value()? Extension::ToZoneType(action->requiredLocation.value()) : ZoneType::Empty;
        steps.push_back(std::make_unique<WaitNode>(npc->GetWorkClipFor(action), action->name, faceZone));
    }
    
    steps.push_back(std::make_unique<ApplyEffectNode>(action));
    return std::make_unique<Sequence>(std::move(steps));
}
