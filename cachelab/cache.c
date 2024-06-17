#include "cache.h"

void inicializarStatsCache(cache_t *cache) {
    cache->data.bytesPorBloque = (args.sizeCache) / ((args.lineasPorSet) * (args.cantidadDeSets));
    cache->data.sizeCache = args.sizeCache;
    cache->data.lineasPorSet = args.lineasPorSet;
    cache->data.cantidadDeSets = args.cantidadDeSets;
    cache->data.n = args.n;
    cache->data.m = args.m;

    cache->op.tag = 0;
    cache->op.set = 0;
    cache->op.offset = 0;

    cache->stats.loads = 0;
    cache->stats.stores = 0;
    cache->stats.rmiss = 0;
    cache->stats.wmiss = 0;
}

// linea_t* makeLinea() {
//     linea_t* l = malloc(sizeof(linea_t));
//     l->bitValides = false;
//     l->dirtyBit = false;
//     l->tag = 0;
//     l->tiempoDeAcceso = 0;
//     l->numeroDeLinea = 0;
//     return l;
// }

// set_t* makeSet(int32_t lineasPorSet) {
//     set_t* s = malloc(sizeof(set_t) + lineasPorSet * sizeof(linea_t));
//     for(int i = 0; i < lineasPorSet; i++) {
//         s->lineas[i] = *makeLinea();
//     }
//     return s;
// }

cache_t* makeCache() {
    //cache_t* c = (cache_t*)malloc(sizeof(cache_t));
    //inicializarStatsCache(c);
    //c = malloc(sizeof(cache_t) + c->data.cantidadDeSets * sizeof(set_t));
    // for(int i = 0; i <  args.cantidadDeSets; i++) {
    //     c->sets[i] = *makeSet(args.lineasPorSet);
    // }
    cache_t* cache = (cache_t*)malloc(sizeof(cache_t));
    cache->sets = (set_t**)malloc(args.cantidadDeSets * sizeof(set_t*));
    for(int i = 0; i < args.cantidadDeSets; i++) {
        cache->sets[i] = (set_t*)malloc(sizeof(set_t));
        cache->sets[i]->lineas = (linea_t**)malloc(args.lineasPorSet * sizeof(linea_t*));
        for(int j = 0; j < args.lineasPorSet; j++) {
            cache->sets[i]->lineas[j] = (linea_t*)malloc(sizeof(linea_t));
        }
    }    
    inicializarStatsCache(cache);
    return cache;
}

void mapearDir(cache_t *cache, transaction_t *t) {
    uint32_t address = t->address2;
    int32_t offsetBit = log2(cache->data.bytesPorBloque);
    int32_t setBit = log2(cache->data.cantidadDeSets);

    uint32_t mascaraSet = (1 << setBit) - 1;
    uint32_t mascaraOffset = (1 << offsetBit) - 1;

    cache->op.tag = address >> (setBit + offsetBit);
    cache->op.set = (address >> offsetBit) & mascaraSet;
    cache->op.offset = address & mascaraOffset;
    cache->op.operation = t->operation;
    cache->op.bytesPorOp = t->size;
}

bool tagEncontrado(cache_t *cache) {
    linea_t* linea;
    for(int i = 0; i < args.lineasPorSet; i++) {
        linea = cache->sets[cache->op.set]->lineas[i];
        if(linea->tag == cache->op.tag) {
            linea->tiempoDeAcceso = 0;
            if(linea->dirtyBit == true) {
                return true;
            }
            else {
                if(cache->op.operation == 'W') {
                    linea->dirtyBit = true;
                }
                else {
                    linea->dirtyBit = false;
                }
            }
            return true;
        }
    }
    return false;
}

linea_t* lineaVacia(cache_t* cache) {
    linea_t* linea;
    for(int i = 0; i < args.lineasPorSet; i++) {
        linea = cache->sets[cache->op.set]->lineas[i];
        if(linea->tag == 0) {
            return linea;
        }
    }
    return NULL;
}

void process(cache_t *cache, transaction_t *t) {
    mapearDir(cache, t);

    if(cache->op.operation == 'R') {
        cache->stats.loads++;
    }
    else {
        cache->stats.stores++;
    }
    
    for(int i = 0; i < args.lineasPorSet; i++) {
        cache->sets[cache->op.set]->lineas[i]->tiempoDeAcceso++;
    }

    if(tagEncontrado(cache)) {
        if(cache->op.operation == 'R') {
            cache->stats.readTime++;
        }
        else {
            cache->stats.writeTime++;
        }
        return;
    }
    else {
        cache->stats.bytesLeidosDeMemoria += cache->data.bytesPorBloque;
        
        if(t->operation == 'R') {
            cache->stats.rmiss++;
        }
        else {
            cache->stats.wmiss++;
        }

        linea_t* linea = lineaVacia(cache);
        if(linea != NULL) {
            //ocupar linea
            linea->bitValides = true;
            if(cache->op.operation == 'W') {
                linea->dirtyBit = true;
                cache->stats.writeTime += 1 + PENALTY;
            }
            else {
                linea->dirtyBit = false;
                cache->stats.readTime += 1 + PENALTY;
            }
            linea->tag = cache->op.tag;
            linea->tiempoDeAcceso = 0;
        }
        else {
            //Desocupar linea
            linea_t* lineaADesocupar = cache->sets[cache->op.set]->lineas[0];
            for(int i = 1; i < args.lineasPorSet; i++) {
                linea_t* lineaActual = cache->sets[cache->op.set]->lineas[i];
                if(lineaADesocupar->tiempoDeAcceso < lineaActual->tiempoDeAcceso) {
                    lineaADesocupar = lineaActual;
                }
            }
            if(lineaADesocupar->dirtyBit == true) {
                cache->stats.bytesEscritosEnMemoria += cache->data.bytesPorBloque;
                if(cache->op.operation == 'R') {
                    cache->stats.dirtyRMiss++;
                    cache->stats.readTime += 1 + 2 * PENALTY;
                }
                else {
                    cache->stats.dirtyWMiss++;
                    cache->stats.writeTime += 1 + 2 * PENALTY;
                }
            }
            else {
                if(cache->op.operation == 'R') {
                    cache->stats.readTime += 1 + PENALTY;
                }
                else {
                    cache->stats.writeTime += 1 + PENALTY;
                }
            }
            
            lineaADesocupar->dirtyBit = false;
            lineaADesocupar->tag = 0;

            linea_t* linea = lineaVacia(cache);
            if(linea != NULL) {
                if(cache->op.operation == 'W') {
                    linea->dirtyBit = true;
                }
                else {
                    linea->dirtyBit = false;
                }
                linea->tag = cache->op.tag;
                linea->tiempoDeAcceso = 0;
            }
            else {
                return;
            }
        }
    }
    cache->stats.missRate = (double_t) (cache->stats.rmiss + cache->stats.wmiss)/100000;
}

void printStats(cache_t *cache) {
    if(cache->data.lineasPorSet > 1) {
        printf("%i-way, %i sets, size = %iKB\n", 
        cache->data.lineasPorSet, cache->data.cantidadDeSets, (cache->data.sizeCache/1000));
    }
    else {
        printf("direct-mapped, %i sets, size = %iKB\n", cache->data.cantidadDeSets, (cache->data.sizeCache/1000));
    }
    printf("loads %i stores %i total %i\n", cache->stats.loads, cache->stats.stores, (cache->stats.loads+cache->stats.stores));
    printf("rmiss %i wmiss %i total %i\n", cache->stats.rmiss, cache->stats.wmiss, (cache->stats.rmiss+cache->stats.wmiss));
    printf("dirty rmiss %i dirty wmiss %i\n", cache->stats.dirtyRMiss, cache->stats.dirtyWMiss);
    printf("bytes read %i bytes written %i\n", cache->stats.bytesLeidosDeMemoria, cache->stats.bytesEscritosEnMemoria);
    printf("read time %i write time %i\n", cache->stats.readTime, cache->stats.writeTime);
    printf("miss rate %.6f\n", cache->stats.missRate);
}

// void realeseLinea(linea_t *l) {
//     free(l);
// }

// void realeseSet(set_t *s, int32_t lineasPorSet) {
//     for(int i = 0; i < lineasPorSet; i++) {
//         realeseLinea(&(s->lineas[i]));
//     }
//     free(s);
// }

void realeseCache(cache_t *cache) {
    // for (int i = 0; i < args.cantidadDeSets; i++) {
    //     realeseSet(&(c->sets[i]), args.lineasPorSet);
    // }
    // free(c);
    // free(args.archTraza);

    for(int i = 0; i < args.cantidadDeSets; i++) {
        for(int j = 0; j < args.lineasPorSet; j++) {
            free(cache->sets[i]->lineas[j]);
        }
        free(cache->sets[i]->lineas);
        free(cache->sets[i]);
    }
    free(cache->sets);
    free(cache);
    
    free(args.archTraza);
}