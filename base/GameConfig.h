//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_GAMECONFIG_H
#define MPIPROJECT_GAMECONFIG_H

class GameConfig {
public:
    static constexpr double lose_average = 21.210312113384926;
    static constexpr double heuristic_average = 26.63044504005798;
    static constexpr double RED_CARD_OF_TWO = 0.1;
    static constexpr double BLACK_CARD_OF_TWO = 0.05;
    static constexpr double NORMAL_CARD = 0.01;
    static constexpr double TRIP_SEQUENCE = 0.04;
    static constexpr double QUAD_SEQUENCE = 0.22;
    static constexpr double QUAD = 0.16;
    static constexpr double PLY_FACTOR = 0.005;
    static constexpr int LATE_CARDS = 6;
    static constexpr int MAX_PLY = 4;
};

#endif //MPIPROJECT_GAMECONFIG_H
