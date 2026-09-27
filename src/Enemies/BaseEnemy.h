#ifndef WILDLIFESIM_BASEENEMY_H
#define WILDLIFESIM_BASEENEMY_H

#include <memory>
#include <optional>
#include "raylib.h"
#include "Astar/Astar.h"
#include "Astar/Domains/GridDomain.h"
#include "Astar/SplinePath.h"
#include "World/GridPos.h"
#include "World/World.h"

class BaseEnemy
{
protected:
    static constexpr float SegmentDuration = 1.0f;

    std::optional<GridPos> reservedTile;
    std::shared_ptr<World> world;

    SplinePath currentPath;
    GridPos position{};
    size_t segmentIndex = 0;

    Vector2 lastMoveDirection{ 0.0f, 1.0f };
    Vector2 actualPosition{};
    Vector2 catchUpFrom{};

    float segmentTimer = 0.0f;
    bool catchingUp = false;
    
    int currentHealth = 0;
    int maxHealth = 100;
    
    bool readyToRemove = false;
    bool dead = false;

public:
    BaseEnemy() = default;
    virtual ~BaseEnemy() = default;

    virtual void Init(std::shared_ptr<World> world, GridPos spawnPosition);
    virtual void Reset();

    bool BeginMove(GridPos target, const std::shared_ptr<Astar<GridPos,GridDomain>>& astar);
    void AdvanceMove(float dt);
    void TakeDamage(int amount);
    void ReleaseReservedTile();
    void ClaimCombatTile();
    void StopMoving();
    void MarkReadyToRemove() { readyToRemove = true; }

    GridPos GetPosition() const { return position; }
    Vector2 GetLastMoveDirection() const { return lastMoveDirection; }
    Vector2 GetActualPosition() const { return actualPosition; }

    int GetHealth() const { return currentHealth; }
    int GetMaxHealth() const { return maxHealth; }

    bool IsReadyToRemove() const { return readyToRemove; }
    bool IsDead() const { return dead; }
    bool IsMoving() const;
};

#endif
