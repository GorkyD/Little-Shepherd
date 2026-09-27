#include "SearchingState.h"
#include <algorithm>
#include <cmath>
#include "Enemies/Wolf.h"
#include "NPC/BaseNpc.h"

void SearchingState::Update()
{
    wolf->PlayMoveClip();

    const auto* npcs = wolf->GetFrameNpcs();

    if (!npcs)
    {
        wolf->GetController()->SetEnemyOnSight(false);
        return;
    }

    std::shared_ptr<BaseNpc> nearest;
    int bestDistance = 0;

    for (const auto& npc : *npcs)
    {
        const int distance = std::max(std::abs(npc->position.row - wolf->GetPosition().row), std::abs(npc->position.col - wolf->GetPosition().col));

        if (distance > Wolf::SearchRadius)
            continue;

        if (!nearest || distance < bestDistance)
        {
            nearest = npc;
            bestDistance = distance;
        }
    }

    if (nearest)
    {
        wolf->SetTargetNpc(nearest);
        wolf->GetController()->SetEnemyOnSight(true);
    }
    else
    {
        wolf->GetController()->SetEnemyOnSight(false);
    }
}
