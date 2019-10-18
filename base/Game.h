//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_GAME_H
#define MPIPROJECT_GAME_H

#include "BaseObject.h"
#include "Player.h"
#include "Reward.h"
#include "GameConfiguration.h"

class Game {
public:
    virtual void move(BaseObject *object);

    virtual Player *getCurrentPlayer();

    virtual int getCurrentPlayerIndex();

    virtual int getPreviousPlayerIndex();

    virtual int getWinner();

    virtual int getMaxPlayer();

    virtual Game *getCopy();

    virtual std::vector<BaseObject *> getAvailableMoves();

    virtual bool end();

    virtual void playRandomly();

    virtual Reward *getReward();

    virtual void put(Player *player);

    virtual int size();

    virtual void scan();

    virtual void next();

    virtual GameConfiguration *getConfig();

    virtual void setConfig(GameConfiguration *config);

    virtual Player *getPlayer(int index);

    virtual bool isPassed(int index);
};

#endif //MPIPROJECT_GAME_H
