#ifndef WILDLIFESIM_WOLF_H
#define WILDLIFESIM_WOLF_H

#include <memory>
#include <optional>
#include <vector>
#include "BaseEnemy.h"
#include "Astar/Astar.h"
#include "Astar/Domains/GridDomain.h"
#include "Fsm/StateMachineControllers/WolfStateMachineController.h"
#include "Render/CharacterAnimator.h"
#include "World/GridPos.h"

class BaseNpc;

class Wolf : public BaseEnemy, public std::enable_shared_from_this<Wolf>
{
    std::unique_ptr<WolfStateMachineController> controller;
    std::shared_ptr<Astar<GridPos, GridDomain>> frameAstar;
    const std::vector<std::shared_ptr<BaseNpc>>* frameNpcs = nullptr;
    std::weak_ptr<BaseNpc> targetNpc;

    CharacterAnimator animator;

public:
    static constexpr int SearchRadius = 6;
    static constexpr int AttackRange = 1;

    Wolf();
    ~Wolf() override;

    void Init(std::shared_ptr<World> world, GridPos spawnPosition) override;
    void Update(float dt, const std::shared_ptr<Astar<GridPos, GridDomain>>& astar, const std::vector<std::shared_ptr<BaseNpc>>& npcs);
    void Reset() override;
    void Draw() const;

    WolfStateMachineController* GetController() const { return controller.get(); }

    std::weak_ptr<BaseNpc> GetTargetNpc() const { return targetNpc; }
    void SetTargetNpc(std::weak_ptr<BaseNpc> npc) { targetNpc = std::move(npc); }
    void ClearTargetNpc() { targetNpc.reset(); }

    const std::vector<std::shared_ptr<BaseNpc>>* GetFrameNpcs() const { return frameNpcs; }
    const std::shared_ptr<Astar<GridPos, GridDomain>>& GetFrameAstar() const { return frameAstar; }
    std::optional<GridPos> FindApproachTileNear(GridPos target) const;

    void PlayMoveClip() { animator.SetClip("Move_Dark"); }
    void PlayAttackClip() { animator.SetClip("Attack_Dark"); }
    void PlayDeathClip() { animator.SetClip("Die_Dark", false); }
    bool IsDeathAnimationFinished() const { return animator.IsFinished(); }
    void FaceTowards(GridPos target);
};

#endif
