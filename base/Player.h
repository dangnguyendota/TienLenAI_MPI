//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_PLAYER_H
#define MPIPROJECT_PLAYER_H

#include <vector>
#include "BaseCard.h"
#include "BaseObject.h"

class Player {
    virtual std::vector<BaseCard*> getStartCards();

    virtual std::vector<BaseObject*> listAvailableMoves();

    virtual std::vector<BaseObject*> listAvailableMovesToAgainst(BaseObject *object);

    virtual void remove(BaseObject *object);

    virtual void setCards(std::vector<BaseCard*> cards);

    virtual Player* withCards(std::vector<BaseCard*> cards);

    virtual void setIndex(int index);

    virtual void getIndex();

    virtual void scan();

    virtual Player* getCopy();

    virtual bool isBot();

    virtual void setBot(bool bot);

    virtual int getCardLength();

    virtual int getHeristicScore();

    double getLosingScore();
};
#endif //MPIPROJECT_PLAYER_H
