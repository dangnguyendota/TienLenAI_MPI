//
// Created by mpiuser on 18/10/2019.
//

#ifndef MPIPROJECT_MONTECARLOTREESEARCH_H
#define MPIPROJECT_MONTECARLOTREESEARCH_H

#include <iostream>
#include "../base/BaseObject.h"
#include "../objects/Card.h"
#include "../base/Game.h"
#include "MctsPlayerConfiguration.h"
#include "../objects/Pass.h"
#include "../base/Node.h"
#include "TienLenNode.h"

using namespace std;

class MonteCarloTreeSearch {
private:
    bool containsNoSet(const vector<BaseObject *> &objects) {
        for (BaseObject *object : objects) {
            if (dynamic_cast<Card *>(object) != nullptr) continue;
            return false;
        }
        return true;
    }

    BaseObject *getReducedMove(Game *game) {
        vector<BaseObject *> list = game->getAvailableMoves();
        bool no_set = containsNoSet(list);
        if (!no_set) return nullptr;
        if (game->getCurrentPlayer()->listAvailableMoves().size() != list.size()) return nullptr;
        if (list.size() == 1) return list[0];

        for (int i = 0; i < game->getMaxPlayer(); i++) {
            if (i == game->getCurrentPlayerIndex() || game->isPassed(i)) continue;
            if (!game->getPlayer(i)->listAvailableMovesToAgainst(list[1]).empty()) {
                return nullptr;
            }
        }
        return list[1];
    }

public:
    BaseObject *selectMove(Game *game, MctsPlayerConfiguration *configuration) {
        int iterations = configuration->iterations;
        /* check must move */
        vector<BaseObject *> list = game->getAvailableMoves();
        if (list.empty()) return new Pass();
        // heuristic for reduction
        BaseObject *object = getReducedMove(game);
        if (object != nullptr) return object;
        /* algorithm */
        Node *root = new TienLenNode(nullptr, nullptr, -1, game);
        root->setC(configuration->C);
        root->setK(configuration->K);
        if (configuration->usingK) root->usingK();
        std::chrono::milliseconds start = Util::currentTimeMillis();
        int count = 0;
        while (iterations > 0 && Util::currentTimeMillis() - start < configuration->maxTime) {
            iterations--;
            /* keep playing while the ratio of winning is less than 50% */
            if (Util::currentTimeMillis() - start > configuration->minTime) {
                double x = 0, y = 0;
                for (int i = 0; i < game->getMaxPlayer(); i++) {
                    if (i == game->getCurrentPlayerIndex()) x = root->getReward()->getScoreForPlayer(i);
                    else y = max(y, root->getReward()->getScoreForPlayer(i));
                }
                if (x > y) break;
            }

            /* continue loop */
            Game *copy = game->getCopy();
            Node *node = root->select(copy);
            node = node->expand(copy);
            Reward *reward = node->simulate(copy);
            node->backPropagation(reward);
            count++;
        }
        /* debug */
        if (configuration->debug) {
            std::cout << "MCTS iterations count: " + std::to_string(count) + ", reward: " +
                         root->getReward()->toString() + ", visited: " +
                         std::to_string(root->getVisit());
            root->printChildren();
        }

        return root->getMostVisitedChildMove();
    }
}

#endif //MPIPROJECT_MONTECARLOTREESEARCH_H