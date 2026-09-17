#ifndef WILDLIFESIM_WOLF_H
#define WILDLIFESIM_WOLF_H

#include "BaseEnemy.h"

class Wolf : public BaseEnemy
{
public:
    Wolf();
    void Init(std::shared_ptr<World> world, Vector2 spawnPosition) override;
    void MoveToPosition(Vector2 newPosition) override;
    void Reset() override;
};

#endif
