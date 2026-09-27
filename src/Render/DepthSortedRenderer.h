#ifndef WILDLIFESIM_DEPTHSORTEDRENDERER_H
#define WILDLIFESIM_DEPTHSORTEDRENDERER_H

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

class DepthSortedRenderer
{
    struct Entry
    {
        float depth;
        std::function<void()> draw;
    };

    std::vector<Entry> entries;

public:
    void Add(float depth, std::function<void()> draw)
    {
        entries.push_back({ depth, std::move(draw) });
    }

    void Flush()
    {
        std::ranges::sort(entries, [](const Entry& first, const Entry& second)
        {
            return first.depth < second.depth;
        });

        for (const auto& entry : entries)
            entry.draw();

        entries.clear();
    }
};

#endif
