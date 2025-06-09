#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"

Token token_atual;
FILE *fonte;

void erro(const char *mensagem, Token *token) {
    if(token->type == TOKEN_ERROR) {
        fprintf(stderr, "Erro lexico na linha %d caracter %d: caracter '%s' nao reconhecido\n", token->line, token->caracter, token->lexeme);
        exit(EXIT_FAILURE);
    } 
    else if(token->type == TOKEN_COMMENT_ERROR) {
        fprintf(stderr, "Erro lexico na linha %d caracter %d: comentario mal formado.\n", token->line, token->caracter);
        exit(EXIT_FAILURE);
    }   
    else if(token->type == TOKEN_EOF) {
        fprintf(stderr, "Erro na linha %d caracter %d: EOF inesperado\n", token->line, token->caracter);
        exit(EXIT_FAILURE);
    } else {
        fprintf(stderr, "Erro sintatico na linha %d caracter %d: %s (token: %s)\n", token->line, token->caracter, mensagem, token->lexeme);
        exit(EXIT_FAILURE);
    }
}

// void consome(FILE *input, TokenType tipo, Token *token) {
//     if(token->type == tipo) {
//         *token = getToken(input);
//     } else {
//         erro("Token inesperado");
//     }
// }

void ASD_preditiva(FILE *input, Token *token) {
    *token = getToken(input);
    programa(input, token);

    if(token->type == TOKEN_EOF) 
        printf("Programa Compilado com SUCESSO!!!");
    else 
        erro("Esperado EOF", token);
}

void programa(FILE *input, Token *token) {
    constante(input, token);
    variavel(input, token);
    procedimento(input, token);
    comando(input, token);

    if(token->type == TOKEN_PERIOD) 
        *token = getToken(input);
    else 
        erro("Esperado '.'", token);
}

void constante(FILE *input, Token *token) {
    if(token->type == TOKEN_CONST) {
        *token = getToken(input);

        if(token->type == TOKEN_IDENTIFIER) 
            *token = getToken(input);
        else 
            erro("Esperado identificador", token);
        
        if(token->type == TOKEN_EQUAL) 
            *token = getToken(input);
        else 
            erro("Esperado '='", token);
        
        if(token->type == TOKEN_NUMBER) 
            *token = getToken(input); 
        else 
            erro("Esperado numero", token);

        mais_const(input, token);

        if(token->type == TOKEN_SEMICOLON) 
            *token = getToken(input);
        else 
            erro("Esperado ';'", token);
    }
}

void mais_const(FILE *input, Token *token) {
    if(token->type == TOKEN_COMMA) {
        *token = getToken(input);
        
        if(token->type == TOKEN_IDENTIFIER) 
            *token = getToken(input);
        else 
            erro("Esperado identificador", token);
        if(token->type == TOKEN_EQUAL) 
            *token = getToken(input); 
        else 
            erro("Esperado '='", token);
        if(token->type == TOKEN_NUMBER)
            *token = getToken(input);
        else
            erro("Esperado numero", token);

        mais_const(input, token);
    }
}

void variavel(FILE *input, Token *token) {
    if(token->type == TOKEN_VAR) {
        *token = getToken(input);
        if(token->type == TOKEN_IDENTIFIER) 
            *token = getToken(input);
        else
            erro("Esperado identificador", token);
        
        while (token->type == TOKEN_COMMA) {
            *token = getToken(input);
            if(token->type == TOKEN_IDENTIFIER) 
                *token = getToken(input); 
            else 
                erro("Esperado identificador", token);
        }
        if(token->type == TOKEN_SEMICOLON) 
            *token = getToken(input); 
        else 
            erro("Esperado ';'", token);
    }
}

void mais_var(FILE *input, Token *token) {
    if (token->type == TOKEN_COMMA) {
        *token = getToken(input);
        if(token->type == TOKEN_IDENTIFIER) 
            *token = getToken(input); 
        else 
            erro("Esperado identificador", token);
        mais_var(input, token);
    }
}

void procedimento(FILE *input, Token *token) {
    if (token->type == TOKEN_PROCEDURE) {
        *token = getToken(input);
        if(token->type == TOKEN_IDENTIFIER) 
            *token = getToken(input);
        else 
            erro("Esperado identificador", token);

        if(token->type == TOKEN_SEMICOLON) 
            *token = getToken(input); 
        else 
            erro("Esperado ';'", token);

        constante(input, token);
        variavel(input, token);
        procedimento(input, token);
        comando(input, token);

        if(token->type == TOKEN_SEMICOLON) 
            *token = getToken(input); 
        else 
            erro("Esperado ';'", token);

        procedimento(input, token);
    }
}

void comando(FILE *input, Token *token) {
    if(token->type == TOKEN_IDENTIFIER) {
        *token = getToken(input);

        if(token->type == TOKEN_ASSIGN)
            *token = getToken(input);
        else
            erro("Esperado ':='", token);

        expressao(input, token);
    } else if(token->type == TOKEN_CALL) {
        *token = getToken(input);

        if(token->type == TOKEN_IDENTIFIER) 
            *token = getToken(input); 
        else 
            erro("Esperado identificador", token);
    } else if(token->type == TOKEN_BEGIN) {
        *token = getToken(input);
        comando(input, token);
        mais_cmd(input, token);

        if(token->type == TOKEN_END) 
            *token = getToken(input);
        else 
            erro("Esperado 'end'", token);
        
    } else if(token->type == TOKEN_IF) {
        *token = getToken(input);
        condicao(input, token);

        if(token->type == TOKEN_THEN)
            *token = getToken(input);
        else 
            erro("Esperado 'then'", token);

        comando(input, token);
    } else if(token->type == TOKEN_WHILE) {
        *token = getToken(input);
        condicao(input, token);

        if(token->type == TOKEN_DO)
            *token = getToken(input); 
        else erro("Esperado 'do'", token);

        comando(input, token);
    }
}

void mais_cmd(FILE *input, Token *token) {
    if(token->type == TOKEN_SEMICOLON) {
        *token = getToken(input);
        comando(input, token);
        mais_cmd(input, token);
    }
}

void expressao(FILE *input, Token *token) {
    if(token->type == TOKEN_PLUS || token->type == TOKEN_MINUS) 
        *token = getToken(input);
    
    termo(input, token);
    mais_termos(input, token);
}

void termo(FILE *input, Token *token) {
    fator(input, token);
    mais_fatores(input, token);
}

void mais_termos(FILE *input, Token *token) {
    if(token->type == TOKEN_PLUS || token->type == TOKEN_MINUS) {
        *token = getToken(input);
        termo(input, token);
        mais_termos(input, token);
    }
}

void fator(FILE *input, Token *token) {
    if(token->type == TOKEN_IDENTIFIER || token->type == TOKEN_NUMBER) {
        *token = getToken(input);
    } else if(token->type == TOKEN_LPAREN) {
        *token = getToken(input);
        expressao(input, token);

        if(token->type == TOKEN_RPAREN) 
            *token = getToken(input); 
        else 
            erro("Esperado ')'", token);
    
    } else {
        erro("Esperado fator válido", token);
    }
}

void mais_fatores(FILE *input, Token *token) {
    if(token->type == TOKEN_MULTIPLY || token->type == TOKEN_DIVIDE) {
        *token = getToken(input);
        fator(input, token);
        mais_fatores(input, token);
    }
}

void condicao(FILE *input, Token *token) {
    if(token->type == TOKEN_ODD) {
        *token = getToken(input);
        expressao(input, token);
    } else {
        expressao(input, token);
        switch (token->type) {
            case TOKEN_EQUAL:
            case TOKEN_DIFFERENT:
            case TOKEN_LESS:
            case TOKEN_LESS_EQ:
            case TOKEN_GREATER:
            case TOKEN_GREATER_EQ:
                *token = getToken(input);
                break;
            default:
                erro("Esperado operador relacional", token);
        }
        expressao(input, token);
    }
}
