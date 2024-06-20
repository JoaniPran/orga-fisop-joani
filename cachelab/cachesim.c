#include "parceador.h"
#include "cache.h"

int main (int argc, char* argv[]){ 
    if(!argsParse(argc, argv)) return -1;  
    
    cache_t *cache = makeCache();
    FILE *file = fopen(args.archTraza, "r");
    if(file) {
        transaction_t t;
        while(readTransaction(file, &t)) {
            process(cache, &t);
        }
        fclose(file);
        printStats(cache);
        realeseCache(cache);
    }
    realeseCache(cache);
    return 0;
}
