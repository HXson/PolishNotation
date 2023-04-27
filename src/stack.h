#ifndef SRC_STACK_H_
#define SRC_STACK_H_

typedef struct stck {
    char symbol;
    struct stck *prevstack;
} stack;

typedef struct cstck {
    double value;
    struct cstck *prevstack;
} calcstack;

calcstack *initc(double value);
calcstack *pushc(calcstack *top, double value);
calcstack *popc(calcstack *top);
void destroyc(calcstack *top);

stack *init(char symbol);
stack *push(stack *top, char symbol);
stack *pop(stack *top);
void destroy(stack *top);

#endif  // SRC_STACK_H_
