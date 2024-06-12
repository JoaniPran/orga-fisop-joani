#include "parceador.h"

args_t args;

void verificarCantidadDeArgumentos(int argc) {
    if(argc != 5 && argc != 8) {
        fprintf(stderr, "La cantidad de parámetros no es la correcta.\n");
        exit(EXIT_FAILURE);
    }
}

char* archivoTraza(char* nombreArchivo) {
    char* archivoTraza = malloc(strlen(nombreArchivo) + strlen("trazas/") + 1);
    strcpy(archivoTraza, "trazas/");
    strcat(archivoTraza, nombreArchivo);
    return archivoTraza;
}

void verificarArchivo(char* nombreArchivo) {
    char* archTraza = archivoTraza(nombreArchivo);
    FILE *file = fopen(archTraza, "r");
    if(file == NULL) {
        fprintf(stderr, "Archivo inexistente.\n");
        free(archTraza);
        exit(EXIT_FAILURE);
    }
    fclose(file);
    free(archTraza);
}

int32_t argCache(char* argCache) {
    int32_t arg = (int32_t)strtol(argCache, NULL, 10);
    return arg;
}

bool esPotenciaDeDos(int32_t numero) {
    return (numero > 0) && ((numero & (numero - 1)) == 0);
}

bool argModoVerbosoValidos(int32_t n, int32_t m) {
    return n >= 0 && n <= m;
}

bool esCombinacionValida(int32_t C, int32_t E, int32_t S) {
    if (C % (E * S) != 0) {
        return false;
    }
    return true;
}

void verificarArgCache(char* argv[]) {
    if(!esPotenciaDeDos(argCache(argv[2]))) {
        fprintf(stderr, "El tamaño de la Cache: %d no es potencia de 2.\n", argCache(argv[2]));
        exit(EXIT_FAILURE);
    }
    if(!esPotenciaDeDos(argCache(argv[3]))) {
        fprintf(stderr, "La cantidad de lineas: %d no es potencia de 2.\n", argCache(argv[3]));
        exit(EXIT_FAILURE);
    }
    if(!esPotenciaDeDos(argCache(argv[4]))) {
        fprintf(stderr, "La cantidad de sets: %d no es potencia de 2.\n", argCache(argv[4]));
        exit(EXIT_FAILURE);
    }
    if(!argModoVerbosoValidos(argCache(argv[6]), argCache(argv[7]))) {
        fprintf(stderr, "Los parámetros deben cumplir 0 ≤ n ≤ m. n = %d, m = %d\n", argCache(argv[6]), argCache(argv[7]));
        exit(EXIT_FAILURE);
    }
    if(!esCombinacionValida(argCache(argv[2]), argCache(argv[3]), argCache(argv[4]))) {
        printf("La combinación de C = %d, E = %d, S = %d no es válida.\n", 
                argCache(argv[2]), argCache(argv[3]), argCache(argv[4]));
        exit(EXIT_FAILURE);
    }
}

args_t crearStructArgs(char* archTraza, int32_t C, int32_t E, int32_t S, int32_t n, int32_t m) {
    args.archTraza = archTraza;
    args.sizeCache = C;
    args.lineasPorSet = E;
    args.cantidadDeSets = S;
    args.n = n;
    args.m = m;
    return args;
}

void argsParse(int argc, char* argv[]) {
    verificarCantidadDeArgumentos(argc);

    verificarArchivo(argv[1]);
    
    verificarArgCache(argv);

    args = crearStructArgs(archivoTraza(argv[1]), argCache(argv[2]), argCache(argv[3]), argCache(argv[4]), 
    argCache(argv[6]), argCache(argv[7]));
}

bool readTransaction(FILE *file, transaction_t *t) {
    char buffer[40];
    if(fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        t->address = (uint32_t)strtol(strtok(buffer, ": "), NULL, 16);
        t->operation = strtok(NULL, " ");
        t->address2 = (uint32_t)strtol(strtok(NULL, " "), NULL, 16);
        t->size = (uint32_t)strtol(strtok(NULL, " "), NULL, 10);
        t->value = (uint32_t)strtol(strtok(NULL, " "), NULL, 16);
        return true;
    }
    return false;
}