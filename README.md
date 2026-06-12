# 🐍 Snake Game (C++ Console)

A classic Snake game built in C++ that runs in the Windows terminal. Control the snake, eat food, grow longer, and avoid hitting walls or yourself!

---

## Gameplay

```
####################
#                  #
#       F          #
#    oooO          #
#                  #
####################
Score: 30
Controls: W/A/S/D to move, X to quit
```

- **`O`** — Snake head  
- **`o`** — Snake body  
- **`F`** — Food  
- **`#`** — Walls  

---

## Features

- Smooth real-time keyboard input (non-blocking via `_kbhit`)
- Collision detection — walls and self
- Snake grows by one segment each time food is eaten
- Score tracking (+10 per food)
- Reverse-direction prevention (can't immediately turn back into yourself)
- Play again prompt after game over

---

## Controls

| Key | Action        |
|-----|---------------|
| `W` | Move Up       |
| `S` | Move Down     |
| `A` | Move Left     |
| `D` | Move Right    |
| `X` | Quit Game     |

---

## Requirements

- **OS:** Windows only  
  *(Uses `<conio.h>` for `_kbhit()`/`_getch()` and `<windows.h>` for `Sleep()`)*
- **Compiler:** Any C++ compiler supporting C++11 or later (e.g. MSVC, MinGW/g++)

---

## Build & Run

**Using g++ (MinGW on Windows):**
```bash
g++ SnakeGame.cpp -o SnakeGame.exe
SnakeGame.exe
```

**Using MSVC (Developer Command Prompt):**
```bash
cl SnakeGame.cpp
SnakeGame.exe
```

---

## Game Details

| Property        | Value            |
|-----------------|------------------|
| Board size      | 20 × 10 cells    |
| Starting position | Center of board |
| Starting direction | Right          |
| Game speed      | 100 ms per tick  |
| Max snake length | 100 segments    |
| Points per food | 10               |

---

## Code Structure

| Function  | Description                                              |
|-----------|----------------------------------------------------------|
| `setup()` | Initialises game state, snake position, food, and score |
| `draw()`  | Renders the board, snake, food, and score to the console |
| `input()` | Reads keyboard input and updates direction               |
| `logic()` | Moves the snake, handles collisions, and food eating     |
| `main()`  | Game loop with play-again support                        |

---

## Known Limitations

- **Windows only** — `<conio.h>` and `<windows.h>` are not available on Linux/macOS. To port, replace `_kbhit()`/`_getch()` with termios-based input and `Sleep()` with `usleep()`, and replace `system("cls")` with `system("clear")`.
- Snake array is fixed at **100 segments** — the game doesn't prevent growing beyond this limit.
- Food can spawn on top of the snake body (no spawn-safety check).

---

## License

This project is open source and free to use for learning and personal projects.

Author Amar

Developed as part of the Thiranex Internship Program.
