#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 3
#define COLS 4

void displayGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void generateMole(char grid[ROWS][COLS]) {
    int x = rand() % ROWS;
    int y = rand() % COLS;
    grid[x][y] = 'M';
}

void handleInput(char grid[ROWS][COLS], int* score) {
    int x, y;
    while (1) {
        printf("Enter coordinates to whack the mole (row [1-%d] and column [1-%d]): ", ROWS, COLS);
        int result = scanf("%d %d", &x, &y);

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
                grid[x][y] = '-';
                (*score)++;
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

int main() {
    char grid[ROWS][COLS];
    int score = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = '-';
        }
    }

    srand(time(NULL));

    printf("Whac-A-Mole Game Start!\n");
    printf("Score: %d\n", score);
    displayGrid(grid);

    generateMole(grid);
    printf("Mole appeared!\n");
    displayGrid(grid);

    handleInput(grid, &score);
    printf("Updated Grid:\n");
    displayGrid(grid);
    printf("Score: %d\n", score);

    return 0;
}
