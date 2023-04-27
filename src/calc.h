#ifndef SRC_CALC_H_
#define SRC_CALC_H_
#include "stack.h"

double calc_all(double x, char **tokens, int lentokens);
int calc_universal(int (*func_ptr)(calcstack **p), calcstack **ptop);
int calc_plus(calcstack **ptop);
int calc_minus(calcstack **ptop);
int calc_unarminus(calcstack **ptop);
int calc_mul(calcstack **ptop);
int calc_dev(calcstack **ptop);
int calc_sin(calcstack **ptop);
int calc_cos(calcstack **ptop);
int calc_tan(calcstack **ptop);
int calc_ctg(calcstack **ptop);
int calc_sqrt(calcstack **ptop);
int calc_ln(calcstack **ptop);
int calc_pow(calcstack **ptop);
int is_num(const char *token);

#endif  // SRC_CALC_H_
