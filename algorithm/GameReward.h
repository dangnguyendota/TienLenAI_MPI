//
// Created by mpiuser on 16/10/2019.
//

#ifndef MPIPROJECT_GAMEREWARD_H
#define MPIPROJECT_GAMEREWARD_H


#include <vector>
#include "../base/Reward.h"

class GameReward : public Reward {
private:
    std::vector<double> score;
    int max = 0;
public:
    GameReward(int max);

    void addReward(Reward *reward) override;

    void setScore(int player, double x) override;

    double getScoreForPlayer(int index) override;

    Reward *getCopy() override;

    Reward *add(std::string reward_str) override;

    std::string toString() override;
};


#endif //MPIPROJECT_GAMEREWARD_H
