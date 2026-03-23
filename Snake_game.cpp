#include <iostream>
#include <deque>
#include "raylib.h"
#include "raymath.h"

using namespace std;

const int cellSize = 30;
const int cellCount = 25;

class Snake {
private:
    deque<Vector2> body;
public:
    Snake() {
        this->body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
    }

    void draw() {
        for (int i = 0; i < this->body.size(); i++) {
            float pos_x = this->body[i].x * cellSize;
            float pos_y = this->body[i].y * cellSize;
            Rectangle segment = Rectangle{ pos_x,pos_y,cellSize,cellSize };
            DrawRectangleRounded(segment, 0.6, 8, MAROON);
        }
    }
};

class Food {
private:
    Vector2 pos;
    Texture2D food_texture;
public:
    Food() {
        Image image = LoadImage("graphics/food.png");
        this->food_texture = LoadTextureFromImage(image);
        UnloadImage(image);
        this->pos = getRandomPosition();
    }

    void draw() const {
        int x = pos.x * cellSize;
        int y = pos.y * cellSize;
        DrawTexture(this->food_texture, x, y, WHITE);
    }

    Vector2 getRandomPosition() {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{ x,y };
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
    Snake snake;

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(DARKGREEN);
        food.draw();
        snake.draw();
        EndDrawing();
    }

    CloseWindow();
        
    return 0;
}
