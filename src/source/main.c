#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexical.h"

#define MAX_TOKEN_LENGTH // Maximum value for a 32-bit signed integer

void writeOutputFile(Token token) {
    printf("%s, ", token.lexeme);
    printf("%s\n", token_names[token.type]);
    //escreve arquivo
}

int main(int argc, char * argv[]) {
    static char* input_path;
    // static char* output_path = "/files/output.txt";

    if(argc == 3){
        input_path = argv[1];
        // output_path = argv[2];
    } else if(argc == 2) {
        input_path = argv[1];
    } else {
        printf("Exemplo de uso:\n");
        printf("$ ./pl0 codigo-fonte.txt lista-tokens.txt\n");
        exit(-1);
    }

    FILE *input_file = fopen(input_path, "r");
    if (!input_file) {
        printf("Erro ao abrir entrada.txt\n");
        return 1;
    }

    // FILE *output_file = fopen(output_path, "w");
    // if (!output_file) {
    //     printf("Erro ao criar saida.txt\n");
    //     fclose(input_file);
    //     return 1;
    // }

    Token token;
    while(1) {
        token = get_token(input_file);
        if (token.type == TOKEN_EOF) {
            break; // Finaliza o loop se o token for EOF
        } else if (token.type != TOKEN_COMMENT) {
            // Escreve no arquivo de saída apenas se não for um comentário
            writeOutputFile(token);
        }
    }

    return 0;
}
