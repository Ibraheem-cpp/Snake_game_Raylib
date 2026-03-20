#include <iostream>
#include "raylib.h"

using namespace std;

int main()
{
    const int width = 750;
    const int height = 750;

    InitWindow(width, height, "Snake Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(width / 2, height / 2, 25.0, RED);
        EndDrawing();
    }


    CloseWindow();
        
        
    return 0;
}
