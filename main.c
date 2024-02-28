#include "raylib.h"
#include "background.h"
#include "main.h"
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int screenHeight = 928;
    int screenWidth = 640;
    int isActive = false;
    int gameOver = false;
    int apples = 0; 
    int x = 0;
    int y = 0;
    int trackCase = 0; 
    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);
    while (!WindowShouldClose()) // esc or x
    {
        // Update
        Rectangle snake = {x, y, 32, 32}; 

        if (IsKeyPressed(KEY_W)) trackCase = 1;
        if (IsKeyPressed(KEY_A)) trackCase = 2;
        if (IsKeyPressed(KEY_S)) trackCase = 3;
        if (IsKeyPressed(KEY_D)) trackCase = 4; 

        switch (trackCase) {
            case 1:
                y-=5;
                break;
            case 2:
                x-=5;
                break;
            case 3:
                y+=5;
                break;
            case 4:
                x+=5;
                break; 
        }
        //Draw
        BeginDrawing();
                background(); 
                DrawRectangleRec(snake,RED); 
        EndDrawing();
    }
    CloseWindow();
    return 0;
}