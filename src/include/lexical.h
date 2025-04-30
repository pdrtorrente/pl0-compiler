#ifndef LEXICAL_H_
#define LEXICAL_H_

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "state_callback.h"

typedef void (*state_callback)(FILE *input, char symbol, Token *token);

Token getToken(FILE *input);

extern state_callback states[];

#endif // LEXICAL_H_