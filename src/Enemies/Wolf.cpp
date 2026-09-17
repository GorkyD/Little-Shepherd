#include "Wolf.h"

Wolf::Wolf()
{
}

void Wolf::Init(std::shared_ptr<World> world, Vector2 spawnPosition)
{
    BaseEnemy::Init(world, spawnPosition);
}

void Wolf::MoveToPosition(Vector2 newPosition)
{
    BaseEnemy::MoveToPosition(newPosition);
}

void Wolf::Reset()
{
    BaseEnemy::Reset();
}
