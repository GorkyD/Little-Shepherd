#include "VisualSensor.h"
#include <cmath>
#include "raymath.h"
#include "Enemies/Wolf.h"
#include "Npc/BaseNpc.h"
#include "World/Grid.h"
#include "World/World.h"

VisualSensor::VisualSensor(const int radius, const float coneAngleDegrees) : radius(radius), coneAngleDegrees(coneAngleDegrees)
{
    const float halfAngleRad = (coneAngleDegrees / 2.0f) * (PI / 180.0f);
    halfAngleCos = std::cos(halfAngleRad);
}

void VisualSensor::DrawDebug(const BaseNpc* npc) const
{
    const Vector2 origin = Grid::ToScreen(npc->position);

    const Vector2 facingRaw = npc->GetLastMoveDirection();
    const Vector2 facing = Vector2LengthSqr(facingRaw) > 0.0f ? Vector2Normalize(facingRaw) : Vector2{ 0.0f, 1.0f };

    const float facingAngle = atan2f(facing.y, facing.x) * RAD2DEG;
    const float halfAngle = coneAngleDegrees / 2.0f;
    const float visualRadius = radius * Grid::TileWidth * 0.5f;

    DrawCircleSector(origin, visualRadius, facingAngle - halfAngle, facingAngle + halfAngle, 24, Fade(YELLOW, 0.25f));
    DrawCircleSectorLines(origin, visualRadius, facingAngle - halfAngle, facingAngle + halfAngle, 24, YELLOW);
}

void VisualSensor::Scan(BaseNpc* npc, const std::shared_ptr<World>& world, const std::shared_ptr<Astar<GridPos, GridDomain>>& astar)
{
    const bool trackingKnownFire = npc->GetKnownFireTile().has_value();

    if (trackingKnownFire)
        npc->ReportFireSighting(npc->IsKnownFireStillBurning(), npc->GetKnownFireTile(), astar);

    const GridPos origin = npc->position;
    const Vector2 originScreen = Grid::ToScreen(origin);

    const Vector2 facingRaw = npc->GetLastMoveDirection();
    const Vector2 facing = Vector2LengthSqr(facingRaw) > 0.0f ? Vector2Normalize(facingRaw) : Vector2{ 0.0f, 1.0f };

    const auto isVisible = [&](const GridPos candidate, int& outDistance)
    {
        outDistance = std::abs(candidate.row - origin.row) + std::abs(candidate.col - origin.col);

        if (outDistance > radius)
            return false;

        if (candidate == origin)
            return true;

        const Vector2 toCandidate = Vector2Subtract(Grid::ToScreen(candidate), originScreen);

        if (Vector2LengthSqr(toCandidate) <= 0.0f)
            return true;

        const float cosAngle = Vector2DotProduct(Vector2Normalize(toCandidate), facing);
        return cosAngle >= halfAngleCos;
    };

    if (!trackingKnownFire)
    {
        bool fireVisible = false;
        std::optional<GridPos> nearestFireTile;
        int bestFireDistance = 0;

        const int width = world->GetWorldWidth();
        const int height = world->GetWorldHeight();

        for (int row = 0; row < width; row++)
        {
            for (int col = 0; col < height; col++)
            {
                const GridPos candidate{ row, col };
                int distance = 0;

                if (!isVisible(candidate, distance))
                    continue;

                if (world->GetTile(candidate.row, candidate.col).onFire)
                {
                    fireVisible = true;

                    if (!nearestFireTile.has_value() || distance < bestFireDistance)
                    {
                        nearestFireTile = candidate;
                        bestFireDistance = distance;
                    }
                }
            }
        }

        npc->ReportFireSighting(fireVisible, nearestFireTile, astar);
    }

    bool alarmedNpcVisible = false;

    if (!world->IsAnyAgentSearchingDanger())
    {
        for (const auto& other : world->GetAgents())
        {
            if (other.get() == npc)
                continue;

            const std::string& otherAction = other->GetCurrentActionName();

            if (otherAction != "RunAwayFromDanger" && otherAction != "RunAwayFromFire" && otherAction != "SearchDanger")
                continue;

            int distance = 0;

            if (isVisible(other->position, distance))
            {
                alarmedNpcVisible = true;
                break;
            }
        }
    }

    std::optional<std::weak_ptr<Wolf>> nearestWolf;
    int bestWolfDistance = 0;

    for (const auto& enemy : world->GetEnemies())
    {
        if (enemy->IsDead())
            continue;

        int distance = 0;

        if (!isVisible(enemy->GetPosition(), distance))
            continue;

        if (!nearestWolf.has_value() || distance < bestWolfDistance)
        {
            nearestWolf = std::weak_ptr<Wolf>(enemy);
            bestWolfDistance = distance;
        }
    }

    npc->ReportNearbyAlarm(alarmedNpcVisible, astar);
    npc->ReportThreatNearby(nearestWolf, astar);
}
