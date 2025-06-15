#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h> 
#include "parser.h"

Token token_atual;
FILE *fonte;
int success = 1;


bool pertence(TokenType token, ConjuntoSimbolos conjunto);
ConjuntoSimbolos uniao(ConjuntoSimbolos a, ConjuntoSimbolos b);
ConjuntoSimbolos conjunto(int n, TokenType lista[]);

bool pertence(TokenType token, ConjuntoSimbolos conjunto) {
    for (int i = 0; i < conjunto.tamanho; i++) {
        if (conjunto.tokens[i] == token) return true;
    }
    return false;
}

ConjuntoSimbolos uniao(ConjuntoSimbolos a, ConjuntoSimbolos b) {
    ConjuntoSimbolos resultado = a;
    for (int i = 0; i < b.tamanho; i++) {
        if (!pertence(b.tokens[i], resultado)) {
            resultado.tokens[resultado.tamanho++] = b.tokens[i];
        }
    }
    return resultado;
}

ConjuntoSimbolos conjunto(int n, TokenType lista[]) {
    ConjuntoSimbolos c;
    c.tamanho = 0;
    for (int i = 0; i < n && i < MAX_TOKENS; i++) {
        c.tokens[c.tamanho++] = lista[i];
    }
    return c;
}

void erro(const char *mensagem, Token *token, FILE *input, ConjuntoSimbolos conjunto_sincronizacao) {
    // Atualiza que o programa não foi compilado com sucesso
    success = 0;

    // Erros léxicos são fatais e encerram a compilação
    if (token->type == TOKEN_ERROR || token->type == TOKEN_COMMENT_ERROR) {
        fprintf(stderr, "Erro lexico na linha %d caracter %d: %s ('%s')\n", token->line, token->caracter, mensagem, token->lexeme);
        exit(EXIT_FAILURE);
    } 
    // Fim de arquivo inesperado também é fatal
    else if (token->type == TOKEN_EOF) {
        fprintf(stderr, "Erro sintatico na linha %d caracter %d: Fim de arquivo inesperado. %s\n", token->line, token->caracter, mensagem);
        exit(EXIT_FAILURE);
    } 
    // Para erros sintáticos, ativa o modo pânico
    else {
        printf("Erro sintático (%s) na linha %d caracter %d\n", mensagem, token->line, token->caracter);
        while (!pertence(token->type, conjunto_sincronizacao) && token_atual.type != TOKEN_EOF) {
            *token = getToken(input);
        }
    }
}

void ASD_preditiva(FILE *input, Token *token) {
    *token = getToken(input);
    TokenType sync[] = { TOKEN_EOF };
    programa(input, token, conjunto(1, sync));

    if(token->type == TOKEN_EOF) {
        if(success == 1)
            printf("Programa Compilado com SUCESSO!!!");
    }
    else {
        TokenType sync[] = { TOKEN_EOF };
        erro("Esperado EOF", token, input, conjunto(1, sync));
    }
}

void programa(FILE *input, Token *token, ConjuntoSimbolos S) {
    TokenType syncConst[] = { TOKEN_VAR, TOKEN_PROCEDURE, TOKEN_IDENTIFIER, TOKEN_CALL, TOKEN_BEGIN, TOKEN_IF, TOKEN_PERIOD, TOKEN_SEMICOLON };
    constante(input, token, uniao(conjunto(8, syncConst), S));

    TokenType syncVar[] = { TOKEN_PROCEDURE, TOKEN_IDENTIFIER, TOKEN_CALL, TOKEN_BEGIN, TOKEN_IF, TOKEN_PERIOD, TOKEN_SEMICOLON };
    variavel(input, token, uniao(conjunto(7, syncVar), S));

    TokenType syncProc[] = { TOKEN_IDENTIFIER, TOKEN_CALL, TOKEN_BEGIN, TOKEN_IF, TOKEN_PERIOD, TOKEN_SEMICOLON };
    procedimento(input, token, uniao(conjunto(6, syncProc), S));

    TokenType syncComand[] = { TOKEN_PERIOD, TOKEN_SEMICOLON };
    comando(input, token, uniao(conjunto(2, syncComand), S));

    if(token->type == TOKEN_PERIOD) {
        *token = getToken(input);
    } else {
        erro("Esperado '.'", token, input, S);
    }
}

void constante(FILE *input, Token *token, ConjuntoSimbolos S) {
    if(token->type == TOKEN_CONST) {
        *token = getToken(input);

        if(token->type == TOKEN_IDENTIFIER) {
            *token = getToken(input);
        } else {
            TokenType sync[] = { TOKEN_EQUAL, TOKEN_NUMBER, TOKEN_SEMICOLON };
            erro("Esperado identificador", token, input, uniao(conjunto(3, sync), S));
            if (pertence(token->type, S)) return;
            // *token = getToken(input);
        }
        
        if(token->type == TOKEN_EQUAL){
            *token = getToken(input);
        } else {
            TokenType sync[] = { TOKEN_NUMBER, TOKEN_COMMA };
            erro("Esperado '='", token, input, uniao(conjunto(2, sync), S));
            if (pertence(token->type, S)) return;
            // *token = getToken(input);
        }
        
        if(token->type == TOKEN_NUMBER) {
            *token = getToken(input); 
        } else {
            TokenType sync[] = { TOKEN_COMMA, TOKEN_SEMICOLON };
            erro("Esperado numero", token, input, uniao(conjunto(2, sync), S));
            if (pertence(token->type, S)) return;
            // *token = getToken(input);
        }

        TokenType sync1[] = { TOKEN_SEMICOLON };
        mais_const(input, token, uniao(conjunto(1, sync1), S));

        if(token->type == TOKEN_SEMICOLON) {
            *token = getToken(input);
        } else {
            TokenType sync[] = { TOKEN_VAR, TOKEN_PROCEDURE, TOKEN_IDENTIFIER, TOKEN_CALL, TOKEN_BEGIN, TOKEN_IF, TOKEN_WHILE };
            erro("Esperado ';'", token, input, uniao(conjunto(7, sync), S));
            if (pertence(token->type, S)) return;
        }
    }
}

void mais_const(FILE *input, Token *token, ConjuntoSimbolos S) {
    if(token->type == TOKEN_COMMA) {
        *token = getToken(input);
        
        if(token->type == TOKEN_IDENTIFIER) {
            *token = getToken(input);
        } else {
            TokenType sync[] = { TOKEN_EQUAL, TOKEN_NUMBER, TOKEN_COMMA };
            erro("Esperado identificador", token, input, uniao(conjunto(3, sync), S));
            if (pertence(token->type, S)) return;
        }
        
        if(token->type == TOKEN_EQUAL) {
            *token = getToken(input); 
        } else {
            TokenType sync[] = { TOKEN_NUMBER, TOKEN_COMMA };
            erro("Esperado '='", token, input, uniao(conjunto(2, sync), S));
            if (pertence(token->type, S)) return;
        }
        
        if(token->type == TOKEN_NUMBER) {
            *token = getToken(input);
        } else {
            TokenType sync[] = { TOKEN_COMMA, TOKEN_SEMICOLON };
            erro("Esperado numero", token, input, uniao(conjunto(2, sync), S));
            if (pertence(token->type, S)) return;
        }

        mais_const(input, token, S);
    }
}

void variavel(FILE *input, Token *token, ConjuntoSimbolos S) {
    if(token->type == TOKEN_VAR) {
        *token = getToken(input);
    } else {
        TokenType sync[] = { TOKEN_IDENTIFIER };
        erro("Erro: esperado 'VAR'", token, input, uniao(conjunto(1, sync), S));
        if (pertence(token->type, S)) return;
    }
    if(token->type == TOKEN_IDENTIFIER) {
        *token = getToken(input);
    } else {
        TokenType sync[] = { TOKEN_COMMA, TOKEN_SEMICOLON };
        erro("Esperado identificador", token, input, uniao(conjunto(2, sync), S));
        if (pertence(token->type, S)) return;
    }

    TokenType sync1[] = { TOKEN_SEMICOLON };
    mais_var(input, token, uniao(conjunto(1, sync1), S));

    if (token->type == TOKEN_SEMICOLON) {
        *token = getToken(input);
    } else {
        TokenType sync[] = { TOKEN_PROCEDURE, TOKEN_IDENTIFIER, TOKEN_CALL, TOKEN_BEGIN, TOKEN_IF, TOKEN_WHILE };
        erro("Erro: ponto e vírgula esperado'", token, input, uniao(conjunto(6, sync), S));
    }
}

void mais_var(FILE *input, Token *token, ConjuntoSimbolos S) {
    if (token->type == TOKEN_COMMA) {
        *token = getToken(input);
        if(token->type == TOKEN_IDENTIFIER) {
            *token = getToken(input); 
            mais_var(input, token, S);
        } else {
            TokenType sync[] = { TOKEN_COMMA, TOKEN_SEMICOLON };
            erro("Erro: identificador esperado após vírgula", token, input, uniao(conjunto(2, sync), S));
        }
    }
}

void procedimento(FILE *input, Token *token, ConjuntoSimbolos S) {
    if (token->type == TOKEN_PROCEDURE) {
        *token = getToken(input);
        
        if(token->type == TOKEN_IDENTIFIER) {
            *token = getToken(input);
        } else {
            TokenType sync[] = { TOKEN_SEMICOLON };
            erro("Esperado identificador", token, input, uniao(conjunto(1, sync), S));
            if (pertence(token->type, S)) return;
        }

        if(token->type == TOKEN_SEMICOLON) {
            *token = getToken(input); 
        } else {
            TokenType sync[] = { TOKEN_CONST, TOKEN_VAR, TOKEN_PROCEDURE, TOKEN_IDENTIFIER, TOKEN_CALL, TOKEN_BEGIN, TOKEN_IF, TOKEN_WHILE };
            erro("Esperado ';'", token, input, uniao(conjunto(8, sync), S));
            if (pertence(token->type, S)) return;
        }

        TokenType syncProc[] = { TOKEN_SEMICOLON };
        ConjuntoSimbolos SProcedimento = uniao(conjunto(1, syncProc), S);
        
        constante(input, token, SProcedimento);
        variavel(input, token, SProcedimento);
        procedimento(input, token, SProcedimento);
        comando(input, token, SProcedimento);

        if(token->type == TOKEN_SEMICOLON) {
            *token = getToken(input); 
        } else {
            TokenType sync[] = { TOKEN_SEMICOLON, TOKEN_PROCEDURE };
            erro("Esperado ';'", token, input, uniao(conjunto(2, sync), S));
            if (pertence(token->type, S)) return;
        }

        procedimento(input, token, S);
    }
}

void comando(FILE *input, Token *token, ConjuntoSimbolos S) {
    if(token->type == TOKEN_IDENTIFIER) {
        *token = getToken(input);

        if(token->type == TOKEN_ASSIGN) {
            *token = getToken(input);
        } else {
            TokenType sync[] = { TOKEN_PLUS, TOKEN_MINUS, TOKEN_IDENTIFIER, TOKEN_NUMBER, TOKEN_LPAREN };
            erro("Esperado ':='", token, input, uniao(conjunto(5, sync), S));
            if (pertence(token->type, S)) return;
        }

        expressao(input, token, S);
        
    } else if(token->type == TOKEN_CALL) {
        *token = getToken(input);

        if(token->type == TOKEN_IDENTIFIER) {
            *token = getToken(input); 
        } else {
            TokenType sync[] = { TOKEN_SEMICOLON, TOKEN_END, TOKEN_PERIOD };
            erro("Esperado identificador", token, input, uniao(conjunto(3, sync), S));
            if (pertence(token->type, S)) return;
        }
        
    } else if(token->type == TOKEN_BEGIN) {
        *token = getToken(input);
        
        TokenType syncCmd[] = { TOKEN_END };
        comando(input, token, uniao(conjunto(1, syncCmd), S));
        mais_cmd(input, token, uniao(conjunto(1, syncCmd), S));

        if(token->type == TOKEN_END) {
            *token = getToken(input);
        } else {
            TokenType sync[] = { TOKEN_SEMICOLON, TOKEN_END, TOKEN_PERIOD };
            erro("Esperado 'end'", token, input, uniao(conjunto(3, sync), S));
            if (pertence(token->type, S)) return;
        }
        
    } else if(token->type == TOKEN_IF) {
        *token = getToken(input);
        
        TokenType syncCond[] = { TOKEN_THEN };
        condicao(input, token, uniao(conjunto(1, syncCond), S));

        if(token->type == TOKEN_THEN) {
            *token = getToken(input);
        } else {
            TokenType sync[] = { TOKEN_IDENTIFIER, TOKEN_CALL, TOKEN_BEGIN };
            erro("Esperado 'then'", token, input, uniao(conjunto(3, sync), S));
            if (pertence(token->type, S)) return;
        }

        comando(input, token, S);
        
    } else if(token->type == TOKEN_WHILE) {
        *token = getToken(input);
        
        TokenType syncCond[] = { TOKEN_DO };
        condicao(input, token, uniao(conjunto(1, syncCond), S));

        if(token->type == TOKEN_DO) {
            *token = getToken(input); 
        } else {
            TokenType sync[] = { TOKEN_IDENTIFIER, TOKEN_CALL, TOKEN_BEGIN, TOKEN_IF, TOKEN_WHILE };
            erro("Esperado 'do'", token, input, uniao(conjunto(5, sync), S));
            if (pertence(token->type, S)) return;
        }

        comando(input, token, S);
    }
}

void mais_cmd(FILE *input, Token *token, ConjuntoSimbolos S) {
    if(token->type == TOKEN_SEMICOLON) {
        *token = getToken(input);
        comando(input, token, S);
        mais_cmd(input, token, S);
    }
}

void expressao(FILE *input, Token *token, ConjuntoSimbolos S) {
    if(token->type == TOKEN_PLUS || token->type == TOKEN_MINUS) {
        *token = getToken(input);
    }
    
    termo(input, token, S);
    mais_termos(input, token, S);
}

void termo(FILE *input, Token *token, ConjuntoSimbolos S) {
    fator(input, token, S);
    mais_fatores(input, token, S);
}

void mais_termos(FILE *input, Token *token, ConjuntoSimbolos S) {
    if(token->type == TOKEN_PLUS || token->type == TOKEN_MINUS) {
        *token = getToken(input);
        termo(input, token, S);
        mais_termos(input, token, S);
    }
}

void fator(FILE *input, Token *token, ConjuntoSimbolos S) {
    if(token->type == TOKEN_IDENTIFIER || token->type == TOKEN_NUMBER) {
        *token = getToken(input);
    } else if(token->type == TOKEN_LPAREN) {
        *token = getToken(input);
        
        TokenType syncExpr[] = { TOKEN_RPAREN };
        expressao(input, token, uniao(conjunto(1, syncExpr), S));

        if(token->type == TOKEN_RPAREN) {
            *token = getToken(input); 
        } else {
            TokenType sync[] = { TOKEN_SEMICOLON, TOKEN_END, TOKEN_PERIOD, TOKEN_PLUS, TOKEN_MINUS, TOKEN_MULTIPLY, TOKEN_DIVIDE, TOKEN_THEN, TOKEN_DO, TOKEN_RPAREN };
            erro("Esperado ')'", token, input, uniao(conjunto(10, sync), S));
            if (pertence(token->type, S)) return;
        }
    } else {
        TokenType sync[] = { TOKEN_IDENTIFIER, TOKEN_NUMBER, TOKEN_LPAREN };
        erro("Esperado fator válido", token, input, uniao(conjunto(3, sync), S));
        if (pertence(token->type, S)) return;
    }
}

void mais_fatores(FILE *input, Token *token, ConjuntoSimbolos S) {
    if(token->type == TOKEN_MULTIPLY || token->type == TOKEN_DIVIDE) {
        *token = getToken(input);
        fator(input, token, S);
        mais_fatores(input, token, S);
    }
}

void condicao(FILE *input, Token *token, ConjuntoSimbolos S) {
    if(token->type == TOKEN_ODD) {
        *token = getToken(input);
        expressao(input, token, S);
    } else {
        TokenType syncRel[] = { TOKEN_EQUAL, TOKEN_DIFFERENT, TOKEN_LESS, TOKEN_LESS_EQ, TOKEN_GREATER, TOKEN_GREATER_EQ };
        expressao(input, token, uniao(conjunto(6, syncRel), S));
        
        switch (token->type) {
            case TOKEN_EQUAL:
            case TOKEN_DIFFERENT:
            case TOKEN_LESS:
            case TOKEN_LESS_EQ:
            case TOKEN_GREATER:
            case TOKEN_GREATER_EQ:
                *token = getToken(input);
                break;
            default:
                TokenType sync[] = { TOKEN_PLUS, TOKEN_MINUS, TOKEN_IDENTIFIER, TOKEN_NUMBER, TOKEN_LPAREN };
                erro("Esperado operador relacional", token, input, uniao(conjunto(5, sync), S));
                if (pertence(token->type, S)) return;
        }
        expressao(input, token, S);
    }
}
