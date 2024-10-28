#pragma once
#include "raylib.h"
#include "raymath.h"

constexpr float RAIDUS = 1.0f;
constexpr float METER_OVER_PIXEL = 100.0f;

typedef struct partical
{
    Vector2 position;
    Vector2 previous_position;
    Vector2 acceleration;

    bool isPinned;

    partical() : position(Vector2Zero()), previous_position(Vector2Zero()), acceleration(Vector2Zero()), isPinned(false) {}
    partical(Vector2 position) : position(position), previous_position(position), acceleration(Vector2Zero()), isPinned(false) {}
    partical(Vector2 position, Vector2 acceleration) : position(position), previous_position(position), acceleration(acceleration), isPinned(false) {}

    ~partical()
    {
        // TraceLog(LOG_DEBUG, "Destorying partical");
    }
} partical;
