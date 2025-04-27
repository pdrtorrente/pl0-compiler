#ifndef LEXICAL_H_
#define LEXICAL_H_

#include <stdio.h>
#include <stdbool.h>

#include "state_callback.h"

/**
 * 
 * TOKENS
 * 
 */
typedef enum {
    TOKEN_IDENTIFICADOR,
    TOKEN_NUMERO,
    TOKEN_PALAVRA_RESERVADA,
    TOKEN_OPERADOR,
    TOKEN_SIMBOLO,
    TOKEN_ERRO,
    TOKEN_BEGIN, TOKEN_END, TOKEN_IF, TOKEN_THEN, TOKEN_WHILE,
    TOKEN_DO, TOKEN_CONST, TOKEN_VAR, TOKEN_PROCEDURE, TOKEN_CALL, TOKEN_ODD,
    TOKEN_EOF
} TokenType;

typedef enum {
    IDENT,
    NUM,
    SPACE,
    OPERATOR,
    NUM_ALPHABET
} Alphabet;

typedef struct {
    TokenType type;
    char lexeme[64]; // texto do token
} Token;

/**
 * 
 * KEY WORDS
 * 
 */

typedef struct {
    const char* lexeme;
    TokenType type;
} Keyword;

Keyword keywords[] = {
    {"begin", TOKEN_BEGIN}, {"end", TOKEN_END}, {"if", TOKEN_IF},
    {"then", TOKEN_THEN}, {"while", TOKEN_WHILE}, {"do", TOKEN_DO},
    {"const", TOKEN_CONST}, {"var", TOKEN_VAR}, {"procedure", TOKEN_PROCEDURE},
    {"call", TOKEN_CALL}, {"odd", TOKEN_ODD}
};

#define NUM_KEYWORDS (sizeof(keywords) / sizeof(Keyword))

/**
 * 
 * STATES
 * 
 */

typedef enum {
    Q0,         // INITIAL STATE
    Q1,         // IDENTIFIER STATE
    Q_ERROR,    // ERROR STATE

    NUM_STATES
} state_num;

typedef state_num (*state_callback)(char symbol, Token *token);

//state[q0](new_symbol, &token);
state_callback states[] = {
    q0_callback,   qerror
};

state_num state_transactions[NUM_STATES][NUM_ALPHABET] = {
    {Q0, Q_ERROR},
    {Q_ERROR, Q0}
};

Token get_token(FILE *input);

#endif // LEXICAL_H_