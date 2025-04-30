#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_UNDEFINED,

    TOKEN_COMMENT,
    TOKEN_NUMBER,
    TOKEN_PALAVRA_RESERVADA,
    TOKEN_IDENTIFIER,
    TOKEN_TRUNCATED_ID,
    
    // Tokens de fim de arquivo e de ERROR
    TOKEN_EOF,
    TOKEN_ERROR,

    // Tokens para palavras reservadas
    TOKEN_BEGIN,        // 'begin'
    TOKEN_END,          // 'end'       
    TOKEN_IF,           // 'if'
    TOKEN_THEN,         // 'then'
    TOKEN_WHILE,        // 'while'
    TOKEN_DO,           // 'do' 
    TOKEN_CONST,        // 'const'
    TOKEN_VAR,          // 'var'            
    TOKEN_PROCEDURE,    // 'procedure'
    TOKEN_CALL,         // 'call'                                        
    TOKEN_ODD,          // 'odd'


    // Tokens para operadores e símbolos reservados
    TOKEN_PLUS,         // '+'
    TOKEN_MINUS,        // '-'
    TOKEN_MULTIPLY,     // '*'
    TOKEN_DIVIDE,       // '/'
    TOKEN_EQUAL,        // '='
    TOKEN_LPAREN,       // '('
    TOKEN_RPAREN,       // ')'
    TOKEN_SEMICOLON,    // ';'
    TOKEN_COMMA,        // ','
    TOKEN_PERIOD,       // '.'

    // Tokens para operadores relacionais e de atribuição
    TOKEN_GREATER,      // '>'
    TOKEN_GREATER_EQ,   // '>='
    TOKEN_LESS,         // '<'
    TOKEN_LESS_EQ,      // '<='
    TOKEN_DIFFERENT,    // '<>'
    TOKEN_ASSIGN        // ':='
} TokenType;


typedef struct {
    TokenType type;     // Classificação do token 
    char lexeme[64];    // Buffer para armazenar o lexema
} Token;

#define MAX_VAR_SIZE 16
#endif // TOKEN_H
