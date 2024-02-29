#include "raylib.h"
#include "background.h"
#include "main.h"
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int screenHeight = 928;
    int screenWidth = 640;
    int gameOver = false;
    int score = 0;
    int highestScore = 0; 
    int apples = 0; 
    int x = 0;
    int y = 0;
    int trackCase = 0; 
    InitWindow(screenWidth, screenHeight, "Snake Game");
    printf(TextFormat("Screen size: %d\n", GetScreenWidth())); 
    SetTargetFPS(60);
    while (!WindowShouldClose()) // esc or x
    {
        // Update
        Rectangle snake = {x, y, 32, 32}; 
        int getSw = GetScreenWidth();
        int getSh= GetScreenHeight();

        if (IsKeyPressed(KEY_W)) trackCase = 1;
        if (IsKeyPressed(KEY_A)) trackCase = 2;
        if (IsKeyPressed(KEY_S)) trackCase = 3;
        if (IsKeyPressed(KEY_D)) trackCase = 4;
        if (gameOver != true) {
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
            } // continually moves because it is just checks if the key is pressed once
        }

        if (snake.x < 0 || snake.x > getSw || snake.y < 0 || snake.y > getSh) {
            x = 0;
            y = 0;
            gameOver = true;
        }

        const char *defaultText = "Please press enter or space to start the game";
        const char *scoreText = "Score: ";
        Vector2 scoreSize = MeasureTextEx(GetFontDefault(), scoreText, 20, 20 / 10);
        Vector2 scorePos = (Vector2){getSw / 2 - scoreSize.x / 2, getSh / 2 - scoreSize.y / 2}; 
        Vector2 size = MeasureTextEx(GetFontDefault(), defaultText, 20, 20 / 10);
        Vector2 textPos = (Vector2){getSw / 2 - size.x / 2, getSh / 2 - size.y / 2}; 
        if (IsKeyPressed(KEY_W || KEY_A || KEY_S || KEY_D) && gameOver == true) {
            gameOver = false;
        }
        //Draw
        BeginDrawing();
                background(); 
                DrawRectangleRec(snake,RED);
                if (gameOver == true) {
                    DrawText(defaultText, (int)textPos.x, (int)textPos.y, 20, BLUE);
                    DrawText(TextFormat("Score: %d", score), (int)scorePos.x, (int)scorePos.y + 30, 20, BLUE);
                }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}