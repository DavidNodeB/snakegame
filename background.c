#include "raylib.h"
#include "main.h"
#include <stdlib.h>

void background() {
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