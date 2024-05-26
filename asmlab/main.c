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

    if((card->stacked->size) == 1 && *(cardStacked->number) == number2 && strcmp(cardStacked->suit, str2) == 0)
        printf("Exito");

    cardDelete(card);
    cardDelete(card2);
}


