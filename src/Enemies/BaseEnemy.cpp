#include "BaseEnemy.h"

void BaseEnemy::Init(std::shared_ptr<World> world, Vector2 spawnPosition)
{
    this->world = std::move(world);
    position = spawnPosition;
}

void BaseEnemy::MoveToPosition(Vector2 newPosition)
{
}

void BaseEnemy::Reset()
{
}
