#ifndef WILDLIFESIM_BASEINTERACTSYSTEM_H
#define WILDLIFESIM_BASEINTERACTSYSTEM_H

class BaseInteractSystem
{
public:
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
    virtual ~BaseInteractSystem() = default;
};


#endif
