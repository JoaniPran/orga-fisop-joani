#include "cache.h"

void inicializarStatsCache(statsCache_t *statsCache) {
    statsCache->bytesPorBloque = (args.sizeCache) / ((args.lineasPorSet) * (args.cantidadDeSets));
    statsCache->sizeCache = args.sizeCache;
    statsCache->lineasPorSet = args.lineasPorSet;
    statsCache->cantidadDeSets = args.cantidadDeSets;
    statsCache->n = args.n;
    statsCache->m = args.m;
    statsCache->loads = 0;
    statsCache->stores = 0;
}

statsCache_t* makeCache() {
    statsCache_t *statsCache = (statsCache_t*)malloc(sizeof(statsCache_t));
    inicializarStatsCache(statsCache);
    cache_t *cache = (cache_t*)malloc(sizeof(cache_t));
    cache->sets = malloc(sizeof(void*) * statsCache->cantidadDeSets);
    for(int i = 0; i < statsCache->cantidadDeSets; i++) {
        set_t *set = (set_t*)malloc(sizeof(set_t));
        set->lineas = malloc(sizeof(void*) * statsCache->lineasPorSet);
    }
    return statsCache;
}

void process(statsCache_t *cache, transaction_t *t) {
    if(strcmp(t->operation, "R")) cache->stores++;
    else if(strcmp(t->operation, "W")) cache->loads++;
}

void printStats(statsCache_t *cache) {
    printf("%i-way, %i sets, size = %iKB\n", cache->lineasPorSet, cache->cantidadDeSets, (cache->sizeCache/1000));
    printf("loads %i stores %i total %i\n", cache->loads, cache->stores, (cache->loads+cache->stores));
}