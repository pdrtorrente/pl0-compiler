#ifndef TABELA_H
#define TABELA_H

#include <stdio.h>
#include <stdbool.h>

#define NUM_STATES 19
#define NUM_FINAL_STATES 12
#define NUM_ALPHABET 11  // 0-10 (espaço até caracteres inválidos)

// Estados
typedef enum state_num {
    Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9,
    Q10, Q11, Q12, Q13, Q14, Q15, Q16, Q17, Q18
} state_num;

extern state_num state_transitions[NUM_STATES - NUM_FINAL_STATES][NUM_ALPHABET];
extern state_num final_states[NUM_FINAL_STATES];

int find_line(state_num Q);
int find_column(char c);

#endif // TABELA_H