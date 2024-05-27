#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "lib.h"

int main (void){    
    int32_t number = 12;
    char str[] = "espada";
    card_t *card = cardNew(str, &number);

    int32_t number2 = 4;
    char str2[] = "oro";
    card_t *card2 = cardNew(str2, &number2);

    cardAddStacked(card, card2);

    card_t *cardStacked = listGet(card->stacked, 0);

    assert((card->stacked->size) == 1);
    assert(*(cardStacked->number) == number2);
    assert(strcmp(cardStacked->suit, str2) == 0);

    cardDelete(card);
    cardDelete(card2);
}


