#include "DeathState.h"
#include "Enemies/Wolf.h"

void DeathState::Update()
{
    wolf->ReleaseReservedTile();
    wolf->StopMoving();
    wolf->PlayDeathClip();

    if (wolf->IsDeathAnimationFinished())
        wolf->MarkReadyToRemove();
}
