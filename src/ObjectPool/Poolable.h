#ifndef WILDLIFESIM_POOLABLE_H
#define WILDLIFESIM_POOLABLE_H

#include <concepts>
#include <utility>

template<typename T, typename... Args>
concept Poolable = std::default_initializable<T> &&
    requires(T& instance, Args&&... args)
{
    instance.Init(std::forward<Args>(args)...);
    instance.Reset();
};

#endif
