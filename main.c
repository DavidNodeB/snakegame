#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

enum direction {
    UP, DOWN, LEFT, RIGHT
}; 

// variables

const int windowHeight = 960; 
const int windowWidth = 640;
const int gridWidth = 32;
const int gridHeight = 32;
const int gridSize = 32; 
int speed = 1;
int frameCounter = 0; 
bool btnClicked = false;
bool isGameOver = false; 

struct {
    Vector2 position; // x and y
    Vector2 size; // 32 by 32 cannot exceed
    Vector2 speed; 
    Texture2D pattern;
    enum direction direction;
} snake;

void initMap(void) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    Color lightgreen = (Color){170, 215, 81, 255};
    Color darkgreen = (Color){162, 209, 73, 255};

    // loops through x and y then makes a light green or dark green box for every 32 pixels
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
    // initializes player variables
    int width = GetScreenWidth(); 
    int height = GetScreenHeight();
    Image snakeImage = LoadImage("resources/textures/head.png");
    snake.position = (Vector2){width / 2, height / 2};
    snake.size = (Vector2){32, 32}; // size of the tiles
    snake.speed = (Vector2){0, 0}; 
    snake.pattern = LoadTextureFromImage(snakeImage);
    UnloadImage(snakeImage); 
}

void playerLogic() {
    int getsw = GetScreenWidth();
    int getsh = GetScreenHeight();
    // increment the counter till hits 10
    frameCounter++;
    // if it is more than or equaled to 10 then move the player
    if (frameCounter / 10 && !isGameOver) {
        if (IsKeyDown(KEY_W)) snake.direction = UP;
        if (IsKeyDown(KEY_A)) snake.direction = LEFT;
        if (IsKeyDown(KEY_S)) snake.direction = DOWN;
        if (IsKeyDown(KEY_D)) snake.direction = RIGHT;

        switch (snake.direction) {
            case UP:
                snake.speed = (Vector2){0, -gridSize}; 
                break;
            case LEFT:
                snake.speed = (Vector2){-gridSize, 0};
                break;
            case DOWN:
                snake.speed = (Vector2){0, gridSize};
                break;
            case RIGHT:
                snake.speed = (Vector2){gridSize, 0};
                break;
        }
        // update the positions
        snake.position.x += snake.speed.x;
        snake.position.y += snake.speed.y;

        if (snake.position.x < 0 || snake.position.x > getsw || snake.position.y < 0 || snake.position.y > getsh) {
            snake.position.x = getsw / 2;
            snake.position.y = getsh / 2;
            isGameOver = true; 
        }

        frameCounter = 0; // reset the count for the loop
    }
}

void gameOver(void) {
    int getSw = GetScreenWidth();
    int getSh = GetScreenHeight(); 
    const char *gameOverText = "Please press w,a,s,d or enter to start the game";
    Vector2 size = MeasureTextEx(GetFontDefault(), gameOverText, 20, 20 / 10);
    Vector2 textPos = (Vector2){getSw / 2 - size.x / 2, getSh / 2 - size.y / 2};
    DrawText(gameOverText, (int)textPos.x, (int)textPos.y, 20, BLUE);
}

void startGame(void) {
    int getSw = GetScreenWidth();
    int getSh = GetScreenHeight();
    Vector2 mousePoint = {0.0f, 0.0f};
    mousePoint = GetMousePosition();
    Rectangle btnFrame = { getSw / 2, getSh / 2, 128, 128};

    if (CheckCollisionPointRec(mousePoint, btnFrame)) {
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            btnClicked = true; 
        } else {
            btnClicked = false; 
        }
    } 

    DrawRectangle(getSw / 2, getSh / 2, 128, 128, WHITE); 
    printf("%d", btnClicked); 
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
            if (isGameOver == true) {
                gameOver(); 
                startGame(); 
            }
            DrawTexture(snake.pattern, snake.position.x, snake.position.y, WHITE); 
        EndDrawing();
    }
    UnloadTexture(snake.pattern); 
    CloseWindow();
    return 0;
}
