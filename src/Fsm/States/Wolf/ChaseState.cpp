#include "ChaseState.h"
#include <algorithm>
#include <cmath>
#include "Enemies/Wolf.h"
#include "NPC/BaseNpc.h"

void ChaseState::Update()
{
    const auto target = wolf->GetTargetNpc().lock();
    auto* controller = wolf->GetController();

    if (!target)
    {
        controller->SetTargetLost(true);
        controller->SetInAttackRange(false);
        wolf->ReleaseReservedTile();
        wolf->StopMoving();
        hasPathTarget = false;
        return;
    }

    const int distance = std::max(std::abs(target->position.row - wolf->GetPosition().row), std::abs(target->position.col - wolf->GetPosition().col));

    if (distance > Wolf::SearchRadius * 2)
    {
        wolf->ClearTargetNpc();
        controller->SetTargetLost(true);
        controller->SetInAttackRange(false);
        wolf->ReleaseReservedTile();
        wolf->StopMoving();
        hasPathTarget = false;
        return;
    }

    controller->SetTargetLost(false);

    if (distance <= Wolf::AttackRange)
    {
        controller->SetInAttackRange(true);
        wolf->StopMoving();
        hasPathTarget = false;
        return;
    }

    controller->SetInAttackRange(false);
    wolf->ReleaseReservedTile();

    if (!wolf->IsMoving() || !hasPathTarget || !(pathTarget == target->position))
    {
        auto approach = wolf->FindApproachTileNear(target->position);

        if (approach.has_value() && wolf->GetFrameAstar() && wolf->BeginMove(*approach, wolf->GetFrameAstar()))
        {
            pathTarget = target->position;
            hasPathTarget = true;
        }
        else
        {
            hasPathTarget = false;
        }
    }

    wolf->PlayMoveClip();
}
