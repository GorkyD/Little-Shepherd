#ifndef WILDLIFESIM_SELECTOR_H
#define WILDLIFESIM_SELECTOR_H

#include "Node.h"

class Selector : public Node
{
    std::vector<std::unique_ptr<Node>> children;
    size_t current = 0;
public:
    explicit Selector(std::vector<std::unique_ptr<Node>> children) : children(std::move(children)) {}
    
    Status Tick(BTContext& ctx) override
    {
        while (current < children.size())
        {
            Status status = children[current]->Tick(ctx);
            if (status == Status::Running) return Status::Running;
            if (status == Status::Success) { current = 0; return Status::Success; }
            current++;
        }
        current = 0;
        return Status::Failure;
    }
};

#endif
