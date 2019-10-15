//
// Created by mpiuser on 15/10/2019.
//

#include <stdexcept>
#include "Quads.h"

Quads::Quads(BaseCard *card1, BaseCard *card2, BaseCard *card3, BaseCard *card4) {
    if (!valid(card1, card2, card3, card4)) throw std::invalid_argument("Quads exception: cards have different values");
    this->card1 = card1;
    this->card2 = card2;
    this->card3 = card3;
    this->card4 = card4;
    this->value = card1->getValue();
}

int Quads::compareTo(Quads *quads) {
    if(this->value == quads->value) return 0;
    return this->value > quads->value ? 1 : -1;
}
