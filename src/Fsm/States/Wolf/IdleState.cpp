#include "IdleState.h"
#include <iostream>

void IdleState::Enter()
{
    WolfState::Enter();
    std::cout << "Idle Enter" << std::endl;
}

void IdleState::Exit()
{
    WolfState::Exit();
    std::cout << "Idle Exit" << std::endl;
}

void IdleState::Update()
{
    WolfState::Update();
    std::cout << "Idle Update" << std::endl;
}

StateId IdleState::GetId() const
{
    std::cout << "Idle GetId" << std::endl;
    return StateId::Idle;
}
