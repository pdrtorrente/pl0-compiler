#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexical.h"

Token token_atual;
FILE *fonte;

void erro(const char *mensagem) {
    fprintf(stderr, "Erro sintatico: %s (token: %s)\n", mensagem, token_atual.lexeme);
    exit(EXIT_FAILURE);
}

void obter_simbolo() {
    token_atual = getToken(fonte);
}

void consome(TokenType tipo) {
    if (token_atual.type == tipo) {
        obter_simbolo();
    } else {
        erro("Token inesperado");
    }
}

void constante();
void variavel();
void procedimento();
void comando();
void mais_cmd();
void expressao();
void termo();
void mais_termos();
void fator();
void mais_fatores();
void condicao();

void programa() {
    constante();
    variavel();
    procedimento();
    comando();
    if (token_atual.type == TOKEN_PERIOD) obter_simbolo();
    else erro("Esperado '.'");
}

void constante() {
    if (token_atual.type == TOKEN_CONST) {
        obter_simbolo();
        if (token_atual.type == TOKEN_IDENTIFIER) obter_simbolo(); else erro("Esperado identificador");
        if (token_atual.type == TOKEN_EQUAL) obter_simbolo(); else erro("Esperado '='");
        if (token_atual.type == TOKEN_NUMBER) obter_simbolo(); else erro("Esperado numero");
        while (token_atual.type == TOKEN_COMMA) {
            obter_simbolo();
            if (token_atual.type == TOKEN_IDENTIFIER) obter_simbolo(); else erro("Esperado identificador");
            if (token_atual.type == TOKEN_EQUAL) obter_simbolo(); else erro("Esperado '='");
            if (token_atual.type == TOKEN_NUMBER) obter_simbolo(); else erro("Esperado numero");
        }
        if (token_atual.type == TOKEN_SEMICOLON) obter_simbolo(); else erro("Esperado ';'");
    }
}

void variavel() {
    if (token_atual.type == TOKEN_VAR) {
        obter_simbolo();
        if (token_atual.type == TOKEN_IDENTIFIER) obter_simbolo(); else erro("Esperado identificador");
        while (token_atual.type == TOKEN_COMMA) {
            obter_simbolo();
            if (token_atual.type == TOKEN_IDENTIFIER) obter_simbolo(); else erro("Esperado identificador");
        }
        if (token_atual.type == TOKEN_SEMICOLON) obter_simbolo(); else erro("Esperado ';'");
    }
}

void procedimento() {
    while (token_atual.type == TOKEN_PROCEDURE) {
        obter_simbolo();
        if (token_atual.type == TOKEN_IDENTIFIER) obter_simbolo(); else erro("Esperado identificador");
        if (token_atual.type == TOKEN_SEMICOLON) obter_simbolo(); else erro("Esperado ';'");
        constante();
        variavel();
        procedimento();
        comando();
        if (token_atual.type == TOKEN_SEMICOLON) obter_simbolo(); else erro("Esperado ';'");
    }
}

void comando() {
    if (token_atual.type == TOKEN_IDENTIFIER) {
        obter_simbolo();
        if (token_atual.type == TOKEN_ASSIGN) obter_simbolo(); else erro("Esperado ':='");
        expressao();
    } else if (token_atual.type == TOKEN_CALL) {
        obter_simbolo();
        if (token_atual.type == TOKEN_IDENTIFIER) obter_simbolo(); else erro("Esperado identificador");
    } else if (token_atual.type == TOKEN_BEGIN) {
        obter_simbolo();
        comando();
        mais_cmd();
        if (token_atual.type == TOKEN_END) obter_simbolo(); else erro("Esperado 'end'");
    } else if (token_atual.type == TOKEN_IF) {
        obter_simbolo();
        condicao();
        if (token_atual.type == TOKEN_THEN) obter_simbolo(); else erro("Esperado 'then'");
        comando();
    } else if (token_atual.type == TOKEN_WHILE) {
        obter_simbolo();
        condicao();
        if (token_atual.type == TOKEN_DO) obter_simbolo(); else erro("Esperado 'do'");
        comando();
    }
}

void mais_cmd() {
    while (token_atual.type == TOKEN_SEMICOLON) {
        obter_simbolo();
        comando();
    }
}

void expressao() {
    if (token_atual.type == TOKEN_PLUS || token_atual.type == TOKEN_MINUS) obter_simbolo();
    termo();
    mais_termos();
}

void termo() {
    fator();
    mais_fatores();
}

void mais_termos() {
    while (token_atual.type == TOKEN_PLUS || token_atual.type == TOKEN_MINUS) {
        obter_simbolo();
        termo();
    }
}

void fator() {
    if (token_atual.type == TOKEN_IDENTIFIER || token_atual.type == TOKEN_NUMBER) {
        obter_simbolo();
    } else if (token_atual.type == TOKEN_LPAREN) {
        obter_simbolo();
        expressao();
        if (token_atual.type == TOKEN_RPAREN) obter_simbolo(); else erro("Esperado ')'");
    } else {
        erro("Esperado fator válido");
    }
}

void mais_fatores() {
    while (token_atual.type == TOKEN_MULTIPLY || token_atual.type == TOKEN_DIVIDE) {
        obter_simbolo();
        fator();
    }
}

void condicao() {
    if (token_atual.type == TOKEN_ODD) {
        obter_simbolo();
        expressao();
    } else {
        expressao();
        switch (token_atual.type) {
            case TOKEN_EQUAL:
            case TOKEN_DIFFERENT:
            case TOKEN_LESS:
            case TOKEN_LESS_EQ:
            case TOKEN_GREATER:
            case TOKEN_GREATER_EQ:
                obter_simbolo();
                break;
            default:
                erro("Esperado operador relacional");
        }
        expressao();
    }
}
