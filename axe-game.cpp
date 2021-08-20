#include "raylib.h"

int main() {
    const int width = 800;
    const int height = 450;
    InitWindow(width, height, "Axe Game");

    SetTargetFPS(60);

    // Player coordinates
    int p_x = 200;
    int p_y = height / 2;
    int p_radius = 25;
    // Player edges
    int l_p_x;
    int r_p_x;
    int u_p_y;
    int b_p_y;

    // Axe coordinates
    int axe_x = 400;
    int axe_y = 0;
    int axe_length = 50;
    // Axe edges
    int l_axe_x;
    int r_axe_x;
    int u_axe_y;
    int b_axe_y;

    int direction = 10;
    float rotation = 0;

    bool collision_with_axe = false;

    Texture2D axe_texture = LoadTexture("axe.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (collision_with_axe) {
            DrawText("Game Over!", width / 2 - MeasureText("Game Over!", 50) / 2, 200, 50, RED);
        }
        else {
            l_p_x = p_x - p_radius;
            r_p_x = p_x + p_radius;
            u_p_y = p_y - p_radius;
            b_p_y = p_y + p_radius;
            l_axe_x = axe_x - axe_length / 2;
            r_axe_x = axe_x + axe_length / 2;
            u_axe_y = axe_y - axe_length / 2;
            b_axe_y = axe_y + axe_length / 2;
            collision_with_axe =
                (b_axe_y >= u_p_y) &&
                (u_axe_y <= b_p_y) &&
                (r_axe_x >= l_p_x) &&
                (l_axe_x <= r_p_x);

            if (IsKeyDown(KEY_D) && p_x < width) p_x += 10;
            if (IsKeyDown(KEY_A) && p_x > 0) p_x -= 10;

            axe_y += direction;
            if (axe_y > height || axe_y < 0) direction = -direction;
            rotation += 10;

            DrawCircle(p_x, p_y, p_radius, (Color) { 255, 219, 172, 255 });
            // DrawRectangle(axe_x, axe_y, axe_length, axe_length, DARKBROWN);
            // DrawTextureEx(axe_texture, (Vector2) { (float)axe_x, (float)axe_y }, rotation, 3.125, WHITE);
            DrawTexturePro(
                axe_texture,
                { 0.0f, 0.0f, 16.0f, 16.0f },
                { (float)axe_x, (float)axe_y, (float)axe_length, (float)axe_length },
                { 16.0f, 16.0f },
                rotation,
                WHITE
            );
        }

        EndDrawing();
    }

    UnloadTexture(axe_texture);

    CloseWindow();

    return 0;
}