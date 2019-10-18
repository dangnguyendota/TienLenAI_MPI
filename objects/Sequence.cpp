//
// Created by mpiuser on 16/10/2019.
//

#include <stdexcept>
#include "Sequence.h"

Sequence::Sequence(std::vector<BaseCard *> cards) {
    if (!valid(cards)) throw std::invalid_argument("Sequence exception: cards are not valid");
    this->cards = cards;
    this->minValue = cards[0]->getValue();
    this->maxValue = cards[cards.size() - 1]->getValue();
    this->type = cards[cards.size() - 1]->getType();
    this->homogeneity = this->isHomogeneity();
}

bool Sequence::isHomogeneity() {
    for (BaseCard *card : this->cards) {
        if (card->getType() != type) return false;
    }
    return true;
}

int Sequence::compareTo(Sequence *sequence) {
    if (this->cards.size() > sequence->cards.size()) return 1;
    if (this->cards.size() < sequence->cards.size()) return -1;
    if (this->minValue > sequence->minValue) return 1;
    if (this->minValue < sequence->minValue) return -1;
    for (int i = (int) cards.size() - 1; i >= 0; i--) {
        if (this->cards[i]->getType() > sequence->cards[i]->getType()) return 1;
        if (this->cards[i]->getType() < sequence->cards[i]->getType()) return -1;
    }
    return 0;
}

int Sequence::getMinValue() {
    return this->minValue;
}
