#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // For Sleep()

#define ROWS 3
#define COLS 4
#define GAME_DURATION 60 // Game duration in seconds

void displayGrid(char grid[ROWS][COLS], int displayTime) {
    system("cls"); // Clear the console for updated grid
    printf("Timer: %d seconds\n", displayTime);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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

void handleInput(char grid[ROWS][COLS], int* score) {
    int x, y;
    while (1) {
        printf("Enter coordinates to whack the mole (row [1-%d] and column [1-%d]): ", ROWS, COLS);
        int result = scanf_s("%d %d", &x, &y);

        if (result != 2) {
            printf("Invalid input. Please enter two numbers.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        x--; // Adjust for 1-based input
        y--;

        if (x >= 0 && x < ROWS && y >= 0 && y < COLS) {
            if (grid[x][y] == 'M') {
                printf("You hit the mole!\n");
                (*score)++;
                return;
            }
            else {
                printf("Miss! No mole here.\n");
            }
            break; // Exit loop after valid input
        }
        else {
            printf("Coordinates out of range. Try again.\n");
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
    srand(time(NULL));

    printf("Whac-A-Mole Game Start!\n");

    int difficulty = selectDifficulty();
    int sleepTime;
    switch (difficulty) {
    case 1: sleepTime = 2000; break; // Easy: 2 seconds
    case 2: sleepTime = 1000; break; // Normal: 1 second
    case 3: sleepTime = 500; break; // Hard: 0.5 seconds
    }

    generateMole(grid); // Initial mole generation

    time_t startTime = time(NULL); // Initialize startTime here

    while (1) {
        int elapsedTime = (int)(time(NULL) - startTime);
        int remainingTime = GAME_DURATION - elapsedTime;

        if (remainingTime <= 0) {
            break;
        }

        displayGrid(grid, remainingTime);
        handleInput(grid, &score);
        generateMole(grid); // Generate a new mole after each input
        Sleep(sleepTime); // Adjust game speed based on difficulty
    }

    printf("Game Over! Final Score: %d\n", score);

    return 0;
}
