#include "parceador.h"

args_t args;

bool argsParse(int argc, char* argv[]) {
    if(!argsCacheCorrectos(argv)) {
        return false;
    }
    if(!cantidadCorrectaDeArgumentos(argc)) {
        return false;
    }
    if(!archivoExistente(argv[1])) {
        return false;
    }
    archivoTraza(argv[1]);
    crearStructArgs(argCache(argv[2]), argCache(argv[3]), argCache(argv[4]), argCache(argv[6]), argCache(argv[7]));
    return true;
}

bool readTransaction(FILE *file, transaction_t *t) {
    char buffer[100];
    char* op;

    if(!fgets(buffer, sizeof(buffer), file)) return false;

    buffer[strcspn(buffer, "\n")] = 0;
    t->address = (uint32_t)strtol(strtok(buffer, ": "), NULL, 16);
    op = strtok(NULL, " ");
    t->operation = op[0];
    t->address2 = (uint32_t)strtol(strtok(NULL, " "), NULL, 16);
    t->size = (uint32_t)strtol(strtok(NULL, " "), NULL, 10);
    t->value = (uint32_t)strtol(strtok(NULL, " "), NULL, 16);

    return true;
}

bool cantidadCorrectaDeArgumentos(int argc) {
    if(argc != 5 && argc != 8) {
        fprintf(stderr, "La cantidad de parámetros no es la correcta.\n");
        return false;
    }
    return true;
}

bool archivoExistente(char* nombreArchivo) {
    char adpcm[] = "adpcm.xex";
    char blowfish[] = "blowfish.xex";
    char fft[] = "FFT.xex";

    if(!strcmp(adpcm, nombreArchivo) || !strcmp(blowfish, nombreArchivo) || !strcmp(fft, nombreArchivo)) {
        fprintf(stderr, "Archivo inexistente.\n");
        return false;
    }

    return true;
}

void archivoTraza(char* nombreArchivo) {
    args.archTraza = malloc(strlen(nombreArchivo) + strlen("trazas/") + 1);
    strcpy(args.archTraza, "trazas/");
    strcat(args.archTraza, nombreArchivo);
}

int32_t argCache(char* argCache) {
    return (int32_t)strtol(argCache, NULL, 10);
}

bool esPotenciaDeDos(int32_t numero) {
    return (numero > 0) && ((numero & (numero - 1)) == 0);
}

bool argModoVerbosoValidos(int32_t n, int32_t m) {
    return n >= 0 && n <= m;
}

bool esCombinacionValida(int32_t C, int32_t E, int32_t S) {
    return (C % (E * S) == 0);
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

void crearStructArgs(int32_t C, int32_t E, int32_t S, int32_t n, int32_t m) {
    args.sizeCache = C;
    args.lineasPorSet = E;
    args.cantidadDeSets = S;
    args.n = n;
    args.m = m;
}