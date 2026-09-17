#ifndef WILDLIFESIM_BASEENEMY_H
#define WILDLIFESIM_BASEENEMY_H

#include <memory>
#include "raylib.h"
#include "World/World.h"

class BaseEnemy
{   
    std::shared_ptr<World> world;
    Vector2 position = {0,0};
    
    int currentHealth = 0;
    int maxHealth = 100;
public:
    BaseEnemy() = default;
    virtual ~BaseEnemy() = default;
    
    virtual void Init(std::shared_ptr<World> world, Vector2 spawnPosition);
    virtual void MoveToPosition(Vector2 newPosition);
    virtual void Reset();
};

#endif
