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

int main() {
    char grid[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = '-';
        }
    }

    srand(time(NULL));

    printf("Whac-A-Mole Game Start!\n");
    displayGrid(grid);

    generateMole(grid);
    printf("Mole appeared!\n");
    displayGrid(grid);

    return 0;
}
