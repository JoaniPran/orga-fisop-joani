#include "parceador.h"
#include "cache.h"

int main (int argc, char* argv[]){ 
    argsParse(argc, argv);   

    cache_t* cache = makeCache();

    FILE *file = fopen(args.archTraza, "r");
    transaction_t t;
    int contador = 0;
    while(readTransaction(file, &t) && contador < 1) {
        process(cache, &t);
        contador++;
    }
    fclose(file);
    printStats(cache);
    realeseCache(cache);
    free(args.archTraza);

    return 0;
}
