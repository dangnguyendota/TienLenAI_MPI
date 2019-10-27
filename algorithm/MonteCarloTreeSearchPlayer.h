//
// Created by mpiuser on 22/10/2019.
//

#ifndef MPIPROJECT_MONTECARLOTREESEARCHPLAYER_H
#define MPIPROJECT_MONTECARLOTREESEARCHPLAYER_H


#include "../base/BaseObject.h"
#include "../base/Game.h"
#include "MctsPlayerConfiguration.h"

class MonteCarloTreeSearchPlayer {
public:
    BaseObject *getMove(Game *game, MctsPlayerConfiguration *configuration);

};


#endif //MPIPROJECT_MONTECARLOTREESEARCHPLAYER_H
