//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_NODE_H
#define MPIPROJECT_NODE_H

#include "Game.h"

class Node {
public:
    virtual Node *select(Game *game);

    virtual Node *expand(Game *game);

    virtual Node *expandFrom(Game *game, std::string basicString);

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

    virtual void setK(double K);

    virtual std::string getNodeStr();

    virtual int getMoveIndex();
};

#endif //MPIPROJECT_NODE_H
