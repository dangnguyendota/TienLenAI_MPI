//
// Created by mpiuser on 18/10/2019.
//

#ifndef MPIPROJECT_TIENLENNODE_H
#define MPIPROJECT_TIENLENNODE_H


#include "../base/Node.h"
#include "math.h"
#include "GameReward.h"
#include "../helper/Util.h"
#include "../objects/Pass.h"

using namespace std;

class TienLenNode : public Node {
private:
    Node *parent;
    BaseObject *move;
    vector<Node *> children;
    vector<BaseObject *> unexploredMoves;
    Reward *reward;
    int visit;
    int currentPlayIndex;
    double C = sqrt(2.0);
    double K = 0;
    bool usingKK = false;
public:
    TienLenNode(TienLenNode *parent, BaseObject *move, int player, Game *game);

    Node *select(Game *game) override;

    Node *expand(Game *game) override;

    Reward *simulate(Game *game) override;

    void backPropagation(Reward *pReward) override;

    BaseObject *getMostVisitedChildMove() override;

    double getUCT() override;

    int getVisit() override;

    BaseObject *getMove() override;

    void setC(double c) override;

    double getC() override;

    Reward *getReward() override;

    void usingK() override;

    void setK(double k) override;


private:
    void removeUnintelligibleMoves();

    void removeUnnecessaryMoves(Game *game);
};


#endif //MPIPROJECT_TIENLENNODE_H
