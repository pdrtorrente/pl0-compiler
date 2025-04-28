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

void q2_callback(FILE *input, char symbol, Token *token);
void q4_callback(FILE *input, char symbol, Token *token);
void q6_callback(FILE *input, char symbol, Token *token);
void q7_callback(FILE *input, char symbol, Token *token);
void q9_callback(FILE *input, char symbol, Token *token);
void q10_callback(FILE *input, char symbol, Token *token);
void q11_callback(FILE *input, char symbol, Token *token);
void q13_callback(FILE *input, char symbol, Token *token);
void q14_callback(FILE *input, char symbol, Token *token);
void q16_callback(FILE *input, char symbol, Token *token);
void q17_callback(FILE *input, char symbol, Token *token);
void q18_callback(FILE *input, char symbol, Token *token);

#endif //STATE_CALLBACK_