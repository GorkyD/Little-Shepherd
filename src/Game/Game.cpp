#include "Game.h"
#include <algorithm>
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
#include "Goap/Actions/General/RunAwayFromDanger.h"
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
#include "Render/RenderSystem.h"
#include "Render/Background/ProceduralBackground.h"
#include "Window/Window.h"
#include "World/Grid.h"
#include "World/World.h"

void Game::Start()
{
    auto window = std::make_shared<Window>();
    window->InitializeWindow();
    
    inputSystem = std::make_shared<InputSystem>(std::make_unique<PcInputStrategy>());
    
    world = std::make_shared<World>();
    world->SetMap(ASSETS_DIR "Maps/Map.txt");
    world->SetZoneEntrance(ZoneType::Barn, GridPos{12, 5});

    renderer = std::make_shared<RenderSystem>(world);
    
    eventBus = std::make_shared<EventBus>();
    
    GridDomain domain = GridDomain(world);
    astar = std::make_shared<Astar<GridPos,GridDomain>>(domain);
    
    auto startPoint = world->GetApproachTarget(ZoneType::Barn,GridPos(0,0));
    
    baseNpcs.push_back(std::make_shared<Farmer>(startPoint.value(), "Farmer1"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter1"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter2"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter3"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter4"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter5"));
    baseNpcs.push_back(std::make_shared<WoodCutter>(startPoint.value(), "WoodCutter6"));
    baseNpcs.push_back(std::make_shared<Fisherman>(startPoint.value(), "Fisherman1"));

    std::vector<Action> fieldWorkerActions = std::vector{MoveToBarn(), MoveToField(), Sleep(), WorkOnField(), WaitUntilPlaced(), RunAwayFromDanger(), SearchDanger()};
    std::vector<Action> forestWorkerActions = std::vector{MoveToBarn(), MoveToForest(), Sleep(), ChopWood(), WaitUntilPlaced(), RunAwayFromDanger(), SearchDanger()};
    std::vector<Action> fishermanActions = std::vector{MoveToBarn(), MoveToWater(), Sleep(), Fish(), WaitUntilPlaced(), RunAwayFromDanger(), SearchDanger()};

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
        eventBus->Subscribe(OnDayTimeChange, npc,[&](const std::shared_ptr<BaseNpc>& self)
        {
            self->Replan(astar);
        });
    }
    
    timeSystem = std::make_shared<TimeSystem>(world, eventBus);
    timeSystem->Start();

    const Vector2 c1 = Grid::ToScreen(0, 0);
    const Vector2 c2 = Grid::ToScreen(world->GetWorldWidth() - 1, 0);
    const Vector2 c3 = Grid::ToScreen(0, world->GetWorldHeight() - 1);
    const Vector2 c4 = Grid::ToScreen(world->GetWorldWidth() - 1, world->GetWorldHeight() - 1);

    const Vector2 boundsMin = { std::min({c1.x, c2.x, c3.x, c4.x}), std::min({c1.y, c2.y, c3.y, c4.y}) };
    const Vector2 boundsMax = { std::max({c1.x, c2.x, c3.x, c4.x}), std::max({c1.y, c2.y, c3.y, c4.y}) };

    cameraController = std::make_shared<CameraController>(inputSystem);
    cameraController->Start(boundsMin, boundsMax);
    
    proceduralBackground = std::make_unique<ProceduralBackground>(timeSystem, world);
    hudSystem = std::make_unique<HudSystem>();
    npcStatusIconSystem = std::make_unique<NpcStatusIconSystem>();
    
    objectMoveSystem = std::make_unique<ObjectMoveSystem>(cameraController, inputSystem, GetNpc(), astar);
}

void Game::Update()
{
    cameraController->Update();
    timeSystem->Update();
    objectMoveSystem->Update();

    proceduralBackground->DrawProceduralBackground();
    hudSystem->Update();

    BeginMode2D(cameraController->Get());

    renderer->Update();
    
    for (const auto& npc : baseNpcs)
        npc->Update(astar, renderer);
    
    std::ranges::sort(baseNpcs, 
    [](const std::shared_ptr<BaseNpc>& first, const std::shared_ptr<BaseNpc>& second)
    {
        return first->GetActualPosition().y < second->GetActualPosition().y;
    });
    
    for (const auto& npc : baseNpcs)
        npc->UpdateDraw();

    npcStatusIconSystem->Draw(baseNpcs);

    EndMode2D();
}
