#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_UNDEFINED,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_PALAVRA_RESERVADA,

    // Tokens para palavras reservadas
    TOKEN_BEGIN, 
    TOKEN_END, 
    TOKEN_IF, 
    TOKEN_THEN, 
    TOKEN_WHILE,
    TOKEN_DO, 
    TOKEN_CONST, 
    TOKEN_VAR, 
    TOKEN_PROCEDURE, 
    TOKEN_CALL, 
    TOKEN_ODD,
    TOKEN_EOF,
    TOKEN_ERROR,

    // Tokens para operadores e símbolos reservados
    TOKEN_PLUS,         // '+'
    TOKEN_MINUS,        // '-'
    TOKEN_MULTIPLY,     // '*'
    TOKEN_DIVIDE,       // '/'
    TOKEN_EQUAL,        // '='
    TOKEN_LPAREN,       // '('
    TOKEN_RPAREN,       // ')'
    TOKEN_SEMICOLON,    // ';'

    // Tokens para operadores relacionais e de atribuição
    TOKEN_GREATER,      // '>'
    TOKEN_GREATER_EQ,   // '>='
    TOKEN_LESS,         // '<'
    TOKEN_LESS_EQ,      // '<='
    TOKEN_DIFFERENT,    // '<>'
    TOKEN_ASSIGN        // ':='
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[64];
    int it;
} Token;

#endif // TOKEN_H
