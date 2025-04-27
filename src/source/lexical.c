#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lexical.h"
#include "state_callback.h"

Keyword keywords[] = {
    {"begin", TOKEN_BEGIN}, {"end", TOKEN_END}, {"if", TOKEN_IF},
    {"then", TOKEN_THEN}, {"while", TOKEN_WHILE}, {"do", TOKEN_DO},
    {"const", TOKEN_CONST}, {"var", TOKEN_VAR}, {"procedure", TOKEN_PROCEDURE},
    {"call", TOKEN_CALL}, {"odd", TOKEN_ODD}
};

#define NUM_KEYWORDS (sizeof(keywords) / sizeof(Keyword))

state_callback states[] = {
    q0_callback, q1_callback, q2_callback, q3_callback, qerror, qfinish
};

state_num state_transactions[NUM_STATES][NUM_ALPHABET] = {
    {Q1     , Q_ERROR, Q2     , Q_ERROR, Q_ERROR, Q_ERROR}, // estado inicial
    {Q1     , QFINISH, QFINISH, QFINISH, QFINISH, QFINISH}, // identificador
    {QFINISH, QFINISH, QFINISH, Q3     , QFINISH, QFINISH}, // menor
    {QFINISH, QFINISH, QFINISH, QFINISH, QFINISH, QFINISH}, // menor igual
    {QFINISH, QFINISH, QFINISH, QFINISH, QFINISH, QFINISH}, // finish
    {QFINISH, QFINISH, QFINISH, QFINISH, QFINISH, QFINISH}, // error
};// alfa      num       minus   equal    space     error

Token get_token(FILE *input) {
    //implementação
    char c;
    state_num current_state = Q0;
    Token current_token = {TOKEN_UNDEFINED, "", 0, false};
    do {
        if (current_state != QFINISH) c = fgetc(input);

        current_state = states[current_state](c, &current_token);
        if (current_token.tkn_ready && c != EOF) {
            fseek(input, -1, SEEK_CUR);
            break;
        }

        if (c == EOF && !current_token.tkn_ready) {
            ungetc(c, input);
        }
    } while (c != EOF || !current_token.tkn_ready);

    if (c == EOF && current_token.type == TOKEN_ERROR) {
        current_token.type = TOKEN_EOF;
    }
    return current_token;
}
