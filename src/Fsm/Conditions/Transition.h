#ifndef EXAMPLES_CONDITION_H
#define EXAMPLES_CONDITION_H

#include <functional>
#include <memory>
#include "../States/State.h"

enum class StateId;

struct Transition
{
    StateId targetId;
    std::function<bool()> condition;
    std::function<std::unique_ptr<State>()> createState;
};

#endif
