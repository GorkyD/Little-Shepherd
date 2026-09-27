#ifndef WILDLIFESIM_ENGAGETHREATSEQUENCE_H
#define WILDLIFESIM_ENGAGETHREATSEQUENCE_H

#include <algorithm>
#include <cmath>
#include "Node.h"
#include "Enemies/Wolf.h"
#include "Goap/Action.h"
#include "Npc/BaseNpc.h"

class EngageThreatSequence : public Node
{
    const Action* action;

    static constexpr int AttackDamage = 12;
    static constexpr const char* AttackClip = "SwordAttack_Sword";

public:
    explicit EngageThreatSequence(const Action* action) : action(action) {}

    Status Tick(BTContext& ctx) override
    {
        auto threat = ctx.npc->GetKnownThreat();

        if (!threat)
        {
            ctx.npc->ReleaseReservedTile();
            return Status::Failure;
        }

        if (threat->IsDead())
        {
            ctx.npc->ReleaseReservedTile();
            ctx.npc->ClearKnownThreat();
            ctx.npc->ApplyActionEffect(action);
            return Status::Success;
        }

        const GridPos threatPos = threat->GetPosition();
        const int distance = std::max(std::abs(threatPos.row - ctx.npc->position.row), std::abs(threatPos.col - ctx.npc->position.col));

        if (distance <= 1)
        {
            ctx.npc->ClaimCombatTile();
            ctx.npc->PlayClip(AttackClip);
            ctx.npc->FacePosition(threatPos);

            if (ctx.npc->ConsumeAttackTick())
                threat->TakeDamage(AttackDamage);

            return Status::Running;
        }

        ctx.npc->ReleaseReservedTile();

        if (!ctx.npc->IsMoving())
        {
            if (!ctx.npc->BeginApproachMove(threatPos, ctx.astar))
            {
                ctx.npc->ClearKnownThreat();
                return Status::Failure;
            }
        }

        ctx.npc->PlayClip(ctx.npc->GetWorkClipFor(action));
        ctx.npc->AdvanceMove(ctx.deltaTime);
        return Status::Running;
    }
};

#endif
