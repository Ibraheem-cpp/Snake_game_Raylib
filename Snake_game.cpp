#include <iostream>
#include "raylib.h"
#include "raymath.h"

using namespace std;

const int cellSize = 25;
const int cellCount = 30;

class Food {
private:
    Vector2 pos;
    Texture2D food_texture;
public:
    Food() {
        Image image = LoadImage("graphics/food.png");
        this->food_texture = LoadTextureFromImage(image);
        UnloadImage(image);
        int x = GetRandomValue(0, cellCount - 1);
        int y = GetRandomValue(0, cellCount - 1);
        this->pos.x = x;
        this->pos.y = y;
    }

    void draw() const {
        int x = pos.x * cellSize;
        int y = pos.y * cellSize;
        DrawTexture(this->food_texture, x, y, WHITE);
    }

    ~Food() {
        UnloadTexture(this->food_texture);
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
