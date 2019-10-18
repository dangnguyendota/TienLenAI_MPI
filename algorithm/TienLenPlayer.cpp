//
// Created by mpiuser on 16/10/2019.
//

#include "TienLenPlayer.h"
#include "../helper/Util.h"
#include "../objects/Card.h"
#include "../base/GameConfig.h"
#include "../objects/TripSequence.h"
#include "../objects/Quads.h"
#include "../objects/QuadSequence.h"
#include "../helper/Filter.h"
#include "../helper/Finder.h"

std::vector<BaseCard *> TienLenPlayer::getStartCards() {
    return this->cards;
}

std::vector<BaseObject *> TienLenPlayer::listAvailableMoves() {
    return this->list;
}

std::vector<BaseObject *> TienLenPlayer::listAvailableMovesToAgainst(BaseObject *object) {
    std::vector<BaseObject *> baseObjects;
    for (BaseObject *o : list) {
        if (o->beats(object)) baseObjects.push_back(o);
    }
    return baseObjects;
}

void TienLenPlayer::remove(BaseObject *object) {
    std::vector<BaseObject *> connector = connectors[object];
    Util::deleteElement(object, this->list);
    this->cardLength -= object->getCards().size();
    if (cardLength < 0) throw std::invalid_argument("length of card can not less than 0");
    for (BaseObject *o : connector) {
        bool flag = Util::deleteElement(object, list);
        if (flag) calculateScore(o);
    }

    calculateScore(object);
    if (score_lose < -0.00001) throw std::invalid_argument("score lose can not be - " + std::to_string(score_lose));
}

void TienLenPlayer::calculateScore(BaseObject *o) {
    if (dynamic_cast<Card *>(o) != nullptr) {
        Card *card = (Card *) o;
        if (card->card->getValue() == BaseCard::TWO) {
            if (card->card->getType() < BaseCard::DIAMOND) score_lose -= GameConfig::BLACK_CARD_OF_TWO;
            else score_lose -= GameConfig::RED_CARD_OF_TWO;
        } else if (dynamic_cast<TripSequence *>(o) != nullptr) {
            score_lose -= GameConfig::TRIP_SEQUENCE;
        } else if (dynamic_cast<Quads *>(o) != nullptr) {
            score_lose -= GameConfig::QUAD;
        } else if (dynamic_cast<QuadSequence *>(o) != nullptr) {
            score_lose -= GameConfig::QUAD_SEQUENCE;
        }
    }
}

void TienLenPlayer::setCards(std::vector<BaseCard *> vector) {
    BaseCard::sort(&vector);
    this->cards = vector;
    this->cardLength = vector.size();
}

Player *TienLenPlayer::withCards(std::vector<BaseCard *> vector) {
    this->setCards(vector);
    return this;
}

int TienLenPlayer::getIndex() {
    return index;
}

void TienLenPlayer::setIndex(int i) {
    this->index = i;
}

void TienLenPlayer::scan() {
    if (cards.empty()) throw std::invalid_argument("Cards of player can not bet null");
    Util::addAll(list, Util::convertToBaseObject(cards));
    Util::addAll(list, Finder::scan(cards, "Dub"));
    Util::addAll(list, Filter::removeUnnecessarySequences(Finder::scan(cards, "Sequence")));
    Util::addAll(list, Finder::scan(cards, "DubSequence"));
    Util::addAll(list, Finder::scan(cards, "Trips"));
    Util::addAll(list, Finder::scan(cards, "TripSequence"));
    Util::addAll(list, Finder::scan(cards, "Quads"));
    Util::addAll(list, Finder::scan(cards, "QuadSequence"));

    for (int i = 0; i < list.size(); i++) {
        BaseObject *o = list[i];
        /* connector */
        vector<BaseObject *> connector;
        for (int j = 0; j < list.size(); j++) {
            if (i == j) continue;
            if (Filter::connect(o->getCards(), list[j]->getCards())) {
                connector.push_back(list[j]);
            }
        }
        connectors[o] = connector;

        /* calculate score lose */
        if (dynamic_cast<Card *>(o) != nullptr) {
            if (((Card *) o)->card->getValue() == BaseCard::TWO) {
                if (((Card *) o)->card->getType() < BaseCard::DIAMOND) score_lose += GameConfig::BLACK_CARD_OF_TWO;
                else score_lose += GameConfig::RED_CARD_OF_TWO;
            } else score_lose += GameConfig::NORMAL_CARD;
        } else if (dynamic_cast<TripSequence *>(o) != nullptr) {
            score_lose += GameConfig::TRIP_SEQUENCE;
        } else if (dynamic_cast<Quads *>(o) != nullptr) {
            score_lose += GameConfig::QUAD;
        } else if (dynamic_cast<QuadSequence *>(o) != nullptr) {
            score_lose += GameConfig::QUAD_SEQUENCE;
        }
    }
}

Player *TienLenPlayer::getCopy() {
    auto *player = new TienLenPlayer();
    player->index = this->index;
    Util::addAll(player->list, this->list);
    player->connectors = connectors;
    player->bot = this->bot;
    player->cardLength = cardLength;
    player->score_lose = score_lose;
    return player;
}

bool TienLenPlayer::isBot() {
    return this->bot;
}

void TienLenPlayer::setBot(bool b) {
    this->bot = b;
}

int TienLenPlayer::getCardLength() {
    return cardLength;
}

int TienLenPlayer::getHeuristicScore() {
    return 0;
}

double TienLenPlayer::getLosingScore() {
    return score_lose;
}

std::vector<BaseObject *> TienLenPlayer::getConnectors(BaseObject *key) {
    return connectors[key];
}

