#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"
#include "parser.h"
#include "printer.h"
#include "stack.h"

int main() {
    printf(
        "You are allowed to use only '+', '-', '*', '/', '(', ')', '^', 'sin()', 'cos()', "
        "'tan()', 'ctg()', 'sqrt()', 'ln()'\nInput expression: ");
    int is_ok = 0;
    char input[100000] = "";
    is_ok = !parse(input);

    if (is_ok) {
        char *array[100000];
        int j = 0;
        char *ptr = strtok(input, " ");
        array[j] = ptr;
        while (ptr != NULL) {
            j++;
            ptr = strtok(NULL, " ");
            array[j] = ptr;
        }
        char grid[width_graph][height_graph];
        double x;
        init_graph(grid);
        int was_correct_point = 0;
        for (x = 0; x < max_x + EPS; x += max_x / (width_graph)) {
            double y;
            y = calc_all(x, array, j);
            if (!isnan(y)) {
                was_correct_point = 1;
                print_graph(rintf(x * rescaled_x), rintf(-y * rescaled_y), grid);
            }
        }
        if (was_correct_point) {
            show_graph(grid);
        } else {
            is_ok = 0;
        }
    }
    if (!is_ok) {
        printf("Input error. You need to enter correct expression");
    }

    return 0;
}
