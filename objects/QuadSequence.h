//
// Created by mpiuser on 16/10/2019.
//

#ifndef MPIPROJECT_QUADSEQUENCE_H
#define MPIPROJECT_QUADSEQUENCE_H


#include "../base/BaseObject.h"
#include "Dub.h"

class QuadSequence : public BaseObject{
private:
    Dub *dub1;
    Dub *dub2;
    Dub *dub3;
    Dub *dub4;
    int minValue;
    int maxType;
public:
    QuadSequence(Dub *dub1, Dub *dub2, Dub *dub3, Dub *dub4);
};


#endif //MPIPROJECT_QUADSEQUENCE_H
