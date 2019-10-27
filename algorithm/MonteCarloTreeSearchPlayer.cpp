//
// Created by mpiuser on 22/10/2019.
//

#include "MonteCarloTreeSearchPlayer.h"
#include "MonteCarloTreeSearch.h"

BaseObject *MonteCarloTreeSearchPlayer::getMove(Game *game, MctsPlayerConfiguration *configuration) {
    auto *search = new MonteCarloTreeSearch;
    return search->selectMove(game, configuration);
}
