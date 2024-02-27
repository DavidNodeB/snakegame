#include "raylib.h"
#include "background.h"
#include "main.h"
#include <stdio.h>

struct snake
{
    /* data */
};


int main(void)
{
    int screenHeight = 928;
    int screenWidth = 640; 
    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);
    while (!WindowShouldClose()) // esc or x
    {
        BeginDrawing();
            background(); 
        EndDrawing();
    }
    CloseWindow();
    return 0;
}