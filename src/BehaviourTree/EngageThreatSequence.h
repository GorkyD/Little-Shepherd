#ifndef WILDLIFESIM_ENGAGETHREATSEQUENCE_H
#define WILDLIFESIM_ENGAGETHREATSEQUENCE_H

#include "Node.h"

class EngageThreatSequence : public Node
{
public:
    Status Tick(BTContext& ctx) override
    {
        return Status::Failure;      
    }
};

#endif
