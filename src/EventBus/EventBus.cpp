#include "EventBus.h"

void EventBus::UnSubscribe(EventType type, int id)
{
    subscribers[type].erase(id);
    weakPtrs[type].erase(id);
}

void EventBus::Publish(EventType type)
{
    for (auto& [id, weakPtr] : weakPtrs[type])
    {
        if (auto locked = weakPtr.lock())
            subscribers[type][id](locked);
    }
}


