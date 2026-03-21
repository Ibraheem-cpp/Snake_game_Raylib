#include <iostream>
#include "raylib.h"
#include "raymath.h"

using namespace std;

const int cellSize = 25;
const int cellCount = 30;

class Food {
private:
    Vector2 pos;
public:
    Food() {
        int x = GetRandomValue(0, cellCount - 1);
        int y = GetRandomValue(0, cellCount - 1);
        this->pos.x = x;
        this->pos.y = y;
    }

    void draw() const {
        int x = pos.x * cellSize;
        int y = pos.y * cellSize;
        DrawRectangle(x, y, cellSize, cellSize, ORANGE);
    }
};

int main()
{
    const int width = cellSize * cellCount;
    const int height = cellSize * cellCount;

    InitWindow(width, height, "Snake Game");
    SetTargetFPS(60);

    Food food;

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(DARKGREEN);
        food.draw();
        EndDrawing();
    }

    CloseWindow();
        
    return 0;
}
