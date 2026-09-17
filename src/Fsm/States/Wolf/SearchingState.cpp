#include "SearchingState.h"
#include <iostream>

void SearchingState::Enter()
{
    WolfState::Enter();
    std::cout << "Patrol Enter" << std::endl;
}

void SearchingState::Exit()
{
    WolfState::Exit();
    std::cout << "Patrol Exit" << std::endl;
}

void SearchingState::Update()
{
    WolfState::Update();
    std::cout << "Patrol Update" << std::endl;
}

StateId SearchingState::GetId() const
{
    std::cout << "Patrol GetId" << std::endl;
    return StateId::Searching;
}
