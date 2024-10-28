#pragma once
#include <memory>
#include "partical.hpp"

struct constrain
{
    partical *const p1;
    partical *const p2;
    float initial_distance;
    bool isPendingRemove;
    Color color;

    constrain(partical *p1, partical *p2) : p1(p1), p2(p2), initial_distance(Vector2Distance(p1->position, p2->position)),
                                            isPendingRemove(false), color(WHITE) {}

    ~constrain()
    {
        // TraceLog(LOG_DEBUG, "Destorying constrain");
    }
};
