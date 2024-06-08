#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <getopt.h>

void argsParse(int args, char* argv[]);

int main (int argc, char* argv[]){ 
    argsParse(argc, argv);   
    return 0;
}

void argsParse(int argc, char* argv[]) {
    if(argc != 5 && argc != 8) {
        fprintf(stderr, "La cantidad de parámetros no es la correcta.\n");
        exit(EXIT_FAILURE);
    }

    char* archivoTraza = malloc(strlen(argv[1]) + 
    strlen("trazas/") + 1);
    strcpy(archivoTraza, "trazas/");
    strcat(archivoTraza, argv[1]);
    
    FILE *file = fopen(archivoTraza, "r");
    
    if(file == NULL) {
        fprintf(stderr, "Archivo inexistente.\n");
        exit(EXIT_FAILURE);
    }
    else {
        printf("%s", argv[1]);
        printf("\n");
    }

    fclose(file);
}


