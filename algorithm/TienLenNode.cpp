//
// Created by mpiuser on 18/10/2019.
//

#include "TienLenNode.h"
#include "../objects/Quads.h"
#include "../objects/QuadSequence.h"
#include "../base/GameConfig.h"
#include "TienLenPlayer.h"

TienLenNode::TienLenNode(TienLenNode *parent, BaseObject *move, int player, Game *game) {
    this->move = move;
    this->parent = parent;
    this->currentPlayIndex = player;
    this->reward = new GameReward(game->getMaxPlayer());
    /* config node */
    if (parent != nullptr) {
        this->C = parent->getC();
        this->usingKK = parent->usingKK;
        this->K = parent->K;
        this->node_str = parent->node_str + "." + to_string(move->getIndex());
    } else {
        this->node_str = "-1";
    }
    /* load moves */
    vector<BaseObject *> list = game->getAvailableMoves();
    if (!game->end()) {
        if (!list.empty() && list[list.size() - 1]->getCards().size() == game->getCurrentPlayer()->getCardLength()) {
            this->unexploredMoves.push_back(list[list.size() - 1]);
        } else {
            Util::addAll(this->unexploredMoves, list);
            if (parent == nullptr && game->getCurrentPlayerIndex() == game->getPreviousPlayerIndex()) {
                removeUnnecessaryMoves(game);
            } else {
                if (game->getCurrentPlayerIndex() != game->getPreviousPlayerIndex()) {
                    this->unexploredMoves.push_back(new Pass());
                }
            }

            if (parent == nullptr) removeUnintelligibleMoves();
        }
    }

    for(int i = 0; i < this->unexploredMoves.size(); i++) {
        this->unexploredMoves[i]->setIndex(i);
    }
}

void TienLenNode::removeUnintelligibleMoves() {
    vector<BaseObject *> rmList;
    bool containsTwo = false;
    for (BaseObject *o : this->unexploredMoves) {
        if (!containsTwo && (o->classCode() == BaseObject::code_card)) {
            if (((Card *) o)->card->getValue() == BaseCard::TWO) containsTwo = true;
        }

        if ((o->classCode() == BaseObject::code_quad) || (o->classCode() == BaseObject::code_quadseq) ||
            (o->classCode() == BaseObject::code_tripseq)) {
            rmList.push_back(o);
        }
    }

    if (!containsTwo) return;
    for (BaseObject *o : rmList) {
        Util::deleteElement(o, this->unexploredMoves);
    }
}

void TienLenNode::removeUnnecessaryMoves(Game *game) {
    GameConfiguration *conf = game->getConfig();
    for (int i = 0; i < conf->maxPlayer; i++) {
        if (game->getPlayer(i)->getCardLength() <= GameConfig::LATE_CARDS) {
            return;
        }
    }

    auto *player = (TienLenPlayer *) game->getCurrentPlayer();
    vector<BaseObject *> rmList;
    for (BaseObject *o : this->unexploredMoves) {
        if (((o->classCode() == BaseObject::code_tripseq) && player->getCardLength() > 7) ||
            ((o->classCode() == BaseObject::code_quadseq) && player->getCardLength() > 9) ||
            (o->classCode() == BaseObject::code_quad) || (o->contains(BaseCard::TWO))) {
            rmList.push_back(o);
        }
    }

    for (BaseObject *o : rmList) {
        Util::deleteElement(o, this->unexploredMoves);
        for (BaseObject *connector : player->getConnectors(o)) {
            Util::deleteElement(connector, this->unexploredMoves);
        }
    }
}

Node *TienLenNode::select(Game *game) {
    if (game->end() || !this->unexploredMoves.empty()) return this;
    Node *selectedNode = this;
    double maxScore = -100000000;

    for (Node *child : children) {
        double uct = child->getUCT();
        if (uct > maxScore) {
            maxScore = uct;
            selectedNode = child;
        }
    }
    if (selectedNode->getMove() != nullptr) {
        game->move(selectedNode->getMove());
    }

    return selectedNode->select(game);
}

Node *TienLenNode::expand(Game *game) {
    if (this->unexploredMoves.empty()) return this;
    int rd = rand() % this->unexploredMoves.size();
    BaseObject *object = Util::deleteElement(rd, this->unexploredMoves);
    int player = game->getCurrentPlayerIndex();
    game->move(object);
    Node *node = new TienLenNode(this, object, player, game);
    this->children.push_back(node);
    return node;
}

Node *TienLenNode::expandFrom(Game *game, std::string basicString) {
    if (this->unexploredMoves.empty()) return this;
    std::vector<std::string> nodes = Util::splitFirst(basicString, ".");
    if(nodes.empty()) return this;
    if(nodes[0] == "-1") {
        if (nodes.size() == 1) return this;
        return this->expandFrom(game, nodes[1]);
    }
    int node_int = std::stoi(nodes[0]);
    if(nodes.size() == 1) {
        for(int i = 0; i < this->unexploredMoves.size(); i++) {
            if(this->unexploredMoves[i]->getIndex() != node_int) continue;
            BaseObject *object = Util::deleteElement(i, this->unexploredMoves);
            int player = game->getCurrentPlayerIndex();
            game->move(object);
            Node *node = new TienLenNode(this, object, player, game);
            this->children.push_back(node);
            return node;
        }
    } else {
        for(Node *node : this->children) {
            if(node->getMoveIndex() == node_int) {
                return node->expandFrom(game, nodes[1]);
            }
        }
    }
    return nullptr;
}

Reward *TienLenNode::simulate(Game *game) {
    game->playRandomly();
    return game->getReward();
}

void TienLenNode::backPropagation(Reward *pReward) {
    this->reward->addReward(pReward);
    this->visit++;
    if (parent != nullptr) {
        parent->backPropagation(pReward);
    }
}

BaseObject *TienLenNode::getMostVisitedChildMove() {
    int mostVisit = 0;
    Node *mostVisitNode = nullptr;
    for (Node *node : this->children) {
        if (node->getVisit() > mostVisit) {
            mostVisit = node->getVisit();
            mostVisitNode = node;
        }
    }

    if (mostVisitNode == nullptr) return nullptr;
    return mostVisitNode->getMove();
}

double TienLenNode::getUCT() {
    double exploit = static_cast<double>(1.0 * reward->getScoreForPlayer(currentPlayIndex)) / static_cast<double>(visit);
    double discover = C * sqrt(log(parent->getVisit()) / static_cast<double >(visit));
    double balance = static_cast<double >(K) / static_cast<double >(K + visit);
    return exploit + discover + balance;
}

int TienLenNode::getVisit() {
    return visit;
}

void TienLenNode::setC(double c) {
    this->C = c;
}

BaseObject *TienLenNode::getMove() {
    return move;
}

double TienLenNode::getC() {
    return this->C;
}

Reward *TienLenNode::getReward() {
    return this->reward;
}

void TienLenNode::usingK() {
    this->usingKK = true;
}

void TienLenNode::setK(double k) {
    this->K = k;
}

string TienLenNode::getNodeStr() {
    return this->node_str;
}



