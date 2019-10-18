//
// Created by mpiuser on 18/10/2019.
//

#include "Game.h"

void Game::move(BaseObject *object) {

}

Player *Game::getCurrentPlayer() {
    return nullptr;
}

int Game::getCurrentPlayerIndex() {
    return 0;
}

int Game::getPreviousPlayerIndex() {
    return 0;
}

int Game::getWinner() {
    return 0;
}

int Game::getMaxPlayer() {
    return 0;
}

Game *Game::getCopy() {
    return nullptr;
}

bool Game::end() {
    return false;
}

void Game::playRandomly() {

}

Reward *Game::getReward() {
    return nullptr;
}

void Game::put(Player *player) {

}

int Game::size() {
    return 0;
}

void Game::scan() {

}

void Game::next() {

}

GameConfiguration *Game::getConfig() {
    return nullptr;
}

void Game::setConfig(GameConfiguration *config) {

}

Player *Game::getPlayer(int index) {
    return nullptr;
}

bool Game::isPassed(int index) {
    return false;
}

std::vector<BaseObject *> Game::getAvailableMoves() {
    return std::vector<BaseObject *>();
}

