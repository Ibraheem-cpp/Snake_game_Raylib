#include <iostream>
#include <deque>
#include "raylib.h"
#include "raymath.h"

using namespace std;

const int cellSize = 30;
const int cellCount = 25;

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

    void changeLoc(const deque<Vector2>& snakeBody) {
        bool isUnique = false;
        Vector2 loc = { 0,0 };
        while (!isUnique) {
            isUnique = true;
            loc = getRandomPosition();
            for (int i = 0; i < snakeBody.size(); i++) {
                if (loc.x == snakeBody[i].x && loc.y == snakeBody[i].y) {
                    isUnique = false;
                    break;
                }
            }
        }
        this->pos = loc;
    }

    Vector2 getFoodLoc() const {
        return this->pos;
    }

    ~Food() {
        UnloadTexture(this->food_texture);
    }
};

class Snake {
private:
    deque<Vector2> body;
    Vector2 Direction = { 1,0 };
    double lastUpdateTime = 0;

    bool triggerEvent(double interval) {
        double currentTime = GetTime();
        if (currentTime - lastUpdateTime >= interval) {
            lastUpdateTime = currentTime;
            return true;
        }
        return false;
    }

public:
    Snake() {
        this->body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
    }

    void draw() {
        for (int i = 0; i < this->body.size(); i++) {
            float pos_x = this->body[i].x * cellSize;
            float pos_y = this->body[i].y * cellSize;
            Rectangle segment = Rectangle{ pos_x,pos_y,cellSize,cellSize };
            DrawRectangleRounded(segment, 0.7, 8, MAROON);
        }
    }

    void Update(bool& snakeGrew) {
        if (this->triggerEvent(0.1)) {
            if (!snakeGrew) {
                this->body.pop_back();
            }
            this->body.push_front({ this->body[0].x + this->Direction.x, this->body[0].y + this->Direction.y });
            snakeGrew = false;
        }
    }

    void updateDirection() {
        if (IsKeyPressed(KEY_W) && this->Direction.y != 1) {
            this->Direction = { 0,-1 };
        }
        if (IsKeyPressed(KEY_S) && this->Direction.y != -1) {
            this->Direction = { 0,1 };
        }
        if (IsKeyPressed(KEY_A) && this->Direction.x != 1) {
            this->Direction = { -1,0 };
        }
        if (IsKeyPressed(KEY_D) && this->Direction.x != -1) {
            this->Direction = { 1,0 };
        }
    }

    bool didEatFood(Food* food) const {
        Vector2 foodLoc = food->getFoodLoc();
        if ((this->body[0].x == foodLoc.x) && (this->body[0].y == foodLoc.y)) {
            return true;
        }
        return false;
    }

    const deque<Vector2>& snakeBody() const {
        return this->body;
    }
};

class Game {
private:
    Snake* snake;
    Food* food;
    bool snakeGrew = false;
public:
    Game() {
        snake = new Snake();
        food = new Food();
    }

    void draw() {
        food->draw();
        snake->draw();
    }

    void updateSnake() {
        snake->Update(this->snakeGrew);
        snake->updateDirection();
    }

    void checkCollosionWithFood() {
        if (snake->didEatFood(food)) {
            food->changeLoc(snake->snakeBody());
            this->snakeGrew = true;
        }
    }

    ~Game() {
        delete snake;
        delete food;
        snake = nullptr;
        food = nullptr;
    }
};

int main()
{
    const int width = cellSize * cellCount;
    const int height = cellSize * cellCount;

    InitWindow(width, height, "Snake Game");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {

        game.checkCollosionWithFood();
    
        game.updateSnake();
  
        BeginDrawing();
        ClearBackground(DARKGREEN);
        game.draw();
        EndDrawing();
    }

    CloseWindow();
        
    return 0;
}
