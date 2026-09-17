#include "TimeSystem.h"
#include "raylib.h"

void TimeSystem::TimeOfDayChange() const
{
    world->SetTimeState(!world->GetTimeState());
}

void TimeSystem::Start() const
{
    world->SetTimeState(true);
    eventBus->Publish(OnDayTimeChange);
}

float TimeSystem::GetCurrentDayTimeProgress() const
{
    const auto duration = world->GetTimeState() ? dayDuration : nightDuration;
    float progress = elapsed / duration;
    
    return progress;
}

void TimeSystem::Update()
{
    elapsed += GetFrameTime();

    const float currentDuration = world->GetTimeState() ? dayDuration : nightDuration;

    if (elapsed >= currentDuration)
    {
        elapsed -= currentDuration;
        TimeOfDayChange();
        eventBus->Publish(OnDayTimeChange);
    }
}