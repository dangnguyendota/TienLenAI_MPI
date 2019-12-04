//
// Created by mpiuser on 18/10/2019.
//

#include "Node.h"

void Node::setK(double K) {

}

void Node::usingK() {

}

Node *Node::select(Game *game) {
    return nullptr;
}

Node *Node::expand(Game *game) {
    return nullptr;
}

Reward *Node::simulate(Game *game) {
    return nullptr;
}

void Node::backPropagation(Reward *reward) {

}

BaseObject *Node::getMostVisitedChildMove() {
    return nullptr;
}

double Node::getUCT() {
    return 0;
}

int Node::getVisit() {
    return 0;
}

BaseObject *Node::getMove() {
    return nullptr;
}

void Node::printTree(std::string space) {

}

void Node::printChildren() {

}

void Node::setC(double c) {

}

double Node::getC() {
    return 0;
}

Reward *Node::getReward() {
    return nullptr;
}

std::string Node::getNodeStr() {
    return std::__cxx11::string();
}
