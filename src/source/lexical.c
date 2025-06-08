#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexical.h"
#include "tabela.h"

// Funções de callback para os estados finais
state_callback states[] = {
    q2_callback, q4_callback, q6_callback, q7_callback, q9_callback, q10_callback, 
    q11_callback, q13_callback, q14_callback, q16_callback, q17_callback, q18_callback
};

// Implementação
Token getToken(FILE *input) {
    state_num current_state = Q0;
    char c;
    Token token = {TOKEN_UNDEFINED, ""};
    
    do {
        /*
            Se o estado atual for um estado final, retornamos 
            o resultado para a main (analisador sintático)
        */
       if (current_state >= NUM_INTERMEDIATE_STATE) {
            states[FINAL_INDEX(current_state)](input, c, &token);
            return token;
        }

        // Lê um caracter
        c = fgetc(input);

        // Ignora espaços quando estamos no estado inicial
        if(current_state == Q0 && isspace(c))
            continue; // Ignora espaços em branco

        // Identifica erro na formação de comentários
        if(current_state == Q15 && c == '\n' ) {
            token.type = TOKEN_COMMENT_ERROR;
            return token;
        }
        
        // Ignora comentários
        if(current_state == Q15 && c != '}')
            continue; // Ignora caracteres dentro das chaves 

        // Adiciona o caracter lido na string do token
        int len = strlen(token.lexeme);
        if (len <= MAX_VAR_SIZE){
            token.lexeme[len] = c;
            token.lexeme[len + 1] = '\0';
        }

        // Faz a transição para o próximo estado de acordo com a tabela
        int column = find_column(c);
        current_state = state_transitions[current_state][column];
    } while (c != EOF);

   token.type = TOKEN_EOF;
   return token;
}
