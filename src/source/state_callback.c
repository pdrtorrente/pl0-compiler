#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "state_callback.h"

state_callback states[] = {
    q0_callback, q1_callback, qerror, qfinish
};

state_num state_transactions[NUM_STATES][NUM_ALPHABET] = {
    {Q1     , Q_ERROR, Q_ERROR, Q_ERROR, Q_ERROR},
    {Q1     , QFINISH, QFINISH, QFINISH, QFINISH},
    {QFINISH, QFINISH, QFINISH, QFINISH, QFINISH},
};

Alphabet classifier(char symbol) {
    if (('a' <= symbol && symbol <= 'z') || ('A' <= symbol && symbol <= 'Z')) return ALPHA;

    if (isdigit(symbol)) return NUM;
    
    switch (symbol) {
        case '<':
            return MINUS;
        default:
            return ERROR;
    }
}

state_num generic_callback(char symbol, Token *token, TokenType type, state_num current_state) {
    Alphabet symbol_type = classifier(symbol);
    state_num next_state = state_transactions[current_state][symbol_type];

    token->type = type;
    token->lexeme[token->it++] = symbol;
    return next_state;
}


/**
 * Initial state
 */
state_num q0_callback(char symbol, Token *token) {
    Alphabet symbol_type = classifier(symbol);
    state_num next_state = state_transactions[Q0][symbol_type];

    token->lexeme[token->it++] = symbol;
    return next_state;
}

/**
 * Identifier
 */
state_num q1_callback(char symbol, Token *token) { return generic_callback(symbol, token, TOKEN_IDENTIFIER, Q1); }

/**
 * Error state
 */
state_num qerror(char symbol, Token *token) {
    token->type = TOKEN_ERROR;
    token->lexeme[token->it] = '\0';
    token->tkn_ready = true;
    return Q_ERROR;
}

/**
 * Finish state
 */
state_num qfinish(char symbol, Token *token) {
    token->lexeme[--token->it] = '\0';
    token->tkn_ready = true;
    return Q0;
}