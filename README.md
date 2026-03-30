**Title & Description** -- "Snake Game" -- A classic snake game made using C++ and Raylib.

**Features:**
1. Classic Snake Gameplay.
2. Food texture with random spawning.
3. Background music with sound effects(eating, dying).
4. Wall and self-collision detection.
5. Score Tracking.
6. Game over and restart system.


---
**REQUIREMENTS**

This project requires external asset files to run.

**Graphics:**

-Create a folder named 'graphics' and add a 'food.png' image inside it(30 x 30 pixels).

**Sounds**

-Create a folder named 'sounds' and add the following audio files:
1. 'background.mp3'--Background music of your choice.
2. 'eat.mp3'--sound effect for eating food.
3. 'die.mp3'--sound effect for game over.

The sounds folder is not included in the repo. Make sure to name the files exactly as written, otherwise the game will crash on launch.

---
**How to Compile and Run:**

```
g++ Snake_game.cpp -o snake -lraylib -lm -lpthread
./snake
```
---

**Controls:**
| Key | Action  |
|-----|-------- |
|  W  | Move Up |
|  A  | Move Left |
|  S  | Move Down |
|  D  | Move Right |

---
**OOP Design:**
1. Food Class - handles texture, position and random spawning.
2. Snake Class - handles movement, direction, growth and collision.
3. Game Class - manages game state, score, audio and all game logic.

---





  
