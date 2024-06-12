#include "cache.h"

void inicializarStatsCache(cache_t *cache) {
    cache->bytesPorBloque = (args.sizeCache) / ((args.lineasPorSet) * (args.cantidadDeSets));
    cache->sizeCache = args.sizeCache;
    cache->lineasPorSet = args.lineasPorSet;
    cache->cantidadDeSets = args.cantidadDeSets;
    cache->n = args.n;
    cache->m = args.m;

    cache->tag = 0;
    cache->set = 0;
    cache->offset = 0;

    cache->loads = 0;
    cache->stores = 0;
    cache->rmiss = 0;
}

linea_t* makeLinea() {
    linea_t* linea = (linea_t*)malloc(sizeof(linea_t));
    linea->bitValides = 0;
    linea->dirtyBit = 0;
    linea->tag = 0;
    linea->bloque = 0;
    return linea;
}

set_t* makeSet(cache_t* cache) {
    set_t* set = (set_t*)malloc(sizeof(set_t));
    set->lineas = malloc(sizeof(void*) * cache->cantidadDeSets);
    for(int i = 0; i < cache->cantidadDeSets; i++) {
        set->lineas[i] = makeLinea();
    }
    return set;
}

cache_t* makeCache() {
    cache_t *cache = (cache_t*)malloc(sizeof(cache_t));
    inicializarStatsCache(cache);
    cache->sets = malloc(sizeof(void*) * cache->cantidadDeSets);
    for(int i = 0; i < cache->cantidadDeSets; i++) {
        cache->sets[i] = makeSet(cache);
    }
    return cache;
}

void mapearDir(cache_t *cache, transaction_t *t) {
    uint32_t address = t->address2;
    int32_t offsetBit = log2(cache->bytesPorBloque);
    int32_t setBit = log2(cache->cantidadDeSets);

    uint32_t mascaraSet = (1 << setBit) - 1;
    uint32_t mascaraOffset = (1 << offsetBit) - 1;

    cache->tag = address >> (setBit + offsetBit);
    cache->set = (address >> offsetBit) & mascaraSet;
    cache->offset = address & mascaraOffset;
}

bool setVacio(cache_t* cache) {
    int32_t cantidadLineasOcupadas = 0;
    set_t *set = (set_t*)cache->sets[cache->set];
    for(int i = 0; i < cache->lineasPorSet; i++) {
        linea_t *linea = set->lineas[i];
        if(linea->tag != 0) {
            cantidadLineasOcupadas++;
        }
    }
    if(cantidadLineasOcupadas == 0) return true;
    else return false;
}

linea_t *llenarLinea(cache_t* cache) {
    linea_t *l = ((set_t*)cache->sets[cache->set])->lineas[0];
    l->tag = cache->tag;
    return l;
}

void process(cache_t *cache, transaction_t *t) {
    mapearDir(cache, t);
    if(strcmp(t->operation, "R")) cache->stores++;
    else if(strcmp(t->operation, "W")) cache->loads++;
    if(setVacio(cache) && strcmp(t->operation, "R")) {
        cache->rmiss++;
        llenarLinea(cache);
    }
}

void printStats(cache_t *cache) {
    printf("%i-way, %i sets, size = %iKB\n", cache->lineasPorSet, cache->cantidadDeSets, (cache->sizeCache/1000));
    printf("loads %i stores %i total %i\n", cache->loads, cache->stores, (cache->loads+cache->stores));
    printf("rmiss %i\n", cache->rmiss);
    printf("%06x tag\n", cache->tag);
}

void realeseCache(cache_t *cache) {
    for(int i = 0; i < cache->cantidadDeSets; i++) {
        set_t *set = cache->sets[i];
        for(int j = 0; j < cache->lineasPorSet; j++) {
            free(set->lineas[j]);
        }
        free(set->lineas);
        free(set);
    }
    free(cache->sets);
    free(cache);
}