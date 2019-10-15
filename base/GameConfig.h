//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_GAMECONFIG_H
#define MPIPROJECT_GAMECONFIG_H

class GameConfig {
public:
    const double    lose_average = 21.210312113384926;
    const double    heuristic_average = 26.63044504005798;
    const double    RED_CARD_OF_TWO = 0.1;
    const double    BLACK_CARD_OF_TWO = 0.05;
    const double    NORMAL_CARD = 0.01;
    const double    TRIP_SEQUENCE = 0.04;
    const double    QUAD_SEQUENCE = 0.22;
    const double    QUAD = 0.16;
    const double    PLY_FACTOR = 0.005;
    const int       LATE_CARDS = 6;
    const int       MAX_PLY = 4;
};

#endif //MPIPROJECT_GAMECONFIG_H
