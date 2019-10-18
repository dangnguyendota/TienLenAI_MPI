//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_REWARD_H
#define MPIPROJECT_REWARD_H

#include <string>

class Reward {
public:
    virtual void addReward(Reward *reward);

    virtual void setScore(int player, double score);

    virtual Reward *getCopy();

    virtual std::string toString();

    virtual double getScoreForPlayer(int index);
};

#endif //MPIPROJECT_REWARD_H
