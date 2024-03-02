#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

enum direction {
    UP, DOWN, LEFT, RIGHT
}; 

// variables

const int windowHeight = 960 % 32; 
const int windowWidth = 640 % 32;
int speed = 4;
bool isGameOver = false; 

struct {
    Vector2 position; // x and y
    Vector2 size; // 32 by 32 cannot exceed
    Texture2D pattern;
    enum direction direction;
} snake;

void initMap(void) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    Color lightgreen = (Color){170, 215, 81, 255};
    Color darkgreen = (Color){162, 209, 73, 255};

    for (int x = 0; x < height + (height - height % 32); x+=32) {
        for (int y = 0; y < width + (width - width % 32); y+=32) {
            if (( x / 32 + y / 32) % 2 == 0) {
                DrawRectangle(x, y, 32, 32, lightgreen); 
            } else {
                DrawRectangle(x, y, 32, 32, darkgreen);
            }
        }
    }
}

void initPlayer(void) {
    int width = GetScreenWidth(); 
    int height = GetScreenHeight();
    Image snakeImage = LoadImage("resources/textures/head.png");
    snake.position = (Vector2){width / 2, height / 2};
    snake.size = (Vector2){32, 32}; // size of the tiles
    snake.pattern = LoadTextureFromImage(snakeImage);
    UnloadImage(snakeImage); 
}

void playerLogic() {

    if (IsKeyDown(KEY_W)) snake.direction = UP;
    if (IsKeyDown(KEY_A)) snake.direction = LEFT;
    if (IsKeyDown(KEY_S)) snake.direction = DOWN;
    if (IsKeyDown(KEY_D)) snake.direction = RIGHT;

    switch (snake.direction) {
        case UP:
            snake.position.y -= speed;
            break;
        case LEFT:
            snake.position.x -= speed;
            break;
        case DOWN:
            snake.position.y += speed;
            break;
        case RIGHT:
            snake.position.x += speed;
            break;
    }
}



int main(void)
{
    InitWindow(windowWidth, windowHeight, "Snake Game");
    SetTargetFPS(60);
    initPlayer(); 
    while (!WindowShouldClose()) // esc or x
    {
        // update 
        playerLogic(); 

        BeginDrawing();
            ClearBackground(RAYWHITE);
            initMap();
            DrawTexture(snake.pattern, snake.position.x, snake.position.y, WHITE); 
        EndDrawing();
    }
    UnloadTexture(snake.pattern); 
    CloseWindow();
    return 0;
}
