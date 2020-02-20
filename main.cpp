//#include <iostream>
//#include <algorithm>
//#include <ctime>
//#include "objects/Card.h"
//#include "helper/Util.h"
#include "vector"
#include "string"
#include "helper/Util.h"
#include "base/Game.h"
#include "helper/Util.h"
#include "mpi.h"
#include "algorithm/MctsPlayerConfiguration.h"
#include "objects/Pass.h"
#include "algorithm/TienLenNode.h"
#include "algorithm/TienLenGame.h"
#include "algorithm/TienLenPlayer.h"
#include "helper/Finder.h"
#include "helper/Filter.h"

static bool containsNoSet(const std::vector<BaseObject *> &objects) {
    for (BaseObject *object : objects) {
        if (object->classCode() == BaseObject::code_card) continue;
        return false;
    }
    return true;
}

static BaseObject *getReducedMove(Game *game) {
    std::vector<BaseObject *> list = game->getAvailableMoves();
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

static vector<BaseCard *> from(string str) {
    Util::replaceAll(str, " ", "");
    vector<string> split = Util::split(str, ",");
    vector<BaseCard *> cards;
    for (const string &i : split) {
        cards.push_back(new BaseCard(i));
    }
    return cards;
}

// TODO
static Game *game_from(const std::string &game_str) {
    //string example = "2|1|0.0|3_1_3♣,3♠|2♥,3♥,2♣,4♥,5♥,6♣,7♣,8♠,J♦,9♦,10♠,K♣,Q♥_10♥,10♦,K♦,K♥,Q♠,A♦,9♥";
    auto *config = new GameConfiguration;
    vector<string> parsed = Util::split(game_str, "|");
    config->maxPlayer = std::stoi(parsed[0]);
    config->currentPlayer = std::stoi(parsed[1]);
    config->previousPlayer = config->currentPlayer;
    config->passed = new bool[config->maxPlayer];
    vector<string> passed_parsed = Util::split(parsed[2], ".");
    for (int i = 0; i < config->maxPlayer; i++) {
        config->passed[i] = passed_parsed[i] == "1";
    }
    if (parsed[3] == "null") {
        config->lastDealt = nullptr;
    } else {
        vector<string> tmp = Util::split(parsed[3], "_");
        int card_code = std::stoi(tmp[0]);
        config->previousPlayer = std::stoi(tmp[1]);
        vector<BaseCard *> cards = from(tmp[2]);
        vector<BaseObject *> list;
        if(card_code == BaseObject::code_pass) {
            config->lastDealt = new Pass();
        } else if(card_code == BaseObject::code_card) {
            list = Util::convertToBaseObject(cards);
            config->lastDealt = list[0];
        } else if(card_code == BaseObject::code_dub) {
            list = Finder::scan(cards, "Dub");
            config->lastDealt = list[0];
        } else if(card_code == BaseObject::code_trip) {
            list = Finder::scan(cards, "Trip");
            config->lastDealt = list[0];
        } else if(card_code == BaseObject::code_quad) {
            list = Finder::scan(cards, "Quad");
            config->lastDealt = list[0];
        } else if(card_code == BaseObject::code_seq) {
            config->lastDealt = new Sequence(cards);
        } else if(card_code == BaseObject::code_dubseq) {
            list = Finder::scan(cards, "DubSequence");
            config->lastDealt = list[0];
        } else if(card_code == BaseObject::code_tripseq) {
            list = Finder::scan(cards, "TripSequence");
            config->lastDealt = list[0];
        } else if(card_code == BaseObject::code_quadseq) {
            list = Finder::scan(cards, "QuadSequence");
            config->lastDealt = list[0];
        }
    }
    Game *game = new TienLenGame(config);
    vector<string> playersCards = Util::split(parsed[4], "_");
    for (int i = 0; i < config->maxPlayer; i++) {
        vector<BaseCard *> cards = from(playersCards[i]);
        Player *player = new TienLenPlayer();
        player->setCards(cards);
        game->put(player);
    }
    return game;
}

// TODO
static MctsPlayerConfiguration *config_from(const std::string &config_str) {
    //string example = "500.1000";
    auto *configuration = new MctsPlayerConfiguration();
    vector<string> parsed = Util::split(config_str, ".");
    configuration->minTime = std::stoi(parsed[0]);
    configuration->maxTime = std::stoi(parsed[1]);
    return configuration;
}

int main(int arg_num, char **args) {
    // example: mpirun -np 4 project "2|0|0.0|3_1_J♣,J♠|2♥,3♥,2♣,4♥,5♥,6♣,7♣,8♠,J♦,9♦,10♠,K♣,Q♥_10♥,10♦,K♦,K♥,Q♠,A♦,9♥" "500.1000"
    std::string game_str = args[1];
    std::string config_str = args[2];
    Game *game = game_from(game_str);

    MctsPlayerConfiguration *configuration = config_from(config_str);
    BaseObject *result = nullptr;
    int iterations = configuration->iterations;
    /* check must move */
    std::vector<BaseObject *> list = game->getAvailableMoves();
    if (list.empty()) {
        result = new Pass();
        Util::println(result->toString());
        return 0;
    }
    // heuristic for reduction
    BaseObject *object = getReducedMove(game);
    if (object != nullptr) {
        result = object;
        Util::println(result->toString());
        return 0;
    }

    /* algorithm */
    Node *root = new TienLenNode(nullptr, nullptr, -1, game);
    root->setC(configuration->C);
    root->setK(configuration->K);
    if (configuration->usingK) root->usingK();
    int count = 0;
    MPI::Status status;
    int receive_buffer_size = 10000;
    char buffer[receive_buffer_size];
    long time_communication = 0;

    int numproc, myid;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &numproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    long start = Util::currentTimeMillis();
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

        if (myid == 0) {
            Node *node = root->select(copy);
            node = node->expand(copy);
            Reward *reward = new GameReward(copy->getConfig()->maxPlayer);
            // send node path to slaves
            std::string node_str = node->getNodeStr();
            long ss = Util::currentTimeMillis();
            for (int s = 1; s < numproc; s++) {
                MPI_Send(node_str.c_str(), node_str.size() + 1, MPI_CHAR, s, 0, MPI_COMM_WORLD);
            }
            // wait for all slaves
            for (int s = 1; s < numproc; s++) {
                // receive  reward as string from slaves
                MPI_Recv(buffer, receive_buffer_size, MPI_CHAR, s, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                std::string reward_str(buffer);
                // add received reward from slave to master's reward
                reward->add(reward_str);
            }
            time_communication += Util::currentTimeMillis() - ss;
            node->backPropagation(reward);
        } else {
            // receive node path as string from master
            MPI_Recv(buffer, receive_buffer_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::string node_str(buffer);
            if (node_str == "end") {
                break;
            }
            // get node from node path
            Node *node = root->expandFrom(copy, node_str);
            // get reward
            Reward *reward = node->simulate(copy);
            // send reward as string to master
            std::string reward_str = reward->toString();
            MPI_Send(reward_str.c_str(), reward_str.size() + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
        count++;
    }

    if (myid == 0) {
        std::string end_flag = "end";
        for (int s = 1; s < numproc; s++) {
            MPI_Send(end_flag.c_str(), end_flag.size() + 1, MPI_CHAR, s, 0, MPI_COMM_WORLD);
        }
        result = root->getMostVisitedChildMove();
        Util::println("Result: " + result->toString());
        Util::println("Time: " + std::to_string(time_communication));
        /* debug */
        Util::println("MCTS iterations count: " + std::to_string(count) + ", reward: " +
                      root->getReward()->toString() + ", visited: " +
                      std::to_string(root->getVisit()));
        root->printChildren();
    }

    MPI_Finalize();
    return 0;
}
