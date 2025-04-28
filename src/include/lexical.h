#ifndef LEXICAL_H_
#define LEXICAL_H_

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "state_callback.h"

typedef enum state_num state_num;

typedef Token (*state_callback)(FILE *input, char symbol, Token *token);

int isFinal(state_num Q);

Token get_token(FILE *input);

extern state_callback states[];

#endif // LEXICAL_H_