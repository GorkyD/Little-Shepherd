#include "IdleState.h"
#include "Enemies/Wolf.h"

void IdleState::Update()
{
    wolf->GetController()->SetPlacedOnMap(true);
    wolf->PlayMoveClip();
}
