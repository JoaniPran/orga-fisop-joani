#include "parceador.h"
#include "cache.h"

int main (int argc, char* argv[]){ 
    argsParse(argc, argv);   

    statsCache_t* cache = makeCache();

    FILE *file = fopen(args.archTraza, "r");
    transaction_t t;
    while(readTransaction(file, &t)) {
        process(cache, &t);
    }
    printStats(cache);
    fclose(file);

    return 0;
}
