#include "parser.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int parse(char *exits) {
    char space = ' ';
    stack *top = init('e');
    char exp[100000] = "";
    char temp;
    char *pexp = exp;
    do {
        scanf("%c", &temp);
        if (temp == '\n') {
            *pexp = '\0';
        } else {
            *pexp = temp;
        }
        pexp++;
    } while (temp != '\n');
    int check = 0;
    int error = 0;
    int func_availability = 1;
    // если цифра или закрывающаяся скобка то после нее обязательно бинарный знак.
    for (char *p = exp; *p; p = p + 1) {
        if (*p == 'x' || (*p >= '0' && *p <= '9')) {
            strncat(exits, p, 1);
            check = 1;
            func_availability = 0;
        } else if (*p == 's' && p[1] == 'i' && p[2] == 'n' && p[3] == '(' && func_availability) {
            top = push(top, SIN);
            p += 2;
            func_availability = 0;
        } else if (*p == 's' && p[1] == 'q' && p[2] == 'r' && p[3] == 't' && p[4] == '(' &&
                   func_availability) {
            top = push(top, SQRT);
            p += 3;
            func_availability = 0;
        } else if (*p == 'c' && p[1] == 'o' && p[2] == 's' && p[3] == '(' && func_availability) {
            top = push(top, COS);
            p += 2;
            func_availability = 0;
        } else if (*p == 't' && p[1] == 'a' && p[2] == 'n' && p[3] == '(' && func_availability) {
            top = push(top, TAN);
            p += 2;
            func_availability = 0;
        } else if (*p == 'c' && p[1] == 't' && p[2] == 'g' && p[3] == '(' && func_availability) {
            top = push(top, CTG);
            p += 2;
            func_availability = 0;
        } else if (*p == '-' && check == 0) {
            top = push(top, UNARMINUS);
        } else if (*p == 'l' && p[1] == 'n') {
            top = push(top, LN);
            p += 1;
        } else if (is_binary_op(p)) {
            func_availability = 1;
            char symb;
            if (check == 0 && *p == '-') {
                symb = 'm';
            } else {
                symb = *p;
            }
            while (get_priority(top->symbol) >= get_priority(symb)) {
                strncat(exits, &space, 1);
                strncat(exits, &top->symbol, 1);
                top = pop(top);
            }
            top = push(top, symb);
            strncat(exits, &space, 1);
            check = 0;
        } else if (*p == '(') {
            func_availability = 1;
            top = push(top, OPBRACK);
            check = 0;
        } else if (*p == ')') {
            func_availability = 0;
            while (top->symbol != OPBRACK && top->symbol != END) {
                strncat(exits, &space, 1);
                strncat(exits, &top->symbol, 1);
                top = pop(top);
            }
            if (top->symbol != END) {
                top = pop(top);
                check = 1;
            } else {
                error = 1;
            }
        } else {
            error = 1;
        }
    }
    while (top->symbol != END) {
        if (top->symbol == '(') {
            error = 1;
        }
        strncat(exits, &space, 1);
        strncat(exits, &top->symbol, 1);

        top = pop(top);
    }
    destroy(top);
    return error;
}

int get_priority(char symb) {
    int pr = 0;
    if (symb == PLUS || symb == MINUS) {
        pr = 1;
    } else if (symb == MUL || symb == DEV) {
        pr = 2;
    } else if (symb == POW) {
        pr = 3;
    } else if (symb == SIN || symb == COS || symb == TAN || symb == CTG || symb == SQRT || symb == LN ||
               symb == UNARMINUS) {
        pr = 4;
    }
    return pr;
}

int is_binary_op(const char *symb) {
    int ans;
    ans = (*symb == PLUS || *symb == MINUS || *symb == MUL || *symb == DEV || *symb == POW);
    return ans;
}
