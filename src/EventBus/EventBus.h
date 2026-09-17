#ifndef WILDLIFESIM_EVENTBUS_H
#define WILDLIFESIM_EVENTBUS_H

#include <functional>
#include <memory>
#include <unordered_map>
#include "EventType.h"

class EventBus
{
    std::unordered_map<EventType, std::unordered_map<int, std::function<void(std::shared_ptr<void>)>>> subscribers;
    std::unordered_map<EventType, std::unordered_map<int, std::weak_ptr<void>>> weakPtrs;
    int nextId = 0;
public:
    template <typename T, typename Func>
    int Subscribe(EventType type, std::shared_ptr<T> subscriber, Func method)
    {
        int id = nextId++;
        weakPtrs[type][id] = subscriber;
    
        subscribers[type][id] = [method](std::shared_ptr<void> obj)
        {
            auto typed = std::static_pointer_cast<T>(obj);
            method(typed);
        };
    
        return id;
    }
    
    void UnSubscribe(EventType type, int id);
    void Publish(EventType type);
};

#endif
