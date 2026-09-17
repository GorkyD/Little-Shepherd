#include "GoalPlanner.h"

bool GoalPlanner::Update(const WorldState& state)
{
    Goal* best = nullptr;

    for (auto& goal : goals)
    {
        if (!goal.IsRelevant(state))
            continue;

        if (goal.IsSatisfied(state))
            continue;

        if (!best || goal.priority > best->priority)
            best = &goal;
    }

    const bool changed = (best != activeGoal);
    activeGoal = best;
    return changed;
}