#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "state_callback.h"

// Lista de palavras reservadas
Keyword keywords[] = {
    {"begin", TOKEN_BEGIN}, 
    {"end", TOKEN_END}, 
    {"if", TOKEN_IF},
    {"then", TOKEN_THEN}, 
    {"while", TOKEN_WHILE}, 
    {"do", TOKEN_DO},
    {"const", TOKEN_CONST},
    {"var", TOKEN_VAR},
    {"procedure", TOKEN_PROCEDURE},
    {"call", TOKEN_CALL}, 
    {"odd", TOKEN_ODD}
};

// Lista de símbolos reservados
Keyword simbols[] = {
    {"+", TOKEN_PLUS},
    {"-", TOKEN_MINUS},
    {"*", TOKEN_MULTIPLY},
    {"/", TOKEN_DIVIDE},
    {"=", TOKEN_EQUAL},
    {"(", TOKEN_LPAREN},
    {")", TOKEN_RPAREN},
    {";", TOKEN_SEMICOLON},
};

const char* token_names[] = {
    "token_undefined",
    "token_identifier",
    "token_number",
    "token_palavra_reservada",

    // Palavras reservadas
    "token_begin",
    "token_end",
    "token_if",
    "token_then",
    "token_while",
    "token_do",
    "token_const",
    "token_var",
    "token_procedure",
    "token_call",
    "token_odd",
    "token_eof",
    "token_error",

    // Operadores e símbolos reservados
    "token_plus",
    "token_minus",
    "token_multiply",
    "token_divide",
    "token_equal",
    "token_lparen",
    "token_rparen",
    "token_semicolon",

    // Operadores relacionais e de atribuição
    "token_greater",
    "token_greater_eq",
    "token_less",
    "token_less_eq",
    "token_different",
    "token_assign"
};

#define NUM_KEYWORDS (sizeof(keywords) / sizeof(Keyword))

void backtracking(FILE *input, char *str) {
    // Remove o último caracter da string do token
    int len = strlen(str);
    if (len > 0) {
        str[len - 1] = '\0';
    }

    // Volta em 1 posição o ponteiro do arquivo de entrada
    fseek(input, -1, SEEK_CUR);
}

// Identifier and Keywords
Token q2_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_IDENTIFIER;
    backtracking(input, token->lexeme);
    return *token;
}

// Números reais interos
Token q4_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_NUMBER;
    backtracking(input, token->lexeme);
    return *token;
}

// '>='
Token q6_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_GREATER_EQ;
    return *token; 
}

// '>'
Token q7_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_GREATER;
    backtracking(input, token->lexeme);
    return *token; 
}

// '<>'
Token q9_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_DIFFERENT;
    return *token; 
}

// '<='
Token q10_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_LESS_EQ;
    return *token; 
}

// '<'
Token q11_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_LESS;
    backtracking(input, token->lexeme);
    return *token; 
}

// ':='
Token q13_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_ASSIGN;
    return *token; 
}

// ':' --> ERROR
Token q14_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_ERROR;
    backtracking(input, token->lexeme);
    return *token; 
}

// Comentários --> acho que a ideia é só consumir os comentários
Token q16_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_UNDEFINED;
    backtracking(input, token->lexeme);
    return *token; 
}

// ERROR
Token q17_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_ERROR;
    return *token; 
}

// Símbolos Reservados
Token q18_callback(FILE *input, char symbol, Token *token) { 
    token->type = TOKEN_PALAVRA_RESERVADA;
    return *token; 
}

Token qfinish(char symbol, Token *token) {
    token->lexeme[--token->it] = '\0';
    return *token;
}