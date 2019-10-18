//
// Created by mpiuser on 16/10/2019.
//

#include "GameReward.h"

GameReward::GameReward(int max) {
    this->max = max;
    for (int i = 0; i < max; i++) {
        score.push_back(0.0);
    }
}

void GameReward::addReward(Reward *reward) {
    for (int i = 0; i < max; i++) {
        this->setScore(i, score[i] + reward->getScoreForPlayer(i));
    }
}

void GameReward::setScore(int player, double x) {
    this->score.at(player) = x;
}

double GameReward::getScoreForPlayer(int index) {
    return this->score[index];
}

Reward *GameReward::getCopy() {
    auto *reward = new GameReward(max);
    for (int i = 0; i < score.size(); i++) {
        reward->setScore(i, score[i]);
    }
    return reward;
}

std::string GameReward::toString() {
    std::string str = "(";
    for (int i = 0; i < max; i++) {
        str += std::to_string(score[i]);
        if (i != max - 1) str += ", ";
    }
    str += ")";
    return str;
}
