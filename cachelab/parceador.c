#include "parceador.h"

args_t args;

bool cantidadCorrectaDeArgumentos(int argc) {
    if(argc != 5 && argc != 8) {
        fprintf(stderr, "La cantidad de parámetros no es la correcta.\n");
        return false;
    }
    return true;
}

char* archivoTraza(char* nombreArchivo) {
    char* arch = malloc(strlen(nombreArchivo) + strlen("trazas/") + 1);
    strcpy(arch, "trazas/");
    strcat(arch, nombreArchivo);
    return arch;
}

bool archivoExistente(char* archivoTraza) {
    FILE *file = fopen(archivoTraza, "r");
    if(file == NULL) {
        fprintf(stderr, "Archivo inexistente.\n");
        return false;
    }
    fclose(file);
    return true;
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

bool argsCacheCorrectos(char* argv[]) {
    if(!esPotenciaDeDos(argCache(argv[2]))) {
        fprintf(stderr, "El tamaño de la Cache: %d no es potencia de 2.\n", argCache(argv[2]));
        return false;
    }
    else if(!esPotenciaDeDos(argCache(argv[3]))) {
        fprintf(stderr, "La cantidad de lineas: %d no es potencia de 2.\n", argCache(argv[3]));
        return false;
    }
    else if(!esPotenciaDeDos(argCache(argv[4]))) {
        fprintf(stderr, "La cantidad de sets: %d no es potencia de 2.\n", argCache(argv[4]));
        return false;
    }
    else if(!argModoVerbosoValidos(argCache(argv[6]), argCache(argv[7]))) {
        fprintf(stderr, "Los parámetros deben cumplir 0 ≤ n ≤ m. n = %d, m = %d\n", argCache(argv[6]), argCache(argv[7]));
        return false;
    }
    else if(!esCombinacionValida(argCache(argv[2]), argCache(argv[3]), argCache(argv[4]))) {
        fprintf(stderr, "La combinación de C = %d, E = %d, S = %d no es válida.\n", 
                argCache(argv[2]), argCache(argv[3]), argCache(argv[4]));
        return false;
    }
    return true;
}

void crearStructArgs(char* archTraza, int32_t C, int32_t E, int32_t S, int32_t n, int32_t m) {
    args.archTraza = archTraza;
    args.sizeCache = C;
    args.lineasPorSet = E;
    args.cantidadDeSets = S;
    args.n = n;
    args.m = m;
}

bool argsParse(int argc, char* argv[]) {
    // char* archTraza = archivoTraza(argv[1]);
    if(!argsCacheCorrectos(argv)) return false;
    if(!cantidadCorrectaDeArgumentos(argc)) return false;
    // if(!archivoExistente(archTraza)) {
    //     free(archTraza);
    //     return false;
    // }
    // crearStructArgs(archTraza, argCache(argv[2]), argCache(argv[3]), argCache(argv[4]), argCache(argv[6]), argCache(argv[7]));
    // free(archTraza);
    return true;
}

bool readTransaction(FILE *file, transaction_t *t) {
    char buffer[100];
    char* op;
    if(fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        t->address = (uint32_t)strtol(strtok(buffer, ": "), NULL, 16);
        op = strtok(NULL, " ");
        t->operation = op[0];
        t->address2 = (uint32_t)strtol(strtok(NULL, " "), NULL, 16);
        t->size = (uint32_t)strtol(strtok(NULL, " "), NULL, 10);
        t->value = (uint32_t)strtol(strtok(NULL, " "), NULL, 16);
        return true;
    }
    else return false;
}