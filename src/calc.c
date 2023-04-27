#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "calc.h"

double calc_all(double x, char **tokens, int lentokens) {
    double result = NAN;
    if (is_num(tokens[0])) {
        double num;
        int res = 1;
        num = (tokens[0][0] == 'x') ? x : atof(tokens[0]);
        calcstack *top = initc(num);
        calcstack **ptop = &top;
        for (int i = 1; i < lentokens; i++) {
            if (is_num(tokens[i])) {
                num = (tokens[i][0] == 'x') ? x : atof(tokens[i]);
                (*ptop) = pushc((*ptop), num);
            } else {
                int (*func_ptr)(calcstack * *ptop);
                if (tokens[i][0] == PLUS) {
                    func_ptr = &calc_plus;
                } else if (tokens[i][0] == MINUS) {
                    func_ptr = &calc_minus;
                } else if (tokens[i][0] == UNARMINUS) {
                    func_ptr = &calc_unarminus;
                } else if (tokens[i][0] == MUL) {
                    func_ptr = &calc_mul;
                } else if (tokens[i][0] == DEV) {
                    func_ptr = &calc_dev;
                } else if (tokens[i][0] == SIN) {
                    func_ptr = &calc_sin;
                } else if (tokens[i][0] == COS) {
                    func_ptr = &calc_cos;
                } else if (tokens[i][0] == TAN) {
                    func_ptr = &calc_tan;
                } else if (tokens[i][0] == CTG) {
                    func_ptr = &calc_ctg;
                } else if (tokens[i][0] == SQRT) {
                    func_ptr = &calc_sqrt;
                } else if (tokens[i][0] == LN) {
                    func_ptr = &calc_ln;
                } else if (tokens[i][0] == POW) {
                    func_ptr = &calc_pow;
                }
                res = calc_universal(func_ptr, ptop);
                if (res == 0) {
                    break;
                }
            }
        }
        if (res && (*ptop)->prevstack == NULL) result = (*ptop)->value;
        destroyc((*ptop));
    }
    return result;
}

int calc_plus(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    if (top->prevstack != NULL) {
        double temp = top->value + top->prevstack->value;
        top = popc(top);
        top->value = temp;
        (*ptop) = top;
    } else {
        res = 0;
    }
    return res;
}

int calc_minus(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    if (top->prevstack != NULL) {
        double temp = top->prevstack->value - top->value;
        top = popc(top);
        top->value = temp;
        (*ptop) = top;
    } else {
        res = 0;
    }
    return res;
}

int calc_mul(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    if (top->prevstack != NULL) {
        double temp = top->value * top->prevstack->value;
        top = popc(top);
        top->value = temp;
        (*ptop) = top;
    } else {
        res = 0;
    }
    return res;
}

int calc_dev(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    if (top->prevstack != NULL) {
        double temp = top->prevstack->value / top->value;
        res = !isnan(temp) && !isinf(temp);
        top = popc(top);
        top->value = temp;
        (*ptop) = top;
    } else {
        res = 0;
    }
    return res;
}

int calc_unarminus(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    double temp = -(top->value);
    top->value = temp;
    (*ptop) = top;
    return res;
}

int calc_sin(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    double temp = sin(top->value);
    res = !isnan(temp) && !isinf(temp);
    top->value = temp;
    (*ptop) = top;
    return res;
}

int calc_cos(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    double temp = cos(top->value);
    res = !isnan(temp) && !isinf(temp);
    top->value = temp;
    (*ptop) = top;
    return res;
}

int calc_tan(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    double temp = tan(top->value);
    res = !isnan(temp) && !isinf(temp);
    top->value = temp;
    (*ptop) = top;
    return res;
}

int calc_ctg(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    double temp = 1.0 / (tan(top->value));
    res = !isnan(temp) && !isinf(temp);
    top->value = temp;
    (*ptop) = top;
    return res;
}

int calc_sqrt(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    double temp = sqrt(top->value);
    res = !isnan(temp) && !isinf(temp);
    top->value = temp;
    (*ptop) = top;
    return res;
}

int calc_ln(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    double temp = log(top->value);
    res = !isnan(temp) && !isinf(temp);
    top->value = temp;
    (*ptop) = top;
    return res;
}

int calc_pow(calcstack **ptop) {
    calcstack *top = (*ptop);
    int res = 1;
    if (top->prevstack != NULL) {
        double temp = pow(top->prevstack->value, top->value);
        res = !isnan(temp) && !isinf(temp);
        top = popc(top);
        top->value = temp;
        (*ptop) = top;
    } else {
        res = 0;
    }
    return res;
}

int is_num(const char *token) {
    int res = 0;
    if (token[0] == 'x' || (token[0] >= '0' && token[0] <= '9')) {
        res = 1;
    }
    return res;
}

int calc_universal(int (*func_ptr)(calcstack **p), calcstack **ptop) {
    int res = (*func_ptr)(ptop);
    return res;
}
