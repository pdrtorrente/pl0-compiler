#ifndef STATE_CALLBACK_
#define STATE_CALLBACK_

#include <stdio.h>
#include <stdbool.h>

#include "lexical.h"

state_num q0_callback(char symbol, Token *token);
state_num q1_callback(char symbol, Token *token);
state_num qerror(char symbol, Token *token);
state_num qfinish(char symbol, Token *token);

extern state_callback states[];
extern state_num state_transactions[NUM_STATES][NUM_ALPHABET];

#endif //STATE_CALLBACK_