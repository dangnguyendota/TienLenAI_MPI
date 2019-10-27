//
// Created by mpiuser on 18/10/2019.
//

#ifndef MPIPROJECT_TEST_H
#define MPIPROJECT_TEST_H

#include "iostream"
#include "../base/Game.h"
#include "../algorithm/MctsPlayerConfiguration.h"
#include "../helper/Util.h"
#include "../algorithm/TienLenPlayer.h"
#include "../algorithm/TienLenGame.h"
#include "../algorithm/MonteCarloTreeSearchPlayer.h"
#include "../objects/Pass.h"

using namespace std;

class Test {
public:

    static bool contains(const vector<BaseCard *> &container, BaseCard *card) {
        for (BaseCard *c : container) {
            if (c->equals(card)) return true;
        }
        return false;
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

    static vector<BaseCard *> getCards(Player *player) {
        vector<BaseCard *> cards = player->getStartCards();
        vector<BaseObject *> objects = player->listAvailableMoves();
        vector<BaseCard *> out;
        for (BaseObject *o : objects) {
            for (BaseCard *c : o->getCards()) {
                if (contains(cards, c) && Util::indexOf(c, out) == -1) out.push_back(c);
            }
        }

        return out;
    }

    static Game *createGame() {
        vector<BaseCard *> deck = BaseCard::deckOfCards();
        vector<BaseCard *> player1Card = BaseCard::randomCards(deck, 13);
        deck = BaseCard::removeFrom(deck, player1Card);
        vector<BaseCard *> player2Card = BaseCard::randomCards(deck, 13);
        deck = BaseCard::removeFrom(deck, player2Card);
        vector<BaseCard *> player3Card = BaseCard::randomCards(deck, 13);
        deck = BaseCard::removeFrom(deck, player3Card);
        vector<BaseCard *> player4Card = BaseCard::randomCards(deck, 13);

        player1Card = from("2♥, 3♥, 2♣, 4♥, 5♥, 6♣, 7♣, 8♠, J♦, 9♦, 10♠, K♣, Q♥");
        player2Card = from("10♥, 10♦, K♦, K♥, Q♠, A♦, 9♥");

//        player1Card = from("2♣, 3♣, 9♦, K♠, A♦");
//        player2Card = from("3♦, 3♥, 3♠, 2♦, 8♣, A♣, J♥, 10♣, 6♥");

//        player2Card = from("8♣, 8♠, 10♣, 10♠, A♣, A♠, A♥");
//        player1Card = from("K♣, K♠");
//        player1Card = from("3♣, 5♠, 5♦, 6♠, 6♣, 6♦, 7♣, 7♦, Q♠, Q♦, A♣, A♦, 2♦");
//        player2Card = from("3♠, 4♠, 5♣, 8♠, 9♠, 10♥, J♦, J♥, Q♣, K♣, A♠, A♥, 2♣");

//        player1Card = from("3♠, 3♦, 3♣, 3♥, 4♠, 4♦, 5♠, 5♦, 6♠, 6♦");
//        player2Card = from("2♠");

//        player2Card = from("3♠, 3♦, 3♣, 3♥, 2♠");
//        player1Card = from("5♥");

        /* config game */
        auto *gameConfiguration = new GameConfiguration();
        gameConfiguration->maxPlayer = 2;
        gameConfiguration->passed = new bool[gameConfiguration->maxPlayer];
        gameConfiguration->currentPlayer = 1;
        gameConfiguration->previousPlayer = gameConfiguration->currentPlayer;
        gameConfiguration->lastDealt = nullptr;
        gameConfiguration->gang_beat = false;
        gameConfiguration->first_turn = false;
        /* create game */
        Game *game = new TienLenGame(gameConfiguration);
        Player *player1 = new TienLenPlayer();
        Player *player2 = new TienLenPlayer();
        Player *player3 = new TienLenPlayer();
        Player *player4 = new TienLenPlayer();

        player1->setBot(false);
        player2->setBot(true);
        player3->setBot(true);
        player4->setBot(true);

        player1->setCards(player1Card);
        player2->setCards(player2Card);
        player3->setCards(player3Card);
        player4->setCards(player4Card);

        game->put(player1);
        game->put(player2);
        if (gameConfiguration->maxPlayer >= 3) game->put(player3);
        if (gameConfiguration->maxPlayer == 4) game->put(player4);
        return game;
    }

    static void playSolo() {
        Game *game = createGame();
        /* config bot */
        auto *configuration = new MctsPlayerConfiguration();
//            configuration.iterations = 1000000000;
//            configuration.C = Math.sqrt(2);
        configuration->debug = true;
//            configuration.usingK = true;
        configuration->minTime = 500;
        configuration->maxTime = 1000;
        /* create bot */
        auto *bot = new MonteCarloTreeSearchPlayer();
        /* search */
        while (!game->end()) {
            int index = game->getCurrentPlayerIndex();
            if (index == 0) {
                Util::println("Player " + Util::vectorToString(getCards(game->getCurrentPlayer())));
                Util::println("your turn, please choose one: ");
                vector<BaseObject *> objects = game->getAvailableMoves();
                if (game->getCurrentPlayerIndex() != game->getPreviousPlayerIndex()) objects.push_back(new Pass());
                for (int i = 0; i < objects.size(); i++) {
                    Util::println(std::to_string(i + 1) + ". " + objects[i]->toString());
                }
                Util::print("Choose: ");
                int choose = Util::nextInt();
                BaseObject *o = objects[choose - 1];
                Util::println("[PLAYER] " + o->toString());
                game->move(o);
            } else {
                string cardStr = Util::vectorToString(getCards(game->getCurrentPlayer()));
                game->getConfig()->using_heuristic = true;
                BaseObject *object = bot->getMove(game, configuration);
                game->move(object);
                Util::println("Bot " + std::to_string(index) + " " + cardStr + " " + object->toString());
            }
        }
        Util::print(
                "********* Winner " + (game->getWinner() == 0 ? "Player" : "Bot " + std::to_string(game->getWinner())) +
                " *********");
    }
};

#endif //MPIPROJECT_TEST_H
