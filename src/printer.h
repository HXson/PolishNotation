#ifndef SRC_PRINTER_H_
#define SRC_PRINTER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define width_graph 80
#define height_graph 25

#define X width_graph / 2 - 1
#define Y 12

#define max_x 4 * M_PI
#define min_x 0
#define max_y 1
#define min_y -1

#define EPS 10E-6

#define rescaled_x (width_graph) / (max_x)
#define rescaled_y (height_graph * 0.999999 / 2) - 1


void red();
void reset_color();
void cyan();

void init_graph(char grid[width_graph][height_graph]);
void show_graph(char grid[width_graph][height_graph]);
void print_graph(int x, int y, char grid[width_graph][height_graph]);

#endif  // SRC_PRINTER_H_
