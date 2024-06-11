#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include "parceador.h"

typedef struct s_statsCache {
    int32_t sizeCache;
    int32_t bytesPorBloque;
    int32_t lineasPorSet;
    int32_t cantidadDeSets;
    int32_t n;
    int32_t m;
    int32_t loads;
    int32_t stores;
} statsCache_t;

typedef struct s_cache {
    void** sets;
} cache_t;

typedef struct s_set {
    void** lineas;
} set_t;

typedef struct s_linea {
    int32_t bitValides;
    int32_t dirtyBit;
    int32_t tag;
    int32_t bloque;
} linea_t;

void inicializarStatsCache(statsCache_t *cache);

statsCache_t* makeCache();

void process(statsCache_t *cache, transaction_t *t);

void printStats(statsCache_t *cache);