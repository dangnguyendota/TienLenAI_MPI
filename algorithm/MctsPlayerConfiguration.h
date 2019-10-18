//
// Created by mpiuser on 18/10/2019.
//

#ifndef MPIPROJECT_MCTSPLAYERCONFIGURATION_H
#define MPIPROJECT_MCTSPLAYERCONFIGURATION_H

#include <cmath>

class MctsPlayerConfiguration {
public:
    int iterations = 1000000000; /* loop */
    double C = sqrt(2); /* factor */
    bool debug = false;
    long minTime = 2000;
    long maxTime = 7000;
    bool usingK = true;
    double K = 500;
};

#endif //MPIPROJECT_MCTSPLAYERCONFIGURATION_H
