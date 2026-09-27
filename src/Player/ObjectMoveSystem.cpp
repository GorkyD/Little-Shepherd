#include "ObjectMoveSystem.h"

void ObjectMoveSystem::Start()
{
    
}

void ObjectMoveSystem::Update()
{
    const bool rawDown = inputSystem->IsPointerActionDown(PointerInputAction::BasePointerClick);

    if (rawDown == confirmedButtonDown)
        agreementStreak = 0;
    else if (++agreementStreak >= ConfirmFrames)
    {
        confirmedButtonDown = rawDown;
        agreementStreak = 0;
    }

    if (!draggedNpc && confirmedButtonDown)
    {
        bool collision = false;
        auto pointerWorldPos = GetScreenToWorld2D(inputSystem->GetPointerScreenPosition(), cameraController->Get());
        for (const auto& npc : allNpcs)
        {
            if (npc->GetCurrentActionName() == SkipState)
                continue;

            collision = CheckCollisionPointCircle(pointerWorldPos, npc->GetActualPosition(), Radius);
            if (collision)
            {
                draggedNpc = npc;
                draggedNpc->SetDraggedState(true);
                draggedNpc->SetDangerState(true);
                draggedNpc->Replan(astar);
                break;
            }
        }
    }

    if (draggedNpc)
    {
        auto pointerWorldPos = GetScreenToWorld2D(inputSystem->GetPointerScreenPosition(), cameraController->Get());
        draggedNpc->SetPosition(pointerWorldPos);

        if (!confirmedButtonDown)
        {
            draggedNpc->SetDraggedState(false);
            draggedNpc->Replan(astar);
            draggedNpc = nullptr;
        }
    }
}

void ObjectMoveSystem::Exit()
{
    if (draggedNpc)
    {
        draggedNpc->SetDraggedState(false);
        draggedNpc->Replan(astar);
        draggedNpc = nullptr;
    }
}
