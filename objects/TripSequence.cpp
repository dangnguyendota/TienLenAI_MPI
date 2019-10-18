//
// Created by mpiuser on 15/10/2019.
//

#include <stdexcept>
#include "TripSequence.h"

TripSequence::TripSequence(Dub *dub1, Dub *dub2, Dub *dub3) {
    if (!valid(dub1, dub2, dub3))
        throw std::invalid_argument("Trip Sequence exception: dub1 + 1 != dub2 or dub2 +1 != dub3");
    this->dub1 = dub1;
    this->dub2 = dub2;
    this->dub3 = dub3;
    this->minValue = dub1->getValue();
    this->maxType = dub3->getMaxType();
}

int TripSequence::compareTo(TripSequence *sequence) {
    if (this->minValue > sequence->minValue) return 1;
    if (this->minValue < sequence->minValue) return -1;
    int c = dub3->compareTo(sequence->dub3);
    if (c != 0) return c;
    c = dub2->compareTo(sequence->dub2);
    if (c != 0) return c;
    return dub1->compareTo(sequence->dub1);
}
