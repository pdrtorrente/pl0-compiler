#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lexical.h"
#include "tabela.h"
state_callback states[] = {
    q2_callback, q4_callback, q6_callback, q7_callback, q9_callback, q10_callback, 
    q11_callback, q13_callback, q14_callback, q16_callback, q17_callback, q18_callback
};

int isFinal(state_num Q) {
    for (int i = 0; i < NUM_FINAL_STATES; i++) {
        if (final_states[i] == Q) {
            return i;
        }
    }
    return -1;
}

//implementação
Token get_token(FILE *input) {
    state_num current_state = Q0;
    char c;
    Token token = {TOKEN_UNDEFINED, "", 0};
    
    do {
        /*
            Se o estado atual for um estado final, retornamos 
            o resultado para a main (analisador sintático)
        */
        int final = isFinal(current_state);
        if (final >= 0) {
            return states[final](input, c, &token);
        }

        // Lê um caracter
        c = fgetc(input);

        // Ignora espaços quando estamos no estado inicial
        if(current_state == Q0 && isspace(c))
            continue; // Ignora espaços em branco

        // Ignora comentários
        if(current_state == Q15 && c != '}')
            continue; // Ignora caracteres dentro das chaves


        // Adiciona o caracter lido na string do token
        int len = strlen(token.lexeme);
        token.lexeme[len] = c;
        token.lexeme[len + 1] = '\0';

        // Faz a transição para o próximo estado de acordo com a tabela
        int line = find_line(current_state);
        int column = find_column(c);
        current_state = state_transitions[line][column];
    } while (c != EOF);

   token.type = TOKEN_EOF;
   return token;
}
