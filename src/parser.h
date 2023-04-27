#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_
#define PLUS '+'
#define MINUS '-'
#define UNARMINUS 'm'
#define MUL '*'
#define DEV '/'
#define OPBRACK '('
#define CLBRACK ')'
#define SIN 's'
#define COS 'c'
#define TAN 't'
#define CTG 'g'
#define SQRT 'q'
#define LN 'l'
#define POW '^'
#define END 'e'

int is_binary_op(const char *symb);
int get_priority(char symb);
int parse(char *exits);

#endif  // SRC_PARSER_H_
