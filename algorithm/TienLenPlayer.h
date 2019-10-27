//
// Created by mpiuser on 16/10/2019.
//

#ifndef MPIPROJECT_TIENLENPLAYER_H
#define MPIPROJECT_TIENLENPLAYER_H


#include <map>
#include "../base/Player.h"
#include "../helper/HashMap.h"

class TienLenPlayer : public Player {
private:
    int index = -1;
    bool bot = false;
    std::vector<BaseCard *> cards;
    std::vector<BaseObject *> list;
    HashMap connectors;
    int cardLength = 13;
    double score_lose = 0.0;


public:
    TienLenPlayer() = default;

    std::vector<BaseCard *> getStartCards() override;

    std::vector<BaseObject *> listAvailableMoves() override;

    std::vector<BaseObject *> listAvailableMovesToAgainst(BaseObject *object) override;

    void remove(BaseObject *object) override;

    void setCards(std::vector<BaseCard *> vector) override;

    Player *withCards(std::vector<BaseCard *> vector) override;

    int getIndex() override;

    void setIndex(int i) override;

    void scan() override;

    Player *getCopy() override;

    bool isBot() override;

    void setBot(bool b) override;

    int getCardLength() override;

    int getHeuristicScore() override;

    double getLosingScore() override;

    std::vector<BaseObject *> getConnectors(BaseObject *key);

private:

    void calculateScore(BaseObject *o);
};


#endif //MPIPROJECT_TIENLENPLAYER_H
