#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// Função para escrever os tokens no arquivo de saída
void writeOutputFile(FILE *output_file, Token token) {
    fprintf(output_file, "%s, ", token.lexeme);
    fprintf(output_file, "%s\n", token_names[token.type]);
}

int main(int argc, char *argv[]) {
    static char* input_path;
    static char* output_path;

    if (argc == 3) {
        input_path = argv[1];
        output_path = argv[2];
    } else if (argc == 2) {
        input_path = argv[1];
        output_path = "output_files/output.txt";
    } else {
        printf("Exemplo de uso:\n");
        printf("$ ./pl0 codigo-fonte.txt [saida.txt]\n");
        exit(EXIT_FAILURE);
    }

    // Abertura do arquivo de entrada para leitura
    FILE *input_file = fopen(input_path, "r");
    if (!input_file) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", input_path);
        return EXIT_FAILURE;
    }

    // Criação do arquivo de saída para escrita
    FILE *output_file = fopen(output_path, "w");
    if (!output_file) {
        printf("Erro ao criar o arquivo de saída: %s\n", output_path);
        fclose(input_file);
        return EXIT_FAILURE;
    }



    Token token;
    ASD_preditiva(input_file, &token);
    // while(1) {
    //     token = getToken(input_file);
    //     printf("Lexema: %s\n Line %d\n Caracter %d\n", token.lexeme, token.line, token.caracter);
    //     if (token.type == TOKEN_EOF) {
    //         break; // Finaliza o loop se o token for EOF
    //     } else if (token.type != TOKEN_COMMENT) {
    //         writeOutputFile(output_file, token);
    //     }
    // }

    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}
