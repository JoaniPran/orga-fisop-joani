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

typedef struct s_cache {
    int32_t sizeCache;
    int32_t bytesPorBloque;
    int32_t lineasPorSet;
    int32_t cantidadDeSets;
    int32_t n;
    int32_t m;

    uint32_t tag;
    uint32_t set;
    uint32_t offset;

    int32_t loads;
    int32_t stores;
    int32_t rmiss;
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

void inicializarStatsCache(cache_t *cache);

linea_t* makeLinea();

set_t* makeSet(cache_t* cache);

cache_t* makeCache();

void mapearDir(cache_t *cache, transaction_t *t);

bool setVacio(cache_t* cache);

linea_t *llenarLinea(cache_t* cache);

void process(cache_t *cache, transaction_t *t);

void printStats(cache_t *cache);

void realeseCache(cache_t *cache);