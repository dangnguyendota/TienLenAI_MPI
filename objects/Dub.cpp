//
// Created by mpiuser on 15/10/2019.
//

#include <stdexcept>
#include "Dub.h"

Dub::Dub(BaseCard *card1, BaseCard *card2) {
    if (!valid(card1, card2)) throw std::invalid_argument("Dub exception: cards have two different values");
    this->card1 = card1;
    this->card2 = card2;
    this->maxType = std::max(card1->getType(), card2->getType());
    this->minType = std::min(card1->getType(), card2->getType());
    this->value = card1->getValue();


}

int Dub::getValue() {
    return this->value;
}

int Dub::compareTo(Dub *dub) {
    if (this->value > dub->value) return 1;
    if (this->value < dub->value) return -1;
    if (this->maxType > dub->maxType) return 1;
    if (this->maxType < dub->maxType) return -1;
    return this->minType < dub->minType ? -1 : 1;
}

int Dub::getMaxType() {
    return this->maxType;
}
