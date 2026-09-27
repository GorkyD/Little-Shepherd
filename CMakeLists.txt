cmake_minimum_required(VERSION 4.3)
project(WildlifeSim)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        WildlifeSim main.cpp
        src/Astar/Astar.h
        src/EventBus/EventBus.cpp
        src/EventBus/EventBus.h
        src/EventBus/EventType.h
        src/World/Tile.h
        src/World/World.cpp
        src/World/World.h
        src/World/ZoneType.h
        src/World/GridPos.h
        src/World/Grid.h
        src/Camera/CameraController.h
        src/Camera/CameraController.cpp
        src/Fsm/Conditions/Transition.h
        src/Fsm/States/Wolf/IdleState.h
        src/Fsm/States/Wolf/IdleState.cpp
        src/Fsm/States/Wolf/SearchingState.h
        src/Fsm/States/Wolf/SearchingState.cpp
        src/Fsm/States/Wolf/ChaseState.h
        src/Fsm/States/Wolf/ChaseState.cpp
        src/Fsm/States/Wolf/AttackState.h
        src/Fsm/States/Wolf/AttackState.cpp
        src/Fsm/States/Wolf/DeathState.h
        src/Fsm/States/Wolf/DeathState.cpp
        src/Fsm/States/State.h
        src/Fsm/StateId.h
        src/Fsm/StateMachine.h
        src/Fsm/StateMachine.cpp
        src/Fsm/StateMachineControllers/Base/StateMachineController.h
        src/World/GlobalWorldState.h
        src/Render/RenderSystem.cpp
        src/Render/RenderSystem.h
        src/Render/SpriteSheet.h
        src/Render/SpriteSheet.cpp
        src/Render/CharacterAnimator.h
        src/Render/CharacterAnimator.cpp
        src/Render/TileAtlas.h
        src/Render/TileAtlas.cpp
        src/Render/DepthSortedRenderer.h
        src/Render/NpcStatusIconSystem.h
        src/Render/NpcStatusIconSystem.cpp
        src/NPC/BaseNpc.h
        src/Enemies/Wolf.cpp
        src/Enemies/Wolf.h
        src/Enemies/BaseEnemy.h
        src/Enemies/BaseEnemy.cpp
        src/Npc/WoodCutter.cpp
        src/Npc/WoodCutter.h
        src/Npc/Farmer.cpp
        src/Npc/Farmer.h
        src/ObjectPool/ObjectPool.h
        src/ObjectPool/Poolable.h
        src/Fsm/StateMachineControllers/WolfStateMachineController.cpp
        src/Fsm/StateMachineControllers/WolfStateMachineController.h
        src/Fsm/States/Wolf/WolfState.h
        src/Fsm/StateMachineControllers/Base/StateMachineController.cpp
        src/Enemies/BaseEnemy.cpp
        src/Astar/Domains/GridDomain.cpp
        src/Astar/Domains/GridDomain.h
        src/Astar/Domains/GoapDomain.cpp
        src/Astar/Domains/GoapDomain.h
        src/Astar/SplinePath.h
        src/Astar/SplinePath.cpp
        src/Game/Game.cpp
        src/Game/Game.h
        src/Window/Window.cpp
        src/Window/Window.h
        src/NPC/BaseNpc.cpp
        src/World/TimeSystem/TimeSystem.cpp
        src/World/TimeSystem/TimeSystem.h
        src/Goap/Action.h
        src/Goap/WorldState.h
        src/Goap/Goal.h
        src/Goap/Goal.cpp
        src/Goap/WorldState.cpp
        src/Goap/Action.cpp
        src/Goap/Actions/General/MoveToBarn.h
        src/Goap/Actions/General/Sleep.h
        src/Goap/Actions/FieldWorker/MoveToField.h
        src/Goap/Actions/FieldWorker/WorkOnField.h
        src/Goap/Goals/Npc/Sleep.h
        src/Goap/Goals/Npc/Work.h
        src/Goap/Actions/WoodCutter/MoveToForest.h
        src/Goap/Actions/WoodCutter/ChopWood.h
        src/Goap/Actions/Fisherman/MoveToWater.h
        src/Goap/Actions/Fisherman/Fish.h
        src/Goap/Goals/GoalPlanner.cpp
        src/Goap/Goals/GoalPlanner.h
        src/BehaviourTree/Node.h
        src/BehaviourTree/Sequence.h
        src/BehaviourTree/WaitNode.h
        src/BehaviourTree/ApplyEffectNode.h
        src/BehaviourTree/MoveToNode.h
        src/Render/Background/ProceduralBackground.h
        src/Npc/Fisherman.cpp
        src/Npc/Fisherman.h
        src/Npc/NpcBehaviourConfig.h
        src/Npc/NpcBehaviourConfig.cpp
        src/BehaviourTree/BehaviourTreeFactory.cpp
        src/BehaviourTree/BehaviourTreeFactory.h
        src/Extension/Extension.h
        src/Render/Hud/HudSystem.cpp
        src/Render/Hud/HudSystem.h
        src/Input/InputSystem.cpp
        src/Input/InputSystem.h
        src/Input/InputStrategy/InputStrategy.h
        src/Input/InputStrategy/PcInputStrategy.h
        src/Input/InputAction.h
        src/Player/ObjectMoveSystem.cpp
        src/Player/ObjectMoveSystem.h
        src/Goap/Goals/Npc/SafeGoal.h
        src/Goap/Actions/General/WaitUntilPlaced.h
        src/Goap/Actions/General/RunAwayFromDanger.h
        src/Goap/Actions/General/RunAwayFromFire.h
        src/Goap/Actions/General/SearchDanger.h
        src/BehaviourTree/TimedWaitNode.h
        src/BehaviourTree/MoveToRandomNode.h
        src/BehaviourTree/Selector.h
        "src/BehaviourTree/CheckForThreatNode .h"
        src/BehaviourTree/EngageThreatSequence.h
        src/Player/PlayerInteractSystem.cpp
        src/Player/PlayerInteractSystem.h
        src/Player/BaseInteractSystem.h
        src/Player/FireObjectSystem.cpp
        src/Player/FireObjectSystem.h
        src/Player/WaterObjectSystem.cpp
        src/Player/WaterObjectSystem.h
        src/Player/SpawnMobSystem.cpp
        src/Player/SpawnMobSystem.h
        src/Player/InteractType.h
        src/Player/SwitchModeSystem.cpp
        src/Player/SwitchModeSystem.h
        src/Player/InteractModeState.h
        src/Goap/Goals/Npc/Extinguish.h
        src/Goap/Actions/General/GetWater.h
        src/Goap/Actions/General/ExtinguishFire.h
        src/BehaviourTree/ExtinguishFireNode.h
        src/Npc/Sensors/Sensor.h
        src/Npc/Sensors/VisualSensor.h
        src/Npc/Sensors/VisualSensor.cpp
)

target_compile_definitions(WildlifeSim PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/Assets/")

target_include_directories(WildlifeSim PRIVATE src)
target_link_libraries(WildlifeSim raylib)
