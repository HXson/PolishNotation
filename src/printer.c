#include "printer.h"

void cyan() { printf("\033[0;40;36m"); }
void red() { printf("\033[1;97;40m"); }
void reset_color() { printf("\033[0m"); }

void show_graph(char grid[width_graph][height_graph]) {
    int x, y;
    for (y = 0; y < height_graph; y++) {
        for (x = 0; x < width_graph; x++) {
            if (grid[x][y] == '*') {
                red();
                putchar(grid[x][y]);
                reset_color();
            } else {
                cyan();
                putchar(grid[x][y]);
                reset_color();
            }
        }

        putchar('\n');
    }
}

void init_graph(char grid[width_graph][height_graph]) {
    int x, y;
    for (y = 0; y < height_graph; y++) {
        for (x = 0; x < width_graph; x++) {
            grid[x][y] = '.';
        }
    }
}

void print_graph(int x, int y, char grid[width_graph][height_graph]) {
    if (y < max_y * rescaled_y && y > min_y * rescaled_y) {
        grid[x][Y - y - 1] = '*';
    }
}
