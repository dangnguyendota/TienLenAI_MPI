//
// Created by mpiuser on 18/10/2019.
//
#include "Player.h"

std::string Player::toString() {
    return std::__cxx11::string();
}

double Player::getLosingScore() {
    return 0;
}

int Player::getHeuristicScore() {
    return 0;
}

int Player::getCardLength() {
    return 0;
}

void Player::setBot(bool bot) {

}

bool Player::isBot() {
    return false;
}

Player *Player::getCopy() {
    return nullptr;
}

void Player::scan() {

}

int Player::getIndex() {
    return 0;
}

void Player::setIndex(int index) {

}

Player *Player::withCards(std::vector<BaseCard *> cards) {
    return nullptr;
}

void Player::setCards(std::vector<BaseCard *> cards) {

}

void Player::remove(BaseObject *object) {

}

std::vector<BaseObject *> Player::listAvailableMovesToAgainst(BaseObject *object) {
    return std::vector<BaseObject *>();
}

std::vector<BaseObject *> Player::listAvailableMoves() {
    return std::vector<BaseObject *>();
}

std::vector<BaseCard *> Player::getStartCards() {
    return std::vector<BaseCard *>();
}
