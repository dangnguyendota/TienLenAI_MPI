//
// Created by mpiuser on 18/10/2019.
//

#include <stdexcept>
#include "TienLenGame.h"
#include "../objects/Pass.h"
#include "GameReward.h"
#include "../base/GameConfig.h"
#include "../helper/Util.h"

void TienLenGame::increaseIndex() {
    if (currentPlayer == maxPlayer - 1) currentPlayer = 0;
    else currentPlayer++;
}

TienLenGame::TienLenGame(GameConfiguration *config) {
    this->maxPlayer = config->maxPlayer;
    this->passed.clear();
    for (int i = 0; i < config->maxPlayer; i++) this->passed.push_back(config->passed[i]);
    this->lastDealt = config->lastDealt;
    this->previousPlayer = config->previousPlayer;
    this->currentPlayer = config->currentPlayer;
    this->configuration = config;
    this->sizee = 0;
    this->scanned = false;
    this->first = config->first_turn;
    this->ply = 0;
}

void TienLenGame::move(BaseObject *object) {
    this->ply++;
    if (first) first = false;
    if (dynamic_cast<Pass *>(object) != nullptr) {
        if (currentPlayer == previousPlayer) throw std::invalid_argument("Current player can not pass");
        passed[currentPlayer] = true;
        this->next();
        return;
    }
    this->lastDealt = object;
    Player *player = this->players[currentPlayer];
    player->remove(object);
    this->previousPlayer = currentPlayer;
    this->next();
}

Player *TienLenGame::getCurrentPlayer() {
    return players[currentPlayer];
}

int TienLenGame::getCurrentPlayerIndex() {
    return currentPlayer;
}

int TienLenGame::getPreviousPlayerIndex() {
    return previousPlayer;
}

int TienLenGame::getWinner() {
    for (int i = 0; i < maxPlayer; i++) {
        if (players[i]->listAvailableMoves().empty()) return i;
    }
    return 0;
}

int TienLenGame::getMaxPlayer() {
    return maxPlayer;
}

Game *TienLenGame::getCopy() {
    auto *game = new TienLenGame(configuration);
    game->players.clear();
    for (int i = 0; i < maxPlayer; i++) {
        game->players.push_back(this->players[i]->getCopy());
    }
    game->scanned = scanned;
    game->first = configuration->first_turn;
    game->sizee = sizee;
    game->currentPlayer = currentPlayer;
    game->previousPlayer = previousPlayer;
    game->maxPlayer = maxPlayer;
    game->passed.clear();
    for (bool b : passed) game->passed.push_back(b);
    game->lastDealt = lastDealt;
    if (reward != nullptr) game->reward = reward->getCopy();
    return game;
}

std::vector<BaseObject *> TienLenGame::getAvailableMoves() {
    Player *player = this->players[currentPlayer];
    if (previousPlayer == currentPlayer) {
        vector<BaseObject *> list = player->listAvailableMoves();
        if (first) {
            auto *card = new BaseCard(BaseCard::THREE, BaseCard::SPADE);
            vector<BaseObject *> objects;
            for (BaseObject *object : list) {
                if (object->contains(card)) objects.push_back(object);
            }
            return objects;
        }
        return list;
    } else {
        return player->listAvailableMovesToAgainst(lastDealt);
    }
}

bool TienLenGame::end() {
    return endd;
}

void TienLenGame::playRandomly() {
    if (!scanned) throw std::invalid_argument("The game can not be played without scan");
    /* keep playing randomly while the game is not over */
    while (true) {
        if (end()) break;
        vector<BaseObject *> list = this->getAvailableMoves();
        if (!list.empty() && list[list.size() - 1]->getCards().size() == this->getCurrentPlayer()->getCardLength()) {
            this->move(list[list.size() - 1]);
            break;
        }

        if (list.empty() || currentPlayer != previousPlayer) list.push_back(new Pass());
        BaseObject *object = list[rand() % list.size()];
        this->move(object);
    }

    /* update reward */
    this->reward = new GameReward(maxPlayer);
    if (configuration->gang_beat) {
        int winner = getWinner();
        if (players[winner]->isBot()) {
            for (int i = 0; i < maxPlayer; i++) {
                if (players[i]->isBot()) this->reward->setScore(i, 1);
                else this->reward->setScore(i, 0);
            }
        } else {
            for (int i = 0; i < maxPlayer; i++) {
                this->reward->setScore(i, players[i]->listAvailableMoves().empty() ? 1 : 0);
            }
        }
    } else {
        if (configuration->using_heuristic) {
            int winner = getWinner();
            double total = -this->ply * GameConfig::PLY_FACTOR;
            for (Player *player : players) total += player->getLosingScore();
            for (int i = 0; i < maxPlayer; i++) {
                if (i == winner) this->reward->setScore(i, 1 + total);
                else this->reward->setScore(i, -getPlayer(i)->getLosingScore());
            }
        } else {
            for (int i = 0; i < maxPlayer; i++) {
                this->reward->setScore(i, players[i]->listAvailableMoves().empty() ? 1 : 0);
            }
        }
    }
}

Reward *TienLenGame::getReward() {
    return reward;
}

void TienLenGame::put(Player *player) {
    if (scanned) throw std::invalid_argument("Can not put player because the game is started");
    player->setIndex(this->players.size());
    player->scan();
    this->players.push_back(player);
    sizee++;
    if (sizee == maxPlayer) scan();
}

int TienLenGame::size() {
    return sizee;
}

void TienLenGame::scan() {
    scanned = true;
    for (Player *player : players) {
        if (player == nullptr) throw std::invalid_argument("Game exception: number of players < max players");
    }
}

void TienLenGame::next() {
    endd = players[currentPlayer]->listAvailableMoves().empty();
    this->increaseIndex();
    while (passed[currentPlayer]) increaseIndex();
    if (currentPlayer == previousPlayer) {
        for(auto && i : passed) {
            i = false;
        }
    }
}

GameConfiguration *TienLenGame::getConfig() {
    return configuration;
}

void TienLenGame::setConfig(GameConfiguration *config) {
    this->configuration = config;
}

Player *TienLenGame::getPlayer(int index) {
    return players[index];
}

bool TienLenGame::isPassed(int index) {
    return passed[index];
}






