#ifndef WILDLIFESIM_SPLINEPATH_H
#define WILDLIFESIM_SPLINEPATH_H

#include <memory>
#include <vector>
#include "raylib.h"
#include "Astar/Domains/GridDomain.h"
#include "World/World.h"

class SplinePath
{
    std::vector<GridPos> nodes;
    std::vector<bool> segmentIsSmooth;

public:
    SplinePath() = default;
    SplinePath(std::vector<GridPos> nodes, std::vector<bool> segmentIsSmooth);

    bool IsEmpty() const;
    size_t SegmentCount() const;
    Vector2 Evaluate(size_t segmentIndex, float t) const;
    GridPos NodeAt(size_t index) const;
    Vector2 NodeWorldPosition(size_t index) const;
};

SplinePath BuildSplinePath(const std::vector<GridPos>& rawPath, const std::shared_ptr<World>& world, int samplesPerSegment = 4);

#endif
