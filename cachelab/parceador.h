#ifndef PARCEADOR_H
#define PARCEADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

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
    uint32_t address;
    char operation;
    uint32_t address2;
    uint32_t size;
    uint32_t value;
} transaction_t;

extern transaction_t t;

bool argsParse(int argc, char* argv[]);
bool readTransaction(FILE *file, transaction_t *t);

bool cantidadCorrectaDeArgumentos(int argc);
void archivoTraza(char* nombreArchivo);
bool archivoExistente(char* archivoTraza);
int32_t argCache(char* argCache);
bool esPotenciaDeDos(int32_t numero);
bool argModoVerbosoValidos(int32_t n, int32_t m);
bool esCombinacionValida(int32_t C, int32_t E, int32_t S);
bool argsCacheCorrectos(char* argv[]);
void crearStructArgs(int32_t C, int32_t E, int32_t S, int32_t n, int32_t m);

#endif 