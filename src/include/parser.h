#ifndef PARSER_H_
#define PARSER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexical.h"

#define MAX_TOKENS 50
typedef struct {
    TokenType tokens[MAX_TOKENS];
    int tamanho;
} ConjuntoSimbolos;

void ASD_preditiva(FILE *input, Token *token);

void programa(FILE *input, Token *token, ConjuntoSimbolos S);
void constante(FILE *input, Token *token, ConjuntoSimbolos S);
void mais_const(FILE *input, Token *token, ConjuntoSimbolos S);
void variavel(FILE *input, Token *token, ConjuntoSimbolos S);
void mais_var(FILE *input, Token *token, ConjuntoSimbolos S);
void procedimento(FILE *input, Token *token, ConjuntoSimbolos S);
void comando(FILE *input, Token *token, ConjuntoSimbolos S);
void mais_cmd(FILE *input, Token *token, ConjuntoSimbolos S);
void expressao(FILE *input, Token *token, ConjuntoSimbolos S);
void termo(FILE *input, Token *token, ConjuntoSimbolos S);
void mais_termos(FILE *input, Token *token, ConjuntoSimbolos S);
void fator(FILE *input, Token *token, ConjuntoSimbolos S);
void mais_fatores(FILE *input, Token *token, ConjuntoSimbolos S);
void condicao(FILE *input, Token *token, ConjuntoSimbolos S);


#endif // PARSER_H_