//
// Created by mpiuser on 16/10/2019.
//

#include <stdexcept>
#include "QuadSequence.h"

QuadSequence::QuadSequence(Dub *dub1, Dub *dub2, Dub *dub3, Dub *dub4) {
    if (!valid(dub1, dub2, dub3, dub4))
        throw std::invalid_argument(
                "Quad Sequence exception: dub1 + 1 != dub2 or dub2 + 1 != dub3 or dub3 + 1 != dub4");
    this->dub1 = dub1;
    this->dub2 = dub2;
    this->dub3 = dub3;
    this->dub4 = dub4;
    this->minValue = dub1->getValue();
    this->maxType = dub4->getMaxType();
}

int QuadSequence::compareTo(QuadSequence *sequence) {
    if (this->minValue < sequence->minValue) return 1;
    if (this->minValue > sequence->minValue) return -1;
    int c = dub4->compareTo(sequence->dub4);
    if (c != 0) return c;
    c = dub3->compareTo(sequence->dub3);
    if (c != 0) return c;
    c = dub2->compareTo(sequence->dub2);
    if (c != 0) return c;
    return dub1->compareTo(sequence->dub1);
}
