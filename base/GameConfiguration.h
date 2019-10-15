//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_GAMECONFIGURATION_H
#define MPIPROJECT_GAMECONFIGURATION_H

#include "BaseObject.h"

class GameConfiguration {
public:
    bool *passed = new bool[4];
    int maxPlayer = 4;
    int previousPlayer = 0;
    BaseObject* lastDealt = nullptr;
    int currentPlayer = 0;
    bool gang_beat = false;
    bool first_turn = false;
    bool using_heuristic = true;
};
#endif //MPIPROJECT_GAMECONFIGURATION_H
