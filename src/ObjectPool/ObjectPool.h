#ifndef WILDLIFESIM_OBJECTPOOL_H
#define WILDLIFESIM_OBJECTPOOL_H

#include <memory>
#include <queue>
#include "Poolable.h"

template<typename T> requires std::default_initializable<T>
class ObjectPool
{
    std::queue<std::shared_ptr<T>> allocator;
public:
    ObjectPool(int startCount)
    {
        for (int i = 0; i < startCount; i++)
            allocator.push(std::make_shared<T>());
    }
    
    template<typename... Args>
    requires Poolable<T, Args...>
    std::shared_ptr<T> Acquire(Args&&... args)
    {
        if (allocator.empty())
        {
            auto value = std::make_shared<T>();
            value->Init(std::forward<Args>(args)...);
            return value;
        }
           
        
        auto value = std::move(allocator.front());
        allocator.pop();
        value->Init(std::forward<Args>(args)...);
        return value;
    }
    
    template<typename... Args>
    requires Poolable<T, Args...>
    void Release(std::shared_ptr<T> obj)
    {
        obj.Reset();
        allocator.push(std::move(obj)); 
    }
};
#endif
