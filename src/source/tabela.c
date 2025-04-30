#include <ctype.h>
#include "tabela.h"

/*
    * Tabela de transições do autômato finito determinístico (AFD) para a análise léxica.
    * A tabela é representada como uma matriz onde cada linha representa um estado intermediário 
    * e cada coluna representa um símbolo do alfabeto. O valor na célula da matriz indica o 
    * próximo estado para a combinação do estado atual e o símbolo lido. 
*/
state_num state_transitions[NUM_INTERMEDIATE_STATE][NUM_ALPHABET] = {
    //       Espaço|Letra|Dígito| '>'| '='| '<'| ':'| '{'| '}'|Símb|Simb_Inválido
    /* Q0 */  {Q0  , Q1  , Q3   , Q5 , Q18, Q8 , Q12, Q15, Q17, Q18, Q17}, // Estado inicial
    /* Q1 */  {Q2  , Q1  , Q1   , Q2 , Q2 , Q2 , Q2 , Q2 , Q2 , Q2 , Q2 }, // IDs
    /* Q3 */  {Q4  , Q17 , Q3   , Q4 , Q4 , Q4 , Q4 , Q4 , Q4 , Q4 , Q17}, // Números
    /* Q5 */  {Q7  , Q7  , Q7   , Q7 , Q6 , Q7 , Q7 , Q7 , Q7 , Q7 , Q17}, // >
    /* Q8 */  {Q11 , Q11 , Q11  , Q9 , Q10, Q11, Q11, Q11, Q11, Q11, Q17}, // <
    /* Q12 */ {Q14 , Q14 , Q14  , Q14, Q13, Q14, Q14, Q14, Q14, Q14, Q17}, // :
    /* Q15 */ {Q15 , Q15 , Q15  , Q15, Q15, Q15, Q15, Q15, Q16, Q15, Q15}, // {
};


// Função que retorna o índice da coluna correspondente ao símbolo lido.
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
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';' || c == ',' || c == '.')
        return 9;
    else
        return 10; // caso não seja um símbolo do alfabeto de PL/0
}
