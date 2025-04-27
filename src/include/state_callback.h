#ifndef STATE_CALLBACK_
#define STATE_CALLBACK_

#include <stdio.h>
#include <stdbool.h>

#include "lexical.h"

state_num q0_callback(char symbol, Token *token);
state_num qerror(char symbol, Token *token);

#endif //STATE_CALLBACK_