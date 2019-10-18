//
// Created by mpiuser on 15/10/2019.
//

#include <stdexcept>
#include "DubSequence.h"

DubSequence::DubSequence(Dub *dub1, Dub *dub2) {
    if (!valid(dub1, dub2)) throw std::invalid_argument("Dub Sequence exception: dub1 + 1 != dub2");
    this->dub1 = dub1;
    this->dub2 = dub2;
    this->minValue = dub1->getValue();
    this->maxType = dub2->getMaxType();
}

int DubSequence::compareTo(DubSequence *sequence) {
    if (this->minValue > sequence->minValue) return 1;
    if (this->minValue < sequence->minValue) return -1;
    if (dub2->equals(sequence->dub2)) return dub1->compareTo(sequence->dub1);
    return dub2->compareTo(sequence->dub2);
}
