#ifndef WILDLIFESIM_ASTAR_H
#define WILDLIFESIM_ASTAR_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

template<typename NodeType, typename Domain, typename GoalType = NodeType>
class Astar
{
    Domain domain;
    
public:
    explicit Astar(Domain domain) : domain(std::move(domain)){}
    
    std::vector<NodeType> AstarAlgorithm(NodeType start, GoalType target)
    {
        struct OpenEntry
        {
            NodeType node;
            float f;
        };

        struct CompareEntry
        {
            bool operator()(const OpenEntry& a, const OpenEntry& b) const
            {
                return a.f > b.f;
            }
        };

        std::unordered_map<NodeType, float> gCost;
        std::unordered_map<NodeType, NodeType> cameFrom;
        std::priority_queue<OpenEntry, std::vector<OpenEntry>, CompareEntry> openSet;
        std::vector<NodeType> path;
        
        gCost[start] = 0;
        openSet.push({start, domain.Heuristic(start,target)});

        while (!openSet.empty())
        {
            NodeType current = openSet.top().node;
            openSet.pop();

            if (domain.IsGoalSatisfied(current,target))
            {
                
                NodeType cursor  = current;
                while (cameFrom.contains(cursor))
                {
                    path.push_back(cursor);
                    cursor = cameFrom[cursor];
                }
                path.push_back(start);
                std::reverse(path.begin(),path.end());
                std::cout << "Path found, size = " << path.size() << std::endl;
                return path;
            }
            
            for (NodeType neighbor : domain.GetNeighbors(current))
            {
                float newG = gCost[current] + domain.Cost(current,neighbor);
                
                if (!gCost.contains(neighbor) || newG < gCost[neighbor])
                {
                    gCost[neighbor] = newG;
                    cameFrom[neighbor] = current;
                    float h = domain.Heuristic(neighbor, target);
                    openSet.push({neighbor, newG + h});
                }
            }
        }
        
        if (path.empty())
            std::cout << "Path is not found"<< std::endl;
        
        return {};
    }
};

#endif
