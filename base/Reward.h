//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_REWARD_H
#define MPIPROJECT_REWARD_H

class Reward {
    virtual void addReward(Reward* reward);

    virtual void setScore(int player, double score);

    virtual double getScoreForPlayer(int index);

    virtual Reward* getCopy();
};

#endif //MPIPROJECT_REWARD_H
