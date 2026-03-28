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

    bool didHitWall() {
        if (this->body[0].x < 0 || this->body[0].x >= cellCount || this->body[0].y >= cellCount || this->body[0].y < 0) {
            return true;
        }
        return false;
    }

    bool didHitSnakeItself() {
        for (int i = 1; i < this->body.size(); i++) {
            if ((this->body[0].x == this->body[i].x) && (this->body[0].y == this->body[i].y)) {
                return true;
            }
        }
        return false;
    }

    void resetSnake() {
        this->body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
        this->Direction = { 1,0 };
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
    int score = 0;
    Music bgMusic;
    Sound eat;
    Sound die;
    bool isRunning = true;
public:
    Game() {
        snake = new Snake();
        food = new Food();
        bgMusic = LoadMusicStream("sounds/background.mp3");
        PlayMusicStream(bgMusic);
        SetMusicVolume(bgMusic, 0.4f);
        eat = LoadSound("sounds/eat.mp3");
        die = LoadSound("sounds/die.mp3");
     }

    void draw() {
        food->draw();
        snake->draw();
    }

    void updateMusic() const {
        UpdateMusicStream(bgMusic);
    }

    void updateSnake() {
        snake->Update(this->snakeGrew);
        snake->updateDirection();
    }

    void checkCollisionWithFood() {
        if (snake->didEatFood(food)) {
            PlaySound(eat);
            food->changeLoc(snake->snakeBody());
            this->snakeGrew = true;
            this->score++;
        }
    }

    void checkCollisionWithWall() {
        if (snake->didHitWall()) {
            PlaySound(die);
            GameOver();
        }
    }

    void checkCollisionWithSnakeItself() {
        if (snake->didHitSnakeItself()) {
            PlaySound(die);
            GameOver();
        }
    }

    void GameOver() {
        snake->resetSnake();
        food->changeLoc(snake->snakeBody());
        snakeGrew = false;
        this->score = 0;
        this->isRunning = false;
        
    }

    void startAgain() {
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A)) {
            this->isRunning = true;
        }
    }

    void drawStartAgain() {
        DrawText("Press 'A','S','D','W' to Start Game Again.", (cellCount * cellSize) / 8, (cellCount * cellSize) / 2, 30, BLACK);
    }

    int getScore() const {
        return this->score;
    }
    
    bool IsRunning() const {
        return this->isRunning;
    }

    ~Game() {
        delete snake;
        delete food;
        snake = nullptr;
        food = nullptr;
        StopMusicStream(bgMusic);
        UnloadMusicStream(bgMusic);
        UnloadSound(eat);
        UnloadSound(die);
    }
};


int main()
{
    const int width = cellSize * cellCount;
    const int height = cellSize * cellCount;

    InitWindow(width, height, "Snake Game");
    InitAudioDevice();
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.updateMusic();

        if (game.IsRunning()) {
            game.checkCollisionWithSnakeItself();
            game.checkCollisionWithWall();
            game.checkCollisionWithFood();

            game.updateSnake();
        }
        else {
            game.startAgain();
        }
  
        BeginDrawing();
        ClearBackground(DARKGREEN);
        DrawText("Score : ", 10, 10, 50, BLACK);
        DrawText(TextFormat("%i", game.getScore()), 200, 10, 50, BLACK);
        game.draw();
        if (!game.IsRunning()) {
            game.drawStartAgain();
        }
        EndDrawing();

    }

    CloseAudioDevice();
    CloseWindow();
        
    return 0;
}