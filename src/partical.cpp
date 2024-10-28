#include "partical.hpp"
#include <vector>
#include <memory>

constexpr int BUFFER_TO_TOP = 20;
constexpr int BUFFER_TO_LEFT = 80;
constexpr int BUFFER_IN_BETWEEN = 8;

std::vector<std::shared_ptr<partical>> prepare_particals(int row, int col)
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    std::vector<std::shared_ptr<partical>> particals;
    particals.reserve(row * col);
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            auto p = std::make_shared<partical>(Vector2{float(BUFFER_TO_LEFT + c * BUFFER_IN_BETWEEN), float(BUFFER_TO_TOP + r * BUFFER_IN_BETWEEN)});
            if (r == 0)
            {
                p.get()->isPinned = true;
            }
            particals.emplace_back(p);
        }
    }
    return particals;
}

void apply_force(partical *p, Vector2 force)
{
    if (p->isPinned)
    {
        return;
    }
    p->acceleration = Vector2Add(p->acceleration, force);
}

void update(partical *p, float eplased_time)
{
    if (p->isPinned)
    {
        return;
    }
    Vector2 velocity = Vector2Subtract(p->position, p->previous_position);
    p->previous_position = p->position;
    p->position = Vector2Add(Vector2Add(p->position, velocity), Vector2Scale(p->acceleration, eplased_time * eplased_time * METER_OVER_PIXEL));
    p->acceleration = Vector2Zero();
}

void constrain_to_bound(partical *p, float width, float height)
{
    if (p->position.x < RAIDUS)
    {
        p->position.x = RAIDUS;
    }

    if (p->position.x > width - RAIDUS)
    {
        p->position.x = width - RAIDUS;
    }

    if (p->position.y < RAIDUS)
    {
        p->position.y = RAIDUS;
    }

    if (p->position.y > height - RAIDUS)
    {
        p->position.y = height - RAIDUS;
    }
}

void draw(partical *p)
{
    DrawCircle(p->position.x, p->position.y, RAIDUS, WHITE);
}