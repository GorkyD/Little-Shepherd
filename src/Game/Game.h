#ifndef WILDLIFESIM_GAME_H
#define WILDLIFESIM_GAME_H

#include <memory>
#include "Astar/Astar.h"
#include "Astar/Domains/GridDomain.h"
#include "Camera/CameraController.h"
#include "Enemies/Wolf.h"
#include "EventBus/EventBus.h"
#include "Input/InputSystem.h"
#include "NPC/BaseNpc.h"
#include "Player/PlayerInteractSystem.h"
#include "Player/SwitchModeSystem.h"
#include "Render/DepthSortedRenderer.h"
#include "Render/RenderSystem.h"
#include "Render/Background/ProceduralBackground.h"
#include "Render/Hud/HudSystem.h"
#include "Render/NpcStatusIconSystem.h"
#include "World/TimeSystem/TimeSystem.h"

class Game
{
    std::unique_ptr<ProceduralBackground> proceduralBackground;
    std::unique_ptr<SwitchModeSystem> switchModeSystem;
    std::unique_ptr<HudSystem> hudSystem;
    std::unique_ptr<NpcStatusIconSystem> npcStatusIconSystem;

    std::vector<std::shared_ptr<BaseNpc>> baseNpcs;
    std::shared_ptr<std::vector<std::shared_ptr<Wolf>>> wolves = std::make_shared<std::vector<std::shared_ptr<Wolf>>>();

    std::shared_ptr<PlayerInteractSystem> playerInteractSystem;
    std::shared_ptr<InteractModeState> interactModeState;
    std::shared_ptr<CameraController> cameraController;
    std::shared_ptr<Astar<GridPos,GridDomain>> astar;
    std::shared_ptr<InputSystem> inputSystem;
    std::shared_ptr<RenderSystem> renderer;
    std::shared_ptr<TimeSystem> timeSystem;
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<World> world;

    bool showSensorDebug = false;

    std::vector<std::shared_ptr<BaseNpc>> GetNpc() { return baseNpcs; }

    void InitWindow();
    void InitWorld();
    void InitPathfinding();
    void InitNpcs();
    void InitTimeSystem();
    void InitCamera();
    void InitInteractMode();
    void InitHud();
    void InitPlayerInteraction();

    void UpdateSystems();
    void UpdateBackgroundAndHud();
    bool UpdateNpcs(DepthSortedRenderer& sceneQueue);
    void UpdateWolves(DepthSortedRenderer& sceneQueue);
    void QueueTrees(DepthSortedRenderer& sceneQueue) const;
    void QueueBarn(DepthSortedRenderer& sceneQueue, bool anyoneSleeping) const;
    void DrawSensorDebug() const;

public:
    Game() = default;

    void Start();
    void Update();
};

#endif
