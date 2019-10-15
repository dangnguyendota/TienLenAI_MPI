//
// Created by mpiuser on 15/10/2019.
//

#include "Card.h"

Card::Card(BaseCard *card) {
    this->card = card;
}

int Card::compareTo(Card *card) {
    return this->card->compareTo(card->card);
}
