#include <vector>
#include <memory>

#include "raylib.h"

#include "partical.cpp"
#include "constrain.cpp"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr char SCREEN_TITLE[] = "Verlet Integration";
constexpr int FPS = 60;
constexpr int MOUSE_RADIUS = 10;

constexpr Vector2 GRAVITY = Vector2{0.0f, 10.0f};

constexpr int ROW = 20;
constexpr int COL = 60;

void update_all_particals(const std::vector<std::shared_ptr<partical>> &particals,
                          float elasped_time, float screen_width, float screen_height)
{
    for (auto &&p : particals)
    {
        apply_force(p.get(), GRAVITY);
        update(p.get(), elasped_time);
        constrain_to_bound(p.get(), screen_width, screen_height);
    }
}

void update_all_constrains(std::vector<constrain> &constrains, Vector2 mouse_position, bool isMouseClicked)
{
    auto iter = constrains.begin();
    while (iter != constrains.end())
    {
        bool isCollideWithMouse = CheckCollisionPointLine(mouse_position, iter->p1->position, iter->p2->position, MOUSE_RADIUS);
        iter->color = isCollideWithMouse ? RED : WHITE;
        satisfy(*iter);

        if (isCollideWithMouse && isMouseClicked)
        {
            iter = constrains.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void draw_all_entity(const std::vector<std::shared_ptr<partical>> &particals, const std::vector<constrain> &constrains)
{
    BeginDrawing();
    ClearBackground(BLACK);

    for (auto &&p : particals)
    {
        draw(p.get());
    }

    for (auto &&c : constrains)
    {
        draw(c);
    }

    EndDrawing();
}

void draw_mouse(Vector2 mouse_position)
{
    DrawCircleLines(mouse_position.x, mouse_position.y, MOUSE_RADIUS, RED);
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    SetTargetFPS(FPS);
    SetTraceLogLevel(LOG_DEBUG);
    auto particals = prepare_particals(ROW, COL);
    auto constrains = prepare_constrains(particals, ROW, COL);
    char fpsText[100];

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        float elapsed_time = GetFrameTime();
        float screen_width = GetScreenWidth();
        float screen_height = GetScreenHeight();
        Vector2 mouse_position = GetMousePosition();
        bool isMouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        update_all_particals(particals, elapsed_time, screen_width, screen_height);
        update_all_constrains(constrains, mouse_position, isMouseClicked);
        draw_all_entity(particals, constrains);

        draw_mouse(mouse_position);
        snprintf(fpsText, 100, "FPS: %d", GetFPS());
        DrawText(fpsText, 10, 10, 10, RAYWHITE);
    }

    CloseWindow();
    return 0;
}