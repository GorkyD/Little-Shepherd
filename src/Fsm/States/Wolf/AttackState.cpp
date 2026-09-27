#include "AttackState.h"
#include <algorithm>
#include <cmath>
#include "Enemies/Wolf.h"
#include "NPC/BaseNpc.h"

void AttackState::Update()
{
    wolf->PlayAttackClip();

    const auto target = wolf->GetTargetNpc().lock();
    auto* controller = wolf->GetController();

    if (!target)
    {
        controller->SetTargetLost(true);
        controller->SetInAttackRange(false);
        wolf->ReleaseReservedTile();
        return;
    }

    wolf->ClaimCombatTile();
    wolf->FaceTowards(target->position);

    const int distance = std::max(std::abs(target->position.row - wolf->GetPosition().row), std::abs(target->position.col - wolf->GetPosition().col));

    controller->SetTargetLost(distance > Wolf::SearchRadius * 2);
    controller->SetInAttackRange(distance <= Wolf::AttackRange);

    if (distance > Wolf::AttackRange)
        wolf->ReleaseReservedTile();
}
