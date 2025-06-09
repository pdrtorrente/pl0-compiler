#ifndef PARSER_H_
#define PARSER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexical.h"


void ASD_preditiva(FILE *input, Token *token);

void programa(FILE *input, Token *token);
void constante(FILE *input, Token *token);
void mais_const(FILE *input, Token *token);
void variavel(FILE *input, Token *token);
void mais_var(FILE *input, Token *token);
void procedimento(FILE *input, Token *token);
void comando(FILE *input, Token *token);
void mais_cmd(FILE *input, Token *token);
void expressao(FILE *input, Token *token);
void termo(FILE *input, Token *token);
void mais_termos(FILE *input, Token *token);
void fator(FILE *input, Token *token);
void mais_fatores(FILE *input, Token *token);
void condicao(FILE *input, Token *token);


#endif // PARSER_H_