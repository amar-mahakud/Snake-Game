#include <iostream>
#include <conio.h>    // for _kbhit() and _getch() - Windows only
#include <windows.h>  // for Sleep() - Windows only
#include <cstdlib>
#include <ctime>
using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

int snakeX[100], snakeY[100]; // arrays to store snake body coordinates
int snakeLength;

int foodX, foodY;
int score;

char direction; // 'U', 'D', 'L', 'R'
bool gameOver;

// ---------------- Setup ----------------
void setup() {
    gameOver = false;
    direction = 'R'; // start moving right

    // Initial snake position (center of board)
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    snakeLength = 1;

    // Initial food position
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;

    score = 0;
}

// ---------------- Draw Board ----------------
void draw() {
    system("cls"); // clear screen (Windows). Use "clear" on Linux/Mac

    // Top wall
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << "\n";

    // Game area
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0)
                cout << "#"; // left wall

            bool printed = false;

            // Check if this cell is the snake head
            if (x == snakeX[0] && y == snakeY[0]) {
                cout << "O";
                printed = true;
            }

            // Check if this cell is part of the snake body
            if (!printed) {
                for (int i2 = 1; i2 < snakeLength; i2++) {
                    if (x == snakeX[i2] && y == snakeY[i2]) {
                        cout << "o";
                        printed = true;
                        break;
                    }
                }
            }

            // Check if this cell is food
            if (!printed && x == foodX && y == foodY) {
                cout << "F";
                printed = true;
            }

            // Otherwise empty space
            if (!printed)
                cout << " ";

            if (x == WIDTH - 1)
                cout << "#"; // right wall
        }
        cout << "\n";
    }

    // Bottom wall
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << "\n";

    cout << "Score: " << score << "\n";
    cout << "Controls: W/A/S/D to move, X to quit\n";
}

// ---------------- Input Handling ----------------
void input() {
    if (_kbhit()) { // returns true if a key has been pressed
        switch (_getch()) {
            case 'w':
            case 'W':
                if (direction != 'D') // prevent reversing into self
                    direction = 'U';
                break;
            case 's':
            case 'S':
                if (direction != 'U')
                    direction = 'D';
                break;
            case 'a':
            case 'A':
                if (direction != 'R')
                    direction = 'L';
                break;
            case 'd':
            case 'D':
                if (direction != 'L')
                    direction = 'R';
                break;
            case 'x':
            case 'X':
                gameOver = true; // manual quit
                break;
        }
    }
}

// ---------------- Game Logic ----------------
void logic() {
    // Save the head's previous position (used to shift body segments)
    int prevX = snakeX[0];
    int prevY = snakeY[0];
    int prev2X, prev2Y;

    // Move the head based on direction
    switch (direction) {
        case 'U': snakeY[0]--; break;
        case 'D': snakeY[0]++; break;
        case 'L': snakeX[0]--; break;
        case 'R': snakeX[0]++; break;
    }

    // Move the body: each segment follows the one in front of it
    for (int i = 1; i < snakeLength; i++) {
        prev2X = snakeX[i];
        prev2Y = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Check if snake ate the food
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        score += 10;
        snakeLength++;
        // New segment takes the position the old tail just vacated
        snakeX[snakeLength - 1] = prevX;
        snakeY[snakeLength - 1] = prevY;

        // Generate new food position
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    }

    // Check wall collision
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT)
        gameOver = true;

    // Check self collision
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
            gameOver = true;
    }
}

// ---------------- Main ----------------
int main() {
    srand(time(0)); // seed random number generator for food positions

    char playAgain;

    do {
        setup();

        while (!gameOver) {
            draw();
            input();
            logic();
            Sleep(100); // controls game speed (lower = faster)
        }

        cout << "\n===== GAME OVER =====\n";
        cout << "Final Score: " << score << "\n";
        cout << "Play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
