#ifndef WILDLIFESIM_GOALPLANNER_H
#define WILDLIFESIM_GOALPLANNER_H
#include "Goap/Goal.h"


class GoalPlanner
{
    std::vector<Goal> goals;
    Goal* activeGoal = nullptr;
public:
    explicit GoalPlanner(std::vector<Goal> goals) : goals(std::move(goals)){}
    
    bool Update(const WorldState& state);
    Goal* GetActiveGoal() const { return activeGoal; }
};


#endif
