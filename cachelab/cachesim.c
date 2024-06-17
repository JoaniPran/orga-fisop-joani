#include "parceador.h"
#include "cache.h"

int main (int argc, char* argv[]){ 
    if(!argsParse(argc, argv)) return -1;  
    
    cache_t *cache = makeCache();

    FILE *file = fopen(args.archTraza, "r");
    transaction_t t;
    //int contador = 0;
    while(readTransaction(file, &t)) {
        process(cache, &t);
        //contador++;
    }
    // printf("%i\n", contador);
    fclose(file);
    
    // for (int i = 0; i < args.cantidadDeSets; ++i) {
    //     for (int j = 0; j < args.lineasPorSet; ++j) {
    //         printf("Set %d - Línea %d: Tag = %06x\n", i, j, cache->sets[i]->lineas[j]->tag);
    //     }
    // }

    printStats(cache);
    realeseCache(cache);
    return 0;
}

