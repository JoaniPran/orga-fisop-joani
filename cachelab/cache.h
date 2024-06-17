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

#define PENALTY 100

typedef struct s_dataCache {
    int32_t sizeCache;
    int32_t bytesPorBloque;
    int32_t lineasPorSet;
    int32_t cantidadDeSets;
    int32_t n;
    int32_t m;
} dataCache_t;

typedef struct s_operationCache {
    uint32_t tag;
    uint32_t set;
    uint32_t offset;
    char operation;
    uint32_t bytesPorOp;
} opCache_t;

typedef struct s_statsCache {
    int32_t loads;
    int32_t stores;
    int32_t rmiss;
    int32_t wmiss;
    int32_t dirtyRMiss;
    int32_t dirtyWMiss;
    int32_t bytesLeidosDeMemoria;
    int32_t bytesEscritosEnMemoria;
    int32_t readTime;
    int32_t writeTime;
    double_t missRate;
} statsCache_t;

typedef struct s_linea {
    bool bitValides;
    bool dirtyBit;
    uint32_t tag;
    uint32_t bloque;
    int32_t tiempoDeAcceso;
} linea_t;

typedef struct s_set {
    linea_t** lineas;
} set_t;

typedef struct s_cache {
    dataCache_t data;
    opCache_t op;
    statsCache_t stats;
    set_t** sets;
} cache_t;

void inicializarStatsCache(cache_t *cache);
linea_t* makeLinea();
set_t* makeSet(int32_t lineasPorSet);
cache_t* makeCache();
void mapearDir(cache_t *cache, transaction_t *t);
linea_t* lineaBuscada(cache_t* c);
linea_t *lineaVacia(cache_t* c);
void llenarLinea(linea_t* linea, cache_t* c);
void process(cache_t *cache, transaction_t *t);
void printStats(cache_t *cache);
void realeseCache(cache_t *cache);