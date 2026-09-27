#ifndef WILDLIFESIM_BASENPC_H
#define WILDLIFESIM_BASENPC_H

#include <memory>
#include "Astar/Astar.h"
#include "Astar/SplinePath.h"
#include "Astar/Domains/GoapDomain.h"
#include "BehaviourTree/BehaviourTreeFactory.h"
#include "BehaviourTree/Node.h"
#include "Extension/Extension.h"
#include "Goap/WorldState.h"
#include "Goap/Goals/GoalPlanner.h"
#include "Render/CharacterAnimator.h"
#include "Render/RenderSystem.h"
#include "Sensors/Sensor.h"
#include "World/GridPos.h"
#include "World/ZoneType.h"

class BaseNpc : public std::enable_shared_from_this<BaseNpc>
{
    const float SEGMENT_DURATION = 1.0f;

    std::unique_ptr<Astar<WorldState, GoapDomain, Goal>> goapAstar;
    std::unique_ptr<BehaviourTreeFactory> behaviourTreeFactory;
    std::unique_ptr<GoalPlanner> goalPlanner;
    std::unique_ptr<GoapDomain> goapDomain;
    std::shared_ptr<Node> currentBehavior;
    std::string currentActionName;

    std::optional<GridPos> reservedTile;
    std::optional<GridPos> knownFireTile;
    std::weak_ptr<Wolf> knownThreat;
    bool nearbyThreatDetected = false;
    std::unique_ptr<Sensor> visionSensor;

    SplinePath currentPath;
    size_t segmentIndex = 0;

    Vector2 actualPosition{};
    Vector2 catchUpFrom{};
    Vector2 workOffset{};
    
    float segmentTimer = 0.0f;
    
    bool catchingUp = false;
    
    void WorldStep(const std::shared_ptr<Astar<GridPos,GridDomain>>& astar);

protected:
    std::shared_ptr<World> world;
    CharacterAnimator animator;
    NpcBehaviour npcBehaviour;
    WorldState currentState;
    
    Vector2 lastMoveDirection{ 0.0f, 1.0f };
    Vector2 targetWorkOffset{};

    void ApplyBehaviourProfile(const std::string& archetype);

public:
    GridPos position;
    std::string name;

    BaseNpc(GridPos startPosition, std::string name) : position(startPosition), actualPosition(Extension::ToWorld(startPosition)), name(std::move(name)){}

    virtual void Update(const std::shared_ptr<Astar<GridPos, GridDomain>>& astar, const std::shared_ptr<RenderSystem>& renderer);
    virtual float CalculateTileOffsetByName(std::string actionName) = 0;
    virtual void CalculateLastDirection(std::string actionName) = 0;
    virtual std::string GetWorkClipFor(const Action* action) = 0;
    virtual void PlayClip(const std::string& clip) = 0;

    virtual void WaitNodeUpdate(std::string actionName) = 0;

    void UpdateDraw() const;
    void Start(const std::shared_ptr<World>& world, std::vector<Action> actions);
    void Replan(const std::shared_ptr<Astar<GridPos,GridDomain>>& astar);
    void ApplyActionEffect(const Action* action);
    void AdvanceMove(float deltaTime);
    void FaceZone(ZoneType zone);
    void SetPosition(Vector2 newPosition);
    void SetDraggedState(bool state);
    void SetDangerState(bool state);

    void ReportFireSighting(bool sawFire, std::optional<GridPos> tile, const std::shared_ptr<Astar<GridPos,GridDomain>>& astar);
    void ReportThreatNearby(std::optional<std::weak_ptr<Wolf>> threat, const std::shared_ptr<Astar<GridPos,GridDomain>>& astar);
    void ReportNearbyAlarm(bool sawAlarmedNpc, const std::shared_ptr<Astar<GridPos,GridDomain>>& astar);

    Tile& GetCurrentTile() const;
    Vector2 GetActualPosition() const {return actualPosition;}
    Vector2 GetLastMoveDirection() const {return lastMoveDirection;}
    const std::string& GetCurrentActionName() const {return currentActionName;}

    int GetNpcCourage() const { return npcBehaviour.courage; }

    std::optional<GridPos> GetKnownFireTile() const { return knownFireTile; }
    void ClearKnownFireTile() { knownFireTile.reset(); }
    bool IsKnownFireStillBurning() const;
    void ExtinguishKnownFire();

    std::shared_ptr<Wolf> GetKnownThreat() const { return knownThreat.lock(); }
    void ClearKnownThreat() { knownThreat.reset(); }
    bool IsKnownThreatAlive() const;
    bool BeginApproachMove(GridPos target, const std::shared_ptr<Astar<GridPos,GridDomain>>& astar);
    void ClaimCombatTile();
    void ReleaseReservedTile();
    void FacePosition(GridPos target);
    bool ConsumeAttackTick();

    bool BeginMove(GridPos targetPosition, const std::shared_ptr<Astar<GridPos,GridDomain>>& astar);
    bool BeginMove(ZoneType targetZone, const std::shared_ptr<Astar<GridPos,GridDomain>>& astar);
    bool IsMoving() const;
    bool HasNearbyThreat() const { return nearbyThreatDetected; };
    bool IsHandlingEmergency() const { return currentState.isInDanger || currentState.fireNearby; }
};

#endif
