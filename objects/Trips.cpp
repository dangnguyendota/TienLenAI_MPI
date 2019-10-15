//
// Created by mpiuser on 15/10/2019.
//

#include <stdexcept>
#include "Trips.h"

Trips::Trips(BaseCard *card1, BaseCard *card2, BaseCard *card3) {
    if(!valid(card1, card2, card3)) throw std::invalid_argument("Trips exception: cards have different values");
    this->card1 = card1;
    this->card2 = card2;
    this->card3 = card3;
    this->value = card1->getValue();
}

int Trips::compareTo(Trips *trips) {
    if (this->value > trips->value) return 1;
    if (this->value < trips->value) return -1;
    int c = this->card3->compareTo(trips->card3);
    if (c != 0) return c;
    c = this->card2->compareTo(trips->card2);
    if (c != 0) return c;
    return this->card1->compareTo(trips->card1);
}

int Trips::getValue() {
    return this->value;
}
