#include "ObjectMoveSystem.h"

void ObjectMoveSystem::Update()
{
    if (currentStrategy == ObjectMoveStrategy::NpcDrag)
    {
        if (inputSystem->IsPointerActionDown(PointerInputAction::BasePointerClick))
        {
            bool collision = false;
            auto pointerWorldPos = GetScreenToWorld2D(inputSystem->GetPointerScreenPosition(), cameraController->Get());
            for (auto& npc : allNpcs)
            {
                collision = CheckCollisionPointCircle(pointerWorldPos, npc->GetActualPosition(), 100.0f);
                if (collision)
                {
                    if (draggedNpc != npc)
                    {
                        draggedNpc = npc;
                        std::cout << draggedNpc->name << std::endl;
                        break;
                    }
                }
            }
        }
        
        if (draggedNpc)
        {
            auto pointerWorldPos = GetScreenToWorld2D(inputSystem->GetPointerScreenPosition(), cameraController->Get());
            draggedNpc->SetDraggedState(true);
            draggedNpc->SetDangerState(true);
            draggedNpc->SetPosition(pointerWorldPos);
            draggedNpc->Replan(astar);
            
            if (inputSystem->IsPointerActionUnPressed(PointerInputAction::BasePointerClick))
            {
                draggedNpc->SetDraggedState(false);
                draggedNpc->Replan(astar);
                draggedNpc = nullptr;
            }
        }
    }
}
