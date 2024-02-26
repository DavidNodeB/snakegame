#include "raylib.h"

int main(void)
{
    const int screenWidth = 700;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            if (IsWindowResized() == true) {
                SetWindowSize(screenWidth, screenHeight); 
            } 
        EndDrawing();
    }
    CloseWindow();
    return 0;
}