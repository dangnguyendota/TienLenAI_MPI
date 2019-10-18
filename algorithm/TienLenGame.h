//
// Created by mpiuser on 18/10/2019.
//

#ifndef MPIPROJECT_TIENLENGAME_H
#define MPIPROJECT_TIENLENGAME_H


#include "../base/Player.h"
#include "../base/Reward.h"
#include "../base/GameConfiguration.h"
#include "../base/Game.h"

using namespace std;

class TienLenGame : public Game {
private:
    vector<Player *> players;
    Reward *reward;
    int maxPlayer;
    int sizee;
    int currentPlayer;
    bool scanned; // not important
    int previousPlayer;
    BaseObject *lastDealt;
    vector<bool> passed;
    GameConfiguration *configuration;
    bool first = false;
    bool endd = false;
    int ply;
public:
    TienLenGame(GameConfiguration *config);

    void move(BaseObject *object) override;

    Player *getCurrentPlayer() override;

    int getCurrentPlayerIndex() override;

    int getPreviousPlayerIndex() override;

    int getWinner() override;

    int getMaxPlayer() override;

    Game *getCopy() override;

    std::vector<BaseObject *> getAvailableMoves() override;

    bool end() override;

    void playRandomly() override;

    Reward *getReward() override;

    void put(Player *player) override;

    int size() override;

    void scan() override;

    void next() override;

    GameConfiguration *getConfig() override;

    void setConfig(GameConfiguration *config) override;

    Player *getPlayer(int index) override;

    bool isPassed(int index) override;

private:
    void increaseIndex();


};


#endif //MPIPROJECT_TIENLENGAME_H
