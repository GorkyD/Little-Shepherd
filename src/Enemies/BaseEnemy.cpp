#include "BaseEnemy.h"
#include "raymath.h"
#include "World/Grid.h"

void BaseEnemy::Init(std::shared_ptr<World> world, GridPos spawnPosition)
{
    this->world = std::move(world);
    position = spawnPosition;
    actualPosition = Grid::ToScreen(spawnPosition);
    currentPath = SplinePath{};
    segmentIndex = 0;
    segmentTimer = 0.0f;
    currentHealth = maxHealth;
    dead = false;
    readyToRemove = false;
}

void BaseEnemy::Reset()
{
    ReleaseReservedTile();
    currentPath = SplinePath{};
    currentHealth = maxHealth;
    dead = false;
    readyToRemove = false;
}

bool BaseEnemy::BeginMove(GridPos target, const std::shared_ptr<Astar<GridPos, GridDomain>>& astar)
{
    auto path = astar->AstarAlgorithm(position, target);
    currentPath = BuildSplinePath(path, world);
    segmentIndex = 0;
    segmentTimer = 0.0f;
    catchUpFrom = actualPosition;
    catchingUp = currentPath.SegmentCount() > 0;
    return !currentPath.IsEmpty();
}

void BaseEnemy::AdvanceMove(const float dt)
{
    if (currentPath.IsEmpty())
        return;

    if (currentPath.SegmentCount() == 0)
    {
        position = currentPath.NodeAt(0);
        actualPosition = currentPath.NodeWorldPosition(0);
        currentPath = SplinePath{};
        return;
    }

    segmentTimer += dt;
    float t = segmentTimer / SegmentDuration;

    Vector2 newPos;

    if (catchingUp)
    {
        if (t >= 1.0f)
        {
            t = 1.0f;
            catchingUp = false;
            segmentTimer = 0.0f;
        }

        const Vector2 graphStart = currentPath.Evaluate(0, 0.0f);
        newPos = Vector2Lerp(catchUpFrom, graphStart, t);
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

        newPos = currentPath.Evaluate(segmentIndex, t);
    }

    const Vector2 delta = Vector2Subtract(newPos, actualPosition);

    if (delta.x != 0.0f || delta.y != 0.0f)
        lastMoveDirection = delta;

    actualPosition = newPos;

    const bool reachedEnd = !catchingUp && (segmentIndex + 1 == currentPath.SegmentCount()) && t >= 1.0f;

    if (reachedEnd)
        currentPath = SplinePath{};
}

void BaseEnemy::StopMoving()
{
    currentPath = SplinePath{};
}

bool BaseEnemy::IsMoving() const
{
    return !currentPath.IsEmpty();
}

void BaseEnemy::ClaimCombatTile()
{
    if (reservedTile && *reservedTile == position)
        return;

    ReleaseReservedTile();

    reservedTile = position;
    world->GetTile(position.row, position.col).isBusy = true;
}

void BaseEnemy::ReleaseReservedTile()
{
    if (reservedTile)
    {
        world->GetTile(reservedTile->row, reservedTile->col).isBusy = false;
        reservedTile.reset();
    }
}

void BaseEnemy::TakeDamage(const int amount)
{
    if (dead)
        return;

    currentHealth -= amount;

    if (currentHealth <= 0)
    {
        currentHealth = 0;
        dead = true;
    }
}
