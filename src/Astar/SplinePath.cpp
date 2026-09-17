#include "SplinePath.h"
#include "World/Grid.h"

namespace
{
    Vector2 Lerp(Vector2 a, Vector2 b, float t)
    {
        return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t };
    }

    Vector2 CatmullRom(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, float t)
    {
        const float t2 = t * t;
        const float t3 = t2 * t;

        const float x = 0.5f * (2.0f * p1.x
                               + (-p0.x + p2.x) * t
                               + (2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * t2
                               + (-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * t3);

        const float y = 0.5f * (2.0f * p1.y
                               + (-p0.y + p2.y) * t
                               + (2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * t2
                               + (-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * t3);

        return { x, y };
    }

    bool IsWalkableSafe(const std::shared_ptr<World>& world, GridPos pos)
    {
        if (pos.row < 0 || pos.row >= world->GetWorldWidth())
            return false;

        if (pos.col < 0 || pos.col >= world->GetWorldHeight())
            return false;

        return world->IsTileWalkable(pos.row, pos.col);
    }
}

SplinePath::SplinePath(std::vector<GridPos> nodes, std::vector<bool> segmentIsSmooth) : nodes(std::move(nodes)), segmentIsSmooth(std::move(segmentIsSmooth)) {}

bool SplinePath::IsEmpty() const
{
    return nodes.empty();
}

size_t SplinePath::SegmentCount() const
{
    return segmentIsSmooth.size();
}

GridPos SplinePath::NodeAt(size_t index) const
{
    return nodes[index];
}

Vector2 SplinePath::NodeWorldPosition(size_t index) const
{
    return Grid::ToScreen(nodes[index]);
}

Vector2 SplinePath::Evaluate(size_t segmentIndex, float t) const
{
    const GridPos p1 = nodes[segmentIndex];
    const GridPos p2 = nodes[segmentIndex + 1];

    if (!segmentIsSmooth[segmentIndex])
        return Lerp(Grid::ToScreen(p1), Grid::ToScreen(p2), t);

    const GridPos p0 = segmentIndex == 0 ? p1 : nodes[segmentIndex - 1];
    const GridPos p3 = segmentIndex + 2 < nodes.size() ? nodes[segmentIndex + 2] : p2;

    return CatmullRom(Grid::ToScreen(p0), Grid::ToScreen(p1), Grid::ToScreen(p2), Grid::ToScreen(p3), t);
}

SplinePath BuildSplinePath(const std::vector<GridPos>& rawPath, const std::shared_ptr<World>& world, int samplesPerSegment)
{
    std::vector<bool> segmentIsSmooth;

    for (size_t i = 0; i + 1 < rawPath.size(); i++)
    {
        const GridPos p1 = rawPath[i];
        const GridPos p2 = rawPath[i + 1];
        const GridPos p0 = i == 0 ? p1 : rawPath[i - 1];
        const GridPos p3 = i + 2 < rawPath.size() ? rawPath[i + 2] : p2;

        bool safe = true;

        for (int s = 0; s <= samplesPerSegment; s++)
        {
            const float t = static_cast<float>(s) / static_cast<float>(samplesPerSegment);
            const Vector2 sample = CatmullRom(Grid::ToScreen(p0), Grid::ToScreen(p1),Grid::ToScreen(p2), Grid::ToScreen(p3), t);

            if (!IsWalkableSafe(world, Grid::ToGrid(sample)))
            {
                safe = false;
                break;
            }
        }

        segmentIsSmooth.push_back(safe);
    }

    return SplinePath(rawPath, segmentIsSmooth);
}
