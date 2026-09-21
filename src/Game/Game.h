#ifndef WILDLIFESIM_GAME_H
#define WILDLIFESIM_GAME_H

#include <memory>
#include "Astar/Astar.h"
#include "Astar/Domains/GridDomain.h"
#include "Camera/CameraController.h"
#include "EventBus/EventBus.h"
#include "Input/InputSystem.h"
#include "NPC/BaseNpc.h"
#include "Player/ObjectMoveSystem.h"
#include "Player/PlayerInteractSystem.h"
#include "Player/SwitchModeSystem.h"
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

    std::shared_ptr<PlayerInteractSystem> playerInteractSystem;
    std::shared_ptr<InteractModeState> interactModeState;
    std::shared_ptr<CameraController> cameraController;
    std::shared_ptr<Astar<GridPos,GridDomain>> astar;
    std::shared_ptr<InputSystem> inputSystem;
    std::shared_ptr<RenderSystem> renderer;
    std::shared_ptr<TimeSystem> timeSystem;
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<World> world;
    
    std::vector<std::shared_ptr<BaseNpc>> GetNpc() { return baseNpcs; }

public:
    Game() = default;
    
    void Start();
    void Update();
};

#endif
