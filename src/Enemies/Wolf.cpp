#include "Wolf.h"
#include "raymath.h"
#include "Fsm/StateMachineControllers/WolfStateMachineController.h"
#include "Fsm/States/Wolf/IdleState.h"
#include "World/Grid.h"

Wolf::Wolf() : animator("IsometricEnemies/Wolf", "Wolf_", 80.0f)
{
    controller = std::make_unique<WolfStateMachineController>(this);
    controller->Initialize();
}

Wolf::~Wolf() = default;

void Wolf::Init(std::shared_ptr<World> world, GridPos spawnPosition)
{
    BaseEnemy::Init(std::move(world), spawnPosition);
    targetNpc.reset();
    animator.SetClip("Move_Dark");
}

void Wolf::Reset()
{
    BaseEnemy::Reset();
    targetNpc.reset();
}

void Wolf::Update(const float dt, const std::shared_ptr<Astar<GridPos, GridDomain>>& astar, const std::vector<std::shared_ptr<BaseNpc>>& npcs)
{
    frameAstar = astar;
    frameNpcs = &npcs;

    controller->SetIsDead(IsDead());
    controller->Update();

    AdvanceMove(dt);
    animator.SetDirection(GetLastMoveDirection());
    animator.Update(dt);
}

void Wolf::Draw() const
{
    animator.Draw(GetActualPosition());

    if (IsDead())
        return;

    constexpr float barWidth = 40.0f;
    constexpr float barHeight = 5.0f;
    constexpr float yOffset = -100.0f;

    const float ratio = GetMaxHealth() > 0 ? static_cast<float>(GetHealth()) / static_cast<float>(GetMaxHealth()) : 0.0f;
    const Vector2 pos = GetActualPosition();
    const float left = pos.x - barWidth / 2.0f;
    const float top = pos.y + yOffset;

    DrawRectangle(static_cast<int>(left), static_cast<int>(top), static_cast<int>(barWidth), static_cast<int>(barHeight), DARKGRAY);
    DrawRectangle(static_cast<int>(left), static_cast<int>(top), static_cast<int>(barWidth * ratio), static_cast<int>(barHeight), RED);
    DrawRectangleLines(static_cast<int>(left), static_cast<int>(top), static_cast<int>(barWidth), static_cast<int>(barHeight), BLACK);
}

std::optional<GridPos> Wolf::FindApproachTileNear(GridPos target) const
{
    return world->GetWalkableNeighbor(target, position);
}

void Wolf::FaceTowards(GridPos target)
{
    animator.SetDirection(Vector2Subtract(Grid::ToScreen(target), Grid::ToScreen(position)));
}
