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
#include "mpi.h"

using namespace std;

class MonteCarloTreeSearch {
private:
    static bool containsNoSet(const vector<BaseObject *> &objects) {
        for (BaseObject *object : objects) {
            if (dynamic_cast<Card *>(object) != nullptr) continue;
            return false;
        }
        return true;
    }

    static BaseObject *getReducedMove(Game *game) {
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
        MPI_Init();
        MPI_Comm_size(MPI_COMM_WORLD, &numproc);
        MPI_Comm_rank(MPI_COMM_WORLD, &myid);

        int iterations = configuration->iterations;
        /* check must move */
        vector<BaseObject *> list = game->getAvailableMoves();
        if (list.empty()) return new Pass();
        // heuristic for reduction
        BaseObject *object = getReducedMove(game);
        if (object != nullptr) return object;
        /* algorithm */
        Node *root = new TienLenNode(nullptr, nullptr, -1, game, -1);
        root->setC(configuration->C);
        root->setK(configuration->K);
        if (configuration->usingK) root->usingK();
        long start = Util::currentTimeMillis();
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
            Util::println(node->getNodeStr());
            Reward *reward = node->simulate(copy);
            node->backPropagation(reward);
            count++;
        }

        MPI_Finalize();
        /* debug */
        if (configuration->debug) {
            Util::println("MCTS iterations count: " + std::to_string(count) + ", reward: " +
                          root->getReward()->toString() + ", visited: " +
                          std::to_string(root->getVisit()));
            root->printChildren();
        }

        return root->getMostVisitedChildMove();
    }
};

#endif //MPIPROJECT_MONTECARLOTREESEARCH_H
