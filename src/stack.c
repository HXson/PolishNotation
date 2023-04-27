#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

stack *init(char symbol) {
    stack *st = malloc(sizeof(stack));
    st->symbol = symbol;
    st->prevstack = NULL;
    return st;
}

stack *push(stack *top, char symbol) {
    stack *st = malloc(sizeof(stack));
    st->symbol = symbol;
    st->prevstack = top;
    return st;
}

stack *pop(stack *top) {
    stack *prev;
    if (top == NULL) {
        prev = top;
    } else {
        prev = top->prevstack;
    }
    free(top);
    return prev;
}

void destroy(stack *top) {
    stack *save = top;
    while (save != NULL) {
        save = top->prevstack;
        free(top);
        top = save;
    }
    free(top);
}

// -------------------------

calcstack *initc(double value) {
    calcstack *st = malloc(sizeof(calcstack));
    st->value = value;
    st->prevstack = NULL;
    return st;
}

calcstack *pushc(calcstack *top, double value) {
    calcstack *st = malloc(sizeof(calcstack));
    st->value = value;
    st->prevstack = top;
    return st;
}

calcstack *popc(calcstack *top) {
    calcstack *prev;
    if (top == NULL) {
        prev = top;
    } else {
        prev = top->prevstack;
    }
    free(top);
    return prev;
}

void destroyc(calcstack *top) {
    calcstack *save = top;
    while (save != NULL) {
        save = top->prevstack;
        free(top);
        top = save;
    }
    free(top);
}
