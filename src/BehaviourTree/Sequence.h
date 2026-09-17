#ifndef WILDLIFESIM_SEQUENCE_H
#define WILDLIFESIM_SEQUENCE_H

#include <memory>
#include <vector>
#include "Node.h"

class Sequence : public Node
{
    std::vector<std::unique_ptr<Node>> children;
    size_t current = 0;
public:
    explicit Sequence(std::vector<std::unique_ptr<Node>> children) : children(std::move(children)) {}
    
    Status Tick(BTContext& ctx) override
    {
        while (current < children.size())
        {
            Status status = children[current]->Tick(ctx);
            if (status == Status::Running) return Status::Running;
            if (status == Status::Failure) { current = 0; return Status::Failure; }
            current++;
        }
        current = 0;
        return Status::Success;
    }
};

#endif
