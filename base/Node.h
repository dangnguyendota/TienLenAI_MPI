//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_NODE_H
#define MPIPROJECT_NODE_H

#include "Game.h"

class Node {
    virtual Node *select(Game *game);

    virtual Node *expand(Game *game);

    virtual Reward *simulate(Game *game);

    virtual void backPropagation(Reward *reward);

    virtual BaseObject *getMostVisitedChildMove();

    virtual double getUCT();

    virtual int getVisit();

    virtual BaseObject *getMove();

    virtual void printTree(std::string space);

    virtual void printChildren();

    virtual void setC(double c);

    virtual double getC();

    virtual Reward *getReward();

    virtual void usingK();

    void setK(double K);
};

#endif //MPIPROJECT_NODE_H
