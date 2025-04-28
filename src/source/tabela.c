#include <ctype.h>

#include "tabela.h"

state_num state_transitions[NUM_STATES-NUM_FINAL_STATES][NUM_ALPHABET] = {
    //        Espaço Letra Dígito '>'  '='  '<'  ':'  '{'  '}'  Símbolo Simb_Inválido
    /* Q0 */  {Q0, Q1, Q3, Q5, Q18, Q8, Q12, Q15, Q17, Q18, Q17}, // Estado inicial
    /* Q1 */  {Q2, Q1, Q1, Q2, Q2, Q2, Q2, Q2, Q2, Q2, Q2}, // IDs
    /* Q3 */  {Q4, Q17, Q3, Q4, Q4, Q4, Q4, Q4, Q4, Q4, Q17}, // Números
    /* Q5 */  {Q7, Q7, Q7, Q7, Q6, Q7, Q7, Q7, Q7, Q7, Q17}, // >
    /* Q8 */  {Q11, Q11, Q11, Q9, Q10, Q11, Q11, Q11, Q11, Q11, Q17}, // <
    /* Q12 */ {Q14, Q14, Q14, Q14, Q13, Q14, Q14, Q14, Q14, Q14, Q17 }, // :
    /* Q15 */ {Q15, Q15, Q15, Q15, Q15, Q15, Q15, Q15, Q16, Q15, Q15 }, // {
};

// Conjunto de estados finais
state_num final_states[NUM_FINAL_STATES] = {
    Q2, Q4, Q6, Q7, Q9, Q10, Q11, Q13, Q14, Q16, Q17, Q18
};

int find_line(state_num Q) {
    if (Q == Q0)
        return 0;
    else if (Q == Q1)
        return 1;
    else if (Q == Q3)
        return 2;
    else if (Q == Q5)
        return 3;
    else if (Q == Q8)
        return 4;
    else if (Q == Q12)
        return 5;
    else if (Q == Q15)
        return 6;
    else
        return -1;
}

int find_column(char c) {
    if (isspace(c))
        return 0;
    else if (isalpha(c))
        return 1;
    else if (isdigit(c))
        return 2;
    else if (c == '>')
        return 3;
    else if (c == '=')
        return 4;
    else if (c == '<')
        return 5;
    else if (c == ':')
        return 6;
    else if (c == '{')
        return 7;
    else if (c == '}')
        return 8;
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';')
        return 9;
    else
        return 10; // Caso não seja um símbolo do alfabeto
}