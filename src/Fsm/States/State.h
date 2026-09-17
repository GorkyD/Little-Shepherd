#ifndef EXAMPLES_STATE_H
#define EXAMPLES_STATE_H

#include "../StateId.h"

class State
{
public:
    virtual void Enter() {}
    virtual void Update() {}
    virtual void Exit() {} 
    virtual StateId GetId() const = 0;
    virtual ~State() = default;
};

#endif
