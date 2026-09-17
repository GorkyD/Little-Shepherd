#ifndef WILDLIFESIM_GRIDPOS_H
#define WILDLIFESIM_GRIDPOS_H

#include <functional>

struct GridPos
{
    int row;
    int col;

    bool operator==(const GridPos&) const = default;
};

template<>
struct std::hash<GridPos>
{
    size_t operator()(const GridPos& pos) const noexcept
    {
        return std::hash<int>()(pos.row) ^ (std::hash<int>()(pos.col) << 1);
    }
};

#endif
