#ifndef TABELA_H
#define TABELA_H

#include <stdio.h>
#include <stdbool.h>

#define NUM_ALPHABET 11  // 0-10 (espaço até caracteres inválidos)

// Estados
typedef enum {
    // estados intermediários
    Q0=0, Q1, Q3, Q5, Q8, Q12, Q15, 
    NUM_INTERMEDIATE_STATE,

    // estados finais
    Q2=100, Q4, Q6, Q7, Q9, Q10, Q11, Q13, Q14, Q16, Q17, Q18,
    NUM_FINAL_STATES
} state_num;

#define NUM_STATES NUM_INTERMEDIATE_STATE + (NUM_FINAL_STATES - 100)
#define FINAL_INDEX(x) ((x) - 100)

extern state_num state_transitions[NUM_INTERMEDIATE_STATE][NUM_ALPHABET];

int find_column(char c);

#endif // TABELA_H