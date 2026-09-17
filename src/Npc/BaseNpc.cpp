#include <iostream>
#include "BaseNpc.h"
#include "raymath.h"
#include "Astar/Domains/GoapDomain.h"
#include "Goap/Action.h"
#include "Goap/WorldState.h"
#include "BehaviourTree/Sequence.h"
#include "BehaviourTree/WaitNode.h"
#include "Extension/Extension.h"
#include "Goap/Goals/Npc/SafeGoal.h"
#include "Goap/Goals/Npc/Sleep.h"
#include "Goap/Goals/Npc/Work.h"
#include "World/Grid.h"

#define DEBUG 1

void BaseNpc::WorldStep(const std::shared_ptr<Astar<GridPos,GridDomain>>& astar)
{
    const bool wasDayTime = currentState.isDayTime;
    currentState.isDayTime = world->GetTimeState();

    if (currentState.isDayTime && !wasDayTime)
        currentState.hasSlept = false;

    if (!currentState.isDayTime && wasDayTime)
        currentState.hasWorked = false;

    currentState.location = Extension::ToLocation(world->GetZoneAt(position));

    goalPlanner->Update(currentState);
    const Goal* activeGoal = goalPlanner->GetActiveGoal();

    if (!activeGoal)
        return;

    auto statePlan = goapAstar->AstarAlgorithm(currentState, *activeGoal);

    if (statePlan.size() < 2)
        return;
    
#if DEBUG
    std::cout << "[" << name << "] Plan:";
    for (size_t i = 0; i + 1 < statePlan.size(); i++)
    {
        const Action* step = goapDomain->FindAction(statePlan[i], statePlan[i + 1]);
        std::cout << " " << (step ? step->name : "?");
    }
    std::cout << std::endl;
#endif
    
    const Action* nextAction = goapDomain->FindAction(statePlan[0], statePlan[1]);

    if (!nextAction)
        return;
    
#if DEBUG   
    std::cout << "[" << name << "] Executing: " << nextAction->name << std::endl;
#endif

    currentBehavior = behaviourTreeFactory->BuildBehaviorFor(this, nextAction);
    currentActionName = nextAction->name;
}

void BaseNpc::Update(const std::shared_ptr<Astar<GridPos, GridDomain>>& astar, const std::shared_ptr<RenderSystem>& renderer)
{
    if (currentBehavior)
    {
        BTContext ctx{ this, astar, renderer, GetFrameTime() };
        Status status = currentBehavior->Tick(ctx);

        if (status != Status::Running)
        {
            currentBehavior.reset();
            WorldStep(astar);
        }
    }
    else
    {
        PlayClip("Idle");
    }

    animator.Update(GetFrameTime());

    constexpr float offsetLerpSpeed = 8.0f;
    workOffset = Vector2Lerp(workOffset, targetWorkOffset, Clamp(GetFrameTime() * offsetLerpSpeed, 0.0f, 1.0f));
}

void BaseNpc::UpdateDraw() const
{
    animator.Draw(Vector2Add(actualPosition, workOffset));
}

void BaseNpc::Start(const std::shared_ptr<World>& world, std::vector<Action> actions)
{
    for (auto& action : actions)
        if (action.name == "SearchDanger") action.cost = Clamp(action.cost - npcBehaviour.courage,0 , 100);

    this->world = world;
    behaviourTreeFactory = std::make_unique<BehaviourTreeFactory>(world);
    goalPlanner = std::make_unique<GoalPlanner>(std::vector{ SleepGoal(), WorkGoal(), SafeGoal() });
    goapDomain = std::make_unique<GoapDomain>(actions);
    goapAstar = std::make_unique<Astar<WorldState, GoapDomain, Goal>>(*goapDomain);
}

void BaseNpc::Replan(const std::shared_ptr<Astar<GridPos,GridDomain>>& astar)
{
    if (reservedTile)
        world->GetTile(reservedTile->row,reservedTile->col).isBusy = false;
    
    WorldStep(astar);
}

bool BaseNpc::BeginMove(GridPos targetPosition, const std::shared_ptr<Astar<GridPos,GridDomain>>& astar)
{
    auto path = astar->AstarAlgorithm(position, targetPosition);
    
    currentPath = BuildSplinePath(path, world);
    segmentIndex = 0;
    segmentTimer = 0.0f;
    catchUpFrom = actualPosition;
    catchingUp = currentPath.SegmentCount() > 0;
    targetWorkOffset = {};

    return !currentPath.IsEmpty();
}

bool BaseNpc::BeginMove(ZoneType targetZone, const std::shared_ptr<Astar<GridPos,GridDomain>>& astar)
{
    auto approach = world->GetApproachTarget(targetZone, position);
        
    if (!approach.has_value())
        return false;
    
    auto path = astar->AstarAlgorithm(position, approach.value());
    
    if (targetZone != ZoneType::Empty && targetZone != ZoneType::Barn)
    {
        reservedTile = approach.value();
        
        world->GetTile(reservedTile->row,reservedTile->col).isBusy = true;
    }
    
    currentPath = BuildSplinePath(path, world);
    segmentIndex = 0;
    segmentTimer = 0.0f;
    catchUpFrom = actualPosition;
    catchingUp = currentPath.SegmentCount() > 0;
    targetWorkOffset = {};

    return !currentPath.IsEmpty();
}

bool BaseNpc::IsMoving() const
{
    return !currentPath.IsEmpty();
}

void BaseNpc::AdvanceMove(float deltaTime)
{
    if (currentPath.IsEmpty())
        return;

    if (currentPath.SegmentCount() == 0)
    {
        position = currentPath.NodeAt(0);

        const Vector2 delta = Vector2Subtract(currentPath.NodeWorldPosition(0), actualPosition);
        animator.SetDirection(delta);
        if (delta.x != 0.0f || delta.y != 0.0f)
            lastMoveDirection = delta;

        actualPosition = currentPath.NodeWorldPosition(0);
        currentPath = SplinePath{};
        return;
    }

    segmentTimer += deltaTime;
    float t = segmentTimer / SEGMENT_DURATION;

    Vector2 npcPosition;

    if (catchingUp)
    {
        if (t >= 1.0f)
        {
            t = 1.0f;
            catchingUp = false;
            segmentTimer = 0.0f;
        }

        Vector2 graphStart = currentPath.Evaluate(0, 0.0f);
        npcPosition = Vector2Lerp(catchUpFrom, graphStart, t);
    }
    else
    {
        if (t >= 1.0f)
        {
            t = 1.0f;
            position = currentPath.NodeAt(segmentIndex + 1);

            if (segmentIndex + 1 < currentPath.SegmentCount())
            {
                segmentIndex++;
                segmentTimer = 0.0f;
                t = 0.0f;
            }
        }

        npcPosition = currentPath.Evaluate(segmentIndex, t);
    }

    const Vector2 delta = Vector2Subtract(npcPosition, actualPosition);
    animator.SetDirection(delta);
    if (delta.x != 0.0f || delta.y != 0.0f)
        lastMoveDirection = delta;

    actualPosition = npcPosition;

    const bool reachedEnd = !catchingUp && (segmentIndex + 1 == currentPath.SegmentCount()) && t >= 1.0f;

    if (reachedEnd)
        currentPath = SplinePath{};
}

void BaseNpc::ApplyActionEffect(const Action* action)
{
    currentState = action->Apply(currentState);
}

void BaseNpc::FaceZone(ZoneType zone)
{
    auto nearest = world->GetNearestTileOfType(zone, position);

    if (!nearest.has_value())
        return;

    animator.SetDirection(Vector2Subtract(Grid::ToScreen(nearest.value()), Grid::ToScreen(position)));
}

void BaseNpc::SetPosition(Vector2 newPosition)
{
    actualPosition = newPosition;
    auto newGridPosition = Grid::ToGrid(actualPosition);
    position = GridPos(Clamp(newGridPosition.row,0,world->GetWorldWidth() - 1),Clamp(newGridPosition.col,0,world->GetWorldHeight() - 1));
}

void BaseNpc::SetDraggedState(bool state)
{
    currentState.isDragged = state;
}

void BaseNpc::SetDangerState(bool state)
{
    currentState.isInDanger = state;
}

Tile& BaseNpc::GetCurrentTile() const
{
    return world->GetTile(position.row, position.col);
}
