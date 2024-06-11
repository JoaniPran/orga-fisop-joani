#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef GLOBALS_H
#define GLOBALS_H
typedef struct s_args {
    char* archTraza;
    int32_t sizeCache;
    int32_t lineasPorSet;
    int32_t cantidadDeSets;
    int32_t n;
    int32_t m;
} args_t;
extern args_t args;

typedef struct s_transaction {
    char* address;
    char* operation;
    char* address2;
    char* size;
    char* value;
} transaction_t;
extern transaction_t t;
#endif

void verificarCantidadDeArgumentos(int argc);
char* archivoTraza(char* nombreArchivo);
void verificarArchivo(char* nombreArchivo);
int32_t argCache(char* argCache);
bool esPotenciaDeDos(int32_t numero);
bool argModoVerbosoValidos(int32_t n, int32_t m);
bool esCombinacionValida(int32_t C, int32_t E, int32_t S);
void verificarArgCache(char* argv[]);
args_t crearStructArgs(char* archTraza, int32_t C, int32_t E, int32_t S, int32_t n, int32_t m);
void argsParse(int argc, char* argv[]);
bool readTransaction(FILE *file, transaction_t *t);
