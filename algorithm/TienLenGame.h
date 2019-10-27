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
    Reward *reward = nullptr;
    int maxPlayer = 0;
    int sizee = 0;
    int currentPlayer = 0;
    bool scanned = false; // not important
    int previousPlayer = 0;
    BaseObject *lastDealt = nullptr;
    vector<bool> passed;
    GameConfiguration *configuration = nullptr;
    bool first = false;
    bool endd = false;
    int ply = 0;
public:
    explicit TienLenGame(GameConfiguration *config);

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
