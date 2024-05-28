#include "lib.h"

funcCmp_t *getCompareFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcCmp_t *)&intCmp;
        break;
    case TypeString:
        return (funcCmp_t *)&strCmp;
        break;
    case TypeCard:
        return (funcCmp_t *)&cardCmp;
        break;
    default:
        break;
    }
    return 0;
}
funcClone_t *getCloneFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcClone_t *)&intClone;
        break;
    case TypeString:
        return (funcClone_t *)&strClone;
        break;
    case TypeCard:
        return (funcClone_t *)&cardClone;
        break;
    default:
        break;
    }
    return 0;
}
funcDelete_t *getDeleteFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcDelete_t *)&intDelete;
        break;
    case TypeString:
        return (funcDelete_t *)&strDelete;
        break;
    case TypeCard:
        return (funcDelete_t *)&cardDelete;
        break;
    default:
        break;
    }
    return 0;
}
funcPrint_t *getPrintFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcPrint_t *)&intPrint;
        break;
    case TypeString:
        return (funcPrint_t *)&strPrint;
        break;
    case TypeCard:
        return (funcPrint_t *)&cardPrint;
        break;
    default:
        break;
    }
    return 0;
}

/** Int **/

int32_t intCmp(int32_t *a, int32_t *b)
{
    int32_t resultado = 0;
    if(*a == *b) {
        resultado = 0;
    } 
    else if(*a < *b) {
        resultado = 1;
    }
    else if(*a > *b) {
        resultado = -1;
    }

    return resultado;
}

void intDelete(int32_t *a)
{
    free(a);
}

void intPrint(int32_t *a, FILE *pFile)
{
    fprintf(pFile, "%d", *a);
}

int32_t *intClone(int32_t *a)
{
    int32_t *clonA = (int32_t*)malloc(sizeof(int32_t));
    *clonA = *a;
    return clonA;
}

/** Lista **/

list_t *listNew(type_t t)
{
    list_t *lista = (list_t*)malloc(sizeof(list_t));
    lista->type = t;
    lista->size = 0;
    lista->first = NULL;
    lista->last = NULL;
    return lista;
}

uint8_t listGetSize(list_t *l)
{
    return l->size;
}

void *listGet(list_t *l, uint8_t i)
{
    if(i > (l->size-1))
        return 0;
    
    int contador = 0;
    listElem_t *actual = l->first;

    while(contador != i) {
        actual = actual->next;
        contador++;
    }

    return actual->data;
}

void listAddFirst(list_t *l, void *data)
{
    //Nuevo nodo de la lista
    listElem_t *nuevoNodo = (listElem_t*)malloc(sizeof(listElem_t));

    //Clonamos el dato y lo guardamos en la data del nodo
    funcClone_t *funcionClonar = getCloneFunction(l->type);
    nuevoNodo->data = funcionClonar(data);

    nuevoNodo->next = l->first;
    nuevoNodo->prev = NULL;

    //Lista vacia
    if(l->first == NULL) 
    {
        l->first = nuevoNodo;
        l->last = nuevoNodo;
    }
    //Lista con elementos
    else 
    {
        l->first->prev = nuevoNodo;
        l->first = nuevoNodo;
    }

    l->size++;
}

void listAddLast(list_t *l, void *data)
{
    //Nuevo nodo de la lista
    listElem_t *nuevoNodo = (listElem_t*)malloc(sizeof(listElem_t));

    //Clonamos el dato y lo guardamos en la data del nodo
    funcClone_t *funcionClonar = getCloneFunction(l->type);
    nuevoNodo->data = funcionClonar(data);

    //Lista vacia
    if(l->first == NULL) 
    {
        nuevoNodo->next = NULL;
        nuevoNodo->prev = NULL;
        l->first = nuevoNodo;
        l->last = nuevoNodo;
    }
    //Lista con elementos
    else
    {
        l->last->next = nuevoNodo;
        nuevoNodo->prev = l->last;
        nuevoNodo->next = NULL;
        l->last = nuevoNodo;
    }
    l->size++;
}

list_t *listClone(list_t *l)
{
    list_t *nuevaLista = listNew(l->type);

    if(l->size != 0) {
        listElem_t* nodoActual = l->first;
        uint8_t contador = 1;

        while(contador <= l->size) {
            listAddLast(nuevaLista, nodoActual->data);
            nodoActual = nodoActual->next;
            contador++;
        }
    }

    return nuevaLista;
}

void *listRemove(list_t *l, uint8_t i)
{
    int contador = 0;
    listElem_t *actual = NULL;
    listElem_t *nodoSiguiente = NULL;

    if(i > (l->size-1))
        return NULL;

    actual = l->first;

    while(contador != i) {
        actual = actual->next;
        contador++;
    }

    //Lista tiene un elemento
    if(l->size == 1) {
        l->first = NULL;
        l->last = NULL;
    }
    //Lista con mas de un elemento y borro el primero
    else if(actual == l->first) {
        nodoSiguiente = actual->next;
        l->first = nodoSiguiente;
        nodoSiguiente->prev = NULL;
    }
    //Lista con mas de un elemento y borro el ultimo
    else if(actual->next == NULL) {
        l->last = actual->prev;
        actual->prev->next = NULL;
    }
    //Lista con mas de un elemento y borro uno del medio
    else {
        actual->prev->next = actual->next;
        actual->next->prev = actual->prev;
    }

    funcClone_t *funcionClonar = getCloneFunction(l->type);
    void* actualData = funcionClonar(actual->data);

    l->size--;

    funcDelete_t *funcionDelete = getDeleteFunction(l->type);
    funcionDelete(actual->data);
    
    free(actual);

    return actualData;
}

void listSwap(list_t* l, uint8_t i, uint8_t j) 
{
    if (i >= l->size || j >= l->size) {
        return;
    }

    listElem_t* elementoI = l->first;
    listElem_t* elementoJ = l->first;

    for (int contador = 0; contador < i; contador++) {
        elementoI = elementoI->next;
    }
    for (int contador = 0; contador < j; contador++) {
        elementoJ = elementoJ->next;
    }

    void* auxiliar = elementoI->data;
    elementoI->data = elementoJ->data;
    elementoJ->data = auxiliar;
}


void listDelete(list_t *l)
{
    funcDelete_t * funcionDelete = getDeleteFunction(l->type);

    listElem_t* nodoActual = l->first;
    listElem_t* next;
    
    while (nodoActual != NULL) {
        next = nodoActual->next;
        funcionDelete(nodoActual->data);
        free(nodoActual);
        nodoActual = next;
    }

    l->first = NULL;
    l->last = NULL;
    l->size = 0;

    free(l);
}

void listPrint(list_t *l, FILE *pFile)
{
    funcPrint_t *printFunction = getPrintFunction(l->type);

    if (printFunction == NULL) {
        return;
    }
    fprintf(pFile, "[");
    listElem_t* nodoActual = l->first;
    while (nodoActual != NULL) {
        printFunction(nodoActual->data, pFile);
        nodoActual = nodoActual->next;
        if (nodoActual != NULL) {
            fprintf(pFile, ",");
        }
    }
    fprintf(pFile, "]");
}

/** Game **/

game_t *gameNew(void *cardDeck, funcGet_t *funcGet, funcRemove_t *funcRemove, funcSize_t *funcSize, funcPrint_t *funcPrint, funcDelete_t *funcDelete)
{
    game_t *game = (game_t *)malloc(sizeof(game_t));
    game->cardDeck = cardDeck;
    game->funcGet = funcGet;
    game->funcRemove = funcRemove;
    game->funcSize = funcSize;
    game->funcPrint = funcPrint;
    game->funcDelete = funcDelete;
    return game;
}
int gamePlayStep(game_t *g)
{
    int applied = 0;
    uint8_t i = 0;
    while (applied == 0 && i + 2 < g->funcSize(g->cardDeck))
    {
        card_t *a = g->funcGet(g->cardDeck, i);
        card_t *b = g->funcGet(g->cardDeck, i + 1);
        card_t *c = g->funcGet(g->cardDeck, i + 2);
        if (strCmp(cardGetSuit(a), cardGetSuit(c)) == 0 || intCmp(cardGetNumber(a), cardGetNumber(c)) == 0)
        {
            card_t *removed = g->funcRemove(g->cardDeck, i);
            cardAddStacked(b, removed);
            cardDelete(removed);
            applied = 1;
        }
        i++;
    }
    return applied;
}
uint8_t gameGetCardDeckSize(game_t *g)
{
    return g->funcSize(g->cardDeck);
}
void gameDelete(game_t *g)
{
    g->funcDelete(g->cardDeck);
    free(g);
}
void gamePrint(game_t *g, FILE *pFile)
{
    g->funcPrint(g->cardDeck, pFile);
}
