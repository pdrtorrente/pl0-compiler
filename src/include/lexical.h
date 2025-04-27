#ifndef LEXICAL_H_
#define LEXICAL_H_

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * 
 * TOKENS
 * 
 */
typedef enum {
    TOKEN_UNDEFINED = -1,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_PALAVRA_RESERVADA,
    TOKEN_OPERADOR,
    TOKEN_SIMBOLO,
    TOKEN_MINUS,
    TOKEN_MINUS_EQUAL,
    TOKEN_ERROR,
    TOKEN_BEGIN, TOKEN_END, TOKEN_IF, TOKEN_THEN, TOKEN_WHILE,
    TOKEN_DO, TOKEN_CONST, TOKEN_VAR, TOKEN_PROCEDURE, TOKEN_CALL, TOKEN_ODD,
    TOKEN_EOF
} TokenType;

typedef enum {
    ALPHA,
    NUM,
    MINUS,
    EQUAL,
    SPACE,
    ERROR,

    NUM_ALPHABET
} Alphabet;

typedef struct {
    TokenType type;
    char lexeme[64]; // texto do token
    int it;
    bool tkn_ready;
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

extern Keyword keywords[];

/**
 * 
 * STATES
 * 
 */

typedef enum {
    Q0,         // INITIAL STATE
    Q1,         // IDENTIFIER STATE
    Q2,
    Q3,
    Q_ERROR,    // ERROR STATE
    QFINISH,

    NUM_STATES,
} state_num;

typedef state_num (*state_callback)(char symbol, Token *token);

Token get_token(FILE *input);

extern state_callback states[];
extern state_num state_transactions[NUM_STATES][NUM_ALPHABET];

#endif // LEXICAL_H_