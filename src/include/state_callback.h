#ifndef STATE_CALLBACK_
#define STATE_CALLBACK_

#include <stdio.h>
#include <stdbool.h>
#include "token.h"


// Keywords
typedef struct {
    const char* lexeme;
    TokenType type;
} Keyword;

// Reserved symbols
typedef struct {
    const char c;
    TokenType type;
} Symbol;

extern const char* token_names[];

Token q2_callback(FILE *input, char symbol, Token *token);
Token q4_callback(FILE *input, char symbol, Token *token);
Token q6_callback(FILE *input, char symbol, Token *token);
Token q7_callback(FILE *input, char symbol, Token *token);
Token q9_callback(FILE *input, char symbol, Token *token);
Token q10_callback(FILE *input, char symbol, Token *token);
Token q11_callback(FILE *input, char symbol, Token *token);
Token q13_callback(FILE *input, char symbol, Token *token);
Token q14_callback(FILE *input, char symbol, Token *token);
Token q16_callback(FILE *input, char symbol, Token *token);
Token q17_callback(FILE *input, char symbol, Token *token);
Token q18_callback(FILE *input, char symbol, Token *token);

#endif //STATE_CALLBACK_