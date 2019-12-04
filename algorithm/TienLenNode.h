//
// Created by mpiuser on 18/10/2019.
//

#ifndef MPIPROJECT_TIENLENNODE_H
#define MPIPROJECT_TIENLENNODE_H


#include "../base/Node.h"
#include "GameReward.h"
#include "math.h"
#include "../helper/Util.h"
#include "../objects/Pass.h"

using namespace std;

class TienLenNode : public Node {
private:
    Node *parent = nullptr;
    BaseObject *move = nullptr;
    vector<Node *> children;
    vector<BaseObject *> unexploredMoves;
    Reward *reward = nullptr;
    int visit = 0;
    int currentPlayIndex = 0;
    double C = sqrt(2.0);
    double K = 0;
    bool usingKK = false;
public:
    string node_str = "";
public:

    TienLenNode(TienLenNode *parent, BaseObject *move, int player, Game *game, int move_index);

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

    string getNodeStr() override;

    void printChildren() override {
        std::string info;
        for (Node *node : children) {
            auto *tienLenNode = (TienLenNode *) node;
            info += "Node " + tienLenNode->getMove()->toString();
            info += "|";
            info += "visit " + std::to_string(tienLenNode->visit);
            info += "|";
            info += "reward " + std::to_string(
                    tienLenNode->reward->getScoreForPlayer(tienLenNode->currentPlayIndex) / tienLenNode->visit);
            info += "\n";
        }
        Util::println(info);
    }

private:
    void removeUnintelligibleMoves();

    void removeUnnecessaryMoves(Game *game);
};


#endif //MPIPROJECT_TIENLENNODE_H
