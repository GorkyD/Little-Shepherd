#include "Game.h"
#include <algorithm>
#include <functional>
#include <memory>
#include "Astar/Astar.h"
#include "Astar/Domains/GridDomain.h"
#include "EventBus/EventBus.h"
#include "Goap/Actions/Fisherman/Fish.h"
#include "Goap/Actions/Fisherman/MoveToWater.h"
#include "Goap/Actions/General/MoveToBarn.h"
#include "Goap/Actions/General/Sleep.h"
#include "Goap/Actions/FieldWorker/MoveToField.h"
#include "Goap/Actions/FieldWorker/WorkOnField.h"
#include "Goap/Actions/General/ExtinguishFire.h"
#include "Goap/Actions/General/GetWater.h"
#include "Goap/Actions/General/RunAwayFromDanger.h"
#include "Goap/Actions/General/RunAwayFromFire.h"
#include "Goap/Actions/General/SearchDanger.h"
#include "Goap/Actions/General/WaitUntilPlaced.h"
#include "Goap/Actions/WoodCutter/ChopWood.h"
#include "Goap/Actions/WoodCutter/MoveToForest.h"
#include "Input/InputStrategy/PcInputStrategy.h"
#include "NPC/BaseNpc.h"
#include "Npc/Farmer.h"
#include "Npc/Fisherman.h"
#include "NPC/WoodCutter.h"
#include "Player/ObjectMoveSystem.h"
#include "Player/SwitchModeSystem.h"
#include "Render/RenderSystem.h"
#include "Render/Background/ProceduralBackground.h"
#include "Window/Window.h"
#include "World/Grid.h"
#include "World/World.h"

void Game::Start()
{
    InitWindow();
    InitWorld();
    InitPathfinding();
    InitNpcs();
    InitTimeSystem();
    InitCamera();
    InitInteractMode();
    InitHud();
    InitPlayerInteraction();
}

void Game::InitWindow()
{
    auto window = std::make_shared<Window>();
    window->InitializeWindow();

    inputSystem = std::make_shared<InputSystem>(std::make_unique<PcInputStrategy>());
}

void Game::InitWorld()
{
    world = std::make_shared<World>();
    world->SetMap(ASSETS_DIR "Maps/Map.txt");
    world->SetZoneEntrance(ZoneType::Barn, GridPos{12, 5});

    for (const auto& tile : world->GetZoneAdjacentWalkableTiles(ZoneType::Water))
        world->SetZoneEntrance(ZoneType::Water, tile);

    renderer = std::make_shared<RenderSystem>(world);
}

void Game::InitPathfinding()
{
    eventBus = std::make_shared<EventBus>();

    GridDomain domain = GridDomain(world);
    astar = std::make_shared<Astar<GridPos,GridDomain>>(domain);
}

void Game::InitNpcs()
{
    auto startPoint = world->GetApproachTarget(ZoneType::Barn, GridPos(0, 0));

    baseNpcs.push_back(std::make_shared<Farmer>(startPoint.value(), "Farmer1", "Brave"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter1", "Coward"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter2", "Brave"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter3", "Brave"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter4", "Brave"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter5"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter6"));
    baseNpcs.push_back(std::make_shared<Fisherman>(startPoint.value(), "Fisherman1"));

    std::vector<Action> fieldWorkerActions = std::vector{MoveToBarn(), MoveToField(), Sleep(), WorkOnField(), WaitUntilPlaced(), RunAwayFromDanger(), SearchDanger(), GetWater(), ExtinguishFire(), RunAwayFromFire()};
    std::vector<Action> forestWorkerActions = std::vector{MoveToBarn(), MoveToForest(), Sleep(), ChopWood(), WaitUntilPlaced(), RunAwayFromDanger(), SearchDanger(), GetWater(), ExtinguishFire(), RunAwayFromFire()};
    std::vector<Action> fishermanActions = std::vector{MoveToBarn(), MoveToWater(), Sleep(), Fish(), WaitUntilPlaced(), RunAwayFromDanger(), SearchDanger(), GetWater(), ExtinguishFire(), RunAwayFromFire()};

    baseNpcs[0]->Start(world, fieldWorkerActions);
    baseNpcs[1]->Start(world, forestWorkerActions);
    baseNpcs[2]->Start(world,forestWorkerActions);
    baseNpcs[3]->Start(world, forestWorkerActions);
    baseNpcs[4]->Start(world, forestWorkerActions);
    baseNpcs[5]->Start(world,forestWorkerActions);
    baseNpcs[6]->Start(world, forestWorkerActions);
    baseNpcs[7]->Start(world,fishermanActions);

    for (const auto& npc : baseNpcs)
    {
        world->RegisterAgent(npc);

        eventBus->Subscribe(EventType::OnDayTimeChange, npc,[&](const std::shared_ptr<BaseNpc>& self)
        {
            if (!self->IsHandlingEmergency())
                self->Replan(astar);
        });
    }
}

void Game::InitTimeSystem()
{
    timeSystem = std::make_shared<TimeSystem>(world, eventBus);
    timeSystem->Start();
}

void Game::InitCamera()
{
    cameraController = std::make_shared<CameraController>(inputSystem);
    cameraController->Start(*world);
}

void Game::InitInteractMode()
{
    interactModeState = std::make_shared<InteractModeState>();
    interactModeState->SetCurrentType(InteractType::Drag);

    switchModeSystem = std::make_unique<SwitchModeSystem>(interactModeState, inputSystem, eventBus);
}

void Game::InitHud()
{
    proceduralBackground = std::make_unique<ProceduralBackground>(timeSystem, world);
    hudSystem = std::make_unique<HudSystem>(interactModeState);
    npcStatusIconSystem = std::make_unique<NpcStatusIconSystem>();
}

void Game::InitPlayerInteraction()
{
    playerInteractSystem = std::make_shared<PlayerInteractSystem>(interactModeState,cameraController, inputSystem, GetNpc(), astar, world, wolves);
    playerInteractSystem->OnInteractSystemSelect();

    eventBus->Subscribe(EventType::OnPlayerInteractModeChange, playerInteractSystem,[&](const std::shared_ptr<PlayerInteractSystem>& self){ self->OnInteractSystemSelect(); });
}

void Game::Update()
{
    UpdateSystems();
    UpdateBackgroundAndHud();

    BeginMode2D(cameraController->Get());

    renderer->Update();

    DepthSortedRenderer sceneQueue;

    const bool anyoneSleeping = UpdateNpcs(sceneQueue);
    UpdateWolves(sceneQueue);
    QueueTrees(sceneQueue);
    QueueBarn(sceneQueue, anyoneSleeping);

    sceneQueue.Flush();

    if (showSensorDebug)
        DrawSensorDebug();

    playerInteractSystem->UpdateCurrentInteractable();

    EndMode2D();
}

void Game::UpdateSystems()
{
    cameraController->Update();
    timeSystem->Update();
    switchModeSystem->Update();

    if (IsKeyPressed(KEY_F1))
        showSensorDebug = !showSensorDebug;
}

void Game::UpdateBackgroundAndHud()
{
    proceduralBackground->DrawProceduralBackground();
    hudSystem->Update();
}

bool Game::UpdateNpcs(DepthSortedRenderer& sceneQueue)
{
    bool anyoneSleeping = false;

    for (const auto& npc : baseNpcs)
    {
        npc->Update(astar, renderer);

        if (npc->GetCurrentActionName() == "Sleep")
            anyoneSleeping = true;

        sceneQueue.Add(npc->GetActualPosition().y, [this, npc]()
        {
            npc->UpdateDraw();
            npcStatusIconSystem->DrawFor(npc);
        });
    }

    return anyoneSleeping;
}

void Game::UpdateWolves(DepthSortedRenderer& sceneQueue)
{
    for (const auto& wolf : *wolves)
        wolf->Update(GetFrameTime(), astar, baseNpcs);

    for (const auto& wolf : *wolves)
        sceneQueue.Add(wolf->GetActualPosition().y, [wolf]() { wolf->Draw(); });

    std::erase_if(*wolves, [](const std::shared_ptr<Wolf>& wolf) { return wolf->IsReadyToRemove(); });
}

void Game::QueueTrees(DepthSortedRenderer& sceneQueue) const
{
    for (const auto& treePos : world->GetTilesOfType(ZoneType::Forest))
    {
        Tile& tile = world->GetTile(treePos.row, treePos.col);

        if (tile.treeVariant < 0)
            continue;

        const Vector2 center = Grid::ToScreen(treePos);

        sceneQueue.Add(center.y, [this, center, &tile]() { renderer->DrawTree(center, tile); });
    }
}

void Game::QueueBarn(DepthSortedRenderer& sceneQueue, const bool anyoneSleeping) const
{
    const auto barnAnchorY = renderer->GetBarnBuildingAnchorY();

    if (!barnAnchorY.has_value())
        return;

    sceneQueue.Add(*barnAnchorY, [this, anyoneSleeping]()
    {
        renderer->DrawBarnBuilding();

        if (anyoneSleeping)
            renderer->DrawSleepIndicator();
    });
}

void Game::DrawSensorDebug() const
{
    for (const auto& npc : baseNpcs)
        npc->DrawSensorDebug();
}
