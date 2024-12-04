#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // For Sleep()
#include <conio.h> // For _kbhit() and _getch()

#define ROWS 3
#define COLS 4
#define GAME_DURATION 60 // Game duration in seconds

void displayGrid(char grid[ROWS][COLS], int displayTime, int playerX, int playerY) {
    system("cls"); // Clear the console for updated grid
    printf("Timer: %d seconds\n", displayTime);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == playerX && j == playerY) {
                printf("P "); // Player position
            }
            else {
                printf("%c ", grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("Use W/A/S/D to move and Space to whack the mole!\n");
}

void clearTheGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = '-';
        }
    }
}

void generateMole(char grid[ROWS][COLS]) {
    clearTheGrid(grid); // Clear the grid before placing a new mole
    int x = rand() % ROWS;
    int y = rand() % COLS;
    grid[x][y] = 'M';
}

void handlePlayerInput(char grid[ROWS][COLS], int* score, int* playerX, int* playerY) {
    if (_kbhit()) {
        char input = _getch();

        switch (input) {
        case 'w': // Move up
            if (*playerX > 0) (*playerX)--;
            break;
        case 's': // Move down
            if (*playerX < ROWS - 1) (*playerX)++;
            break;
        case 'a': // Move left
            if (*playerY > 0) (*playerY)--;
            break;
        case 'd': // Move right
            if (*playerY < COLS - 1) (*playerY)++;
            break;
        case ' ': // Whack the mole
            if (grid[*playerX][*playerY] == 'M') {
                printf("You hit the mole!\n");
                (*score)++;
                generateMole(grid);
            }
            else {
                printf("Miss! No mole here.\n");
            }
            Sleep(100); // Reduced delay after whacking
            break;
        }
    }
}

int selectDifficulty() {
    int difficulty;
    printf("Select difficulty (1 = Easy, 2 = Normal, 3 = Hard): ");
    while (scanf_s("%d", &difficulty) != 1 || difficulty < 1 || difficulty > 3) {
        printf("Invalid selection. Please choose 1, 2, or 3: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    return difficulty;
}

int main() {
    char grid[ROWS][COLS];
    int score = 0;
    int playerX = 0, playerY = 0; // Initial player position
    srand(time(NULL));

    printf("Whac-A-Mole Game Start!\n");

    int difficulty = selectDifficulty();
    int sleepTime;
    switch (difficulty) {
    case 1: sleepTime = 100; break; // Easy: 100ms
    case 2: sleepTime = 50; break;  // Normal: 50ms
    case 3: sleepTime = 25; break;  // Hard: 25ms
    }

    generateMole(grid); // Initial mole generation

    time_t startTime = time(NULL); // Initialize startTime here

    while (1) {
        int elapsedTime = (int)(time(NULL) - startTime);
        int remainingTime = GAME_DURATION - elapsedTime;

        if (remainingTime <= 0) {
            break;
        }

        displayGrid(grid, remainingTime, playerX, playerY);
        handlePlayerInput(grid, &score, &playerX, &playerY);
        Sleep(sleepTime); // Faster refresh rate for smoother gameplay
    }

    printf("Game Over! Final Score: %d\n", score);

    return 0;
}
