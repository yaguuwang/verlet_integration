#include "constrain.hpp"

void satisfy(const constrain &c)
{
    auto delta = Vector2Subtract(c.p2->position, c.p1->position);
    auto current_distance = Vector2Length(delta);
    auto difference = (current_distance - c.initial_distance) / current_distance;
    auto correction = Vector2Scale(delta, 0.5 * difference);
    if (!c.p1->isPinned)
    {
        c.p1->position = Vector2Add(c.p1->position, correction);
    }
    if (!c.p2->isPinned)
    {
        c.p2->position = Vector2Subtract(c.p2->position, correction);
    }
}

std::vector<constrain> prepare_constrains(const std::vector<std::shared_ptr<partical>> &particals, int row, int col)
{
    auto constrains = std::vector<constrain>();
    constrains.reserve(row * col * 2);
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            auto p = particals[r * col + c].get();
            if (c != col - 1)
            {
                constrains.emplace_back(p, particals[r * col + c + 1].get());
            }
            if (r != row - 1)
            {
                constrains.emplace_back(p, particals[(r + 1) * col + c].get());
            }
        }
    }
    return constrains;
}

void draw(const constrain &c)
{
    DrawLine(c.p1->position.x, c.p1->position.y, c.p2->position.x, c.p2->position.y, c.color);
}